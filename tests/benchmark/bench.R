library(bench)
library(fastats)

set.seed(42)
x_large <- rnorm(1e6, mean = 5, sd = 2)
y_large <- rnorm(1e6, mean = 4, sd = 1)

results_welch <- bench::mark(
  Base_R = t.test(x_large, y_large, var.equal = FALSE),
  fastats = welch_t_test(x_large, y_large, mu = 0, alternative = "two.sided"),
  check = FALSE,
  iterations = 1000
)

results_paired <- bench::mark(
  Base_R = t.test(x_large, y_large, paired = TRUE),
  fastats = paired_t_test(x_large, y_large, mu = 0, alternative = "two.sided"),
  check = FALSE,
  iterations = 1000
)

print(results_welch)
print(results_paired)