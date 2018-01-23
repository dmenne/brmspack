# Generate stan file with brms

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

