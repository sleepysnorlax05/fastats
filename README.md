# fastats: High-Performance T-Test Suite

<!-- badges: start -->
[![R-CMD-check](https://github.com/sleepysnorlax05/fastats/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/sleepysnorlax05/fastats/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

**fastats** is an R package focused on equality-of-means testing via a comprehensive suite of t-test family methods. The package prioritizes high-performance C++ implementations exposed through both functional and R6 OOP interfaces.

## Key Features

The package roadmap includes seven core tests, all utilizing **Welford's Online Algorithm** for numerically stable single-pass variance calculations and **RcppArmadillo** for multivariate linear algebra.

1. **One-sample t-test**
2. **Two-sample Student t-test** (equal variances)
3. **Two-sample Welch t-test** (unequal variances)
4. **Paired t-test** (within-pair differences)
5. **Yuen’s trimmed-mean t-test** (robust to outliers)
6. **Bootstrapped t-test** (empirical p-values via resampling)
7. **Hotelling’s T² test** (multivariate equality of mean vectors)

## Numerical Policies

- **Welford’s Algorithm:** Standardized single-pass computation of mean and variance to prevent catastrophic cancellation.
- **RcppArmadillo:** High-performance linear algebra for Hotelling's T² (covariance and stable solves).
- **RNG Discipline:** Bootstrap resampling respects R’s global RNG state (`set.seed()`) via Rcpp RNG scoping.

## Installation

```r
# install.packages("devtools")
devtools::install_github("sleepysnorlax05/fastats")
```

## Quick Start (Welch's T-Test)

```r
library(fastats)

set.seed(42)
x <- rnorm(100, mean = 5, sd = 2)
y <- rnorm(100, mean = 4, sd = 1)

# Functional API call
results <- welch_t_test(x, y)

print(results$t_statistic)
print(results$p_value)
```

## Architecture

The package follows a strict three-layer "bridge" pattern:
- **C++ Core:** Abstract Base Classes (ABC) and header-only math helpers in `src/`.
- **Rcpp Bridge:** Minimal wrappers in `src/rcpp_wrappers.cpp`.
- **R Interface:** Functional API and R6 OOP API in `R/`.

---

**Project Lead:** Huy Nhat Minh Nguyen  
**Project Status:** In Development
