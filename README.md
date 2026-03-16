fastats: Fast Statistical Hypothesis Tests in R.
====

[![R-CMD-check](https://github.com/sleepysnorlax05/fastats/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/sleepysnorlax05/fastats/actions)

`fastats` provides statistical hypothesis tests implemented in highly optimized C++ for maximum performance and memory efficiency. It utilizes zero-allocation single-pass inline iteration and loop vectorization to dramatically outperform standard R functions.

## Features

*   **Extremely Fast:** Leverages C++ loop vectorization for optimal CPU caching and execution speed.
*   **Memory Efficient:** Zero-allocation algorithms process missing values (`NA`) entirely in-place without copying data.
*   **Drop-in Replacement:** Returns standard base R `"htest"` equivalent lists for seamless integration into existing pipelines.

## Installation

### On current R

You can install the development version from GitHub:

```r
# install.packages("devtools")
devtools::install_github("sleepysnorlax05/fastats")
```

## Where to get help

*   Use the [issue tracker](https://github.com/sleepysnorlax05/fastats/issues) for bug reporting, infelicities, and feature requests.

## Development notes

`fastats` is developed using a mixture of:

*   traditional R package building tools (`Write R Extensions`).
*   `Rcpp` for seamless C++ integration.
*   'tidyverse'-style tools, including `testthat` for unit testing and `roxygen2` for documentation.