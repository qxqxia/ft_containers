# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 11:38:22 by qxia              #+#    #+#              #
#    Updated: 2023/03/14 16:44:01 by qxia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ft_containers

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)

%.o : %.cpp
	$(CC) $(CFLAGS) $< -c 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

all : $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
r : re
	./$(NAME)

re: fclean all

.PHONY: all clean fclean re
