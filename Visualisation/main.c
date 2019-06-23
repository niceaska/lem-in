/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:38:40 by jschille          #+#    #+#             */
/*   Updated: 2019/06/23 16:48:09 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int		main(void)
{
	t_env	*env;

	env = parser();
	// while (env->list)
	// {
	// 	printf("Name: %d\n", ((t_room*)env->list->content)->coords[1]);
	// 	while (((t_room*)env->list->content)->links)
	// 	{
	// 		printf("Links: %d\n", ((t_room*)((t_room*)env->list->content)->links->content)->coords[1]);
	// 		((t_room*)env->list->content)->links = ((t_room*)env->list->content)->links->next;
	// 	}
	// 	env->list = env->list->next;
	// }
	display_out(env);
	exit(0);
}