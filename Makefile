NAME = philo

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
LDFLAGS = -pthread

SRC = philo.c utils.c getters.c init.c simulation.c special_cases.c
OBJ = $(SRC:.c=.o)
HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
