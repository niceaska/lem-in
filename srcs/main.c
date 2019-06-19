/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:49:02 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/19 14:52:17 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmin.h"

t_env	*env_init(void)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		err_out(0, 0, 0);
	env->start = NULL;
	env->end = NULL;
	env->list = NULL;
	env->links = NULL;
	if (!(env->ht = init_hashtab(HT_SIZE)))
		ft_error(env);
	return (env);
}

int		main(void)
{
	t_env	*env;

	env = parser("lll");;
	bfs_controller(env, NULL, NULL, 0);
	free_env(env);
	exit(EXIT_SUCCESS);
}