#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include <Rcpp.h>
#include <cmath>

namespace HelperFuncs{

    struct Accumulate {
        int n = 0;
        double mean = 0.0;
        double ssq = 0.0;

        inline void add(double val){
            n ++;
            double prev_mean = mean;
            mean += (val - mean)/n;
            ssq += ((val - mean) * (val - prev_mean));
        }

        inline double variance() const {
            return (n > 1) ? (ssq / (n - 1)) : NAN;
        }
    };

    struct statsResult {
        double mean;
        double variance;
        double sumOfSquares;
        int n;
    };

    /*
    Implementation of Welford's Online Algorithm:

    Reference: https://davidma.me/blog/2025/Welfords-Algo/
    */

    inline statsResult computeStats(const Rcpp::NumericVector& vec){
        Accumulate stat;

        auto it = vec.begin();
        auto end = vec.end();

        for (; it != end; ++it) {
            if (!Rcpp::NumericVector::is_na(*it)){
                stat.add(*it);
            }
        }

        return {stat.mean, stat.variance(), stat.ssq, stat.n};
    };
};

#endif // HELPERFUNCS_H