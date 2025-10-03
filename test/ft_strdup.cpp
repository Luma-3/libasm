#include <cstring>
#include <gtest/gtest.h>
#include <string>

extern "C" char *ft_strdup(const char *str);

TEST(strdup, basic) {
  const std::string str = "Hello, World!";
  const char *c_str = str.c_str();

  char *ft = ft_strdup(c_str);
  char *lib = strdup(c_str);

  EXPECT_EQ(std::string(ft), std::string(lib));
}

TEST(strdup, empty) {
  const char *c_str = "";

  char *ft = ft_strdup(c_str);
  char *lib = strdup(c_str);

  EXPECT_EQ(std::string(ft), std::string(lib));
}

TEST(strdup, long_str) {
  std::string str(1000000, 'n');
  const char *c_str = str.c_str();

  char *ft = ft_strdup(c_str);
  char *lib = strdup(c_str);

  EXPECT_EQ(std::string(ft), std::string(lib));
}

TEST(strdup, null) {
  EXPECT_DEATH({ ft_strdup(NULL); }, ".*");
  EXPECT_DEATH({ char *lib = strdup(NULL); }, ".*");
}
