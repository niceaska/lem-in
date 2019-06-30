/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:06:48 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/30 21:45:14 by lgigi            ###   ########.fr       */
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

int			compare_double(t_bfs *bs, t_node *list1, t_node *list2)
{
	t_node *trav;

	if (!list1 || !list2)
		return (0);
	while (list1->next)
	{
		trav = list2;
		while (trav->next)
		{
			if ((CURRIND(list1) == CURRIND(trav)\
			&& CURRIND(trav) != START && CURRIND(list1) != START\
			&& CURRIND(trav) != END && CURRIND(list1) != END))
				return (1);
			trav = trav->next;
		}
		list1 = list1->next;
	}
	return (0);
}

int		*check_unused_paths(t_node **p_arr, t_bfs *bs, int i, int j)
{
	int		min_ind;
	int		*ways;
	int		p_count;
	int		*paths;

	p_count = 0;
	while (p_arr[p_count])
		p_count++;
	if (!(paths = (int *)malloc(sizeof(int) * p_count)))
		return (NULL);
	if (!(ways = (int *)malloc(sizeof(int) * p_count)))
		return (NULL);
	while (p_arr[++i])
		ways[i] = 0;
	ways[i] = 0;
	i = -1;
	while (p_arr[++i])
		paths[i] = list_size(p_arr[i]);
	while (j < bs->ants)
	{
		min_ind = find_min_index(paths, p_count);
		paths[min_ind]++;
		ways[min_ind]++;
		j++;
	}
	free(paths);
	return (ways);
}

t_node			**realloc_paths(t_bfs *bs, t_node **p_arr)
{
	t_node	**n;
	int		i;
	int		j;

	i = -1;
	j = 0;
	n = init_nodes_arr(bs->ants);
	while (++i < bs->ants)
		if (p_arr[i])
			n[j++] = p_arr[i];
	free(p_arr);
	return (n);
}

t_node			**remove_unused_paths(t_bfs *bs, t_node **p_arr)
{
	int		*ways;
	int		i;

	i = 0;
	ways = check_unused_paths(p_arr, bs, -1, 0);
	while (p_arr[i])
	{
		if (!ways[i])
		{
			free_list(p_arr[i]);
			p_arr[i] = 0;
		}
		i++;
	}
	free(ways);
	return (realloc_paths(bs, p_arr));
}

t_node 			**find_doubles(t_bfs *bs, t_node **p_arr)
{
	int		i;
	int		j;

	i = 0;
	while (i < bs->ants)
	{
		j = i + 1;
		while (j < bs->ants)
		{
			if (compare_double(bs, p_arr[i], p_arr[j]))
			{
				free_list(p_arr[j]);
				p_arr[j] = NULL;
			}
			j++;
		}
		i++;
	}
	return (realloc_paths(bs, p_arr));
}

t_node			**choose_best_paths(t_bfs *bs, t_node **p1, t_node **p2)
{
	int		i;
	int		j;
	int		ind;
	int		count;

	i = 0;
	while (p1[i])
	{
		j = 0;
		count = 0;
		while (p2[j])
		{
			if (compare_double(bs, p1[i], p2[j]))
			{
				ind = j;
				count++;
			}
			j++;
		}
		if (count == 1 && list_size(p1[i]) < list_size(p2[ind]))
			p2[ind] = p1[i];
		else if (count == 0)
			p2[j] = p1[i];
		i++;
	}
	return (p2);
}
t_node			**get_paths_controller(t_node **arr, t_bfs *bs, int i)
{
	t_node	**p_arr;
	t_node	**n;
	t_node	**p;

	p_arr = init_nodes_arr(bs->ants);
	while (bfs(arr, bs))
	{
		ft_find_path(p_arr, bs, i);
		if (bs->ants == 1 || i >= bs->ants)
			return (p_arr);
		set_is_hold(p_arr[i], arr, 1);
		init_bfs_arr(&bs);
		i++;
	}
	find_crosses(p_arr, arr);
	bs->stage++;
	init_bfs_arr(&bs);
	p = init_nodes_arr(bs->ants);
	p = get_all_paths(p, 0, arr, bs);
	n = find_doubles(bs, p_arr);
	p = remove_unused_paths(bs, p);
	n = choose_best_paths(bs, n, p);
	return (n);
}
