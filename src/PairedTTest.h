// PairedTTest.h

#ifndef PAIRED_T_TEST_H
#define PAIRED_T_TEST_H

#include "baseClass.h"
#include "helperFuncs.h"


class PairedTTest : public BaseClass {
private:
    const Rcpp::NumericVector& x_;
    const Rcpp::NumericVector& y_;

    double mean_diff;
    double var_diff;
    int n;

    double t_statistic;
    double degrees_of_freedom;
    double p_value;

    double std_error;

    double conf_lower;
    double conf_upper;

public:
    // Constructor
    PairedTTest(const Rcpp::NumericVector& x, const Rcpp::NumericVector& y,
            double mu = 0.0, std::string alternative = "two.sided",
            double conf_level = 0.95)
        : BaseClass(alternative, mu, conf_level), x_(x), y_(y), mean_diff(NA_REAL), var_diff(NA_REAL), n(NA_INTEGER),
        t_statistic(NA_REAL), degrees_of_freedom(NA_REAL), p_value(NA_REAL), std_error(NA_REAL), conf_lower(NA_REAL), conf_upper(NA_REAL)
    {
        if (x.size() != y.size()) {
            Rcpp::stop("Input vectors must have the same length.");
        }

    }
    // Compute Paired t-test results
    void compute() override;

    // Get results as a list
    Rcpp::List getResults() const override;

    // Destructor
    virtual ~PairedTTest() = default;

};

#endif // PAIRED_T_TEST_H