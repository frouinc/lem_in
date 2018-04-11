# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/25 16:12:57 by kda-silv          #+#    #+#              #
#    Updated: 2017/10/31 17:12:57 by kda-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in

SRCS		=	srcs/main.c \
				srcs/get_data.c \
				srcs/delete.c \
				srcs/ft_split_string.c \
				srcs/create_room.c \
				srcs/check_error.c \
				srcs/create_tube.c \
				srcs/resolve.c \
				srcs/take_color.c \
				srcs/safe_gnl.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wextra -Wall -I./includes/

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -C libft
				gcc $(OBJS) -o $(NAME) -L./libft -lft

test:
				gcc srcs/resolve.c srcs/main_test.c srcs/delete.c -o $(NAME) -L./libft -lft -I./includes

clean:
				@make clean -C libft
				rm -rf $(OBJS)

fclean:			clean
				rm -rf libft/libft.a
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
