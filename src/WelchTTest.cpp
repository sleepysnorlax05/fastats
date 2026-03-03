#include "WelchTTest.h"
#include <Rmath.h>
#include <Rcpp.h>
#include <cmath>

void WelchTTest::compute() {
    if (is_computed) return;

    double mean_diff = mean_x - mean_y;
    double se = std::sqrt((var_x / n_x) + (var_y / n_y));

    t_statistic = (mean_diff - mu) / se;

    double df_num = std::pow((var_x / n_x) + (var_y / n_y), 2);
    double df_den = (std::pow(var_x / n_x, 2) / (n_x - 1)) +
                    (std::pow(var_y / n_y, 2) / (n_y - 1));
    degrees_of_freedom = df_num / df_den;

    if (alternative == "two.sided") {
        p_value = 2 * (1 - R::pt(std::abs(t_statistic), degrees_of_freedom, 1, 0));
        double q = R::qt(1 - (1 - conf_level) / 2, degrees_of_freedom, 1, 0);
        conf_lower = mean_diff - q * se;
        conf_upper = mean_diff + q * se;
    } else if (alternative == "greater") {
        p_value = 1 - R::pt(t_statistic, degrees_of_freedom, 1, 0);
        double q = R::qt(conf_level, degrees_of_freedom, 1, 0);
        conf_lower = mean_diff - q * se;
        conf_upper = R_PosInf;
    } else if (alternative == "less") {
        p_value = R::pt(t_statistic, degrees_of_freedom, 1, 0);
        double q = R::qt(conf_level, degrees_of_freedom, 1, 0);
        conf_lower = R_NegInf;
        conf_upper = mean_diff + q * se;
    } else {
        Rcpp::stop("Invalid alternative hypothesis. Use 'two.sided', 'greater', or 'less'.");
    }

    is_computed = true;
}

Rcpp::List WelchTTest::getResults() const {
    if (!is_computed) Rcpp::stop("Results not computed yet. Call compute() first.");

    Rcpp::NumericVector estimate = Rcpp::NumericVector::create(
        Rcpp::Named("mean of x") = mean_x,
        Rcpp::Named("mean of y") = mean_y
    );

    Rcpp::NumericVector ci = Rcpp::NumericVector::create(conf_lower, conf_upper);
    ci.attr("conf.level") = conf_level;

    return Rcpp::List::create(
        Rcpp::Named("method")      = "Welch Two Sample t-test",
        Rcpp::Named("alternative") = alternative,
        Rcpp::Named("statistic")   = t_statistic,
        Rcpp::Named("df")          = degrees_of_freedom,
        Rcpp::Named("p_value")     = p_value,
        Rcpp::Named("conf_int")    = ci,
        Rcpp::Named("estimate")    = estimate
    );
}