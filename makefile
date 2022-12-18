# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvargas <dvargas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 08:03:05 by dvargas           #+#    #+#              #
#    Updated: 2022/12/15 17:31:57 by dvargas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			parse.c

OBJS		= ${SRCS:%.c=%.o}
NAME		= philosophers
CC			= cc
CCFLAGS	= -g -Wall -Wextra -Werror
ARGS		= 10 1 1 1 1

all:		${NAME}

$(NAME):	${OBJS}
			@ echo 'Creating the monster ${NAME}'
			@ ${CC} ${CCFLAGS} ${OBJS} ${LIB} -o ${NAME}
			@ echo ' '
			@ echo 'ITS ALIVE!!!!!!!!!'
			@ echo ' '

%.o: %.c
			${CC} ${CCFLAGS} -c $< -o $@
			@ echo ' '

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

run:		all
			@ echo ' '
			./${NAME} ${ARGS}
			@ echo ' '
.PHONY:		all clean fclean re run
