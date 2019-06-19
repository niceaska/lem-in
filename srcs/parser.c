/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:50:45 by jschille          #+#    #+#             */
/*   Updated: 2019/06/19 19:36:45 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lemmin.h"
#include <fcntl.h>

void			err_out(int e, char *line, t_env *env)
{
	(line) ? free(line) : 0;
	if (e == 0)
		write(2, "Error! Don't have memory\n", 25);
/*	if (e == 1)
		write(2, "Error! Don't open file\n", 23);
	if (e == 2)
		write(2, "Error! Can not open file\n", 25);
	if (e == 3)
		write(2, "Error! Numbers of ants have invalid symbol\n", 43);
	if (e == 4)
		write(2, "Error! Dublicate Start/End\n", 27);
	if (e == 4)
		write(2, "Error! Bad symbol\n", 18);*/
	return (ft_error(env));
}

static void		check_line(char *line, t_env **env)
{
	static unint	count = 0;

	if (line && count == 0 && line[0] != '#' && (count = 1))
		set_ants(line, env);
	else if (line && line[0] == '#' && count < 2)
		parser_comment(line, env);
	else if (line && (ft_strchr(line, '-') || count == 2))
	{
		if (!ft_strchr(line, '-') && line[0] != '#')
			err_out(2, line, *env);
		set_links(line, env);
		count = 2;
	}
	else if (line && count == 1)
		set_rooms(line, env, 0);
	else
		err_out(2, line, *env);
}

static void		read_data(int fd, t_env **env)
{
	char	*line;
	int		rd;

	while ((rd = get_next_line(fd, &line)) > 0)
	{
		if (!line || !*line)
		{
			(line) ? free(line) : 0;
			ft_error(*env);
		}
		check_line(line, env);
		free(line);
	}
	(line) ? free(line) : 0;
	if (rd < 0)
		ft_error(*env);
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
	read_data(0, &env);
	// close(fd);
	return (env);
}