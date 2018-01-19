# Generated stan file with brms

## Ordinal regression modeling patient's rating of inhaler instructions 
## category specific effects are estimated for variable 'treat'
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