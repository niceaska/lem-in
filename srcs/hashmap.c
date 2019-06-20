/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:07:56 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/20 14:51:54 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

/*
** Init hashtable
*/

t_hashtable		*init_hashtab(size_t size)
{
	t_hashtable		*hash_tab;
	size_t			i;

	i = 0;
	if (!size)
		return (NULL);
	if (!(hash_tab = (t_hashtable *)malloc(sizeof(t_hashtable))))
		return (NULL);
	if (!(hash_tab->tab = (t_entry **)malloc(sizeof(t_entry *) * (size + 1))))
	{
		free(hash_tab);
		return (NULL);
	}
	while (i < size)
		hash_tab->tab[i++] = NULL;
	hash_tab->size = size;
	hash_tab->curr_size = 0;
	return (hash_tab);
}

/*
** Convert string to int and get hash by djb2 hash function
** http://www.partow.net/programming/hashfunctions/#PJWHashFunction
*/

static unsigned int		get_hash(t_hashtable *hash_tab, int *coor, const char *key)
{
	size_t	hash;
	char	*str;
	int		c;

	str = (char *)key;
	hash = 5381;
    while (*str && coor == NULL)
	{
		c = *str;
		hash = ((hash << 5) + hash) + c;
		str++;
	}
	if (coor)
	{
		hash = ((hash << 5) + hash) + coor[0];
		hash = ((hash << 5) + hash) + coor[1];
	}
	return (hash % hash_tab->size);
}

/*
** Create and insert a new key-value into table.
*/

static int		set_value(t_entry **entry, t_entry *new_entry)
{
	t_entry *traverse;

	if (!*entry)
	{
		*entry = new_entry;
		return (1);
	}
	traverse = *entry;
	if (!ft_strcmp(traverse->key, new_entry->key))
		return (0);
	if (traverse->coords[0] == new_entry->coords[0]\
		&& traverse->coords[1] == new_entry->coords[1])
		return (0);
	while (traverse->next)
	{
		if (!ft_strcmp(traverse->key, new_entry->key))
			return (0);
		if (traverse->coords[0] == new_entry->coords[0]\
			&& traverse->coords[1] == new_entry->coords[1])
			return (0);
		traverse = traverse->next;
	}
	traverse->next = new_entry;
	return (1);
}

int		ft_set_htval(t_hashtable *hash_tab, const char *key, int *coor, int val)
{
	unsigned int	hash_id;
	t_entry			*new_entry;

	if (!key || !hash_tab)
		return (0);
	hash_id = (val == -42) ? get_hash(hash_tab, coor, key)\
							: get_hash(hash_tab, 0, key);
	if (!(new_entry = (t_entry *)malloc(sizeof(t_entry))))
		return (0);
	if (!(new_entry->data = init_data((char *)key, val)))
		return (0);
	new_entry->key = new_entry->data->name;
	new_entry->coords[0] = coor[0];
	new_entry->coords[1] = coor[1];
	new_entry->next = NULL;
	if (!set_value(&hash_tab->tab[hash_id], new_entry))
		return (0);
	hash_tab->curr_size++;
	return (1);
}

/*
** Get entry from table
*/

t_data		*get_entry(t_hashtable *hash_tab, const char *key)
{
	t_entry			*entry;

	if (!key)
		return (0);
	entry = hash_tab->tab[get_hash(hash_tab, 0, key)];
	if (!entry || !entry->key)
		return (0);
	while (entry && ft_strcmp(entry->key, key))
		entry = entry->next;
	return ((entry) ? entry->data : NULL);
}
