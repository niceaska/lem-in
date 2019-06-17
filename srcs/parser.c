/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:50:45 by jschille          #+#    #+#             */
/*   Updated: 2019/06/17 22:35:53 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"
#include <fcntl.h>

void			err_out(int e) // Not needed? We should print "ERROR" only
{
	if (e == 0)
		write(2, "Error! Don't have memory\n", 25);
	if (e == 1)
		write(2, "Error! Don't open file\n", 23);
	if (e == 2)
		write(2, "Error! Can not open file\n", 25);
	if (e == 3)
		write(2, "Error! Numbers of ants have invalid symbol\n", 44);
	if (e == 4)
		write(2, "Error! Dublicate Start/End\n", 26);
	if (e == 4)
		write(2, "Error! Bad symbol\n", 18);
	exit(1);
}
/*
static int		check_chr(char *line)
{
	unint	i;
	unint	f;

	i = 0;
	f = 0;
	while (line[i])
	{
		if (line[i] == '\n' && i != 0 && line[i + 1] != '\0')
		{
			if (f == 1)
				err_out(5);
			f = 1;
		}
		++i;
	}
	return (f);
}
*/
static void		check_line(char *line, t_env *env)
{
	static unint	count = 0;

	if (count == 0 && line[0] != '#' && (count = 1))
		set_ants(line, env);
	else if (line[0] == '#')
		parser_comment(line, env);
	else if (ft_strchr(line, '-'))
		set_links(line, &env);
	else if (count == 1)
		set_rooms(line, env);
	else
		err_out(2);
}

static void		read_data(int fd, t_env *env)
{
	char	*line;
	int		rd;

	while (get_next_line(fd, &line) > 0)
	{
		if (!*line)
		{
			free(line);
			// error
		}
		check_line(line, env);
		free(line);
	}
	if (rd < 0)
	{
		// free & error
	}
}

static t_env	*env_init(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		err_out(0);
	env->list = NULL;
	env->links = NULL;
	env->start = NULL;
	env->end = NULL;
	env->ht = init_hashtab(10000);
	return (env);
}

t_env			*parser(char *file)
{
	t_env   *env;
	//int		fd;

	if (file)
		file  = 0;
	env = env_init();
	// if ((fd = open(file, O_RDONLY)) == -1)
	// 	err_out(1);
	read_data(0, env);
	// close(fd);
	return (env);
}
#include <time.h>

int		main(void)
{
	t_env	*env;
    clock_t time;
	t_list *links;
    
	time=clock();

	env = parser("lll");
	printf("Ants = %d\n", env->ants);
	printf("Rooms\n");
	while (env->list)
	{
		printf("Name: %s\t\tIndex: %u\n", ((t_room*)env->list->content)->name, ((t_room*)env->list->content)->index);
		printf("Start Name: %s\t\tStart Index: %u\n", ((t_room*)env->start->content)->name, ((t_room*)env->start->content)->index);
		printf("End Name: %s\t\tEnd Index: %u\n", ((t_room*)env->end->content)->name, ((t_room*)env->end->content)->index);		
		env->list = env->list->next;
	}
//	print_hash_val(env->ht);
	links = env->links;
	while (links)
	{
		printf("Name: %s\n", (char *)links->content);
		links = links->next;
	}
	bfs_controller(env);
	free_hashtab(env->ht);
	printf("END\n");
	  time = clock() - time;
    printf("%f", (double)time/CLOCKS_PER_SEC);
}