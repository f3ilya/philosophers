SRCS	= philo_bonus.c\
                     	utils_bonus.c
OBJS	= ${SRCS:.c=.o}
NAME	= philo_bonus

HDRS	= -I philo_bonus.h

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror ${HDRS}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				${CC} ${HDRS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
