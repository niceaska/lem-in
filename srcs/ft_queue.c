/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:55:11 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/23 12:58:19 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

t_queue			*init_queue(void)
{
	t_queue *q;

	if (!(q = (t_queue *)malloc(sizeof(t_queue))))
		return (0);
	q->first = NULL;
	q->last = NULL;
	return (q);
}

void			ft_enqueue(t_queue *queue, t_data *data)
{
	t_node *temp;

	if (!(temp = (t_node *)malloc(sizeof(t_node))))
		return ;
	temp->data = data;
	temp->next = NULL;
	if (!queue->first)
		queue->first = temp;
	if (queue->last)
		queue->last->next = temp;
	queue->last = temp;
}

t_data			*ft_dequeue(t_queue *queue)
{
	t_data	*ret;
	t_node	*temp;

	ret = NULL;
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

t_data			*ft_peek_q(t_queue *queue)
{
	t_data *ret;

	ret = 0;
	if (queue->first)
		ret = queue->first->data;
	return (ret);
}

int				is_empty_q(t_queue *queue)
{
	return (queue->first) ? 0 : 1;
}
