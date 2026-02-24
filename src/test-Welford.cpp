#include <testthat.h>
#include "helperFuncs.h"

context("Welford Online Algorithm") {

    test_that("Basic calculation is correct for positive integers") {
        Rcpp::NumericVector data = {1.0, 2.0, 3.0, 4.0, 5.0};
        
        HelperFuncs::statsResult res = HelperFuncs::computeStats(data);
        
        expect_true(res.mean == Approx(3.0));
        expect_true(res.sumOfSquares == Approx(10.0));
        expect_true(res.variance == Approx(2.5)); 
    }

    test_that("Handles identical values with zero variance") {
        Rcpp::NumericVector data = {7.4, 7.4, 7.4, 7.4};
        
        HelperFuncs::statsResult res = HelperFuncs::computeStats(data);
        
        expect_true(res.mean == Approx(7.4));
        expect_true(res.sumOfSquares == Approx(0.0).margin(1e-9));
        expect_true(res.variance == Approx(0.0).margin(1e-9));
    }

    test_that("Handles negative numbers correctly") {
        Rcpp::NumericVector data = {-5.0, -1.0, 3.0, 7.0};
        
        HelperFuncs::statsResult res = HelperFuncs::computeStats(data);
        
        expect_true(res.mean == Approx(1.0));
        expect_true(res.sumOfSquares == Approx(80.0));
        expect_true(res.variance == Approx(26.6666666667));
    }

    test_that("Handles single element safely") {
        Rcpp::NumericVector data = {42.0};
        
        HelperFuncs::statsResult res = HelperFuncs::computeStats(data);
        
        expect_true(res.mean == Approx(42.0));
        expect_true(res.sumOfSquares == Approx(0.0).margin(1e-9));
    }
}
