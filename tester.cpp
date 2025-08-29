#include <cerrno>
#include <chrono>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RES "\033[0m"
#define YELLOW "\033[33m"

extern "C" size_t ft_strlen(const char *s);
extern "C" char *ft_strcpy(char *dest, const char *src);
extern "C" int ft_strcmp(const char *s1, const char *s2);
extern "C" ssize_t ft_write(int fd, const void *buf, size_t count);
extern "C" ssize_t ft_read(int fd, void *buf, size_t count);
extern "C" char *ft_strdup(const char *s);

extern "C" int ft_atoi_base(const char *str, const char *base);

class Benchmarker {
public:
  static double run(const std::function<void()> &func, size_t iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i)
      func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
  }
};

void print_header(const std::string &title, size_t width = 69) {
  std::cout << std::string(YELLOW) << "\n";
  std::cout << std::string(width, '=') << "\n";
  std::cout << std::setw((width + title.size()) / 2) << title << "\n";
  std::cout << std::string(width, '=') << "\n";
  std::cout << std::string(RES);
}

void printf_table_header(const std::vector<std::string> &headers,
                         const std::vector<size_t> &widths) {
  for (size_t i = 0; i < headers.size(); ++i) {
    std::cout << std::left << std::setw(widths[i]) << headers[i];
  }
  std::cout << "\n";
  size_t total_width = 0;
  for (size_t w : widths)
    total_width += w;
  std::cout << std::string(total_width, '-') << "\n";
}

void test_strlen(std::vector<int> sizes, size_t iteration) {
  print_header("Testing ft_strlen vs strlen");
  printf_table_header(
      {"Size", "Result", "as", "expected", "std (s)", "ft (s)", "Compare"},
      {12, 12, 12, 12, 15, 15, 15});

  for (int size : sizes) {
    std::string str(size, 'b');
    const char *cstr = str.c_str();

    double std_time = Benchmarker::run(
        [&]() {
          volatile size_t l = strlen(cstr);
          (void)l;
        },
        iteration);

    double ft_time = Benchmarker::run(
        [&]() {
          volatile size_t l = ft_strlen(cstr);
          (void)l;
        },
        iteration);

    size_t std_result = strlen(cstr);
    size_t ft_result = ft_strlen(cstr);

    std::string result = (std_result == ft_result)
                             ? (std::string(GREEN) + "OK" + RES)
                             : (std::string(RED) + "FAIL" + RES);

    std::string compare;
    if (ft_time < std_time)
      compare = std::string(GREEN) + "ft faster" + RES;
    else
      compare = std::string(RED) + "ft slower" + RES;

    std::cout << std::left << std::setw(12) << size << std::setw(21) << result
              << std::setw(12) << std_result << std::setw(12) << ft_result
              << std::setw(15) << std::fixed << std::setprecision(6) << std_time
              << std::setw(15) << ft_time << compare << "\n";
  }
}

void test_strcpy(std::vector<int> sizes, size_t iteration) {
  print_header("Testing ft_strcpy vs strcpy");
  printf_table_header({"Size", "Result", "std (s)", "ft (s)", "Compare"},
                      {12, 12, 15, 15, 15});

  for (int size : sizes) {
    std::string src(size, 'a');
    char *dest_std = new char[size + 1];
    char *dest_ft = new char[size + 1];
    const char *csrc = src.c_str();

    double std_time =
        Benchmarker::run([&]() { strcpy(dest_std, csrc); }, iteration);

    double ft_time =
        Benchmarker::run([&]() { ft_strcpy(dest_ft, csrc); }, iteration);

    std::string std_result(dest_std);
    std::string ft_result(dest_ft);

    std::string result = (std_result == ft_result)
                             ? (std::string(GREEN) + "OK" + RES)
                             : (std::string(RED) + "FAIL" + RES);

    std::string compare;
    if (ft_time < std_time)
      compare = std::string(GREEN) + "ft faster" + RES;
    else
      compare = std::string(RED) + "ft slower" + RES;

    std::cout << std::left << std::setw(12) << size << std::setw(21) << result
              << std::setw(15) << std::fixed << std::setprecision(6) << std_time
              << std::setw(15) << ft_time << compare << "\n";

    delete[] dest_std;
    delete[] dest_ft;
  }
}

void test_strcmp(size_t iteration) {
  print_header("Testing ft_strcmp vs strcmp");
  printf_table_header(
      {"Size", "Result", "as", "expected", "std (s)", "ft (s)", "Compare"},
      {12, 12, 12, 12, 15, 15, 15});

  std::vector<std::pair<std::string, std::string>> test_cases = {
      {"hello", "hello"},
      {"hello", "world"},
      {"abc", "abcd"},
      {"abcd", "abc"},
      {"", ""},
      {"a", ""},
      {"", "a"},
      {"sameprefix", "sameprefixbutlonger"},
      {"differentprefix", "different"},
      {"yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyo",
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoy"
       "oyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"
       "yoyoyoyoyoyoyoyoyoyoyoyoyoyoyo"}};

  for (const auto &pair : test_cases) {
    const std::string &s1 = pair.first;
    const std::string &s2 = pair.second;
    const char *cstr1 = s1.c_str();
    const char *cstr2 = s2.c_str();
    size_t size = std::max(s1.size(), s2.size());

    double std_time = Benchmarker::run(
        [&]() {
          volatile int res = strcmp(cstr1, cstr2);
          (void)res;
        },
        iteration);

    double ft_time = Benchmarker::run(
        [&]() {
          volatile int res = ft_strcmp(cstr1, cstr2);
          (void)res;
        },
        iteration);

    int std_result = strcmp(cstr1, cstr2);
    int ft_result = ft_strcmp(cstr1, cstr2);

    std::string result = (std_result == ft_result)
                             ? (std::string(GREEN) + "OK" + RES)
                             : (std::string(RED) + "FAIL" + RES);

    std::string compare;
    if (ft_time < std_time)
      compare = std::string(GREEN) + "ft faster" + RES;
    else
      compare = std::string(RED) + "ft slower" + RES;

    std::cout << std::left << std::setw(12) << size << std::setw(21) << result
              << std::setw(12) << ft_result << std::setw(12) << std_result
              << std::setw(15) << std::fixed << std::setprecision(6) << std_time
              << std::setw(15) << ft_time << compare << "\n";
  }
}

void test_write() {
  print_header("Testing ft_write vs write");
  printf_table_header(
      {"Case", "Result", "ret std", "ret ft", "errno std", "errno ft"},
      {20, 12, 15, 15, 15, 15});

  int fd = open("test_write.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
  if (fd == -1) {
    std::cerr << "Failed to open test_write.txt for writing.\n";
    return;
  }

  struct WriteCase {
    std::string name;
    int fd;
    const char *buf;
    size_t count;
  };

  std::vector<WriteCase> cases = {
      {"Hello, World!", fd, "Hello, World!\n", 14},
      {"empty", fd, "", 0},
      {"simple", fd, "A\n", 2},
      {"long", fd, "This is a longer string to test the write function.\n", 52},
      {"invalid fd", -1, "Invalid FD\n", 12},
      {"null", fd, nullptr, 10}};

  for (const auto &c : cases) {
    ssize_t ret_std = write(c.fd, c.buf, c.count);
    int err_std = errno;
    ssize_t ret_ft = ft_write(c.fd, c.buf, c.count);
    int err_ft = errno;

    std::string result = (ret_std == ret_ft && err_std == err_ft)
                             ? (std::string(GREEN) + "OK" + RES)
                             : (std::string(RED) + "FAIL" + RES);

    std::cout << std::left << std::setw(20) << c.name << std::setw(21) << result
              << std::setw(15) << ret_std << std::setw(15) << ret_ft
              << std::setw(15) << err_std << std::setw(15) << err_ft << "\n";
  }

  if (close(fd) == -1) {
    std::cerr << "Failed to close test_write.txt after writing.\n";
  }
  errno = 0;
}

void test_read() {
  print_header("Testing ft_read vs read");
  printf_table_header(
      {"Case", "Result", "ret std", "ret ft", "errno std", "errno ft"},
      {20, 12, 15, 15, 15, 15});

  int fd = open("test_read.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
  if (fd == -1) {
    std::cerr << "Failed to open test_read.txt for reading.\n";
    return;
  }
  const char *content = "This is a test file for read function.\n";
  write(fd, content, strlen(content));
  lseek(fd, 0, SEEK_SET); // Reset file offset to the beginning

  struct ReadCase {
    std::string name;
    int fd;
    size_t count;
  };
  std::vector<ReadCase> cases = {
      {"normal read", fd, 10},
      {"read more than file", fd, 100},
      {"zero bytes", fd, 0},
      {"invalid fd", -1, 10},
  };

  for (const auto &c : cases) {
    char buf_std[101] = {0};
    char buf_ft[101] = {0};

    ssize_t ret_std = read(c.fd, buf_std, c.count);
    int err_std = errno; // Save errno after standard read
    lseek(fd, 0, SEEK_SET);
    ssize_t ret_ft = ft_read(c.fd, buf_ft, c.count);
    int err_ft = errno; // Save errno after ft_read
    lseek(fd, 0, SEEK_SET);

    std::string result = (ret_std == ret_ft && err_std == err_ft &&
                          std::memcmp(buf_std, buf_ft, sizeof(buf_std)) == 0)
                             ? (std::string(GREEN) + "OK" + RES)
                             : (std::string(RED) + "FAIL" + RES);

    std::cout << std::left << std::setw(20) << c.name << std::setw(21) << result
              << std::setw(15) << ret_std << std::setw(15) << ret_ft
              << std::setw(15) << err_std << std::setw(15) << err_ft << "\n";
  }

  // Special case: read
  // null buffer

  char *null_buf = nullptr;
  ssize_t ret_std = read(fd, null_buf, 10);
  int err_std = errno;
  lseek(fd, 0, SEEK_SET);
  ssize_t ret_ft = ft_read(fd, null_buf, 10);
  int err_ft = errno;
  lseek(fd, 0, SEEK_SET);

  std::string result = (ret_std == ret_ft && err_std == err_ft)
                           ? (std::string(GREEN) + "OK" + RES)
                           : (std::string(RED) + "FAIL" + RES);

  std::cout << std::left << std::setw(20) << "null buffer" << std::setw(21)
            << result << std::setw(15) << ret_std << std::setw(15) << ret_ft
            << std::setw(15) << err_std << std::setw(15) << err_ft << "\n";

  if (close(fd) == -1) {
    std::cerr << "Failed to close test_read.txt after reading.\n";
  }
  errno = 0;
}

void test_strdup(size_t iteration = 1000) {
  print_header("Testing ft_strdup vs strdup");
  printf_table_header({"Case", "Result", "std (s)", "ft (s)", "Compare"},
                      {20, 12, 15, 15, 15});

  struct StrdupCase {
    std::string name;
    const char *str;
  };

  std::vector<StrdupCase> cases = {{"normal", "Hello, World!"},
                                   {"empty", ""},
                                   {"long", std::string(1000, 'a').c_str()}};

  (void)iteration; // Currently not used in timing

  for (const auto &c : cases) {
    double std_time = Benchmarker::run(
        [&]() {
          char *dup = strdup(c.str);
          free(dup);
        },
        iteration);

    double ft_time = Benchmarker::run(
        [&]() {
          char *dup = ft_strdup(c.str);
          free(dup);
        },
        iteration);

    char *std_dup = strdup(c.str);
    char *ft_dup = ft_strdup(c.str);

    std::string std_result = std_dup ? std_dup : "nullptr";
    std::string ft_result = ft_dup ? ft_dup : "nullptr";

    std::string result = (std_result == ft_result)
                             ? (std::string(GREEN) + "OK" + RES)
                             : (std::string(RED) + "FAIL" + RES);

    std::string compare;
    if (ft_time < std_time)
      compare = std::string(GREEN) + "ft faster" + RES;
    else
      compare = std::string(RED) + "ft slower" + RES;

    std::cout << std::left << std::setw(20) << c.name << std::setw(21) << result
              << std::setw(15) << std::fixed << std::setprecision(6) << std_time
              << std::setw(15) << ft_time << compare << "\n";

    free(std_dup);
    free(ft_dup);
  }
}

int main() {
  std::vector<int> sizes = {0, 1, 10, 100, 1000, 10000, 100000};

  test_strlen(sizes, 10000);
  test_strcpy(sizes, 10000);
  test_strcmp(10000);

  test_write();
  test_read();

  test_strdup(10000);

  std::cout << ft_atoi_base("A2", "0123456789ABCDEF") << '\n';

  return 0;
}
