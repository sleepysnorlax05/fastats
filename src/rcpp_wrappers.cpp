#include <Rcpp.h>
#include "WelchTTest.h"

// [[Rcpp::export]]
Rcpp::List welch_t_test(Rcpp::NumericVector x, Rcpp::NumericVector y, double mu = 0.0, std::string alternative = "two.sided") {
    WelchTTest test(x, y, mu, alternative);
    test.compute();
    return test.getResults();
}