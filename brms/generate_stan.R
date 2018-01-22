# Generated stan file with brms

## Ordinal regression modeling patient's rating of inhaler instructions 
## category specific effects are estimated for variable 'treat'
library(brms)
stopifnot(file.exists("DESCRIPTION")) # Make sure we start from project file
modelfile = "src/stan_files/inhaler.stan"
inhaler_model = brm(rating ~ period + carry + cs(treat), 
            save_model = modelfile,
            save_dso = TRUE, # not needed later
            chains = 1,
            iter = 100,
            data = inhaler, family = sratio("cloglog"), 
            prior = set_prior("normal(0,5)"))
# In case you have a version of brms before 20.01.2018
cat("\n", file = modelfile, append = TRUE)

if (is.null(getCall(inhaler_model)))
 inhaler_model$call = rating ~ period + carry + cs(treat)


saveRDS(inhaler_model, file = "inst/extdata/inhaler.rds")

#inhaler_model_1 = readRDS("inst/extdata/inhaler.rds")
#fit2 = update(inhaler_model_1, recompile = "never")

# retrieve file in package via 
# system.file("extdata/inhaler.rds", package = "brmspack")