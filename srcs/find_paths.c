/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:06:48 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/02 18:58:11 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

int				find_min_index(int *paths, int p_count)
{
	int		min_ind;
	int		min;
	int		i;

	i = 0;
	min_ind = 0;
	min = 2147483647;
	while (i < p_count)
	{
		if (paths[i] < min)
		{
			min = paths[i];
			min_ind = i;
		}
		i++;
	}
	return (min_ind);
}

void			refresh_bfs(t_node **p_arr, t_bfs **bs)
{
	int		i;
	t_node	*list;

	init_bfs_arr(bs, 0);
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
	int		flow;

	path = 0;
	crawl = bs->end->index;
	flow = bs->curr_f[END];
	push_back(&path, bs->end, 0);
	while (bs->p[crawl] != NULL)
	{
		update_flow(bs, crawl, bs->p[crawl]->index, flow);
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
	ft_find_path(p_arr, bs, i);
	refresh_bfs(p_arr, &bs);
	return (get_all_paths(p_arr, i + 1, arr, bs));
}

t_node			**get_paths_controller(t_node **arr, t_bfs *bs, int i)
{
	t_node	**p_arr;
	t_node	**n;
	t_node	**p;

	p_arr = init_nodes_arr(bs->ants);
	bs->graph = arr;
	while (bfs(arr, bs))
	{
		if (i >= bs->ants)
			break ;
		ft_find_path(p_arr, bs, i);
		if (bs->ants == 1)
			return (p_arr);
		set_is_hold(p_arr[i], arr, bs->curr_f[END]);
		init_bfs_arr(&bs, 0);
		i++;
	}
	find_crosses(p_arr, arr);
	bs->stage++;
	init_bfs_arr(&bs, 0);
	p = init_nodes_arr(bs->ants);
	p = get_all_paths(p, 0, arr, bs);
	p = remove_unused_paths(bs, p);
	n = find_doubles(bs, remove_unused_paths(bs, p_arr));
	return (choose_best_paths(bs, n, p));
}
