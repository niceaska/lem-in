/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:03:36 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/03 13:10:16 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static int		process_bfs(t_bfs **bs, t_node **arr, t_queue *queue)
{
	t_node	*list;
	t_data	*u;

	u = ft_dequeue(queue);
	list = arr[u->index];
	while (list)
	{
		if ((*bs)->v[list->data->index] == 0 &&\
		(((!(*bs)->stage && (list->cap - list->flow) > 0))\
		|| ((*bs)->stage && list->is_hold < 2)))
		{
			(*bs)->v[list->data->index] = 1;
			(*bs)->d[list->data->index] = (*bs)->d[u->index] + 1;
			(*bs)->p[list->data->index] = u;
			(*bs)->curr_f[CURRIND(list)] = MIN((*bs)->curr_f[u->index],
												(list->cap - list->flow));
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
	int			i;

	i = 0;
	(bs->v == NULL) ? init_bfs_arr(&bs, 0) : 0;
	queue = init_queue_bfs(bs->start);
	if (!(bs->curr_f))
		if (!(bs->curr_f = (int *)malloc(sizeof(int) * bs->vrt)))
			return (-1);
	while (i < bs->vrt)
		bs->curr_f[i++] = 0;
	bs->curr_f[START] = 2147483647;
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

static int		link_free_onerr(char *link1, char *link2)
{
	(link1) ? free(link1) : 0;
	(link2) ? free(link2) : 0;
	return (-1);
}

static int		process_links(t_node **arr, short f,
								t_list *links, t_hashtable *ht)
{
	char	*link1;
	char	*link2;
	t_data	*l1;
	t_data	*l2;

	while (links)
	{
		if (((char *)links->content)[0] != '#')
		{
			link2 = ft_strdup(ft_strchr(links->content, '-') + 1);
			link1 = ft_strdup(links->content);
			*(ft_strchr(link1, '-')) = '\0';
			if (!(l1 = get_entry(ht, link1))\
				|| !(l2 = get_entry(ht, link2)))
				return (link_free_onerr(link1, link2));
			if (!ft_strcmp(l1->name, l2->name))
				return (0);
			if (!ft_addedge(arr, l1, l2) && (f & CHECK_FL))
				return (link_free_onerr(link1, link2));
			ft_memdel((void *)&link2);
			ft_memdel((void *)&link1);
		}
		links = links->next;
	}
	return (1);
}

void			bfs_controller(t_env *e, t_node **arr,
									t_node **p_arr, int size)
{
	t_bfs	*bs;

	if (!(e->start) || !(e->end))
		ft_error(e);
	bs = init_bfs(get_entry(e->ht, ((t_room*)e->start->content)->name),
					get_entry(e->ht, ((t_room*)e->end->content)->name),
											e->ht->curr_size, e->ants);
	arr = init_nodes_arr(bs->vrt);
	if ((e->f & DEBUG_FL) || (e->f & DEBUG_HT))
		bs->debug = init_nodes_arr(e->ants);
	if (((process_links(arr, e->f, e->links, e->ht)) <= 0)\
		|| !arr[bs->end->index] || !arr[bs->start->index])
	{
		free_bfs(bs);
		free_list_arr(arr, size, 0);
		ft_error(e);
	}
	p_arr = get_paths_controller(arr, bs, 0);
	if (p_arr && p_arr[0])
		print_res(e, p_arr, bs);
	free_list_arr(arr, size, 0);
	(!p_arr[0]) ? ft_memdel((void *)&p_arr) : 0;
	(p_arr) ? free_list_arr(p_arr, bs->ants, 0) : 0;
	free_bfs(bs);
	(!p_arr) ? ft_error(e) : 0;
}
