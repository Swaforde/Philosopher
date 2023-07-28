NAME = philosopher
SRCS = src/main.c src/parsing.c src/init.c src/checker.c
OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) bonus -C ./Libft
	$(CC) $(OBJS) $(CFLAGS) ./Libft/libft.a -o $(NAME) -G3

$(OBJ_DIR)/%.o : src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@

clean:
	$(RM) -r obj/*
	make fclean -C ./Libft

fclean: clean
	$(RM) $(NAME)

re: fclean all