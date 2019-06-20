/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:40:31 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/20 21:45:58 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"
#include <stdio.h>

/*
** usefull function for printing all finded paths
*/

void print_paths(t_node **p_arr, short fl)
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
	while ((size_t)i < hash->size)
	{
		if (hash->tab[i])
		{
			ft_printf("hashtab array index - %d\n", i);
			ft_printf("hashtab list\n");
			entr = hash->tab[i];
			while (entr)
			{
				ft_printf("list name - %s\n", entr->data->name);
				ft_printf("list value - %d\n", entr->data->index);
				entr = entr->next;
			}
		}
		i++;
	}
}