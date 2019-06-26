/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:49:43 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/26 21:24:08 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static t_node	**init_ants_arr(t_node **p_arr, t_bfs *bs, int i, int j)
{
	t_node	**ants_arr;
	int count = 0;

	if (!(ants_arr = init_nodes_arr(bs->ants)))
		return (NULL);
	while (i < bs->ants)
	{
		if ((p_arr[j] && !count) \
		|| (count && p_arr[j] &&\
		list_size(p_arr[j]) < list_size(p_arr[0]) + ((bs->ants <= 75) ? 3 : 6)))
			ants_arr[i] = p_arr[j++];
		else
		{
			j = 0;
			ants_arr[i] = p_arr[j++];
			if (i > bs->ants / 2)
				count = 1;
		}
		i++;
	}
	return (ants_arr);
}

static int		print_ant_move(int *rooms, t_node **ants, int i, int j)
{
	int ret;

	ret = 0;
	if (i - 1 >= j)
		ft_printf(" ");
	if (ants[i]->next && ants[i + 1] && ants[i + 1]->next
		&& NXTIND(ants[i + 1]) == NXTIND(ants[i])\
		&& CURRIND(ants[i]) == CURRIND(ants[i + 1]))
		ret = 1;
	rooms[CURRIND(ants[i])]--;
	ft_printf("L%d-%s", i + 1, ants[i]->next->data->name);
	rooms[NXTIND(ants[i])]++;
	ants[i] = ants[i]->next;
	return (ret);
}

void			print_moves(t_node **p_arr, t_bfs *bs, int i, int j)
{
	int		*rooms;
	t_node	**ants;

	rooms = init_rooms(bs->vrt, START, bs->ants);
	ants = init_ants_arr(p_arr, bs, 0, 0);
	while (rooms[END] != bs->ants)
	{
		j = 0;
		while (!ants[j]->next || (rooms[NXTIND(ants[j])]\
		&& NXTIND(ants[j]) != END))
			j++;
		i = j - 1;
		while (++i < bs->ants)
			if (ants[i] && ants[i]->next && rooms[CURRIND(ants[i])] && \
			(!rooms[NXTIND(ants[i])] || (NXTIND(ants[i]) == END)))
				if (st_moves_ch(ants, rooms, bs, &i) && 
					print_ant_move(rooms, ants, i, j) && ants[i] &&\
					!ants[i]->next && NXTIND(ants[i + 1]) == END)
					break ;
		ft_printf("\n");
	}
	free(ants);
	free(rooms);
}

static void		print_rooms(t_list *start, t_list *end,
										t_list *rooms)
{
	while (rooms)
	{
		ft_putstr(((t_room *)rooms->content)->name);
		if (!ft_strcmp(((t_room *)rooms->content)->name, "##start"))
			ft_printf("\n%s %d %d", ((t_room *)start->content)->name,
									((t_room *)start->content)->coords[0],
									((t_room *)start->content)->coords[1]);
		if (!ft_strcmp(((t_room *)rooms->content)->name, "##end"))
			ft_printf("\n%s %d %d", ((t_room *)end->content)->name,
									((t_room *)end->content)->coords[0],
									((t_room *)end->content)->coords[1]);
		if (!((t_room *)rooms->content)->comment)
		{
			write(1, " ", 1);
			ft_putnbr(((t_room *)rooms->content)->coords[0]);
			write(1, " ", 1);
			ft_putnbr(((t_room *)rooms->content)->coords[1]);
		}
		write(1, "\n", 1);
		rooms = rooms->next;
	}
}

void			print_res(t_env *e,t_node **p_arr, t_bfs *bs)
{
	t_list *rooms;
	t_list *links;

	rooms = e->list;
	links = e->links;
	print_rooms(e->start, e->end, rooms);
	while (links)
	{
		ft_putendl(links->content);
		links = links->next;
	}
	write(1, "\n", 1);
	print_moves(p_arr, bs, 0, 0);
	if (bs->debug)
		debug_controller(bs, e->ht, p_arr, e->f);
}
