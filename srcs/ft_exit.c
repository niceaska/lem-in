/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:07:40 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/19 18:01:25 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static void		list_del(void *data, size_t size)
{
	free(data);
	size += 0;
}

static void 	free_env_list(t_list *list)
{
	t_list *temp;
	char	*tmp;

	while (list)
	{
		temp = list;
		list = list->next;
		tmp = ((t_room *)temp->content)->name;
		(tmp) ? free(tmp) : 0;
		ft_lstdelone(&temp, list_del);
	}
}

void			free_env(t_env *e)
{
	if (e->list)
		free_env_list(e->list);
	if (e->start)
		free_env_list(e->start);
	if (e->end)
		free_env_list(e->end);
	if (e->links)
		ft_lstdel(&(e->links), list_del);
	if (e->ht)
		free_hashtab(e->ht);
	free(e);
}

void			ft_error(t_env *e)
{
	if (e)
		free_env(e);
	write(1, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}