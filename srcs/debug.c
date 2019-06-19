/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:40:31 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/19 15:43:04 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"
#include <stdio.h>

/*
** usefull function for printing all finded paths
*/

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

/*
** utility hashtable printing function
*/

void	print_hash_val(t_hashtable *hash)
{
	int i;

	i = 0;
	while ((size_t)i < hash->size)
	{
		if (hash->tab[i])
		{
			printf("hashtab array index - %d\n", i);
			printf("hashtab list\n");
			t_entry *entr = hash->tab[i];
			while (entr)
			{
				printf("list name - %s\n", entr->data->name);
				printf("list value - %d\n", entr->data->index);
				entr = entr->next;
			}
		}
		i++;
	}
}