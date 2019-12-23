[![Travis-CI Build Status](https://travis-ci.org/dmenne/brmspack.svg?branch=master)](https://travis-ci.org/dmenne/brmspack)

brmspack: Using precompiled models in brms
===========================================


Dieter Menne   
Menne Biomed Consulting Tübingen, Germany    
http://www.menne-biomed.de   

Paul Bürkner's package [brms](https://github.com/paul-buerkner/brms) is a flexible complement to [rstanarm](https://github.com/stan-dev/rstanarm). The latter is more limited and uses prebuild Stan models with many branches, avoiding lengthy recompiles before start. `brms` generates beautiful Stan code, but running without recompiling only works within a session by default.

This demo package uses the `inhaler` examples from `brms/brm` (with venerable BUGS roots) to demonstate how to generate precompiled models that can be used with new data sets in an approach similar to that of `rstanarm`. 

# Howto

* To run the examples in this package, you need a version of `brms` >= 2.1.0. 
* Generate a Stan package skeleton with `rstantools/rstan_package_skeleton`. It is assumed that you do not know the names of your Stan files yet, so leave the parameter `stan_files` empty.
* I assume that you work in RStudio; emacs afficionados don't need tutorials. Make sure that you let `roxygen2` build `NAMESPACE` and `.Rd` files in your project settings.
* Create your model template from R code in a directory which you add to `.Rbuildignore`. I use `brms`, but the name does not matter. Do not save the code, use `save_dso = FALSE`; it will be replaced by system-specific code generated during installation.

```
# Example from brms/generate_stan
# Ordinal regression modeling patient's rating of inhaler instructions 
# category specific effects are estimated for variable 'treat'
library(brms)
stopifnot(file.exists("DESCRIPTION")) # Make sure we start from project directory
modelfile = "src/stan_files/inhaler.stan"
inhaler_model = brm(rating ~ period + carry + cs(treat), 
            save_model = modelfile,
            save_dso = FALSE, # will be replaced by compiled code
            chains = 1,
            iter = 100,
            data = inhaler, family = sratio("cloglog"), 
            prior = set_prior("normal(0,5)"))

dir.create("inst/extdata")
saveRDS(inhaler_model, file = "inst/extdata/inhaler.rds")
```

* Run your model with at least 1 iteration; `brms` does not allow for 0 iterations as `rstan/stan` does.
* The Stan model must be stored in `src/stan_files/` via parameter `save_model`. 
* Save the result in `inst/extdata/inhaler.rda`. It will be used to generate an instance of `brms_fit` at run-time. 
* After installation, this file will be shifted up one level into `<package>/extdata`. This makes debugging a bit awkward; tell me if you know of a better place. Don't build the package yet, it will fail.
* Write the [user R function](https://github.com/dmenne/brmspack/blob/master/R/run_inhaler.R). It is important that you add `@useDynLib <packagename>` in this file or somewhere else in the project; on failure, check that the dynlib has been transferred to the `NAMESPACE` file.
* During development, I access `stanmodels` with `:::`; you must remove this for the final build, CRAN and friends do not like :::. 

## Correct skeleton defaults

**This section is kept for historical reasons, most items have been resolved in recent versions of rstantools.**


1. _The easy one:_  File `license.stan` must be copied to subdirectory `src/stan_files/pre`, from `chunks` where the skeleton puts it.
2. In `R/zzz.R`, change  `loadModule(m, what = TRUE)` to `Rcpp::loadModule(m, what = TRUE)`. Alternatively, you can add `@importFrom Rcpp loadModule` to one of your R files.
3. _The ugly one:_ When you have not used `stan_files` during skeleton creation, or when you have added Stan files to your project, you must manually insert their names to `Makevars` and to `Makevars.win`, for example: `SOURCES = stan_files/inhaler.stan`. In more recent version of the skeleton generator, you must remove the bogus list of stan models (`stan_files/bernoulli.stan`) before you insert your file name. See  [issue on github](https://github.com/stan-dev/rstantools/issues/33#issuecomment-383628575.)
  3a. Alternatively: [Ben Goodrich's](http://discourse.mc-stan.org/t/brms-without-recompile-sample/3090/2) : By adding `SystemRequirements: GNU make` in DESCRIPTION you can use `SOURCES = $(wildcard stan_files/*.stan)` - see branch `use-gnumake`, but it will produce a `NOTE` during CRAN build. This is the default now, and the NOTE generated will be tolerated by CRAN.
4.  _The slow long-term killer:_ Stan and Rcpp are moving targets, and to handle changes in compilers requires updates in `.cpp, .hpp`, `StanModels.R` and `Makevars`. When I am flooded with error message after a version change, I generate a new skeleton in an empty directory, and compare the core-files to find out what has changed. See [here](http://discourse.mc-stan.org/t/new-cppobject-xp-constructor-in-2-16-and-how-to-configure-travisci/1192/26?u=denne) for details.  Some sort of versioning probably would be nice in the future. 

I have moved `Depends: Rcpp` to `Imports: Rcpp` in DESCRIPTION. There are cases where you might have to move it back.


See also [Step by step guide for creating a package that depends on RStan](http://mc-stan.org/rstantools/articles/minimal-rstan-package.html)

# Caveat

Priors are hard-wired in `brms` code and require recompilation when changed by default. In more recent versions you can use parameter `stanvars` to changes these at run-time (See github issues [here](https://github.com/paul-buerkner/brms/issues/357) and [here](https://github.com/paul-buerkner/brms/issues/219))

