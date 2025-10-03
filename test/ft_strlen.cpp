#include "gtest/gtest.h"
#include <cstddef>
#include <cstring>
#include <gtest/gtest.h>
#include <string>

extern "C" size_t ft_strlen(const char *src);

TEST(strlen, basic) {
  std::string str(16, 'n');

  const char *c_str = str.c_str();

  const size_t i = ft_strlen(c_str);

  const size_t lib = strlen(c_str);

  EXPECT_EQ(i, lib);
}

TEST(strlen, null) {
  EXPECT_DEATH({ ft_strlen(NULL); }, ".*");
  EXPECT_DEATH({ size_t i = strlen(NULL); }, ".*");
}

TEST(strlen, empty) {
  const char *c_str = "";

  const size_t i = ft_strlen(c_str);

  const size_t lib = strlen(c_str);

  EXPECT_EQ(i, lib);
}

TEST(strlen, long_str) {
  std::string str(1000000, 'n');

  const char *c_str = str.c_str();

  const size_t i = ft_strlen(c_str);

  const size_t lib = strlen(c_str);

  EXPECT_EQ(i, lib);
}
