/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:32:55 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/17 23:01:37 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

void ft_addedge(t_node **arr, t_data *start, t_data *end) 
{ 
	push_back(&(arr[start->index]), end); 
	push_back(&(arr[end->index]), start); 
}

t_data	*init_data(char *name, int index)
{
	t_data *data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->name = ft_strdup(name);
	data->index = index;
	return (data);
}
