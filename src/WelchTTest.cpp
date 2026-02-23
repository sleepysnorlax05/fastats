#include "WelchTTest.h"

void WelchTTest::compute() {
    if (is_computed) return;

    HelperFuncs::statsResult res_x = HelperFuncs::computeStats(x);
    HelperFuncs::statsResult res_y = HelperFuncs::computeStats(y);

    double mean_diff = res_x.mean - res_y.mean;
    double se = std::sqrt((res_x.variance / x.size()) + (res_y.variance / y.size()));
    
    t_statistic = mean_diff / se;

    double df_num = std::pow((res_x.variance / x.size()) + (res_y.variance / y.size()), 2);
    double df_den = (std::pow(res_x.variance / x.size(), 2) / (x.size() - 1)) + 
                    (std::pow(res_y.variance / y.size(), 2) / (y.size() - 1));
    degrees_of_freedom = df_num / df_den;

    p_value = 2 * ::Rf_pt(-std::abs(t_statistic), degrees_of_freedom, 1, 0);

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
