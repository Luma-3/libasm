#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string>

extern "C" ssize_t ft_write(int fd, const void *buf, size_t count);

TEST(write, basic) {

  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, str.size());
  ssize_t lib_ret = write(1, c_str, str.size());

  testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, empty) {
  const char *c_str = "";

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, 0);
  ssize_t lib_ret = write(1, c_str, 0);
  testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, long_str) {
  std::string str(1000000, 'n');
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, str.size());
  ssize_t lib_ret = write(1, c_str, str.size());

  testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, invalid_fd) {
  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  testing::internal::CaptureStderr();
  ssize_t ft_ret = ft_write(-1, c_str, str.size());
  ssize_t lib_ret = write(-1, c_str, str.size());
  testing::internal::GetCapturedStderr();

  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, null_buf) {
  testing::internal::CaptureStderr();
  ssize_t ft_ret = ft_write(1, NULL, 10);
  ssize_t lib_ret = write(1, NULL, 10);
  testing::internal::GetCapturedStderr();

  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, zero_count) {
  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, 0);
  ssize_t lib_ret = write(1, c_str, 0);
  testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, partial_write) {
  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, 5);
  ssize_t lib_ret = write(1, c_str, 5);
  testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_ret, lib_ret);
}
