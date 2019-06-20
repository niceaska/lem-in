/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:27:31 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/20 15:49:37 by lgigi            ###   ########.fr       */
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

int		push_back(t_node **node, t_data *data, short graph)
{
	t_node *list;
	t_node *new;
	int		ret;

	list = *node;
	ret = 1;
	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (0);
	new->data = data;
	new->next = 0;
	if (!*node)
	{
		*node = new;
		return (1);
	}
	while (list->next)
	{
		if (graph && !(ft_strcmp(list->data->name, new->data->name)))
			ret = 0;
		list = list->next;
	}
	list->next = new;
	return (ret);
}

void	list_push(t_node **node, t_data *data)
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

t_data		*list_pop(t_node **list)
{
	t_data	*ret;
	t_node	*tmp;

	ret = (*list)->data;
	tmp = *list;
	*list = (*list)->next;
	free(tmp);
	return (ret);
}