# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 15:52:53 by hmickey           #+#    #+#              #
#    Updated: 2022/02/19 23:28:55 by hmickey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ProxyServer

INCLUDE		=	./srcs/

SRCS		=	./srcs/Server.cpp \
				./srcs/Client.cpp

OBJS		= ${SRCS:.cpp=.o}

CXX			= c++

RM			= rm -f

CPPFLAGS	= #-Wall -Wextra -Werror 

all:			${NAME}

$(NAME):		${OBJS} ${INCLUDE}
				${CXX} ./srcs/Server.o -o server
				${CXX} ./srcs/Client.o -o client

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} server client

re:				fclean all

.PHONY:			all clean fclean re