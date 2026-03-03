#' @export
R6BaseClass <- R6::R6Class("R6BaseClass",
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

    initialize = function() { stop("Abstract class cannot be instantiated directly") },
    compute = function() { stop("Must be implemented in subclass") },

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