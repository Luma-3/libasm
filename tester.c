#include <stdio.h>

extern size_t ft_strlen(const char *s);


int main(void) {
  const char *str = "Hello, World!";
  printf("Length of '%s' is %zu\n", str, ft_strlen(str));
}
