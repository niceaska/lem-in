/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:03:36 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/14 20:04:49 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"

static int		process_bfs(t_bfs **bs, t_node **arr, t_queue *queue)
{
	t_node	*list;
	t_data	*u;
	
	u = ft_dequeue(queue);
	list = arr[u->index];
	while (list)
	{ 
		if ((*bs)->v[list->data->index] == 0)
		{ 
			(*bs)->v[list->data->index] = 1; 
			(*bs)->d[list->data->index] = (*bs)->d[u->index] + 1; 
			(*bs)->p[list->data->index] = u; 
			ft_enqueue(queue, list->data);  
			if (list->data->index == (*bs)->end->index)
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

void	print_moves(t_node **p_arr, t_bfs *bs)
{
	int		*rooms;
	int		i;
	//t_node	*list;
	t_node	**ants;

	i = 0;
	if (!(rooms = (int *)malloc(sizeof(int) * bs->vrt)))
		return ;
	while (i < bs->vrt)
		rooms[i++] = 0;
	rooms[bs->start->index] = bs->ants;
	ants = init_nodes_arr(bs->ants);
	ants[0] = p_arr[0];
	ants[1] = p_arr[1];
	ants[2] = p_arr[0];
	ants[3] = p_arr[1];
	while (rooms[bs->end->index] != bs->ants)
	{
		ft_printf("\n");
		i = rooms[bs->end->index];
		while (i < bs->ants)
		{
			if (rooms[ants[i]->data->index] && \
				(!rooms[ants[i]->next->data->index] \
				|| ants[i]->next->data->index == bs->end->index))
			{
				rooms[ants[i]->data->index]--;
				ft_printf("L%d-%s", i + 1, ants[i]->next->data->name);		
				rooms[ants[i]->next->data->index]++;
				ants[i] = ants[i]->next;
				if (ants[i + 1] && (!rooms[ants[i + 1]->next->data->index] \
				|| ants[i + 1]->next->data->index == bs->end->index))
					ft_printf(" ");
			}
			i++;
		}
	}
}

int main() 
{ 
	t_node **arr;
	t_bfs *bs;
	t_data *one = init_data("one", 0);
	t_data *start = init_data("start", 1);
	t_data	*end = init_data("end", 2);
	t_data	*two = init_data("two", 3);
	t_data	*tree = init_data("tree", 4);


	arr = 0;
	bs = init_bfs(start, end, 5, 4);
	arr = init_nodes_arr(bs->vrt);

	t_data **all_d = malloc(sizeof(t_data *) * bs->vrt);
	all_d[0] = one;
	all_d[1] = start;
	all_d[2] = end;
	all_d[3] = two;
	all_d[4] = tree;
	ft_addedge(arr, start,one);
	ft_addedge(arr, start,two);
	ft_addedge(arr, two, tree);
	ft_addedge(arr, tree, end); 
	ft_addedge(arr, end, one); 
	//ft_addedge(arr, 5, 3); 
	//ft_addedge(arr, 4, 6); 
	//ft_addedge(arr, 7, 6); 
	//ft_addedge(arr, 2, 7); 
	//ft_addedge(arr, 4, 5); 
	//ft_addedge(arr, 5, 2);
	//ft_addedge(arr, 0, 1);


	t_node **p_arr = get_paths_controller(arr, bs);
	print_moves(p_arr, bs);
	for(int i = 0; i < bs->vrt; i++)
	{
		free(all_d[i]->name);
		free(all_d[i]);
	}
	free(all_d);
	free_bfs(bs);
	free_list_arr(arr);
	free_list_arr(p_arr);

	return 0;
}