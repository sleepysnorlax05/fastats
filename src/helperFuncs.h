#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include <Rcpp.h>
#include <cmath>

namespace HelperFuncs{

    struct statsResult {
        double mean;
        double variance;
        double sumOfSquares;
    };

    /*
    Implementation of Welford's Online Algorithm:

    Reference: https://davidma.me/blog/2025/Welfords-Algo/
    */
    inline statsResult computeStats(const Rcpp::NumericVector& vec){
        int n = 0;
        double mean = 0.0;
        double ssq = 0.0;

        for (int i = 0; i < vec.size(); i ++){
            n ++;
            double prev_mean = mean;
            mean += (vec[i] - mean)/n;
            ssq += ((vec[i] - mean) * (vec[i] - prev_mean));
        }

        double var = ssq / (n - 1);

        return {mean, var, ssq, n};
    };

};

#endif // HELPERFUNCS_H