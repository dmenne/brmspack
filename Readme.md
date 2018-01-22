[![Travis-CI Build Status](https://travis-ci.org/dmenne/brmspack.svg?branch=master)](https://travis-ci.org/dmenne/brmspack)

brmspack: Use precompiled models in brms
===========================================

## Caveat

This does not work yet. See issues for details



Dieter Menne   
Menne Biomed Consulting Tübingen, Germany    
http://www.menne-biomed.de   

Paul Bürkners package [brms](https://github.com/paul-buerkner/brms) is a flexible and transparent alternative or complement to [rstanarm](https://github.com/stan-dev/rstanarm). The latter is more limited and uses prebuild Stan models with many branches, avoiding lengthy recompiles before start. `brms` uses lean Stan code, but the compiled code by default can only be used easily without recompiling within a session.

This demo package uses the `inhaler` examples from `brms/brm` (with venerable BUGS roots) to demonstate how to generated precompiled models that can be used with new data sets in an approach similar to that of `rstanarm`.

# Howto

* Generate a Stan package skeleton with `rstantools/rstan_package_skeleton`. It is assumed that you do not know the names of your Stan files yet, so you probably leave the parameter `stan_files` empty.
* I assume that you work in RStudio; emacs afficionados don't need tutorials. Make sure that you let roxygen build your `NAMESPACE` and `.Rd` files in your project settings.
* Create your model file in a directory which you add to `.Rbuildignore`. I use `brms`, but the name does not matter.

```
library(brms)
stopifnot(file.exists("DESCRIPTION")) # Make sure we start from project file dir
inhaler_model <- brm(rating ~ period + carry + cs(treat), 
            save_model = "src/stan_files/inhaler.stan",
            iter = 1,
            data = inhaler, family = sratio("cloglog"), 
            prior = set_prior("normal(0,5)"))
save(inhaler_model, file = "inst/extdata/inhaler.rda")

# retrieve file in package via 
# system.file("extdata", package = "brmspack")
```

* Run your model with at least 1 iteration; too bad `brms` does not permit 0 iteration as `rstan/stan` does.
* The Stan model must be stored in `src/stan_files/` via parameter `save_model`. Currently there is a bug that a newline is missing at the end of file which will produce a warning. Until this has been corrected, add a newline manually at the end.
* Save the result in `inst/extdata/xxd.rda`. I use it to generated a class instance of `brms_fit`; Could be that there is an easier way to produce it. 
* After installation, this file will be shifted up one level into `<package>/extdata`. This makes debugging a bit awkward, but it that's what R-core decided; tell me if you know a better place. Don't build the package yet, it will fail.
* Write the user R function; it is called `run_inhaler` here. It is important that you add `@useDynLib <packagename>` in this file or somewhere else in the project; on failure, check that the dynlib has been transferred to the `NAMESEPACE` file.     

```
#' @title Run inhaler analysis with new data
#' @description Runs the inhaler example from brms/brm with new data set
#'
#' @useDynLib brmspack
#'
#' @examples
#' run_inhaler()
#' @export

run_inhaler = function(){
  mod = stanmodels[["inhaler"]]
  # load inhaler_model (TODO: better use rds to assign?)
  load(system.file("extdata/inhaler.rda", package = "brmspack"))
  
  # for debugging
  #mod = brmspack:::stanmodels[["inhaler"]] 
  # load inhaler_model 
  #load("inst/extdata/inhaler.rda")
  
  # mix up results a bit so we get a random result  
  newdata = inhaler
  newdata$rating = sample(newdata$rating, nrow(newdata))
  # priors cannot be changed without recompiling
  fit2 = update(inhaler_model, newdata = inhaler, 
                iter = 500, chains = 1)
  plot(fit2, ask = FALSE)
}
```

* Note that for quick debugging I access `stanmodels` with `:::`; you must remove this for the final build, CRAN and friends do not like this. 
* Now comes the not so funny part, correcting the inconsistencies of the Stan skeleton; some have been reported by [Paul Brückner](https://github.com/stan-dev/rstantools/issues/19); so check out, some things might have been corrected in versions >1.4.0.

1. _The good-natured one:_  The license file must be in subdirectory `src/stan_files/pre`, not in `chunks` where the skeleton puts it.
2. In `R/zzz.R`, change  `loadModule(m, what = TRUE)` to `Rcpp::loadModule(m, what = TRUE)`. Alternatively, you can add `@importFrom Rcpp loadModule` to one of your R files.
3. _The ugly one:_ When you have not used `stan_files` during skeleton creation, or when you have added more Stan files, you must manually add their names to `Makevars` and to `Makevars.win`, for example: `SOURCES = stan_files/inhaler.stan`.
4.  _The slow long-term killer:_ Stan and Rcpp are moving targets, and to handle changes in compilers requires update in `.cpp, .hpp`, and `StanModels.R`. When after a version change I am flooded with error message, I generate a new skeleton in an empty directory, and compare the core-files to find out what has changed. Some sort of versioning probably would be nice in the future.

Optionally, I have moved `Depends: Rcpp` to `Imports: Rcpp` in DESCRIPTION. There are cases where you might have to move it back.

# Limitations
Priors cannot be changed in the model without recompilation. `brms` is clever enough to do this automatically, but the new model is not stored for later use.

