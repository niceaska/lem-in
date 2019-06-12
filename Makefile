# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgigi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/10 18:28:17 by lgigi             #+#    #+#              #
#    Updated: 2019/06/10 18:34:28 by lgigi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = lem-in
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = ./libft/
INC = includes/
SRC_DIR = ./srcs/
FILES =  find_paths.c  ft_free.c  ft_init.c  ft_queue.c  list_utils.c  shortest_path.c
SRCS = $(addprefix $(SRC_DIR), $(FILES))
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	make -C libft
	$(CC) $(CFLAGS) -c $(SRCS) -I $(INC) -I $(LIBFT_DIR)$(INC)
	$(CC) $(CFLAGS) $(OBJS) -o  $(NAME) -L libft/ -lft

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re