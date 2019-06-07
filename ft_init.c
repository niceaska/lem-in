/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:15:21 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/07 18:46:03 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"
# include "bfs.h"

int		*init_arr(int vert, char c)
{
	int		*ret;
	int		i;

	i = 0;
	if (!(ret = (int *)malloc(sizeof(int) * vert)))
		return (NULL);
	if (c == 'v')
		ft_bzero((void *)ret, (size_t)vert);
	else if (c == 'p')
		while (i < vert)
			ret[i++] = -1;
	else if (c == 'd')
		while (i < vert)
			ret[i++] = INT_MAX;
	else
		ft_memdel((void *)ret);
	return (ret);
}

int		*init_bfs_arr(t_bfs **bs)
{
	int *v;

	if (!(v = init_arr((*bs)->vrt, 'v')))
		return (0);
	if (!((*bs)->p = init_arr((*bs)->vrt, 'p')))
		return (0);
	if (!((*bs)->d = init_arr((*bs)->vrt, 'd')))
		return (0);
	v[(*bs)->start] = 1; 
	(*bs)->d[(*bs)->start] = 0;
	return (v);
}

t_queue	*init_queue_bfs(int start)
{
	t_queue *q;

	if (!(q = init_queue()))
		return (NULL);
	ft_enqueue(q, start); 
	return (q);
}

t_bfs	*init_bfs(int start, int end, int v)
{
	t_bfs *bfs;

	if (!(bfs = (t_bfs *)malloc(sizeof(t_bfs))))
		return (NULL);
	bfs->start = start;
	bfs->end = end;
	bfs->vrt = v;
	bfs->d = NULL;
	bfs->p = NULL;
	return (bfs);
}