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
#' run_inhaler()
#' @export
run_inhaler = function(){
  #mod = stanmodels[["inhaler"]]
  # load inhaler_model (TODO: better use rds to assign?)
  #inhaler_model = readRDS(system.file("extdata/inhaler.rds", package = "brmspack"))
  
  # for debugging
  #mod = brmspack:::stanmodels[["inhaler"]] 
  # load inhaler_model 
  #inhaler_model = readRDS("inst/extdata/inhaler.rds")
  
  # mix up results a bit so we get a random result  
  data("inhaler", package = "brms")
  newdata = inhaler
  newdata$rating = sample(newdata$rating, nrow(newdata))
  # priors cannot be changed without recompiling
  library(brms)
  fit2 = update(inhaler_model,  newdata = inhaler)
  plot(fit2, ask = FALSE)
}
