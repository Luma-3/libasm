#include <cstring>
#include <gtest/gtest.h>
#include <string>

extern "C" int ft_strcmp(const char *s1, const char *s2);

TEST(Strcmp, basic) {
  const std::string str(16, 'n');
  const char *str_c = str.c_str();

  int ft = ft_strcmp(str_c, str_c);
  int lib = strcmp(str_c, str_c);

  EXPECT_EQ(ft, lib);
}

TEST(Strcmp, less) {
  const std::string str1 = "Hello, world!";
  const std::string str2 = "Hello, World!";

  int ft = ft_strcmp(str1.c_str(), str2.c_str());
  int lib = strcmp(str1.c_str(), str2.c_str());

  EXPECT_EQ(ft, lib);
}

TEST(Strcmp, great) {
  const std::string str1 = "Hello, World!";
  const std::string str2 = "Hello, world!";

  int ft = ft_strcmp(str1.c_str(), str2.c_str());
  int lib = strcmp(str1.c_str(), str2.c_str());

  EXPECT_EQ(ft, lib);
}
