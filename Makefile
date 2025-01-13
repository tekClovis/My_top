##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

NAME = my_top

SRCS =  src/my_top.c		\
	src/parsing.c			\
	src/struct_init.c		\
	src/init_f_line.c		\
	src/format_up_time.c	\
	src/init_cpu.c			\
	src/tasks.c				\
	src/mem_info.c			\
	src/process_init.c 		\
	src/print_system.c		\
	src/print_process.c 	\
	src/update.c 			\
	src/update_user.c 		\
	src/update_in_statm.c 	\

CFLAGS = -Wall -Wextra -Iinclude/ -lncurses

all :
	make -C ./lib
	gcc -o $(NAME) $(SRCS) -I ./include -L ./lib -lmy $(CFLAGS)
clean:
	rm -f $(NAME)

fclean: clean
	make fclean -C ./lib
	rm -rf ./*~

unit_tests:	fclean $(NAME)
	gcc -o unit_tests tests/*.c -L./ -lmy -I./include --coverage -lcriterion

tests_run:	unit_tests
	./unit_tests

debug: CFLAGS += -g
debug: fclean all

re : fclean all
