#include <Rcpp.h>
#include "WelchTTest.h"
#include "PairedTTest.h"

//' Welch's Two-Sample t-test
//' 
//' @description
//' Performs a Welch's two-sample t-test on vectors of data. This procedure
//' calculates the t-statistic and p-value for two independent samples with 
//' highly optimized C++ loop vectorization, assuming unequal variances.
//' 
//' @param x A numeric vector representing the first sample.
//' @param y A numeric vector representing the second sample.
//' @param mu A numeric value indicating the true value of the difference in means
//'   under the null hypothesis. Default is `0.0`.
//' @param alternative A character string specifying the alternative hypothesis,
//'   must be one of `"two.sided"` (default), `"greater"`, or `"less"`.
//' 
//' @return A list with class `"htest"` equivalent containing the following components:
//' \describe{
//'   \item{statistic}{The value of the t-statistic.}
//'   \item{df}{The degrees of freedom for the t-statistic.}
//'   \item{p_value}{The p-value for the test.}
//'   \item{conf_int}{A numeric vector of length 2 containing the confidence interval for the specified true difference in means.}
//'   \item{estimate}{The estimated means of `x` and `y`.}
//'   \item{method}{A character string indicating what type of t-test was performed.}
//'   \item{alternative}{A character string describing the alternative hypothesis.}
//' }
//' 
//' @export
// [[Rcpp::export]]
Rcpp::List welch_t_test(Rcpp::NumericVector x, Rcpp::NumericVector y, double mu = 0.0, std::string alternative = "two.sided") {
    WelchTTest test(x, y, mu, alternative);
    test.compute();
    return test.getResults();
}


//' Paired Two-Sample t-test
//' 
//' @description
//' Performs a paired two-sample t-test on vectors of data. This function computes
//' the test statistic efficiently using a zero-allocation single-pass inline iteration 
//' over the paired differences, skipping missing (`NA`) values automatically.
//' 
//' @param x A numeric vector representing the first sample.
//' @param y A numeric vector representing the second sample. Must be the same length as `x`.
//' @param mu A numeric value indicating the true value of the mean difference
//'   under the null hypothesis. Default is `0.0`.
//' @param alternative A character string specifying the alternative hypothesis,
//'   must be one of `"two.sided"` (default), `"greater"`, or `"less"`.
//' 
//' @return A list with class `"htest"` equivalent containing the following components:
//' \describe{
//'   \item{statistic}{The value of the t-statistic.}
//'   \item{df}{The degrees of freedom for the t-statistic.}
//'   \item{p_value}{The p-value for the test.}
//'   \item{conf_int}{A numeric vector of length 2 containing the confidence interval for the mean difference.}
//'   \item{estimate}{The estimated mean of the paired differences.}
//'   \item{method}{A character string indicating what type of t-test was performed.}
//'   \item{alternative}{A character string describing the alternative hypothesis.}
//' }
//' 
//' @export
// [[Rcpp::export]]
Rcpp::List paired_t_test(Rcpp::NumericVector x, Rcpp::NumericVector y, double mu = 0.0, std::string alternative = "two.sided") {
    PairedTTest test(x, y, mu, alternative);
    test.compute();
    return test.getResults();
}