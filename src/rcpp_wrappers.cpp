#include <Rcpp.h>
#include "WelchTTest.h"
#include "PairedTTest.h"

//' @export
// [[Rcpp::export]]
Rcpp::List welch_t_test(Rcpp::NumericVector x, Rcpp::NumericVector y, double mu = 0.0, std::string alternative = "two.sided") {
    WelchTTest test(x, y, mu, alternative);
    test.compute();
    return test.getResults();
}

//' @export
// [[Rcpp::export]]
Rcpp::List paired_t_test(Rcpp::NumericVector x, Rcpp::NumericVector y, double mu = 0.0, std::string alternative = "two.sided") {
    PairedTTest test(x, y, mu, alternative);
    test.compute();
    return test.getResults();
}