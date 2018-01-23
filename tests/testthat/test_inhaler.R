context("Inhaler test")
library(brms)

test_that("Fitting with precompiled model returns brmsfit",{
  data("inhaler", package = "brms")

  fit1 = run_inhaler(inhaler)
  expect_is(fit1, "brmsfit")
  ps = prior_summary(fit1)
  expect_equal(ps$prior[1], "normal(0,5)")
  
  # mix up results a bit so we get a random result  
  newdata = inhaler
  newdata$rating = sample(newdata$rating, nrow(newdata))
  fit3 = run_inhaler(newdata)
  expect_is(fit3, "brmsfit")
})