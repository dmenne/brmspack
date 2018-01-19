[![Travis-CI Build Status](https://travis-ci.org/dmenne/breathteststan.svg?branch=master)](https://travis-ci.org/dmenne/breathteststan)

brmspack: Sample how to use precompiled models in brms
===========================================

Dieter Menne   
Menne Biomed Consulting Tübingen, Germany    
http://www.menne-biomed.de   

Paul Bürkners package [brms](https://github.com/paul-buerkner/brms) is a flexible and transparent companion of [rstanarm](https://github.com/stan-dev/rstanarm). The latter is more limited and uses prebuild Stan models with many branches, avoiding lengthy recompiles before start.

`brms` produces easy-to-read Stan code without bells and whistles, but the compiled code by default can only be used easily without recompiling within a session

This demo package uses the `inhaler` examples from `brms/brm` (with venerable BUGS roots) to demonstate how to use precompiled models that can be used with new data set in an approach similar to that of `rstanarm`.

# HowTo

* Generate a Stan package skeleton with `rstantools/rstan_package_skeleton`. It is assumed that you do not know the names of your Stan files yet, so you probably leave the parameter `stan_files` empty.

* Create your model in a directory which you add to `.Rbuildignore`. I use `brms`, but the name does not matter.
* Run your model with at least 1 iteration; too bad `brms` does not permit

```
library(brms)
stopifnot(file.exists("DESCRIPTION")) # Make sure we start from project file
inhaler_model <- brm(rating ~ period + carry + cs(treat), 
            save_model = "src/stan_files/inhaler.stan",
            iter = 1,
            data = inhaler, family = sratio("cloglog"), 
            prior = set_prior("normal(0,5)"))
save(inhaler_model, file = "inst/extdata/inhaler.rda")

# retrieve file in package via 
# system.file("extdata", package = "brmspack")
```


https://github.com/stan-dev/rstantools/issues/19