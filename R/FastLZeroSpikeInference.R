#' FastLZeroSpikeInference: FastLZeroSpikeInference: A package for estimating spike
#' times from calcium imaging data using an L0 penalty
#'
#' This package implements an algorithm for deconvolving calcium imaging data
#' for a single neuron in order to estimate the times at which the neuron
#' spikes.
#'
#'
#' @seealso
#' \strong{Estimate spikes:}
#' \code{\link{ARFPOP}}}

#'
#'
#' @details
#'
#' This package implements an algorithm for deconvolving calcium imaging data for a single 
#' neuron in order to estimate the times at which the neuron spikes. This algorithim is a
#' modification of the constrained functional pruning algorithm of Hocking et al. (2017). 

#' This algorithm solves the optimization problems
#' 
#'   \strong{AR(1) model:}
#'   
#'  minimize_{c1,...,cT} 0.5 sum_{t=1}^T ( y_t - c_t )^2 + lambda sum_{t=2}^T 1_{c_t neq gamma c_{t-1} }
#'  
#'  subject to c_t >= 0, t = 1, ..., T
#'  
#'  for the global optimum, where y_t is the observed fluorescence at the tth timepoint.
#'
#'  \strong{Constrained AR(1) model}
#'  
#' minimize_{c1,...,cT} 0.5 sum_{t=1}^T ( y_t - c_t )^2 + lambda sum_{t=2}^T 1_{c_t neq gamma c_{t-1} }
#' 
#' subject to c_t >= 0, t = 1, ..., T
#' 
#' c_{t} >= gamma c_{t-1}, t = 2, ..., T
#'
#' See Jewell and Witten (2017) <arXiv:1703.08644> and 
#' 
#' Hocking, T. D., Rigaill, G., Fearnhead, P., and Bourque, G. (2017) <arXiv:1703.03352> 
#'
#' @examples
#'
#' @docType package
#' @name FastLZeroSpikeInference
NULL
