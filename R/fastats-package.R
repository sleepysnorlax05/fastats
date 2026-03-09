#' @keywords internal
#' @aliases fastats-package fastats
#' @title fastats: High-Performance T-Test Suite
#' @description A comprehensive, highly optimized suite of t-test family methods 
#' (classical, robust, bootstrapped, and multivariate) for R. The package is built 
#' on a C++ core via Rcpp, prioritizing raw computational speed and strict numerical stability.
#' 
#' @section Numerical Architecture:
#' The fastats C++ backend enforces several stringent numerical policies:
#' \itemize{
#' \item \strong{Welford's Algorithm:} A standard, single-pass mathematical engine is used for all mean and variance computations. This prevents catastrophic cancellation during moment calculations and maintains an $O(1)$ memory footprint, essential for high-throughput streaming calculations.
#' \item \strong{RcppArmadillo Integration:} Leverages highly optimized linear algebra solvers for covariance matrices required by tests like Hotelling's T2.
#' \item \strong{Strict RNG Discipline:} C++ level resampling algorithms correctly map to R's global Random Number Generator state, guaranteeing reproducibility under \code{set.seed()}.
#' }
#' 
#' @section Core Test Suite:
#' \enumerate{
#' \item One-sample t-test  
#' \item Two-sample Student t-test (equal variances)  
#' \item Two-sample Welch t-test (unequal variances)  
#' \item Paired t-test (on within-pair differences natively)  
#' \item Yuen’s trimmed-mean t-test (robust to outliers)  
#' \item Bootstrapped t-test (empirical p-values via fast resampling)  
#' \item Hotelling’s T2 test (multivariate equality of mean vectors)
#' }
#'
## usethis namespace: start
#' @useDynLib fastats, .registration = TRUE
#' @importFrom Rcpp sourceCpp
## usethis namespace: end
"_PACKAGE"
NULL