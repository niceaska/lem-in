/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:49:43 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/15 15:59:53 by lgigi            ###   ########.fr       */
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

static void		print_ant_move(int *rooms, t_bfs *bs, t_node **ants, int i)
{
	if (rooms[ants[i]->data->index] && \
		(!rooms[ants[i]->next->data->index] \
		|| ants[i]->next->data->index == bs->end->index))
	{
		rooms[ants[i]->data->index]--;
		ft_printf("L%d-%s", i + 1, ants[i]->next->data->name);		
		rooms[ants[i]->next->data->index]++;
		ants[i] = ants[i]->next;
		if (ants[i + 1] && (!rooms[ants[i + 1]->next->data->index]\
		|| ants[i + 1]->next->data->index == bs->end->index))
			ft_printf(" ");
	}
}

void			print_moves(t_node **p_arr, t_bfs *bs)
{
	int		*rooms;
	int		i;
	t_node	**ants;

	i = 0;
	if (!(rooms = (int *)malloc(sizeof(int) * bs->vrt)))
		return ;
	while (i < bs->vrt)
		rooms[i++] = 0;
	rooms[bs->start->index] = bs->ants;
	ants = init_ants_arr(p_arr, bs->ants);
	while (rooms[bs->end->index] != bs->ants)
	{
		ft_printf("\n");
		i = rooms[bs->end->index];
		while (i < bs->ants)
		{
			print_ant_move(rooms, bs, ants, i);
			i++;
		}
	}
	ft_printf("\n");
	free(ants);
	free(rooms);
}