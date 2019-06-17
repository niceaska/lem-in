/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:22:55 by jschille          #+#    #+#             */
/*   Updated: 2019/06/17 20:38:40 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"

void	set_ants(char *line, t_env *env)
{
	unint	i;

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
	printf("line = %s\n", line);
	if (c == 's')
	{
		if (env->start)
			err_out(4);
		env->start = ft_lstnew(get_room(line, &env), sizeof(t_room));
		free(line);
	}
	else if (c == 'e')
	{
		if (env->end)
			err_out(4);
		env->end = ft_lstnew(get_room(line, &env), sizeof(t_room));
		free(line);
	}
}

void	parser_comment(char *line, t_env *env)
{
	if (ft_strcmp(line, "##start") == 0)
		set_soe(env, 's');
	else if (ft_strcmp(line, "##end") == 0)
		set_soe(env, 'e');
}

t_room	*get_room(char *line, t_env **env)
{
	t_room			*room;
	static unint	index = 0;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		err_out(0);
	if (*line)
		*(ft_strchr(line, ' ')) = '\0';
	room->name = ft_strdup(line);
	room->index = index;
	if (*line)
		ft_set_htval((*env)->ht, line, index);
	++index;
	return (room);
}

void	set_rooms(char *line, t_env *env)
{
	static size_t	i = 2;
	t_list	*ptr;

	if (env->list == NULL)
	{
		env->list = ft_lstnew(get_room(line, &env), sizeof(t_room));
		return ;
	}
	ptr = env->list;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ft_lstnew(get_room(line, &env), sizeof(t_room));
	++i;
}

void	set_links(char *line, t_env **env)
{
	t_list	*ptr;

	if (!(*env)->start || !(*env)->end)
	{
		// error
	}
	if ((*env)->links == NULL)
	{
		(*env)->links = ft_lstnew(line, ft_strlen(line));
		return ;
	}
	ptr = (*env)->links;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ft_lstnew(line, ft_strlen(line));
}