/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:22:55 by jschille          #+#    #+#             */
/*   Updated: 2019/06/19 19:34:56 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"

void	set_ants(char *line, t_env **env)
{
	unint	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			err_out(3, line, *env);
		++i;
	}
	if (!((*env)->ants = ft_atoi(line)))
		err_out(3, line, *env);
	set_rooms(line, env, 1);
}

static void	set_soe(t_env **env, char c)
{
	char	*line;
	t_room	*room;

	get_next_line(0, &line);
	if (c == 's')
	{
		if ((*env)->start != NULL)
			err_out(4, line, *env);
		room = get_room(line, env, 0);
		(*env)->start = ft_lstnew(room, sizeof(*room));
		free(room);
	}
	else if (c == 'e')
	{
		if ((*env)->end != NULL)
			err_out(4, line, *env);
		room = get_room(line, env, 0);
		(*env)->end = ft_lstnew(room, sizeof(*room));
		free(room);
	}
	(line) ? free(line) : 0;
}

void	parser_comment(char *line, t_env **env)
{
	if (line && !ft_strcmp(line, "##start"))
	{
		set_soe(env, 's');
		set_rooms(line, env, 1);
	}
	else if (line && !ft_strcmp(line, "##end"))
	{
		set_soe(env, 'e');
		set_rooms(line, env, 1);
	}
	else
		set_rooms(line, env, 1);

}

void	set_rooms(char *line, t_env **env, short fl)
{
	t_list	*ptr;
	t_room	*room;
	static size_t	i = 2;

	if ((*env)->list == NULL)
	{
		room = get_room(line, env, fl);
		(*env)->list = ft_lstnew(room, sizeof(*room));
		free(room);
		return ;
	}
	ptr = (*env)->list;
	while (ptr->next)
		ptr = ptr->next;
	room = get_room(line, env, fl);
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