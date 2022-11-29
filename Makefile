NAME = container
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf
CC = c++

SRCS_VEC = main.cpp
SRCS_STACK = main_stack.cpp
SRCS_MAP = main_map.cpp

vectorr:
	$(CC) $(CFLAGS) $(SRCS_VEC) -o $(NAME)
stackk:
	$(CC) $(CFLAGS) $(SRCS_STACK) -o $(NAME)
mapp:
	$(CC) $(CFLAGS) $(SRCS_MAP) -o $(NAME)
clean:
	@$(RM) $(NAME)
	@echo "successfuly cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "executable removed successfuly"

re: fclean all