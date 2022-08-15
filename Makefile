# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgretche <cgretche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 08:49:01 by cgretche          #+#    #+#              #
#    Updated: 2022/05/02 15:34:46 by cgretche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

SRCS			=	main.c ft_simulate.c utils.c \

HEADER			=	philo.h

OBJS			=	$(SRCS:%.c=%.o)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(HEADER)
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o 			:	%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					@rm -f $(OBJS)

fclean			:	clean
					@$(RM) $(NAME)

re				:	fclean all