#include "gtest/gtest.h"
#include <cstddef>
#include <cstring>
#include <gtest/gtest.h>
#include <string>

extern "C" size_t ft_strlen(const char *src);

TEST(Strlen, basic) {
  std::string str(16, 'n');

  const char *c_str = str.c_str();

  const size_t i = ft_strlen(c_str);

  const size_t lib = strlen(c_str);

  EXPECT_EQ(i, lib);
}

TEST(Strlen, null) {
  EXPECT_DEATH({ ft_strlen(NULL); }, ".*");
  EXPECT_DEATH({ size_t i = strlen(NULL); }, ".*");
}

TEST(Strlen, Long) {
  std::string str(10000, 'n');

  const char *c_str = str.c_str();

  const size_t i = ft_strlen(c_str);

  const size_t lib = strlen(c_str);

  EXPECT_EQ(i, lib);
}

TEST(Strlen, Max) {
  std::string str(2147483647, 'n');

  const char *c_str = str.c_str();

  const size_t i = ft_strlen(c_str);

  const size_t lib = strlen(c_str);

  EXPECT_EQ(i, lib);
}
