/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:49:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/22 20:54:10 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

static void		print_usage(void)
{
	write(1, "usage:\n./lem-in ", 16); 
	write(1, "[-flags] [:file]\n", 17);
	write(1, "flags:\n-f [:file] ", 18);
	write(1, "-- Read data from file\n", 23);
	write(1, "--debug[=ht] -- Print debug information\n", 40);
	write(1, "-c [--check-negative] -- Strict checking. ", 42);
	write(1, "Checks coords and pipes dublicates.\n", 36);
}

static char	*parse_argv(short *f, int ac, char **argv, int i)
{
	while (++i < ac)
	{
		if (!(ft_strcmp("-c", argv[i])))
			*f |= CHECK_FL;
		else if (!(ft_strcmp("--debug", argv[i])))
			*f |= DEBUG_FL;
		else if (!(ft_strcmp("--debug=ht", argv[i])))
			*f |= DEBUG_HT;
		else if (!(ft_strcmp("-f", argv[i])))
		{
			*f |= FILE_FL;
			return (argv[i + 1]);
		}
		else if (!ft_strcmp("--check-negative", argv[i]))
			*f |= (*f & CHECK_FL) ? CHECK_NEG_FL : 0;
		else
		{
			*f |= ERROR_FL;
			print_usage();
		}
	}
	return (NULL);
}

void	init_values(t_env **e)
{
	(*e)->f = 0;
	(*e)->fd = 0;
	(*e)->start = NULL;
	(*e)->end = NULL;
	(*e)->list = NULL;
	(*e)->links = NULL;
	(*e)->ht = NULL;
	(*e)->coor_ht = NULL;
}

t_env	*env_init(int ac, char **argv)
{
	t_env	*env;
	char	*file;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		err_out(0, 0, 0);
	init_values(&env);
	if (ac > 1)
	{
		file = parse_argv(&(env->f), ac, argv, 0);
		if ((env->f & ERROR_FL) || ((env->f & FILE_FL) && !file))
			ft_error(env);
	}
	env->fd = ((env->f & FILE_FL)) ? open(file, O_RDONLY) : 0;
	if (env->fd < 0)
		ft_error(env);
	if (!(env->ht = init_hashtab(HT_SIZE)))
		ft_error(env);
	if (env->f & CHECK_FL)
		if (!(env->coor_ht = init_hashtab(HT_SIZE)))
			ft_error(env);
	return (env);
}

int		main(int ac, char **argv)
{
	t_env	*env;

	if (ac > 6 || (argv[1] && !ft_strcmp("--help", argv[1])))
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	env = parser(ac, argv);
	bfs_controller(env, NULL, NULL, (int)env->ht->curr_size);
	free_env(env);
	exit(EXIT_SUCCESS);
}