#include <Rcpp.h>
#include "WelchTTest.h"

//' Welch's Two-Sample t-test
//' 
//' Computes the Welch's two-sample t-test for unequal variances using C++ for performance.
//' 
//' @param x A numeric vector of data values.
//' @param y A numeric vector of data values.
//' @return A list containing the t-statistic (`t_statistic`), degrees of freedom (`df`), and p-value (`p_value`).
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