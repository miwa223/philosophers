NAME = philo
CC = gcc
INC = includes
CFLAGS = -Wall -Wextra -Werror -I$(INC)
SRCS = srcs/main.c srcs/init.c srcs/action.c srcs/fork_operation.c\
		srcs/print_msg.c srcs/monitor.c srcs/free.c \
		srcs/utils/ft_atoi.c srcs/utils/ft_isdigit.c \
		srcs/utils/ft_strlen.c srcs/utils/get_time.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
