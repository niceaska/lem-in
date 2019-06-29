/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:48:57 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/29 21:01:59 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

void			set_is_hold(t_node *list, t_node **arr, int hold)
{
	t_node *trav;

	while (list->next)
	{
		trav = arr[CURRIND(list)];
		while (trav)
		{
			if (CURRIND(trav) == NXTIND(list))
			{
				trav->is_hold = hold;
			}
			trav = trav->next;
		}
		list = list->next;
	}
}

void			set_unaval(t_node *node, t_node *trav)
{
	while (node)
	{
		if (CURRIND(node) == CURRIND(trav))
			node->is_hold = 2;
		node = node->next;
	}
}

void			list_cmp(t_node *list1, t_node *list2, t_node **arr)
{
	t_node *trav;

	while (list1->next)
	{
		trav = list2;
		while (trav->next)
		{
			if (CURRIND(list1) == NXTIND(trav)\
			&& CURRIND(trav) == NXTIND(list1))
			{
				set_unaval(arr[CURRIND(list1)], trav);
				set_unaval(arr[CURRIND(trav)], list1);
			}
			trav = trav->next;
		}
		list1 = list1->next;
	}
}

void			find_crosses(t_node **p_arr, t_node **arr)
{
	int		i;
	int		j;

	i = 0;
	while (p_arr[i])
	{
		j = i + 1;
		while (p_arr[j])
		{
			list_cmp(p_arr[i], p_arr[j], arr);
			j++;
		}
		i++;
	}
}
