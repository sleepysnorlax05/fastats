#ifndef BASECLASS_H
#define BASECLASS_H

#include <Rcpp.h>
#include <cmath>

class BaseClass {
protected:
    bool is_computed = false;

    std::string alternative;
    double mu;

public:
    BaseClass(const std::string& alt, double mu_val) : alternative(alt), mu(mu_val) {}

    virtual ~BaseClass() = default;

    virtual void compute() = 0;
    virtual Rcpp::List getResults() const = 0;
    
    bool isComputed() const {
        return is_computed;
    }
};

#endif // BASECLASS_H