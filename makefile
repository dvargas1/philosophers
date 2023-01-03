# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 08:03:05 by dvargas           #+#    #+#              #
#    Updated: 2022/12/22 12:34:11 by dvargas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			parse.c \
			print.c \
			ignite.c \
			reaper.c \
			routine.c \
			threads.c \
			free.c

OBJS		= ${SRCS:%.c=%.o}
NAME		= philo
CC			= cc
CCFLAGS		= -g -Wall -Wextra -Werror

all:		${NAME}

$(NAME):	${OBJS}
			@ echo 'Creating the monster ${NAME}'
			@ ${CC} ${CCFLAGS} ${OBJS} ${LIB} -o ${NAME}
			@ echo 'ITS ALIVE!!!!!!!!!'

%.o: %.c
			@ ${CC} ${CCFLAGS} -c $< -o $@

clean:
			@ echo 'clean rule'
			@ rm -f ${OBJS} bonus.o
			@ echo ' '

fclean:		clean
			@ echo 'Removing ${NAME}'
			@ rm -f ${NAME}
			@ echo ' '

re:			fclean all
			@ echo 're rule done'
			@ echo ' '

.PHONY:		all clean fclean re run
