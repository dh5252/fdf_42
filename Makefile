# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 16:24:19 by cahn              #+#    #+#              #
#    Updated: 2023/08/08 21:15:05 by cahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = draw.c ft_split.c get_next_line.c get_next_line_utils.c main.c parsing.c utility.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIB = -lmlx -framework OpenGL -framework Appkit
RM = rm -rf

all: $(NAME)
%.o : %.c
	$(CC) $(CFLAGS)  -c $< -o $@
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(CLIB) $(SRCS) -o $(NAME)
# install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re:	fclean all

.PHONY: all clean fclean re
