#include <Rcpp.h>
#include "WelchTTest.h"

//' Welch's Two-Sample t-test (Unequal Variances)
//' 
//' Computes the Welch's two-sample t-test using Welford's online algorithm for single-pass performance and numerical stability.
//' 
//' @param x A numeric vector of data values.
//' @param y A numeric vector of data values.
//' @return A list conforming to the package consistency contract:
//' \itemize{
//'   \item \code{method} (string) "Welch's Two-Sample t-test"
//'   \item \code{alternative} (string) "two.sided"
//'   \item \code{statistic} (numeric) The calculated t-statistic.
//'   \item \code{p_value} (numeric) The two-sided p-value based on Satterthwaite's degrees of freedom.
//'   \item \code{df} (numeric) Satterthwaite's degrees of freedom.
//'   \item \code{estimate} (list) Contains \code{mean_x}, \code{mean_y}, and \code{mean_diff}.
//'   \item \code{stderr} (numeric) Standard error of the difference.
//'   \item \code{n} (list) Sample sizes \code{n_x} and \code{n_y}.
//' }
//' @examples
//' set.seed(42)
//' x <- rnorm(100, mean = 5, sd = 2)
//' y <- rnorm(100, mean = 4, sd = 1)
//' welch_t_test(x, y)
//' @export
// [[Rcpp::export]]
Rcpp::List welch_t_test(Rcpp::NumericVector x, Rcpp::NumericVector y) {
    WelchTTest test(x, y);
    test.compute();
    return test.getResults();
}