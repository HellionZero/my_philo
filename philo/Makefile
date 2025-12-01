NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
RESET := \033[0m # Resets all formatting

SRC = main.c \
		forks.c \
		init.c \
		monitor.c \
		philo_utils.c \
		philo.c \
		time_utils.c \
		validator.c \

OBJ = $(SRC:.c=.o)
RF = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) -pthread
	@echo "$(GREEN)$(NAME) Compiled!$(RESET)"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RF) $(OBJ)

fclean: clean
	$(RF) $(NAME)

re: fclean all

.PHONY:
	all clean fclean re

