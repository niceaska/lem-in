/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:52:29 by jschille          #+#    #+#             */
/*   Updated: 2019/06/15 20:05:42 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"

#define unint unsigned int

// typedef struct	s_list t_list;

// struct			s_list
// {
// 	void	*data;
// 	size_t	size;
// 	t_list	*next;
// };
typedef struct	s_link
{
	int	i;
	int	p;
}				t_link;

typedef struct	s_room
{
	char	*name;
	unint	index;
}				t_room;

typedef struct  s_env
{
	unint	ants;
	t_list	*list;
	t_list	*start;
	t_list	*end;
	t_link	*links;
}				t_env;

void			err_out(int e);

/*	Parser */
t_env			*parser(char *file);
void			set_rooms(char *line, t_env *env);
void			parser_comment(char *line, t_env *env);
void			set_ants(char *line, t_env *env);
void			set_links(char *line, t_env *env);
t_room	*get_room(char *line);
#endif
