#include "PairedTTest.h"
#include <Rmath.h>
#include <Rcpp.h>
#include <cmath>

void PairedTTest::compute(){
    if (is_computed) return;

    n = x_.size();
    if (n < 2) {
        Rcpp::stop("Insufficient number of observations.");
    }

    HelperFuncs::Accumulate diff_stat;
    for (int i = 0; i < n; ++i) {
        if (!Rcpp::NumericVector::is_na(x_[i]) && !Rcpp::NumericVector::is_na(y_[i])) {
            diff_stat.add(x_[i] - y_[i]);
        }
    }

    mean_diff = diff_stat.mean;
    var_diff = diff_stat.variance();
    std_error = std::sqrt(var_diff / n);
    t_statistic = (mean_diff - mu) / std_error;
    degrees_of_freedom = n - 1;
    
    if (alternative == "two.sided") {
        p_value = 2 * (1 - R::pt(std::abs(t_statistic), degrees_of_freedom, 1, 0));
        double q = R::qt(1 - (1 - conf_level) / 2, degrees_of_freedom, 1, 0);
        conf_lower = mean_diff - q * std_error;
        conf_upper = mean_diff + q * std_error;
    } else if (alternative == "greater") {
        p_value = 1 - R::pt(t_statistic, degrees_of_freedom, 1, 0);
        double q = R::qt(conf_level, degrees_of_freedom, 1, 0);
        conf_lower = mean_diff - q * std_error;
        conf_upper = R_PosInf;
    } else if (alternative == "less") {
        p_value = R::pt(t_statistic, degrees_of_freedom, 1, 0);
        double q = R::qt(conf_level, degrees_of_freedom, 1, 0);
        conf_lower = R_NegInf;
        conf_upper = mean_diff + q * std_error;
    } else {
        Rcpp::stop("Invalid alternative hypothesis. Use 'two.sided', 'greater', or 'less'.");
    }

    is_computed = true;
};

Rcpp::List PairedTTest::getResults() const {
    if (!is_computed) Rcpp::stop("Results not computed yet. Call compute() first.");

    Rcpp::NumericVector estimate = Rcpp::NumericVector::create(
        Rcpp::Named("mean of x") = mean_diff + mu,
        Rcpp::Named("mean of y") = mu
    );

    Rcpp::NumericVector ci = Rcpp::NumericVector::create(conf_lower, conf_upper);
    ci.attr("conf.level") = conf_level;

    return Rcpp::List::create(
        Rcpp::Named("method")      = "Paired t-test",
        Rcpp::Named("alternative") = alternative,
        Rcpp::Named("statistic")   = t_statistic,
        Rcpp::Named("df")          = degrees_of_freedom,
        Rcpp::Named("p_value")     = p_value,
        Rcpp::Named("conf_int")    = ci,
        Rcpp::Named("estimate")    = estimate
    );
}