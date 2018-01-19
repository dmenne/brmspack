#' @title Run inhaler analysis with new data
#' @description Runs the inhaler example from brms/brm with new data set
#'
#' @useDynLib brmspack
#'
#' @examples
#' run_inhaler()
#' @export
run_inhaler = function(){
  mod = stanmodels[["inhaler"]]
  # load inhaler_model (TODO: better use rds to assign?)
  load(system.file("extdata/inhaler.rda", package = "brmspack"))
  
  # for debugging
  #mod = brmspack:::stanmodels[["inhaler"]] 
  # load inhaler_model 
  #load("inst/extdata/inhaler.rda")
  
  # mix up results a bit so we get a random result  
  newdata = inhaler
  newdata$rating = sample(newdata$rating, nrow(newdata))
  # priors cannot be changed without recompiling
  fit2 = update(inhaler_model, newdata = inhaler, 
                iter = 500, chains = 1)
  plot(fit2, ask = FALSE)
}
