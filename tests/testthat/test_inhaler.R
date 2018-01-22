context("Inhaler test")
library(brms)



test_that("Use model as saved in RDS",{
  # Make sure you have run brms/generated_stan before on your system
  # This test must be removed later
  inhaler_model = readRDS(system.file("extdata/inhaler.rds", package = "brmspack"))
  
  # Error: need an object with call component"
  fit2 = update(inhaler_model, recompile = "never")
})

test_that("Locally generated file can be updated without recompile",{
  modelfile = "src/stan_files/inhaler.stan"
  inhaler_model = brm(rating ~ period + carry + cs(treat), 
                      save_model = modelfile,
                      chains = 1,
                      iter = 100,
                      data = inhaler, family = sratio("cloglog"), 
                      prior = set_prior("normal(0,5)"))
  # In case you have a version of brms before 20.01.2018
  # cat("\n", file = modelfile, append = TRUE)
  
  rds_file = "inst/extdata/inhaler.rds"
  saveRDS(inhaler_model, file = rds_file)
  inhaler_model = readRDS(rds_file)
  # requires recompiling the model. Why?
  fit2 = update(inhaler_model, recompile = "never")
})