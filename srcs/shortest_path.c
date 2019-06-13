/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:03:36 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/13 16:20:22 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"

static int		process_bfs(t_bfs **bs, t_node **arr, t_queue *queue)
{
	t_node	*list;
	int		u;
	
	u = ft_dequeue(queue);
	list = arr[u];
	while (list)
	{ 
		if ((*bs)->v[list->data] == 0)
		{ 
			(*bs)->v[list->data] = 1; 
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

	(bs->v == NULL) ? init_bfs_arr(&bs) : 0;
	queue = init_queue_bfs(bs->start);
	while (!is_empty_q(queue))
	{
		if (process_bfs(&bs, arr, queue))
		{
			free_queue(queue);
			return (1);
		}
	}
	free_queue(queue);
	return (0); 
}


/*
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
	{
		int pop =  list_pop(&path);
		bs->v[pop] = 1;;
		printf("%d\n", pop);
	}

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
	{
		int pop =  list_pop(&path);
		bs->v[pop] = 1;
		printf("%d\n",pop);
	}
} 
*/


void ft_addedge(t_node **arr, int start, int end) 
{ 
	push_back(&(arr[start]), end); 
	push_back(&(arr[end]), start); 
}
/*
int main() 
{ 
	t_node **arr;
	t_bfs *bs;
	
	arr = 0;
	bs = init_bfs(1, 2, 8);
	arr = init_nodes_arr(bs->vrt);

	ft_addedge(arr, 1, 4); 
	ft_addedge(arr, 0, 3); 
	ft_addedge(arr, 5, 3); 
	ft_addedge(arr, 4, 6); 
	ft_addedge(arr, 7, 6); 
	ft_addedge(arr, 2, 7); 
	ft_addedge(arr, 4, 5); 
	ft_addedge(arr, 5, 2);
	ft_addedge(arr, 0, 1);


	t_node **p_arr = get_paths_controller(arr, bs, 2);
	free_bfs(bs);
	free_list_arr(arr);
	free_list_arr(p_arr);
	return 0;
} */