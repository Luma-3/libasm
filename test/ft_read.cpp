#include <gtest/gtest.h>
#include <string>
#include <sys/types.h>

extern "C" ssize_t ft_read(int fd, void *buf, size_t count);

TEST(read, basic) {
  const std::string str = "Hello, World!";
  const char *c_str = str.c_str();
  char buffer[50] = {0};

  FILE *temp = tmpfile();
  fwrite(c_str, 1, str.size(), temp);
  fseek(temp, 0, SEEK_SET);
  int fd = fileno(temp);

  ssize_t ft_bytes = ft_read(fd, buffer, str.size());
  EXPECT_EQ(ft_bytes, str.size());
  EXPECT_EQ(std::string(buffer), str);

  fclose(temp);
}

TEST(read, empty) {
  const char *c_str = "";
  char buffer[50] = {0};

  FILE *temp = tmpfile();
  fwrite(c_str, 1, 0, temp);
  fseek(temp, 0, SEEK_SET);
  int fd = fileno(temp);

  ssize_t ft_bytes = ft_read(fd, buffer, 10);
  EXPECT_EQ(ft_bytes, 0);
  EXPECT_EQ(std::string(buffer), "");

  fclose(temp);
}

TEST(read, long_str) {
  std::string str(1000000, 'n');
  const char *c_str = str.c_str();
  char buffer[1000001] = {0};

  FILE *temp = tmpfile();
  fwrite(c_str, 1, str.size(), temp);
  fseek(temp, 0, SEEK_SET);
  int fd = fileno(temp);

  ssize_t ft_bytes = ft_read(fd, buffer, str.size());
  EXPECT_EQ(ft_bytes, str.size());
  EXPECT_EQ(std::string(buffer), str);

  fclose(temp);
}

TEST(read, invalid_fd) {
  char buffer[50] = {0};
  ssize_t ft_bytes = ft_read(-1, buffer, 10);
  ssize_t lib_bytes = read(-1, buffer, 10);
  EXPECT_EQ(ft_bytes, lib_bytes);
}

TEST(read, null_buffer) {
  FILE *temp = tmpfile();
  int fd = fileno(temp);
  ssize_t ft_bytes = ft_read(fd, NULL, 10);
  ssize_t lib_bytes = read(fd, NULL, 10);
  EXPECT_EQ(ft_bytes, lib_bytes);
  fclose(temp);
}

TEST(read, zero_count) {
  const std::string str = "Hello, World!";
  const char *c_str = str.c_str();
  char buffer_ft[50] = {0};
  char buffer_lib[50] = {0};

  FILE *temp = tmpfile();
  fwrite(c_str, 1, str.size(), temp);
  fseek(temp, 0, SEEK_SET);
  int fd = fileno(temp);

  ssize_t ft_bytes = ft_read(fd, buffer_ft, 0);
  ssize_t lib_bytes = read(fd, buffer_lib, 0);
  EXPECT_EQ(ft_bytes, 0);
  EXPECT_EQ(std::string(buffer_ft), std::string(buffer_lib));

  fclose(temp);
}
