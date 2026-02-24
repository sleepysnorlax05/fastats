#include <Rcpp.h>
#include "WelchTTest.h"

// [[Rcpp::export]]
Rcpp::List welch_t_test(Rcpp::NumericVector x, Rcpp::NumericVector y) {
    WelchTTest test(x, y);
    test.compute();
    return test.getResults();
}