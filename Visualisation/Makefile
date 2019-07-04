# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschille <jschille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 12:09:02 by jschille          #+#    #+#              #
#    Updated: 2019/07/04 11:29:32 by lgigi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= vis-hex
FLAGS		= -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit
INCLUDES	= ../libft/includes
SRCS		= cleaner.c doit.c hooker.c modiffy.c parser.c scaleble.c set_mim_max.c display.c draw_line.c main.c moveble.c room_utils.c set_color.c setters.c
OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	make -C ../libft
	gcc $(FLAGS) $(SRCS)  -o $(NAME)  -I $(INCLUDES) -L ../libft/ -lft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
