/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:50:45 by jschille          #+#    #+#             */
/*   Updated: 2019/06/18 15:13:42 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"
#include <fcntl.h>

void			err_out(int e, t_env *env)
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
	return (ft_error(env));
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
		err_out(2, env);
}

static void		read_data(int fd, t_env *env)
{
	char	*line;
	int		rd;

	while ((rd = get_next_line(fd, &line)) > 0)
	{
		if (!*line)
		{
			free(line);
			ft_error(env);
		}
		check_line(line, env);
		free(line);
	}
	(line) ? free(line) : 0;
	if (rd < 0)
		ft_error(env);
}

static t_env	*env_init(void)
{
	t_env	*env;

	env = NULL;
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		err_out(0, env);
	env->list = NULL;
	env->links = NULL;
	env->start = NULL;
	env->end = NULL;
	if (!(env->ht = init_hashtab(10000)))
		ft_error(env);
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

	env = parser("lll");;
	bfs_controller(env);
	free_env(env);
	exit(EXIT_SUCCESS);
}