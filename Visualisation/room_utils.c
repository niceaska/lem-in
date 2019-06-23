/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:54:37 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/23 16:46:29 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

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

t_room	*get_room(char *line, t_env **env, short comm)
{
	t_room			*room;
	static unint	index = 0;
	char			**split;

	printf("Get_room start line: %s\n", line);

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		err_out(0, line, *env);
	split = ft_strsplit(line, ' ');
	room->name = ft_strdup(split[0]);
	room->index = index;
	room->coords[0] = ft_atoi(split[1]);
	room->coords[1] = ft_atoi(split[2]);
	room->links = NULL;
	free(split[0]);
	free(split[1]);
	free(split[2]);
	//room->comment = comm;
	// if (!comm && !(ft_set_htval((*env)->ht, line, index)))
	// {
	// 	free(line);
	// 	free(room->name);
	// 	free(room);
	// 	ft_error(*env);
	// }
	// index += (comm) ? 0 : 1;
	++index;
	return (room);
}
