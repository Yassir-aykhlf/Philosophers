NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = philo.c utils.c getters.c init.c
OBJ = $(SRC:.c=.o)
HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
