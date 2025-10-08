#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

extern "C" ssize_t ft_write(int fd, const void *buf, size_t count);

TEST(write, basic) {

  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, str.size());
  std::string ft_out = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ssize_t lib_ret = write(1, c_str, str.size());
  std::string lib_out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_out, lib_out);
  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, empty) {
  const char *c_str = "";

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, 0);
  std::string ft_out = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ssize_t lib_ret = write(1, c_str, 0);
  std::string lib_out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_out, lib_out);
  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, long_str) {
  std::string str(1000000, 'n');
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, str.size());
  std::string ft_out = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ssize_t lib_ret = write(1, c_str, str.size());
  std::string lib_out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_out, lib_out);
  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, invalid_fd) {
  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  ssize_t ft_ret = ft_write(-1, c_str, str.size());
  int ft_errno = errno;
  errno = 0;

  ssize_t lib_ret = write(-1, c_str, str.size());
  int lib_errno = errno;
  errno = 0;

  std::cout << "ft_errno: " << ft_errno << ", lib_errno: " << lib_errno
            << std::endl;
  EXPECT_EQ(ft_errno, lib_errno);
  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, null_buf) {
  ssize_t ft_ret = ft_write(1, NULL, 10);
  int ft_errno = errno;
  errno = 0;

  ssize_t lib_ret = write(1, NULL, 10);
  int lib_errno = errno;
  errno = 0;

  std::cout << "ft_errno: " << ft_errno << ", lib_errno: " << lib_errno
            << std::endl;
  EXPECT_EQ(ft_errno, lib_errno);
  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, zero_count) {
  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, 0);
  std::string ft_out = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ssize_t lib_ret = write(1, c_str, 0);
  std::string lib_out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_out, lib_out);
  EXPECT_EQ(ft_ret, lib_ret);
}

TEST(write, partial_write) {
  const std::string str = "Hello, World!\n";
  const char *c_str = str.c_str();

  testing::internal::CaptureStdout();
  ssize_t ft_ret = ft_write(1, c_str, 5);
  std::string ft_out = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  ssize_t lib_ret = write(1, c_str, 5);
  std::string lib_out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(ft_out, lib_out);
  EXPECT_EQ(ft_ret, lib_ret);
}
