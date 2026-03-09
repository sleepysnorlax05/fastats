test_that("Welch T-test: two-sided parity with base R", {
  set.seed(42)
  x <- rnorm(100, mean = 5, sd = 2)
  y <- rnorm(100, mean = 4, sd = 1)

  res_fastats <- welch_t_test(x, y, mu = 0, alternative = "two.sided")
  res_base <- t.test(x, y, var.equal = FALSE)

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$df, unname(res_base$parameter), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
  
  expect_equal(res_fastats$estimate[["mean of x"]], res_base$estimate[["mean of x"]], tolerance = 1e-5)
  expect_equal(res_fastats$estimate[["mean of y"]], res_base$estimate[["mean of y"]], tolerance = 1e-5)

  expect_equal(as.numeric(res_fastats$conf_int), as.numeric(res_base$conf.int), tolerance = 1e-5)
  expect_equal(attr(res_fastats$conf_int, "conf.level"), attr(res_base$conf.int, "conf.level"))
})

test_that("Welch T-test: alternative greater", {
  set.seed(111)
  x <- rnorm(50, mean = 2, sd = 3)
  y <- rnorm(60, mean = 0, sd = 1.5)

  res_fastats <- welch_t_test(x, y, mu = 0, alternative = "greater")
  res_base <- t.test(x, y, var.equal = FALSE, alternative = "greater")

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
  expect_equal(as.numeric(res_fastats$conf_int), as.numeric(res_base$conf.int), tolerance = 1e-5)
})

test_that("Welch T-test: alternative less", {
  set.seed(222)
  x <- rnorm(45, mean = -1, sd = 2)
  y <- rnorm(40, mean = 1, sd = 2.5)

  res_fastats <- welch_t_test(x, y, mu = 0, alternative = "less")
  res_base <- t.test(x, y, var.equal = FALSE, alternative = "less")

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
  expect_equal(as.numeric(res_fastats$conf_int), as.numeric(res_base$conf.int), tolerance = 1e-5)
})

test_that("Welch T-test: custom mu", {
  set.seed(333)
  x <- rnorm(30, mean = 10, sd = 2)
  y <- rnorm(35, mean = 5, sd = 2)

  res_fastats <- welch_t_test(x, y, mu = 4, alternative = "two.sided")
  res_base <- t.test(x, y, mu = 4, var.equal = FALSE)

  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
})

test_that("Welch T-test: unequal vector lengths", {
  set.seed(444)
  x <- rnorm(10)
  y <- rnorm(100)
  
  res_fastats <- welch_t_test(x, y)
  res_base <- t.test(x, y, var.equal = FALSE)
  
  expect_equal(res_fastats$statistic, unname(res_base$statistic), tolerance = 1e-5)
  expect_equal(res_fastats$p_value, res_base$p.value, tolerance = 1e-5)
})

test_that("Welch T-test: zero variance edge case", {
  x <- c(5, 5, 5, 5, 5)
  y <- c(5, 5, 5, 5, 5)

  res_fastats <- welch_t_test(x, y)
  
  expect_true(is.nan(res_fastats$statistic) || is.infinite(res_fastats$statistic))
  expect_true(is.nan(res_fastats$p_value))
})

test_that("Welch T-test: API output schema contract", {
  x <- rnorm(15)
  y <- rnorm(15)
  res <- welch_t_test(x, y)

  expect_true(all(c("method", "alternative", "statistic", "p_value", "df", "estimate", "conf_int") %in% names(res)))

  expect_equal(res$method, "Welch Two Sample t-test")
  expect_equal(res$alternative, "two.sided")

  expect_true(all(c("mean of x", "mean of y") %in% names(res$estimate)))
})