/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:22:55 by jschille          #+#    #+#             */
/*   Updated: 2019/06/18 15:26:02 by lgigi            ###   ########.fr       */
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
			err_out(3, env);
		++i;
	}
	env->ants = ft_atoi(line);
}

static void	set_soe(t_env *env, char c)
{
	char	*line;
	t_room	*room;

	get_next_line(0, &line);
	if (c == 's')
	{
		if (env->start)
			err_out(4, env);
		room = get_room(line, &env);
		env->start = ft_lstnew(room, sizeof(*room));
		free(room);
	}
	else if (c == 'e')
	{
		if (env->end)
			err_out(4, env);
		room = get_room(line, &env);
		env->end = ft_lstnew(room, sizeof(*room));
		free(room);
	}
	(line) ? free(line) : 0;
}

void	parser_comment(char *line, t_env *env)
{
	if (ft_strcmp(line, "##start") == 0)
		set_soe(env, 's');
	else if (ft_strcmp(line, "##end") == 0)
		set_soe(env, 'e');
}

void	set_rooms(char *line, t_env *env)
{
	t_list	*ptr;
	t_room	*room;
	static size_t	i = 2;

	if (env->list == NULL)
	{
		room = get_room(line, &env);
		env->list = ft_lstnew(room, sizeof(*room));
		free(room);
		return ;
	}
	ptr = env->list;
	while (ptr->next)
		ptr = ptr->next;
	room = get_room(line, &env);
	ptr->next = ft_lstnew(room, sizeof(*room));
	free(room);
	++i;
}

void	set_links(char *line, t_env **env)
{
	t_list	*ptr;

	if (!(*env)->start || !(*env)->end)
	{
		free(line);
		ft_error(*env);
	}
	if ((*env)->links == NULL)
	{
		(*env)->links = ft_lstnew(line, ft_strlen(line) + 1);
		return ;
	}
	ptr = (*env)->links;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = ft_lstnew(line, ft_strlen(line) + 1);
}