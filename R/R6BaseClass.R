#' R6BaseClass
#' Abstract base class for statistical test results.
#' @docType class
#'
#' @details 
#' This class serves as a template for all specific t-test result classes (e.g., OneSampleTTest, TwoSampleTTest, etc.). It defines the common structure and methods for storing and displaying test results, including the test statistic, degrees of freedom, p-value, confidence intervals, and estimates. Subclasses must implement the `compute()` method to perform the actual calculations based on the input data.
#'
#' \code{R6BaseClass} cannot be instantiated directly; it is meant to be inherited by specific test classes that implement the necessary computations.
#' 
#' @field method The name of the statistical method used.
#' @field alternative The alternative hypothesis (e.g., "two.sided", "greater", "less").
#' @field statistic The computed test statistic (e.g., t-value).
#' @field p_value The p-value associated with the test statistic.
#' @field df The degrees of freedom for the test.
#' @field estimate A list containing mean estimates (e.g., mean_x, mean_y
#' and mean_diff for two-sample tests).
#' @field stderr The standard error of the estimate.
#' @field conf_int A numeric vector of length 2 containing the lower and upper bounds of the confidence interval.
#' @field n The sample size(s) used in the test.
#' @importFrom R6 R6Class
#' @export
R6BaseClass <- R6Class("R6BaseClass",
  public = list(
    method = NULL,
    alternative = NULL,
    statistic = NULL,
    p_value = NULL,
    df = NULL,
    estimate = NULL,
    stderr = NULL,
    conf_int = NULL,
    n = NULL,

    #' @description Initialize the base class (abstract).
    #' @details This method should not be called directly. It is meant to be overridden by
    #' subclasses that implement specific t-test computations. Attempting to instantiate this class directly will result in an error.
    #' 
    #' 
    initialize = function() { stop("Abstract class cannot be instantiated directly") },
    
    #' @description Compute the test results.
    #' @details This method must be implemented in subclasses to perform the actual calculations based on the
    #' input data. It should compute the test statistic, p-value, confidence intervals, and estimates as appropriate for the specific t-test being performed.
    #' 
    #' 
    compute = function() { stop("Must be implemented in subclass") },

    #' @description Print the test results in a readable format.
    #' @details This method formats and displays the results of the t-test, including the test
    #' statistic, degrees of freedom, p-value, confidence intervals, and mean estimates. It provides a user-friendly summary of the test results when the object is printed.
    #' 
    #' 
    print = function() {
      cat("\n\t", self$method, "\n\n")

      cat("t =", self$statistic, ", df =", self$df, ", p-value =", self$p_value, "\n")

      cat("alternative hypothesis: true difference in means is", self$alternative, "\n")

      if (!is.null(self$conf_int)) {
        cat("95 percent confidence interval:", self$conf_int[1], "to", self$conf_int[2], "\n")
      }

      if (!is.null(self$estimate)) {
        cat("mean of x:", self$estimate$mean_x, "\n")
        cat("mean of y:", self$estimate$mean_y, "\n")
        cat("difference in means:", self$estimate$mean_diff, "\n")
      }

      
      invisible(self)
    }
  )
)