/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:49:43 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/18 15:52:00 by lgigi            ###   ########.fr       */
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

void			print_moves(t_node **p_arr, t_bfs *bs, int i, int j)
{
	int		*rooms;
	t_node	**ants;

	rooms = init_rooms(bs->vrt, bs->start->index, bs->ants);
	ants = init_ants_arr(p_arr, bs->ants);
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

static void		print_rooms_links(t_list *rooms, t_list *links)
{
	while (rooms)
	{
		ft_putstr(((t_room *)rooms->content)->name);
		write(1, " ", 1);
		ft_putnbr(((t_room *)rooms->content)->coords[0]);
		write(1, " ", 1);
		ft_putnbr(((t_room *)rooms->content)->coords[1]);
		write(1, "\n", 1);
		rooms = rooms->next;
	}
	while (links)
	{
		ft_putendl(links->content);
		links = links->next;
	}
}

void	print_res(t_env *e, t_node **p_arr, t_bfs *bs)
{
	t_list *rooms;
	t_list *links;

	rooms = e->list;
	links = e->links;
	ft_putnbr(e->ants);
	write(1, "\n", 1);
	ft_printf("##start\n%s %d %d\n", ((t_room *)e->start->content)->name,
									((t_room *)e->start->content)->coords[0],
									((t_room *)e->start->content)->coords[1]);
	ft_printf("##end\n%s %d %d\n", ((t_room *)e->end->content)->name,
									((t_room *)e->end->content)->coords[0],
									((t_room *)e->end->content)->coords[1]);
	print_rooms_links(rooms, links);
	write(1, "\n", 1);
	return (print_moves(p_arr, bs, 0, 0));
}
