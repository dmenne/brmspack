# Generate stan file with brms

## Ordinal regression modeling patient's rating of inhaler instructions 
## category specific effects are estimated for variable 'treat'
library(brms)
stopifnot(file.exists("DESCRIPTION")) # Make sure we start from project file
modelfile = "src/stan_files/inhaler.stan"
inhaler_model = brm(rating ~ period + carry + cs(treat), 
            save_model = modelfile,
            chains = 1,
            iter = 100,
            data = inhaler, family = sratio("cloglog"), 
            prior = set_prior("normal(0,5)"),
            stan_model_args = list(save_dso = FALSE))

suppressWarnings(dir.create("inst/extdata"))
saveRDS(inhaler_model, file = "inst/extdata/inhaler.rds")

