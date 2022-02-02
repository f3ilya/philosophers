SRCS	= philo.c\
                     	utils.c
OBJS	= ${SRCS:.c=.o}
NAME	= philo

HDRS	= -I philo.h

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
