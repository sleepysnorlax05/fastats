// language: cpp
#include <Rcpp.h>
#include <testthat.h>-
#include "WelchTTest.h"

context("Welch's T-Test"){

    test_that("Small two samples test") {

        Rcpp::NumericVector x = {2.3, 2.5, 2.1, 2.4, 2.6};
        Rcpp::NumericVector y = {1.8, 1.9, 2.0, 1.7, 1.6};

        WelchTTest tTest(x, y);
        tTest.compute();
        Rcpp::List res = tTest.getResults();

        double t_stat = Rcpp::as<double>(res["t_statistic"]);
        double df     = Rcpp::as<double>(res["df"]);
        double p_val  = Rcpp::as<double>(res["p_value"]);

        expect_true(t_stat == Approx(5.2086).epsilon(1e-4));
        expect_true(df     == Approx(7.7111).epsilon(1e-4));
        expect_true(p_val  == Approx(0.0009).epsilon(1e-4));
    }

    test_that("Samples with negative values") {

        Rcpp::NumericVector x = {-2.0, -1.5, -1.0, -0.5, 0.0};
        Rcpp::NumericVector y = {-3.0, -2.5, -2.0, -1.5, -1.0};

        WelchTTest tTest(x, y);
        tTest.compute();
        Rcpp::List res = tTest.getResults();

        double t_stat = Rcpp::as<double>(res["t_statistic"]);
        double df     = Rcpp::as<double>(res["df"]);
        double p_val  = Rcpp::as<double>(res["p_value"]);

        expect_true(t_stat == Approx(2.0).epsilon(1e-4));
        expect_true(df     == Approx(8.0).epsilon(1e-4));
        expect_true(p_val  == Approx(0.08052).epsilon(1e-4));
    }
}