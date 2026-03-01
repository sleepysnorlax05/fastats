test_that("welch_t_test produces correct results", {
  # Set seed for reproducibility
  set.seed(42)
  x <- rnorm(100, mean = 5, sd = 2)
  y <- rnorm(100, mean = 4, sd = 1)
  
  # Call your Rcpp wrapper
  res_fastats <- welch_t_test(x, y)
  
  # Compare to base R's t.test
  res_base <- t.test(x, y, var.equal = FALSE)
  
  expect_equal(res_fastats$t_statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$df, unname(res_base$parameter), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
})