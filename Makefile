NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRC = philo.c utils.c getters.c init.c actions.c actions_utils.c forks.c threads.c routine.c \
     log_utils.c monitor.c monitor_utils.c sim_utils.c timing.c special_cases.c
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
