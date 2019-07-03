/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:27:31 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/03 13:15:03 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

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

static t_node	*init_new_list_el(t_data *data)
{
	t_node *new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (0);
	new->data = data;
	new->is_hold = 0;
	new->cap = 1;
	new->flow = 0;
	new->next = 0;
	return (new);
}

int				push_back(t_node **node, t_data *data, short graph)
{
	t_node	*list;
	t_node	*new;
	int		ret;

	list = *node;
	ret = 1;
	if (!(new = init_new_list_el(data)))
		return (0);
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

void			list_push(t_node **node, t_data *data)
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

t_data			*list_pop(t_node **list)
{
	t_data	*ret;
	t_node	*tmp;

	ret = (*list)->data;
	tmp = *list;
	*list = (*list)->next;
	free(tmp);
	return (ret);
}
