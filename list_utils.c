/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:27:31 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/10 18:06:40 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

int		list_empty(t_node *list)
{
	return (list ? 0 : 1);
}

unsigned int	list_size(t_node *list)
{
	unsigned int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	push_back(t_node **node, int data)
{
	t_node *list;
	t_node *new;

	list = *node;
	new = 0;
	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return ;
	new->data = data;
	new->next = 0;
	if (!*node)
	{
		*node = new;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = new;
}

void	list_push(t_node **node, int data)
{
	t_node *new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return ;
	new->data = data;
	if (!*node)
		new->next = 0;
	else
		new->next = *node;
	*node = new;
}

int		list_pop(t_node **list)
{
	int		ret;
	t_node	*tmp;

	ret = (*list)->data;
	tmp = *list;
	*list = (*list)->next;
	free(tmp);
	return (ret);
}