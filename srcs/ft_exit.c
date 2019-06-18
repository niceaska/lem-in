/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:07:40 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/18 12:34:04 by lgigi            ###   ########.fr       */
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
	}
}

void			free_env(t_env *e)
{
	if (e->start)
		free_env_list(e->start);
	if (e->end)
		free(e->end);
	if (e->list)
		free(e->list);
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
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}