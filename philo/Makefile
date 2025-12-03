###	ARGUMENTS	###
NAME		= philo
CFLAGS		= -Wall -Werror -Wextra
CC			= cc
DBGFLAGS	:= -g3

###	SOURCES		###
SRCS		= init.c\
			main.c\
			monitor.c\
			routine.c\
			utils.c\
			print.c\

OBJS		= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

###	RULES		###
all	: ${NAME}

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)
	@printf "Compiled ✅\n"

clean	:
	rm -f ${OBJS}
	@printf "Clean 🧹\n"

fclean	: clean
	rm -f ${NAME}
	@printf "Big Clean 🧼\n"

re	: fclean all

val :          ### use : make val ARGS="5 800 200 200 7"  
	$(CC) ${DBGFLAGS} -o $(NAME)  $(SRCS)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

data_races :
	$(CC) ${DBGFLAGS} -o $(NAME)  $(SRCS)
	valgrind  --tool=helgrind ./$(NAME) $(ARGS)

.PHONY	: all clean fclean re val data_races