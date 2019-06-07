/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:22:16 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/07 19:01:43 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMMIN_H
# define FT_LEMMIN_H

# include "libft/includes/libft.h"
# include <stdlib.h>
# include <limits.h>

typedef struct	s_node
{
	int data;
	struct s_node *next;
} 				t_node;

typedef struct	s_queue
{
	struct s_node *first;
	struct s_node *last;
}				t_queue;


void			ft_enqueue(t_queue *queue, int data);
int				ft_dequeue(t_queue *queue);
int				ft_peek_q(t_queue *queue);
int				is_empty_q(t_queue *queue);
t_queue			*init_queue(void);
t_queue			*init_queue_bfs(int start);
int				list_empty(t_node *list);
void			push_back(t_node **node, int data);
int				list_pop(t_node **list);
void			list_push(t_node **node, int data);

#endif