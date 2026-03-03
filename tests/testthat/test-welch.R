test_that("Welch_t_test", {
  
  set.seed(42)
  x <- rnorm(100, mean = 5, sd = 2)
  y <- rnorm(100, mean = 4, sd = 1)
  
  # fastats result
  res_fastats <- welch_t_test(x, y, mu = 0, alternative = "two.sided")
  
  # base R result
  res_base <- t.test(x, y, var.equal = FALSE)
  
  # Core statistics
  expect_equal(res_fastats$statistic, res_base$statistic, tolerance = 1e-5, ignore_attr = TRUE)  
  expect_equal(res_fastats$df, res_base$parameter, tolerance = 1e-5, ignore_attr = TRUE)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5, ignore_attr = TRUE)

  # Estimates
  expect_equal(res_fastats$estimate[["mean of x"]], res_base$estimate[["mean of x"]], tolerance = 1e-5, ignore_attr = TRUE)
  expect_equal(res_fastats$estimate[["mean of y"]], res_base$estimate[["mean of y"]], tolerance = 1e-5, ignore_attr = TRUE)

  # Confidence intervals
  expect_equal(as.numeric(res_fastats$conf_int), as.numeric(res_base$conf.int), tolerance = 1e-5)
  expect_equal(attr(res_fastats$conf_int, "conf.level"), attr(res_base$conf.int, "conf.level"))
})
