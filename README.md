# fastats: High-Performance T-Test Suite in R

<!-- badges: start -->
[![R-CMD-check](https://github.com/sleepysnorlax05/fastats/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/sleepysnorlax05/fastats/actions/workflows/R-CMD-check.yaml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
<!-- badges: end -->

**fastats** provides a comprehensive, highly optimized suite of t-test family methods for R. Designed for high-performance computing, the package relies on an underlying C++ core bridged via `Rcpp`, guaranteeing strict numerical stability and exceptional speed when scaling to millions of observations.

The package exposes both a standard Functional API familiar to Base R users and an object-oriented R6 API tailored for application developers.

## Numerical Architecture

To ensure both performance and mathematical correctness across large datasets, `fastats` implements the following numerical policies natively in C++:

- **Welford’s Online Algorithm:** Guarantees a stable, single-pass computation of mean and variance, preventing catastrophic cancellation errors common in standard two-pass approaches while maintaining an $O(1)$ memory footprint.
- **RcppArmadillo Integration:** Provides high-performance, BLAS/LAPACK-backed multivariate linear algebra for covariance matrices and stable inverses.
- **Strict RNG Scoping:** Bootstrap and resampling operations correctly map to R's global Random Number Generator, guaranteeing perfect reproducibility with `set.seed()`.

## Installation

You can install the development version of `fastats` from GitHub:

```r
# install.packages("devtools")
devtools::install_github("sleepysnorlax05/fastats")
```

## Quick Start

`fastats` functions are designed as drop-in replacements for standard base R statistical tests, yielding identical results at higher computational efficiency.

```r
library(fastats)

# Generate sample data
set.seed(42)
x <- rnorm(10^5, mean = 5.0, sd = 2)
y <- rnorm(10^5, mean = 4.5, sd = 1)

# Welch's Two-Sample T-Test (Unequal Variances)
welch_res <- welch_t_test(x, y, mu = 0, alternative = "two.sided")
print(welch_res$p_value)

# Paired T-Test
paired_res <- paired_t_test(x, y, alternative = "greater")
print(paired_res$conf_int)
```

## Roadmap & Features

The complete statistical suite encompasses classical, robust, bootstrapped, and multivariate extensions:

1. **One-Sample t-test** _(Pending)_
2. **Two-Sample Student t-test** (Equal Variances) _(Pending)_
3. **Two-Sample Welch t-test** (Unequal Variances) - **Available**
4. **Paired t-test** (Within-Pair Differences) - **Available**
5. **Yuen’s Trimmed-Mean t-test** (Robust to Outliers) _(Pending)_
6. **Bootstrapped t-test** (Empirical P-values) _(Pending)_
7. **Hotelling’s T² Test** (Multivariate Mean Vectors) _(Pending)_

## Developer Architecture

The project maintains a strict three-layer architectural separation:

1. **C++ OOP Core (`src/`)**: Pure numeric abstraction leveraging abstract base classes (`BaseClass`) and memory-aligned iterators.
2. **Rcpp Bridge (`src/rcpp_wrappers.cpp`)**: A minimal serialization envelope mapping C++ classes to robust R types.
3. **R Interface (`R/`)**: R-facing functional wrappers ensuring safe argument validation prior to C++ delegation.

## License

MIT © 2026 fastats authors
