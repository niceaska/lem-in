/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:54:37 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/19 17:44:16 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static int	check_coords(char *coords)
{
	unint spaces;

	spaces = 0; 
	if (!coords)
		return (0);
	if (*coords == '#')
		return (0);
	while (*coords)
	{
		if (!ft_isspace(*coords)\
			&& !ft_isdigit(*coords))
			return (0);
		else if (ft_isspace(*coords))
			spaces++;
		coords++;
	}
	return ((!spaces || spaces > 1) ? 0 : 1);
}

static t_room		*get_room_coord(char *line, t_room *room,
									t_env **env, int i)
{
	char	*parse;

	parse = ft_strchr(line, ' ');
	if (!parse || !*(parse + 1) \
		|| !(check_coords(parse + 1)))
	{
		free(room);
		(line) ? free(line) : 0;
		ft_error(*env);
	}
	parse = parse + 1;
	while (i < 2)
	{
		if ((room->coords[i] = ft_atoi(parse)) < 0)
		{
			free(room);
			(line) ? free(line) : 0;
			ft_error(*env);
		}
		parse = ft_strchr(parse, ' ');
		i++;
	}
	return (room);
}

t_room	*get_room(char *line, t_env **env, short comm)
{
	t_room			*room;
	static unint	index = 0;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		err_out(0, line, *env);
	room->name = 0;
	room = (!comm) ? get_room_coord(line, room, env, 0) : room;
	(!comm) ? *(ft_strchr(line, ' ')) = '\0' : 0;
	room->name = ft_strdup(line);
	room->index = (comm) ? 4294967295U : index;
	room->comment = comm;
	if (!comm && !(ft_set_htval((*env)->ht, line, index)))
	{
		free(line);
		free(room->name);
		free(room);
		ft_error(*env);
	}
	index += (comm) ? 0 : 1;
	return (room);
}
