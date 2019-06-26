/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:06:48 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/26 21:12:57 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

void			refresh_bfs(t_node **p_arr, t_bfs **bs)
{
	int		i;
	t_node	*list;

	init_bfs_arr(bs);
	i = 0;
	while (p_arr[i])
	{
		list = p_arr[i];
		while (list)
		{
			(*bs)->v[list->data->index] = 1;
			list = list->next;
		}
		i++;
	}
	(*bs)->v[(*bs)->end->index] = 0;
}

void			ft_find_path(t_node **p_arr, t_bfs *bs, int i)
{
	t_node	*path;
	int		crawl;

	path = 0;
	crawl = bs->end->index;
	push_back(&path, bs->end, 0);
	while (bs->p[crawl] != NULL)
	{
		list_push(&path, bs->p[crawl]);
		crawl = bs->p[crawl]->index;
	}
	while (!list_empty(path))
		push_back(&p_arr[i], list_pop(&path), 0);
	free_list(path);
}

t_node			**get_all_paths(t_node **p_arr, int i, t_node **arr, t_bfs *bs)
{
	if (!bfs(arr, bs) || i >= bs->ants)
		return (p_arr);
	if (i != 0 && (bs->d[bs->end->index] > (int)(list_size(p_arr[0]) * 2 - 1)))
		return (p_arr);
	ft_find_path(p_arr, bs, i);
	refresh_bfs(p_arr, &bs);
	return (get_all_paths(p_arr, i + 1, arr, bs));
}

void			set_is_hold(t_node *list,
								t_node **arr, int hold)
{
	t_node *trav;

	while (list->next)
	{
		trav = arr[CURRIND(list)];
		while (trav)
		{
			if (CURRIND(trav) == NXTIND(list))
			{
				trav->is_hold = hold;
				trav->data->w = -1;
			}
			trav = trav->next;
		}
		list = list->next;
	}
}

void				list_cmp(t_node *list1, t_node *list2, t_node **arr)
{
	t_node *trav;

	while (list1->next)
	{
		trav = list2;
		while (trav->next)
		{
			if (CURRIND(list1) == NXTIND(trav)\
			&& CURRIND(trav) == NXTIND(list1))
			{
				t_node *node = arr[CURRIND(list1)];
				while (node)
				{
					if (CURRIND(node) == CURRIND(trav))
						node->is_hold = 2;
					node = node->next;
				}
				node = arr[CURRIND(trav)];
				while (node)
				{
					if (CURRIND(node) == CURRIND(list1))
						node->is_hold = 2;
					node = node->next;
				}
			}
			trav = trav->next;
		}
		list1 = list1->next;
	}
}

void			find_crosses(t_node **arr, t_node **p_arr)
{
	int		i;
	int		j;


	i = 0;
	while (p_arr[i])
	{
		j = i + 1;
		while (p_arr[j])
		{
			list_cmp(p_arr[i], p_arr[j], arr);

			j++;
		}
		i++;
	}
}

t_node			**get_paths_controller(t_node **arr, t_bfs *bs, int i, int j)
{
	t_node	**p_arr;

	j++;
	bs->stage = 0;
	p_arr = init_nodes_arr(100000);
	while (bfs(arr, bs))
	{
		if (i >= bs->ants)
			break ;
		ft_find_path(p_arr, bs, i);
		set_is_hold(p_arr[i], arr, 1);
		init_bfs_arr(&bs);
		i++;
	}
	find_crosses(arr, p_arr);
	bs->stage++;
	init_bfs_arr(&bs);
	free_list_arr(p_arr, bs->ants, 0);
	p_arr = init_nodes_arr(bs->ants);
	p_arr = get_all_paths(p_arr, 0, arr, bs);
	return (p_arr);
}
