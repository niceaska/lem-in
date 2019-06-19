/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:32:55 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/19 14:56:02 by lgigi            ###   ########.fr       */
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

int		*init_rooms(int vrt, int start_index, int ants)
{
	int		i;
	int		*rooms;

	i = 0;
	if (!(rooms = (int *)malloc(sizeof(int) * vrt)))
		return (NULL);
	while (i < vrt)
		rooms[i++] = 0;
	rooms[start_index] = ants;
	return (rooms);
}