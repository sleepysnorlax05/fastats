test_that("Paired T-test: two-sided parity with base R", {
  set.seed(123)
  x <- rnorm(30, mean = 5, sd = 2)
  y <- x + rnorm(30, mean = 0.5, sd = 1)

  res_fastats <- paired_t_test(x, y, mu = 0, alternative = "two.sided")
  res_base <- t.test(x, y, paired = TRUE)

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$df, unname(res_base$parameter), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
  
  expect_equal(as.numeric(res_fastats$conf_int), as.numeric(res_base$conf.int), tolerance = 1e-5)
})

test_that("Paired T-test: alternative greater", {
  set.seed(42)
  x <- rnorm(20, mean = 6, sd = 1)
  y <- x - rnorm(20, mean = 1, sd = 0.5)

  res_fastats <- paired_t_test(x, y, mu = 0, alternative = "greater")
  res_base <- t.test(x, y, paired = TRUE, alternative = "greater")

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
  expect_equal(as.numeric(res_fastats$conf_int), as.numeric(res_base$conf.int), tolerance = 1e-5)
})

test_that("Paired T-test: alternative less", {
  set.seed(99)
  x <- rnorm(25, mean = 4, sd = 1)
  y <- x + rnorm(25, mean = 2, sd = 0.5)

  res_fastats <- paired_t_test(x, y, mu = 0, alternative = "less")
  res_base <- t.test(x, y, paired = TRUE, alternative = "less")

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
  expect_equal(as.numeric(res_fastats$conf_int), as.numeric(res_base$conf.int), tolerance = 1e-5)
})

test_that("Paired T-test: custom mu", {
  set.seed(11)
  x <- rnorm(15, mean = 10, sd = 2)
  y <- x - rnorm(15, mean = 3, sd = 1)

  res_fastats <- paired_t_test(x, y, mu = 3, alternative = "two.sided")
  res_base <- t.test(x, y, mu = 3, paired = TRUE)

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
})

test_that("Paired T-test: exact zero variance in differences", {
  x <- c(1, 2, 3, 4, 5)
  y <- c(1, 2, 3, 4, 5) 

  res_fastats <- paired_t_test(x, y)
  
  expect_true(is.nan(res_fastats$statistic) || is.infinite(res_fastats$statistic))
  expect_true(is.nan(res_fastats$p_value))
})

test_that("Paired T-test: error handling for missing/mismatched data", {
  x <- c(1, 2, 3)
  y <- c(1, 2)
  
  expect_error(paired_t_test(x, y), "Input vectors must have the same length")
  
  x2 <- c(1)
  y2 <- c(2)
  expect_error(paired_t_test(x2, y2), "Insufficient number of observations")
})

test_that("Paired T-test: handles missing values (NA)", {
  x <- c(1, 2, NA, 4, 5)
  y <- c(1, NA, 3, 4, 5)
  
  res_fastats <- paired_t_test(x, y)
  
  # After removing NA pairs, only (1,1), (4,4), and (5,5) remain.
  res_base <- t.test(x, y, paired = TRUE, na.action = na.omit)
  
  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$df, unname(res_base$parameter), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
})

test_that("Paired T-test: API output schema contract", {
  x <- rnorm(10)
  y <- rnorm(10)
  res <- paired_t_test(x, y)
  
  expect_true(all(c("method", "alternative", "statistic", "p_value", "df", "estimate", "conf_int") %in% names(res)))
  
  expect_equal(res$method, "Paired t-test")
  expect_equal(res$alternative, "two.sided")
  
  expect_true("mean of the differences" %in% names(res$estimate))
})
