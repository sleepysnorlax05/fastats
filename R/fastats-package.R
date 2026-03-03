#' @keywords internal
#' @aliases fastats-package fastats
#' @title fastats: High-Performance T-Test Suite
#' @description A comprehensive suite of high-performance t-test family methods
#' (classical, robust, bootstrapped, and multivariate) implemented in C++ and
#' exposed to R via Rcpp and R6.
#' 
#' @section Core Numerical Policies:
#' - **Welfords Algorithm:** Standardized single-pass computation of mean and variance.
#' - **RcppArmadillo:** High-performance linear algebra for Hotelling's T2 tests.
#' - **RNG Discipline:** Bootstrap resampling respects R's global RNG state (set.seed()).
#' 
#' @section Key Features:
#' 1. One-sample t-test  
#' 2. Two-sample Student t-test (equal variances)  
#' 3. Two-sample Welch t-test (unequal variances)  
#' 4. Paired t-test (on within-pair differences)  
#' 5. Yuen’s trimmed-mean t-test (robust to outliers)  
#' 6. Bootstrapped t-test (empirical p-values via resampling)  
#' 7. Hotelling’s T2 test (multivariate equality of mean vectors)
#'
## usethis namespace: start
#' @useDynLib fastats, .registration = TRUE
#' @importFrom Rcpp sourceCpp
## usethis namespace: end
"_PACKAGE"
NULL