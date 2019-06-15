/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:22:55 by jschille          #+#    #+#             */
/*   Updated: 2019/06/15 20:37:40 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_ants(char *line, t_env *env)
{
	unint	i;

	printf("SET_ANTS %p\n", env);
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			err_out(3);
		++i;
	}
	env->ants = ft_atoi(line);
}

static void	set_soe(t_env *env, char c)
{
	char *line;

	get_next_line(0, &line);
	if (c == 's')
	{
		if (env->start)
			err_out(4);
		env->start = ft_lstnew((void*)get_room(line), 0);
		printf("SET_SOE %p\n", env->start);
	}
	else if (c == 'e')
	{
		if (env->end)
			err_out(4);
		env->end = ft_lstnew((void*)get_room(line), 1);
	}
}

void	parser_comment(char *line, t_env *env)
{
	if (ft_strcmp(line, "##Start\n") == 0)
		set_soe(env, 's');
	else if (ft_strcmp(line, "##End\n") == 0)
		set_soe(env, 'e');
}

t_room	*get_room(char *line)
{
	t_room			*room;
	static unint	index = 0;

	printf("GET_ROOM\n");
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		err_out(0);
	room->name = ft_strdup(line);
	room->index = index;
	++index;
	printf("ROOM %p\n", room);
	return (room);
}

void	set_rooms(char *line, t_env *env)
{
	static size_t	i = 2;
	t_list	*ptr;

	printf("SET_ROOMS %p\n", env->list);
	if (env->list == NULL)
	{
		env->list = ft_lstnew(get_room(line), i);
		return ;
	}
	ptr = env->list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ft_lstnew(get_room(line), i);
	printf("SET_ROOMS S = %d\n", ((t_room*)env->list->content)->index);
	++i;
}

void	set_links(char *line, t_env *env)
{

}