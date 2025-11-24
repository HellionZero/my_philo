NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c \

OBJ = $(SRC:.c=.o)
RF = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RF) $(OBJ)

fclean: clean
	$(RF) $(NAME)

re: fclean all

.PHONY:
	all clean fclean re

