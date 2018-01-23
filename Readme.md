[![Travis-CI Build Status](https://travis-ci.org/dmenne/brmspack.svg?branch=master)](https://travis-ci.org/dmenne/brmspack)

brmspack: Using precompiled models in brms
===========================================


Dieter Menne   
Menne Biomed Consulting Tübingen, Germany    
http://www.menne-biomed.de   

Paul Bürkner's package [brms](https://github.com/paul-buerkner/brms) is a flexible and transparent alternative or complement to [rstanarm](https://github.com/stan-dev/rstanarm). The latter is more limited and uses prebuild Stan models with many branches, avoiding lengthy recompiles before start. `brms` generates beautiful Stan code, but the compiled code by default can only be used easily without recompiling within a session.

This demo package uses the `inhaler` examples from `brms/brm` (with venerable BUGS roots) to demonstate how to generate precompiled models that can be used with new data sets in an approach similar to that of `rstanarm`. 

# Howto

* To run the examples in this package, you need a github version of `brms` Version 2.03 and data >= 2018-01-22. Use `devtools::install_github("paul-buerkner/brms")`
* Generate a Stan package skeleton with `rstantools/rstan_package_skeleton`. It is assumed that you do not know the names of your Stan files yet, so you probably leave the parameter `stan_files` empty.
* I assume that you work in RStudio; emacs afficionados don't need tutorials. Make sure that you let roxygen build your `NAMESPACE` and `.Rd` files in your project settings.
* Create your model file in a directory which you add to `.Rbuildignore`. I use `brms`, but the name does not matter. This generates your brmsfit-template, and the code will be replace at run time by code generated at installation time.

```
# From brms/generate_stan
## Ordinal regression modeling patient's rating of inhaler instructions 
## category specific effects are estimated for variable 'treat'
library(brms)
stopifnot(file.exists("DESCRIPTION")) # Make sure we start from project file
modelfile = "src/stan_files/inhaler.stan"
inhaler_model = brm(rating ~ period + carry + cs(treat), 
            save_model = modelfile,
            save_dso = FALSE, # will be replaced by compiled 
            chains = 1,
            iter = 100,
            data = inhaler, family = sratio("cloglog"), 
            prior = set_prior("normal(0,5)"))

saveRDS(inhaler_model, file = "inst/extdata/inhaler.rds")
```

* Run your model with at least 1 iteration; `brms` does not allow for 0 iterations as `rstan/stan` does.
* The Stan model must be stored in `src/stan_files/` via parameter `save_model`. 
* Save the result in `inst/extdata/xxd.rda`. It will be used it to generate an instance of `brms_fit` at run-time. 
* After installation, this file will be shifted up one level into `<package>/extdata`. This makes debugging a bit awkward; tell me if you know of a better place. Don't build the package yet, it will fail.
* Write the [user R function](https://github.com/dmenne/brmspack/blob/master/R/run_inhaler.R). It is important that you add `@useDynLib <packagename>` in this file or somewhere else in the project; on failure, check that the dynlib has been transferred to the `NAMESPACE` file.* Note that for quick debugging I access `stanmodels` with `:::`; you must remove this for the final build, CRAN and friends do not like :::. 

## Correct skeleton defaults

Now comes the not so amusing part, correcting the inconsistencies of the Stan skeleton; some have been reported by [Paul Brückner](https://github.com/stan-dev/rstantools/issues/19), so check out, things might have been corrected in versions of rstantools >1.4.0.

1. _The easy one:_  The license file must be copied to subdirectory `src/stan_files/pre`, from `chunks` where the skeleton puts it.
2. In `R/zzz.R`, change  `loadModule(m, what = TRUE)` to `Rcpp::loadModule(m, what = TRUE)`. Alternatively, you can add `@importFrom Rcpp loadModule` to one of your R files.
3. _The ugly one:_ When you have not used `stan_files` during skeleton creation, or when you have added more Stan files, you must manually add their names to `Makevars` and to `Makevars.win`, for example: `SOURCES = stan_files/inhaler.stan`.
4.  _The slow long-term killer:_ Stan and Rcpp are moving targets, and to handle changes in compilers requires updates in `.cpp, .hpp`, `StanModels.R` and `Makevars`. When I am flooded with error message after a version change, I generate a new skeleton in an empty directory, and compare the core-files to find out what has changed. Some sort of versioning probably would be nice in the future.

I have moved `Depends: Rcpp` to `Imports: Rcpp` in DESCRIPTION. There are cases where you might have to move it back.

# Caveat

Priors are hard-wired in `brms` code and require recompilation. There is no error message when you set priors in `update`, but they are not used. This might change in the future, but the mechanism for autochecking of recompiles currently creates false alarm and has been overridden.


