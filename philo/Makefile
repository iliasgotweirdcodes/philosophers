
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
INCLUDE = philo.h
RM = rm -f

SRCS = philo.c parsing.c utils.c routine.c free.c time.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
