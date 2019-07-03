/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:32:55 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/03 17:37:01 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

int				ft_addedge(t_node **arr, t_data *start, t_data *end)
{
	int ret;

	ret = 1;
	if (!(push_back(&(arr[start->index]), end, 1)))
		ret--;
	if (!(push_back(&(arr[end->index]), start, 1)))
		ret--;
	return ((ret < 0) ? 0 : ret);
}

t_data			*init_data(char *name, int index)
{
	t_data *data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->name = ft_strdup(name);
	data->index = index;
	return (data);
}

int				*init_rooms(int vrt, int start_index, int ants)
{
	int		i;
	int		*rooms;

	i = 0;
	if (!(rooms = (int *)malloc(sizeof(int) * vrt)))
		return (NULL);
	while (i < vrt)
		rooms[i++] = 0;
	rooms[start_index] = ants;
	return (rooms);
}

static void		add_to_debug_arr(t_node *list, t_bfs **bs, int i)
{
	t_data	*d;

	if (!list || !list->next)
		return ;
	d = init_data(list->next->data->name, NXTIND(list));
	push_back(&((*bs)->debug[i]), d, 0);
}

int				st_moves_ch(t_node **ants, int *rooms, t_bfs *bs, int *i)
{
	int		j;
	t_node	*temp;

	j = 0;
	if (ants[*i] && CURRIND(ants[*i]) == START)
		while (ants[j] && j != *i && (CURRIND(ants[j]) != START\
				|| !rooms[NXTIND(ants[j])] || \
				!ants[j]->next || NXTIND(ants[j]) == END))
			j++;
	if (j < *i && ants[j] && j != 0)
	{
		temp = ants[*i];
		ants[*i] = ants[j];
		ants[j] = temp;
		*i = j;
	}
	if (bs->debug)
		add_to_debug_arr(ants[*i], &bs, *i);
	return (1);
}
