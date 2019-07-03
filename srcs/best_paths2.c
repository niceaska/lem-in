/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_paths2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:52:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/03 17:09:38 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

t_node			**cpy_path_arr(t_bfs *bs, t_node **arr)
{
	t_node	**cpy;
	int		i;

	i = 0;
	cpy = init_nodes_arr(bs->ants);
	while (arr[i])
	{
		cpy[i] = list_cpy(arr[i]);
		i++;
	}
	return (cpy);
}

void			cmp_best(t_bfs *bs, t_node **cpy1, t_node **cpy2)
{
	int i;
	int j;

	i = -1;
	while (++i < bs->ants)
	{
		j = -1;
		while (++j < bs->ants)
		{
			if (cpy1[i] && cpy2[j] && compare_double(bs, cpy1[i], cpy2[j]))
			{
				if (list_size(cpy1[i]) < list_size(cpy2[j]))
				{
					free_list(cpy2[j]);
					cpy2[j] = NULL;
				}
				else
				{
					free_list(cpy1[i]);
					cpy1[i] = NULL;
				}
			}
		}
	}
}

t_node			**try_find_best(t_bfs *bs, t_node **p1, t_node **p2)
{
	t_node	**cpy1;
	t_node	**cpy2;
	int		i;
	int		j;

	j = 0;
	i = 0;
	cpy1 = cpy_path_arr(bs, p1);
	cpy2 = cpy_path_arr(bs, p2);
	cmp_best(bs, cpy1, cpy2);
	cpy1 = realloc_paths(bs, cpy1);
	cpy2 = realloc_paths(bs, cpy2);
	while (cpy1[i])
		i++;
	while (cpy2[j] && i < bs->ants)
		cpy1[i++] = list_cpy(cpy2[j++]);
	free_list_arr(cpy2, bs->ants, 0);
	return (cpy1);
}

t_node			**compare_paths(t_bfs *bs, t_node **p1, t_node **p2)
{
	if (!p1)
		return (p2);
	if (!p2)
		return (p1);
	return ((best_way(bs, p1, p2)) ? p2 : p1);
}
