/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:22:16 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/10 18:27:31 by lgigi            ###   ########.fr       */
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

typedef struct	s_bfs
{
	int			start;
	int			end;
	int			vrt;
	int			*v;
	int			*p;
	int			*d;
}				t_bfs;

t_bfs			*init_bfs(int start, int end, int v);
int				*init_arr(int vert, char c);
void			init_bfs_arr(t_bfs **bs);
t_node			**init_nodes_arr(int size);
void			refresh_bfs(t_node **p_arr, t_bfs **bs);
void			ft_find_path(t_node **p_arr, t_bfs *bs, int i);
t_node			**get_all_paths(t_node **p_arr, int i, t_node **arr, t_bfs *bs);
t_node			**get_paths_controller(t_node **arr, t_bfs *bs, int ants);
void			free_bfs(t_bfs *bs);
int				bfs(t_node **arr, t_bfs *bs);

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
unsigned int	list_size(t_node *list);
void			free_list(t_node *list);
void			free_list_arr(t_node **arr);
void			free_queue(t_queue *q);

#endif