/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:49:43 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/17 16:03:17 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static t_node	**init_ants_arr(t_node **p_arr, int ants)
{
	t_node	**ants_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(ants_arr = init_nodes_arr(ants)))
		return (NULL);
	while (i < ants)
	{
		if (p_arr[j])
		{
			ants_arr[i] = p_arr[j++];
		}
		else
		{
			j = 0;
			ants_arr[i] = p_arr[j++];
		}
		i++;
	}
	return (ants_arr);
}

static void		print_ant_move(int *rooms, t_node **ants, int i, int j)
{
	if (i - 1 >= j)
		ft_printf(" ");
	rooms[ants[i]->data->index]--;
	ft_printf("L%d-%s", i + 1, ants[i]->next->data->name);		
	rooms[ants[i]->next->data->index]++;
	ants[i] = ants[i]->next;
}

static int		*init_rooms(int vrt, int start_index, int ants)
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

void			print_moves(t_node **p_arr, t_bfs *bs)
{
	int		*rooms;
	int		i;
	int		j;
	t_node	**ants;

	rooms = init_rooms(bs->vrt, bs->start->index, bs->ants);
	ants = init_ants_arr(p_arr, bs->ants);
	ft_printf("\n");
	while (rooms[bs->end->index] != bs->ants)
	{
		j = 0;
		while (!ants[j]->next)
			j++;
		i = j;
		while (i < bs->ants)
		{
			if (ants[i] && ants[i]->next && rooms[ants[i]->data->index] && \
			(!rooms[ants[i]->next->data->index] \
			|| (ants[i]->next->data->index == bs->end->index)))
				print_ant_move(rooms, ants, i, j);
			i++;
		}
		ft_printf("\n");
	}
	free(ants);
	free(rooms);
}