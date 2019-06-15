/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:09:47 by jschille          #+#    #+#             */
/*   Updated: 2019/06/15 21:46:10 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


int		main(void)
{
	t_env	*env;

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
	printf("END\n");
}