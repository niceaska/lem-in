/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:15:21 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/14 13:58:55 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static int		*set_start_val(int *ar, char c, int vert)
{
	int		i;

	i = 0;
	if (c == 'v')
		while (i < vert)
			ar[i++] = 0;
	else if (c == 'd')
		while (i < vert)
			ar[i++] = INT_MAX;
	return (ar);
}

void	init_bfs_arr(t_bfs **bs)
{
	int i;

	i = 0;
	if (!(*bs)->v)
		if (!((*bs)->v = (int *)malloc(sizeof(int) * (*bs)->vrt)))
			return ;
	if (!(*bs)->p)
		if (!((*bs)->p = (t_data **)malloc(sizeof(t_data *)\
											* (*bs)->vrt)))
			return ;
	if (!(*bs)->d)
		if (!((*bs)->d = (int *)malloc(sizeof(int) * (*bs)->vrt)))
			return ;
	if ((*bs)->v != NULL)
		(*bs)->v = set_start_val((*bs)->v, 'v', (*bs)->vrt);
	if ((*bs)->p != NULL)
		while (i < (*bs)->vrt)
			(*bs)->p[i++] = NULL; 
	if ((*bs)->d != NULL)
		(*bs)->d = set_start_val((*bs)->d, 'd', (*bs)->vrt);
	(*bs)->v[(*bs)->start->index] = 1;
	(*bs)->v[(*bs)->end->index] = 0;
	(*bs)->d[(*bs)->start->index] = 0;
}

t_queue	*init_queue_bfs(t_data *start)
{
	t_queue *q;

	if (!(q = init_queue()))
		return (NULL);
	ft_enqueue(q, start); 
	return (q);
}

t_bfs	*init_bfs(t_data *start, t_data *end, int v)
{
	t_bfs *bfs;

	if (!(bfs = (t_bfs *)malloc(sizeof(t_bfs))))
		return (NULL);
	bfs->start = start;
	bfs->end = end;
	bfs->vrt = v;
	bfs->d = NULL;
	bfs->p = NULL;
	bfs->v = NULL;
	return (bfs);
}

t_node	**init_nodes_arr(int size)
{
	t_node	**arr;
	int		i;

	i = 0;
	if (!(arr = (t_node **)malloc(sizeof(t_node *) * (size + 1))))
		return (0);
	while (i < size)
		arr[i++] = 0;
	arr[i] = 0;
	return (arr);
}