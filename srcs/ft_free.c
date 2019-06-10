/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:20:13 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/10 18:46:24 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

void	free_list(t_node *list)
{
	t_node *tmp;

	tmp = 0;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = 0;
	}
}

void	free_list_arr(t_node **arr)
{
	int i;

	if (!arr)	
		return ;
	i = 0;
	while (arr[i])
		free_list(arr[i++]);
	free(arr);
}

void	free_bfs(t_bfs *bs)
{
	if (!bs)
		return ;
	if (bs->v)
		free(bs->v);
	if (bs->p)
		free(bs->p);
	if (bs->d)
		free(bs->d);
	free(bs);
}

void	free_queue(t_queue *q)
{
	if (!q)
		return ;
	while (!is_empty_q(q))
		ft_dequeue(q);
	free(q);
}