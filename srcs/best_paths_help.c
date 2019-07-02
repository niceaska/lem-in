/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_paths_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 12:24:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/02 19:23:49 by lgigi            ###   ########.fr       */
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

static int		ch_cr(t_node **cr, t_node *l)
{
	while (l)
	{
		if (cr[l->cap] && list_size(cr[l->cap]) > 1)
			return (0);
		l = l->next;
	}
	return (1);
}

static void		check_crossed_paths(t_node **crosses, t_node **p_arr, t_bfs *bs, int i)
{
	t_node *l;

	while (++i < bs->ants)
	{
		if (crosses[i] && list_size(crosses[i]) > 1)
		{
			l = crosses[i];
			if (ch_cr(crosses, crosses[i]))
			{
				free_list(p_arr[i]);
				p_arr[i] = NULL;
			}
			while (p_arr[i] && l)
			{
				free_list(p_arr[l->cap]);
				p_arr[l->cap] = 0;
				l = l->next;
			}		
		}
		else if (crosses[i] && list_size(crosses[i]) == 1)
		{
			free_list(p_arr[crosses[i]->cap]);
			p_arr[crosses[i]->cap] = NULL;
		}
	}
}

t_node 			**find_doubles(t_bfs *bs, t_node **p_arr)
{
	int		i;
	int		j;
	t_node	**crosses;

	i = 0;
	crosses = init_nodes_arr(bs->ants);
	while (i < bs->ants)
	{
		j = i + 1;
		while (j < bs->ants)
		{
			if (compare_double(bs, p_arr[i], p_arr[j]))
			{
				push_back(&crosses[i], p_arr[j]->data, 0);
				crosses[i]->cap = j;
			}
			j++;
		}
		i++;
	}
	check_crossed_paths(crosses, p_arr, bs, -1);
	free_list_arr(crosses, bs->ants, 0);
	return (realloc_paths(bs, p_arr));
}