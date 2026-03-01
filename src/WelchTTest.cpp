#include "WelchTTest.h"
#include <Rmath.h>

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
        p_value = 2 * (1 - R::pt(std::abs(t_statistic), degrees_of_freedom, true, false));
    } else if (alternative == "greater") {
        p_value = 1 - R::pt(t_statistic, degrees_of_freedom, true, false);
    } else if (alternative == "less") {
        p_value = R::pt(t_statistic, degrees_of_freedom, true, false);
    } else {
        Rcpp::stop("Invalid alternative hypothesis. Use 'two.sided', 'greater', or 'less'.");
    }

    is_computed = true;
}

Rcpp::List WelchTTest::getResults() const {
    if (!is_computed) {
        Rcpp::stop("Results not computed yet. Call compute() first.");
    }

    return List::create(
        Named("t_statistic") = t_statistic,
        Named("df") = degrees_of_freedom,
        Named("p_value") = p_value
    );
}