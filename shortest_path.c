/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:03:36 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/07 19:19:41 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"
#include "bfs.h"

static int		process_bfs(t_bfs **bs, int *v, t_node **arr, t_queue *queue)
{

	t_node	*list;
	int		u;
	
	u = ft_dequeue(queue);
	list = arr[u];
	while (list)
	{ 
		if (v[list->data] == 0)
		{ 
			v[list->data] = 1; 
			(*bs)->d[list->data] = (*bs)->d[u] + 1; 
			(*bs)->p[list->data] = u; 
			ft_enqueue(queue, list->data);  
			if (list->data == (*bs)->end) 
				return (1); 
		} 
		list = list->next;
	}
	return (0);
} 

int				bfs(t_node **arr, t_bfs *bs) 
{ 
	t_queue		*queue;
	int			u;
	int			*v;

	v = init_bfs_arr(&bs);
	queue = init_queue_bfs(bs->start);
	while (!is_empty_q(queue))
		if (process_bfs(&bs, v, arr, queue))
			return (1);
	return (0); 
} 



void	print_shortest_dist(t_node **arr, t_bfs *bs) 
{
	t_node	*path;
	int		crawl;

	path = 0;
	if (bfs(arr, bs) == 0) 
	{ 
		printf("path not foind");
		return ; 
	} 
	crawl = bs->end; 
	push_back(&path, crawl);
	while (bs->p[crawl] != -1)
	{ 
		list_push(&path, bs->p[crawl]); 
		crawl = bs->p[crawl]; 
	} 
	printf( "Shortest path length is : %d\n", bs->d[bs->end]); 
	printf("\nPath is::\n"); 
	while (!list_empty(path))
		printf("%d\n", list_pop(&path));
} 



void ft_addedge(t_node **arr, int start, int end) 
{ 
	push_back(&(arr[start]), end); 
	push_back(&(arr[end]), start); 
}

int main() 
{ 
	t_node **arr;
	t_bfs *bs;
	
	bs = init_bfs(0, 1, 4);
	arr = (t_node **)malloc(sizeof(t_node *) * bs->vrt);
	ft_addedge(arr, 0, 2); 
	ft_addedge(arr, 2, 3); 
	ft_addedge(arr, 3, 1); 
	print_shortest_dist(arr, bs); 
	return 0; 
} 