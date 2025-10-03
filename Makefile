NASM = nasm
GCC = g++

SRCS_DIR = src/
SRCS =	ft_strlen.s \
				ft_strcpy.s \
				ft_strcmp.s \
				ft_write.s	\
				ft_read.s	\
				ft_strdup.s \
				ft_atoi_base.s
SRCS_TESTER = tester.cpp

OBJ_DIR = obj/
OBJ = $(SRCS:%.s=$(OBJ_DIR)%.o)

NAME = libasm.a
NAME_TEST = tester

CFLAGS = -Wall -Wextra -Werror -g3 -fPIC -fPIE
NASMFLAGS = -f elf64 -DPIC -g -F dwarf -w+all

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

$(OBJ_DIR)%.o : $(SRCS_DIR)%.s
	mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) -o $@ $<

init: test/build/Makefile
		bear -- make -B -C.
		jq -s 'add' compile_commands.json test/build/compile_commands.json > compile_commands_tmp.json
		mv compile_commands_tmp.json compile_commands.json

###############################
###########  TEST  ############
###############################

CMAKE_SRCS := $(wildcard test/*.cpp test/*.hpp)

test:	test/build/Makefile
	make -C test/build

test/build/Makefile : $(CMAKE_SRCS) $(NAME)
	mkdir -p test/build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S test -B test/build

run-test: test
	cd test/build && ./asm_test

clean:
	rm -rf $(OBJ_DIR)
	rm -f test_read.txt
	rm -f test_write.txt

fclean: clean
	rm -f $(NAME) $(NAME_TEST)

re: fclean all

