/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:54:37 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/03 13:15:21 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static long			ft_atol(const char *str)
{
	unsigned long	res;
	long			sign;
	char			*s;
	unsigned long	cutoff;

	res = 0;
	s = (char *)str;
	while (*s == ' ' || *s == '\t' || *s == '\n' \
			|| *s == '\r' || *s == '\v' || *s == '\f')
		s++;
	cutoff = 922337203685477580L;
	sign = (*s == '-') ? -1 : 1;
	s += (*s == '-' || *s == '+') ? 1 : 0;
	while (*s >= '0' && *s <= '9')
	{
		if (res >= cutoff || (res == cutoff && (((*s - '0') > 7 && sign == 1) \
						|| ((*s - '0') > 8 && sign == -1))))
		{
			res = (sign == -1) ? -9223372036854775808U : 9223372036854775807L;
			return ((long)res);
		}
		res = res * 10 + *s - '0';
		s++;
	}
	return ((long)res * sign);
}

static int			check_coords(char *coords)
{
	t_unint spaces;

	spaces = 0;
	if (!coords)
		return (0);
	if (*coords == '#')
		return (0);
	if (*coords && *coords == '-')
		coords++;
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
	if (!parse || !*(parse + 1) || !(check_coords(parse + 1)))
	{
		free(room);
		(line) ? free(line) : 0;
		ft_error(*env);
	}
	parse = parse + 1;
	while (i < 2)
	{
		room->coords[i] = ft_atol(parse);
		if (((room->coords[i] < 0) && ((*env)->f & CHECK_NEG_FL))\
		|| room->coords[i] > 2147483647 || room->coords[i] < -2147483648)
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

t_room				*get_room(char *line, t_env **env, short comm)
{
	t_room			*room;
	static t_unint	index = 0;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		err_out(0, line, *env);
	room->name = 0;
	room = (!comm) ? get_room_coord(line, room, env, 0) : room;
	(!comm) ? *(ft_strchr(line, ' ')) = '\0' : 0;
	room->name = ft_strdup(line);
	room->index = (comm) ? 4294967295U : index;
	room->comment = comm;
	if (room->name[0] == 'L' || (!comm &&\
	!(ft_set_htval((*env)->ht, line, room->coords, index)))\
	|| (((*env)->f & CHECK_FL) && !comm &&\
	!ft_set_htval((*env)->coor_ht, line, room->coords, -42)))
	{
		free(line);
		free(room->name);
		free(room);
		ft_error(*env);
	}
	index += (comm) ? 0 : 1;
	return (room);
}

int					list_empty(t_node *list)
{
	return (list ? 0 : 1);
}
