/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_paths_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 12:24:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/01 12:25:18 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

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
	n[j] = NULL;
	free(p_arr);
	return (n);
}


t_node			*list_cpy(t_node *l)
{
	t_node *n;

	n = NULL;
	while (l)
	{
		push_back(&n, l->data, 0);
		l = l->next;
	}
	return (n);
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