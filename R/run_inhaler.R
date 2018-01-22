#' @title Run inhaler analysis with new data
#' @description Runs the inhaler example from brms/brm with new data set
#'
#' @useDynLib brmspack
#' @importFrom graphics plot
#' @importFrom stats update
#' @importFrom utils data
#' @importFrom Rcpp loadModule
#'
#' @examples
#' #run_inhaler()
#' @export
run_inhaler = function(){
  mod = stanmodels[["inhaler"]] # Not yet used
  # load inhaler_model 
  inhaler_model = readRDS(system.file("extdata/inhaler.rds", package = "brmspack"))

    # for debugging
#  mod = brmspack:::stanmodels[["inhaler"]] 
#  inhaler_model = readRDS("inst/extdata/inhaler.rds")
  stopifnot(!is.null(getCall(inhaler_model))) # required patch version 
# inhaler_model$fit@stanmodel = mod # Don't replace yet
  
# mix up results a bit so we get a random result  
#  data("inhaler", package = "brms")
#  newdata = inhaler
#  newdata$rating = sample(newdata$rating, nrow(newdata))

  # Error: need an object with call component"
  fit2 = update(inhaler_model, recompile = "never")
  plot(fit2, ask = FALSE)
}
