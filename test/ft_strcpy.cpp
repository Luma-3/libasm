#include "gtest/gtest.h"
#include <cstring>
#include <gtest/gtest.h>
#include <string>

extern "C" char *ft_strcpy(char *dest, const char *src);

TEST(strcpy, basic) {
  std::string src = "Hello, World!";
  char dest_ft[14];
  char dest_lib[14];

  char *ft = ft_strcpy(dest_ft, src.c_str());
  char *lib = strcpy(dest_lib, src.c_str());

  EXPECT_EQ(std::string(dest_ft), std::string(dest_lib));
  EXPECT_EQ(ft, dest_ft);
  EXPECT_EQ(lib, dest_lib);
}

TEST(strcpy, empty) {
  std::string src = "";
  char dest_ft[1];
  char dest_lib[1];

  char *ft = ft_strcpy(dest_ft, src.c_str());
  char *lib = strcpy(dest_lib, src.c_str());

  EXPECT_EQ(std::string(dest_ft), std::string(dest_lib));
  EXPECT_EQ(ft, dest_ft);
  EXPECT_EQ(lib, dest_lib);
}

TEST(strcpy, long_str) {
  std::string src(1000000, 'a');
  char *dest_ft = new char[1000001];
  char *dest_lib = new char[1000001];

  char *ft = ft_strcpy(dest_ft, src.c_str());
  char *lib = strcpy(dest_lib, src.c_str());

  EXPECT_EQ(std::string(dest_ft), std::string(dest_lib));
  EXPECT_EQ(ft, dest_ft);
  EXPECT_EQ(lib, dest_lib);

  delete[] dest_ft;
  delete[] dest_lib;
}

TEST(strcpy, null) {
  char dest_ft[10];
  char dest_lib[10];

  EXPECT_DEATH({ ft_strcpy(NULL, "Hello"); }, ".*");
  EXPECT_DEATH({ strcpy(NULL, "Hello"); }, ".*");

  EXPECT_DEATH({ ft_strcpy(dest_ft, NULL); }, ".*");
  EXPECT_DEATH({ strcpy(dest_lib, NULL); }, ".*");
}
