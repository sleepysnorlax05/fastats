// WelchTTest.h

#ifndef WELCH_T_TEST_H
#define WELCH_T_TEST_H

#include "baseClass.h"
#include "helperFuncs.h"

using namespace Rcpp;

class WelchTTest : public BaseClass {
private:
    double mean_x, var_x;
    int n_x;

    double mean_y, var_y;
    int n_y;

    double mu;
    std::string alternative;

    double t_statistic;
    double degrees_of_freedom;
    double p_value;

public:

    // Constructor
    WelchTTest(const NumericVector& x, const NumericVector& y,
            double mu = 0.0, std::string alternative = "two.sided")
        : mu(mu), alternative(alternative),
          t_statistic(NA_REAL), degrees_of_freedom(NA_REAL), p_value(NA_REAL)
    {
        HelperFuncs::statsResult res_x = HelperFuncs::computeStats(x);
        mean_x = res_x.mean;
        var_x = res_x.variance;
        n_x = res_x.n;

        HelperFuncs::statsResult res_y = HelperFuncs::computeStats(y);
        mean_y = res_y.mean;
        var_y = res_y.variance;
        n_y = res_y.n;
    }

    // Compute Welch's t-test results
    void compute() override;

    // Get results as a list
    List getResults() const override;

    // Destructor
    virtual ~WelchTTest() = default;

};

#endif // WELCH_T_TEST_H