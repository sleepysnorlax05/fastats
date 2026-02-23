// WelchTTest.h

#ifndef WELCH_T_TEST_H
#define WELCH_T_TEST_H

#include "baseClass.h"
#include "helperFuncs.h"

using namespace Rcpp;

class WelchTTest : public BaseClass {
private:
    const NumericVector x;
    const NumericVector y;

    double t_statistic;
    double degrees_of_freedom;
    double p_value;

public:

    // Constructor
    WelchTTest(const NumericVector& x, const NumericVector& y)
        : x(x), y(y), t_statistic(NA_REAL), degrees_of_freedom(NA_REAL), p_value(NA_REAL) {}

    // Compute Welch's t-test results
    void compute() override;

    // Get results as a list
    List getResults() const override;

    // Destructor
    virtual ~WelchTTest() = default;

};

#endif // WELCH_T_TEST_H