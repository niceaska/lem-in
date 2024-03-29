/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 12:19:00 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/04 17:07:07 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

int				compare_double(t_bfs *bs, t_node *list1, t_node *list2)
{
	t_node *trav;

	if (!list1 || !list2)
		return (0);
	if (list_size(list1) == list_size(list2) &&\
		CURRIND(list1) == START && CURRIND(list2) == START\
		&& list1->next && NXTIND(list1) == END)
		return (1);
	while (list1->next)
	{
		trav = list2;
		while (trav->next)
		{
			if ((CURRIND(list1) == CURRIND(trav)\
			&& CURRIND(trav) != START && CURRIND(list1) != START\
			&& CURRIND(trav) != END && CURRIND(list1) != END))
				return (1);
			trav = trav->next;
		}
		list1 = list1->next;
	}
	return (0);
}

int				*check_unused_paths(t_node **p_arr, t_bfs *bs, int i, int j)
{
	int		min_ind;
	int		*ways;
	int		p_count;
	int		*paths;

	p_count = 0;
	while (p_arr[p_count])
		p_count++;
	if (!(paths = (int *)malloc(sizeof(int) * p_count)))
		return (NULL);
	if (!(ways = (int *)malloc(sizeof(int) * p_count)))
		return (NULL);
	while (p_arr[++i])
		ways[i] = 0;
	i = -1;
	while (p_arr[++i])
		paths[i] = list_size(p_arr[i]);
	while (++j < bs->ants)
	{
		min_ind = find_min_index(paths, p_count);
		paths[min_ind]++;
		ways[min_ind]++;
	}
	free(paths);
	return (ways);
}

t_node			**remove_unused_paths(t_bfs *bs, t_node **p_arr)
{
	int		*ways;
	t_node	**n;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ways = check_unused_paths(p_arr, bs, -1, -1);
	n = init_nodes_arr(bs->ants);
	while (p_arr[i])
	{
		if (ways[i] != 0)
			n[j++] = list_cpy(p_arr[i]);
		i++;
	}
	free(ways);
	free_list_arr(p_arr, bs->ants, 0);
	return (n);
}

static void		compare_cross_paths(t_bfs *bs, t_node **p2, t_node *p1)
{
	int		j;
	int		ind;
	int		count;

	j = 0;
	count = 0;
	while (p2[j])
	{
		if (compare_double(bs, p1, p2[j]))
		{
			ind = j;
			count++;
		}
		j++;
	}
	if (count == 1 && list_size(p1) < list_size(p2[ind]))
	{
		free_list(p2[ind]);
		p2[ind] = list_cpy(p1);
	}
	else if (p2[j] == NULL && count == 0)
		p2[j++] = list_cpy(p1);
}

t_node			**choose_best_paths(t_bfs *bs, t_node **p1, t_node **p2)
{
	int		i;
	t_node	**p3;
	t_node	**p4;
	t_node	**ret;

	i = 0;
	p4 = NULL;
	p3 = try_find_best(bs, p1, p2);
	while (p1[i])
	{
		compare_cross_paths(bs, p2, p1[i]);
		i++;
	}
	p1 = realloc_paths(bs, p1);
	p2 = realloc_paths(bs, p2);
	p4 = compare_paths(bs, p1, p2);
	p4 = compare_paths(bs, p3, p4);
	ret = cpy_path_arr(bs, p4);
	free_list_arr(p1, bs->ants, 0);
	free_list_arr(p2, bs->ants, 0);
	free_list_arr(p3, bs->ants, 0);
	return (ret);
}
