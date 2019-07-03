/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:46:57 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/03 17:34:48 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

int				fake_print_ant_move(int *rooms, t_node **ants, int i)
{
	int ret;

	ret = 0;
	if (ants[i]->next && ants[i + 1] && ants[i + 1]->next
		&& NXTIND(ants[i + 1]) == NXTIND(ants[i])\
		&& CURRIND(ants[i]) == CURRIND(ants[i + 1]))
		ret = 1;
	rooms[CURRIND(ants[i])]--;
	rooms[NXTIND(ants[i])]++;
	ants[i] = ants[i]->next;
	return (ret);
}

int				count_way(t_bfs *bs, t_node **p_arr, int i)
{
	int		*rooms;
	t_node	**ants;

	bs->w_count = 0;
	rooms = init_rooms(bs->vrt, START, bs->ants);
	ants = init_ants_arr(p_arr, bs, 0, 0);
	while (rooms[END] != bs->ants)
	{
		i = -1;
		while (++i < bs->ants)
			if (ants[i] && ants[i]->next && rooms[CURRIND(ants[i])] && \
			(!rooms[NXTIND(ants[i])] || (NXTIND(ants[i]) == END)))
				if (fake_print_ant_move(rooms, ants, i))\
					if (ants[i] && !ants[i]->next && NXTIND(ants[i + 1]) == END)
						break ;
		bs->w_count++;
		if (bs->w_count > bs->ants)
			break ;
	}
	free(ants);
	free(rooms);
	return (bs->w_count);
}

int				best_way(t_bfs *bs, t_node **p1, t_node **p2)
{
	int w1;
	int w2;

	w1 = 0;
	w2 = 0;
	bs->stage = 2;
	w1 = count_way(bs, p1, -1);
	w2 = count_way(bs, p2, -1);
	if (w1 > w2)
		return (1);
	return (0);
}
