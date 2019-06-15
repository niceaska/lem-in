/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:09:47 by jschille          #+#    #+#             */
/*   Updated: 2019/06/15 20:37:18 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int		main(void)
{
	t_env	*env;

	env = parser("lll");
	printf("Ants = %d\n", env->ants);
	while (env->list)
	{
		printf("Rooms\n");
		printf("RIndex: %u\t\tIndex: %zu\n", ((t_room*)(env->list->content))->index, env->list->content_size);
		env->list = env->list->next;
	}
	printf("END\n");
}