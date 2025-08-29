NASM = nasm
GCC = g++

SRCS_DIR = src/
SRCS =	ft_strlen.s \
				ft_strcpy.s \
				ft_strcmp.s \
				ft_write.s	\
				ft_read.s		\
				ft_strdup.s \
				ft_atoi_base.s
SRCS_TESTER = tester.cpp

OBJ_DIR = obj/
OBJ = $(SRCS:%.s=$(OBJ_DIR)%.o)

NAME = libasm.a
NAME_TEST = tester

CFLAGS = -Wall -Wextra -Werror -g3 -fPIC -fPIE -no-pie
NASMFLAGS = -f elf64 -DPIC

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

$(OBJ_DIR)%.o : $(SRCS_DIR)%.s
	mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) -o $@ $<

test: $(NAME) $(SRCS_TESTER)
	$(GCC) $(CFLAGS) -o $(NAME_TEST) $(SRCS_TESTER) -L. -lasm
	./$(NAME_TEST)

clean:
	rm -rf $(OBJ_DIR)
	rm -f test_read.txt
	rm -f test_write.txt

fclean: clean
	rm -f $(NAME) $(NAME_TEST)

re: fclean all

