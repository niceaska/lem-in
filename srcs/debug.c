/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:40:31 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/01 16:59:40 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"
#include <stdio.h>

void	free_debug_arr(t_node **debug)
{
	int		i;
	t_node	*tmp;
	t_node	*list;

	if (!debug)
		return ;
	i = -1;
	while (debug[++i])
	{
		list = debug[i];
		while (list)
		{
			tmp = list;
			list = list->next;
			free(tmp->data->name);
			free(tmp->data);
			free(tmp);
		}
	}
	free(debug);
}

int		check_moves(t_node **moves, t_node **p_arr, int i, int j)
{
	t_node	*mv;
	t_node	*path;

	while (moves[i])
	{
		j = 0;
		while (p_arr[j])
		{
			mv = moves[i];
			path = p_arr[j]->next;
			while (path && moves\
			&& !ft_strcmp(path->data->name, mv->data->name))
			{
				path = path->next;
				mv = mv->next;
			}
			if (!path && !mv)
				break ;
			j++;
		}
		if (!p_arr[j])
			break ;
		i++;
	}
	return (moves[i] ? 0 : 1);
}

void	debug_controller(t_bfs *bs, t_hashtable *ht,
							t_node **p_arr, short fl)
{
	char r;

	if (fl & DEBUG_HT)
	{
		print_hash_val(ht);
		return ;
	}
	if (check_moves(bs->debug, p_arr, 0, 0))
		ft_printf("\nALL MOVES OK!\n");
	else
		ft_printf("\nERROR: WRONG MOVES\n");
	ft_printf("\n---------------\n");
	ft_printf("Do you want to print paths and moves?\n");
	read(0, &r, 1);
	if (r == 'y' || r == 'Y' || !r)
	{
		print_paths(p_arr, 0);
		print_paths(bs->debug, 1);
	}
}

/*
** usefull function for printing all finded paths
*/

void	print_paths(t_node **p_arr, short fl)
{
	t_node	*list;
	int		i;

	i = 0;
	list = 0;
	if (fl)
		ft_printf("\nMoves:\n---------------\n");
	else
		ft_printf("\nPaths:\n---------------\n");
	while (p_arr[i])
	{
		list = p_arr[i];
		while (list)
		{
			ft_printf("%s ", list->data->name);
			list = list->next;
		}
		ft_printf("\n---------------\n");
		i++;
	}
}

/*
** utility hashtable printing function
*/

void	print_hash_val(t_hashtable *hash)
{
	int		i;
	t_entry	*entr;

	i = 0;
	ft_printf("\n");
	while ((size_t)i < hash->size)
	{
		if (hash->tab[i])
		{
			ft_printf("Hashtable array index is %d\n", i);
			ft_printf("Hashtable values:\n");
			entr = hash->tab[i];
			while (entr)
			{
				ft_printf("|name - %s  |", entr->data->name);
				ft_printf("  index - %d|\n", entr->data->index);
				entr = entr->next;
			}
		}
		i++;
	}
}
