/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:07:56 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/17 14:05:57 by lgigi            ###   ########.fr       */
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

static unsigned int		get_hash(t_hashtable *hash_tab, const char *key)
{
	size_t	hash;
	char	*str;
	int		c;

	str = (char *)key;
	hash = 5381;
    while (*str)
	{
		c = *str;
		hash = ((hash << 5) + hash) + c;
		str++;
	}
	return (hash % hash_tab->size);
}

/*
** Create and insert a new key-value into table.
*/

static void		set_value(t_entry **entry, t_entry *new_entry)
{
	t_entry *traverse;

	if (!*entry)
	{
		*entry = new_entry;
		return ;
	}
	traverse = *entry;
	while (traverse->next)
		traverse = traverse->next;
	traverse->next = new_entry;
}

int		ft_set_htval(t_hashtable *hash_tab, const char *key, int val)
{
	unsigned int	hash_id;
	t_entry			*new_entry;

	if (!key || !hash_tab)
		return (0);
	hash_id = get_hash(hash_tab, key);
	if (!(new_entry = (t_entry *)malloc(sizeof(t_entry))))
		return (0);
	if (!(new_entry->data = init_data((char *)key, val)))
		return (0);
	new_entry->key = ft_strdup(key);
	new_entry->next = NULL;
	set_value(&hash_tab->tab[hash_id], new_entry);
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
	entry = hash_tab->tab[get_hash(hash_tab, key)];
	if (!entry || !entry->key)
		return (0);
	while (entry && ft_strcmp(entry->key, key))
		entry = entry->next;
	return ((entry) ? entry->data : NULL);
}

/*
** utility printing function
*/

#include <stdio.h>


void	print_hash_val(t_hashtable *hash)
{
	int i;

	i = 0;
	while ((size_t)i < hash->size)
	{
		if (hash->tab[i])
		{
			printf("hashtab array index - %d\n", i);
			printf("hashtab list\n");
			t_entry *entr = hash->tab[i];
			while (entr)
			{
				printf("list name - %s\n", entr->data->name);
				printf("list value - %d\n", entr->data->index);
				entr = entr->next;
			}
		}
		i++;
	}
}

/*
int main()
{
	int i = 0;
	char test[] = "AB";
	t_hashtable *hash = init_hashtab(100);
	while (i < 100)
	{
		ft_set_htval(hash, test, i);
		i++;
		test[0]++;
	}
	print_hash_val(hash);
	free_hashtab(hash);
}
*/
