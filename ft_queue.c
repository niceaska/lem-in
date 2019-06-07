/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:55:11 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/07 12:37:47 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

t_queue		*init_queue(void)
{
	t_queue *q;

	q = (t_queue *)malloc(sizeof(t_queue));
	q->first = NULL;
	q->last = NULL;
	return (q);
}

void		ft_enqueue(t_queue *queue, void *content)
{
	t_node *temp;

	if (!(temp = (t_node *)malloc(sizeof(t_node))))
		return ;
	temp->data = content;
	temp->next = NULL;
	if (!queue->first)
		queue->first = temp;
	if (queue->last)
		queue->last->next = temp;
	queue->last = temp;
}

int		ft_dequeue(t_queue *queue)
{
	int		ret;
	t_node	*temp;

	if (queue->first)
	{
		ret = queue->first->data;
		temp = queue->first;
		queue->first = queue->first->next;
		queue->last = (queue->first ? queue->last : NULL);
		free(temp);
	}
	return (ret);
}

int			ft_peek_q(t_queue *queue)
{
	int ret;

	if (queue->first)
		ret = queue->first->data;
	return (ret);
}

int			is_empty_q(t_queue *queue)
{
	return (queue->first) ? 0 : 1;
}