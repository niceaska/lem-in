/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:49:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/20 15:21:53 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static void		print_usage(void)
{
	write(1, "usage:\n./lem-in ", 16); 
	write(1, "[-flags] [:file]\n", 17);
	write(1, "flags:\n-f [:file] ", 18);
	write(1, "-- Read data from file\n", 23);
	write(1, "-c -- Strict checking. ", 23);
	write(1, "Checks coords and pipes dublicates.\n", 36);
}

static char	*parse_argv(short *f, int ac, char **argv)
{
	int		i;
	char	*file;

	i = 1;
	file = NULL;
	while (i < ac)
	{
		if (!(ft_strcmp("-c", argv[i])))
			*f |= CHECK_FL;
		else if (!(ft_strcmp("-f", argv[i])))
		{
			*f |= FILE_FL;
			file = argv[i + 1];
			break ;
		}
		else
		{
			*f |= ERROR_FL;
			print_usage();
		}
		i++;
	}
	return (file);
}

t_env	*env_init(int ac, char **argv)
{
	t_env	*env;
	char	*file;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		err_out(0, 0, 0);
	env->f = 0;
	if (ac > 1)
	{
		file = parse_argv(&(env->f), ac, argv);
		if ((env->f & ERROR_FL) || ((env->f & FILE_FL) && !file))
			ft_error(env);
	}
	env->fd = ((env->f & FILE_FL)) ? open(file, O_RDONLY) : 0;
	if (env->fd < 0)
		ft_error(env);
	env->start = NULL;
	env->end = NULL;
	env->list = NULL;
	env->links = NULL;
	if (!(env->ht = init_hashtab(HT_SIZE)))
		ft_error(env);
	env->coor_ht = NULL;
	if (env->f & CHECK_FL)
		if (!(env->coor_ht = init_hashtab(HT_SIZE)))
			ft_error(env);
	return (env);
}

int		main(int ac, char **argv)
{
	t_env	*env;

	if (ac > 4 || (argv[1] &&!ft_strcmp("--help", argv[1])))
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	env = parser(ac, argv);
	bfs_controller(env, NULL, NULL, 0);
	//print_hash_val(env->ht);
	free_env(env);
	exit(EXIT_SUCCESS);
}