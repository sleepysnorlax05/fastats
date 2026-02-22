#ifndef BASECLASS_H
#define BASECLASS_H

#include <Rcpp.h>
#include <cmath>

class BaseClass {
protected:
    bool is_computed = false;

public:
    virtual ~BaseClass() = default;

    virtual void compute() = 0;
    virtual Rcpp::List getResults() const = 0;
    bool isComputed() const {
        return is_computed;
    }
};

#endif // BASECLASS_H