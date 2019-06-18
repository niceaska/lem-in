/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:32:55 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/18 18:17:05 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

void ft_addedge(t_node **arr, t_data *start, t_data *end) 
{ 
	push_back(&(arr[start->index]), end); 
	push_back(&(arr[end->index]), start); 
}

t_data	*init_data(char *name, int index)
{
	t_data *data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->name = ft_strdup(name);
	data->index = index;
	return (data);
}

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

t_room	*get_room(char *line, t_env **env)
{
	t_room			*room;
	static unint	index = 0;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		err_out(0, line, *env);
	room->name = 0;
	room = get_room_coord(line, room, env, 0);
	*(ft_strchr(line, ' ')) = '\0';
	room->name = ft_strdup(line);
	room->index = index;
	if (!(ft_set_htval((*env)->ht, line, index)))
	{
		free(room);
		ft_error(*env);
	}
	++index;
	return (room);
}
