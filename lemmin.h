/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:22:16 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/07 12:36:39 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMMIN_H
# define FT_LEMMIN_H

# include <libft.h>
# include <stdlib.h>

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

t_queue		*init_queue(void);
void		ft_enqueue(t_queue *queue, void *content);
int			ft_dequeue(t_queue *queue);
int			ft_peek_q(t_queue *queue);
int			is_empty_q(t_queue *queue);


#endif