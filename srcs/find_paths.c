/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:06:48 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/18 18:58:46 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

void	refresh_bfs(t_node **p_arr, t_bfs **bs)
{
	int		i;
	t_node *list;

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
}

int		*init_rooms(int vrt, int start_index, int ants)
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

void	ft_find_path(t_node **p_arr, t_bfs *bs, int i)
{
	t_node	*path;
	int		crawl;

	path = 0;
	crawl = bs->end->index; 
	push_back(&path, bs->end);
	while (bs->p[crawl] != NULL)
	{ 
		list_push(&path, bs->p[crawl]); 
		crawl = bs->p[crawl]->index; 
	}
	while (!list_empty(path))
		push_back(&p_arr[i], list_pop(&path));
	free_list(path);
}

t_node	**get_all_paths(t_node **p_arr, int i, t_node **arr, t_bfs *bs)
{
	if (!bfs(arr, bs) || i >= bs->ants) 
		return (p_arr); 
	if (i != 0 && (bs->d[bs->end->index] > (int)(list_size(p_arr[0]) * 2)))
		return (p_arr);
	ft_find_path(p_arr, bs, i);
	refresh_bfs(p_arr, &bs);
	return (get_all_paths(p_arr, i + 1, arr, bs));
}

#include <stdio.h>

void print_paths(t_node **p_arr)
{
	t_node *list;
	int i;

	i = 0;
	list = 0;
	while (p_arr[i])
	{
		list = p_arr[i];
		while (list)
		{
			printf("%s ", list->data->name);
			list = list->next;
		}
		printf("\n");
		i++;
	}
}

t_node	**get_paths_controller(t_node **arr, t_bfs *bs) 
{
	t_node **p_arr;
	int i;
	int j;

	i = 0;
	p_arr = init_nodes_arr(bs->ants);
	p_arr = get_all_paths(p_arr, 0, arr, bs);
	while (p_arr[i])
		i++;
	while (list_size(arr[bs->start->index]) > 1 && i < bs->ants)
	{
		j = -1;
		init_bfs_arr(&bs);
		while (p_arr[++j])
			bs->v[p_arr[j]->next->data->index] = 1;
		if (!bfs(arr, bs))
			break ;
		if (bs->d[bs->end->index] > (int)list_size(p_arr[0]) + 1)
			break ;
		ft_find_path(p_arr, bs, i);
		i++;
	}
	//print_paths(p_arr);
	return (p_arr);
}

