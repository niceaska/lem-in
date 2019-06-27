/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:06:48 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/27 17:04:21 by lgigi            ###   ########.fr       */
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
	ft_find_path(p_arr, bs, i);
	refresh_bfs(p_arr, &bs);
	return (get_all_paths(p_arr, i + 1, arr, bs));
}

t_node			**get_paths_controller(t_node **arr, t_bfs *bs, int i, int j)
{
	t_node	**p_arr;

	bs->stage = 0;
	j++;
	p_arr = init_nodes_arr(bs->ants * 2);
	while (bfs(arr, bs))
	{
		ft_find_path(p_arr, bs, i);
		if (bs->ants == 1)
			return (p_arr);
		set_is_hold(p_arr[i], arr, 1);
		init_bfs_arr(&bs);
		i++;
	}
	find_crosses(p_arr, arr);
	free_list_arr(p_arr, bs->ants * 2, 0);
	bs->stage++;
	p_arr = init_nodes_arr(bs->ants);
	p_arr = get_all_paths(p_arr, 0, arr, bs);
	return (p_arr);
}
