/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 03:19:21 by jschille          #+#    #+#             */
/*   Updated: 2019/06/23 18:34:53 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void	move(t_mlx *mlx)
{
	t_list	*lst;

	lst = mlx->env->list;
	while (mlx->env->list)
	{
		((t_room*)mlx->env->list->content)->coords[0] -= (mlx->extrem[1] - mlx->extrem[0]) / 2 - HIGHT / 2;
		((t_room*)mlx->env->list->content)->coords[1] -= (mlx->extrem[3] - mlx->extrem[2]) / 2 - WIDTH / 2;
		mlx->env->list = mlx->env->list->next;
	}
	mlx->env->list =lst;
}

static void	move_back(t_mlx *mlx)
{
	t_list	*lst;

	lst = mlx->env->list;
	while (mlx->env->list)
	{
		((t_room*)mlx->env->list->content)->coords[0] += (mlx->extrem[1] - mlx->extrem[0]) / 2 - HIGHT / 2;
		((t_room*)mlx->env->list->content)->coords[1] += (mlx->extrem[3] - mlx->extrem[2]) / 2 - WIDTH / 2;
		if (((t_room*)mlx->env->list->content)->coords[0] > mlx->extrem[1])
				mlx->extrem[1] = ((t_room*)mlx->env->list->content)->coords[0];
			if (((t_room*)mlx->env->list->content)->coords[0] < mlx->extrem[0])
				mlx->extrem[0] = ((t_room*)mlx->env->list->content)->coords[0];
			if (((t_room*)mlx->env->list->content)->coords[1] > mlx->extrem[3])
				mlx->extrem[3] = ((t_room*)mlx->env->list->content)->coords[1];
			if (((t_room*)mlx->env->list->content)->coords[1] < mlx->extrem[2])
				mlx->extrem[2] = ((t_room*)mlx->env->list->content)->coords[1];
		mlx->env->list = mlx->env->list->next;
	}
	mlx->env->list =lst;
}

int		key_press(int keycode, t_mlx *img)
{
	t_list	*lst;
	t_list	*tmp;
	t_env	*env;
	char	*line;
	char	**split;
	char	*name;

	env = img->env;
	mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	img->img_ptr = mlx_new_image(img->mlx_ptr, WIDTH, HIGHT);
	img->img_data = (unsigned int*)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->alpha);
	if (keycode == 53)
		exit(0);
	if (keycode == 2)
	{
		lst = img->env->list;
		//move(img);
		while (env->list)
		{
			printf("name %s\n", ((t_room*)env->list->content)->name);
			//((t_room*)env->list->content)->coords[0] += 2;
			((t_room*)env->list->content)->coords[1] += 2;
			tmp = ((t_room*)env->list->content)->links;
			while (tmp)
			{
				//((t_room*)tmp->content)->coords[0] += 2;
				((t_room*)tmp->content)->coords[1] += 2;
				tmp = tmp->next;
			}
			env->list = env->list->next;
		}
		env->list = lst;
		//move_back(img);
		trace_point(img->env, img);
	}
	if (keycode == 0)
	{
		lst = img->env->list;
		//move(img);
		while (env->list)
		{
			//((t_room*)env->list->content)->coords[0] -= 2;
			((t_room*)env->list->content)->coords[1] -= 2;
			tmp = ((t_room*)env->list->content)->links;
			while (tmp)
			{
				//((t_room*)tmp->content)->coords[0] -= 2;
				((t_room*)tmp->content)->coords[1] -= 2;
				tmp = tmp->next;
			}
			env->list = env->list->next;
		}
		env->list = lst;
		//move_back(img);
		trace_point(img->env, img);
	}
	if (keycode == 1)
	{
		get_next_line(0, &line);
		{
			printf("Line %s\n", line);
			lst = img->env->list;
			int	i = 0;
			split = ft_strsplit(line, ' ');
			while (lst)
				{
					((t_room*)lst->content)->clr = 0xFFFFFF;
					lst = lst->next;
				}
			lst = img->env->list;
			while (split[i])
			{
				name = ft_strdup((char*)(ft_strchr(split[i], '-') + 1));
				while (lst)
				{
					if (ft_strcmp(((t_room*)lst->content)->name, name) == 0)
						((t_room*)lst->content)->clr =0xFF00;
					lst = lst->next;
				}
				++i;
			}
		}
		trace_point(img->env, img);
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

void	hooker(t_mlx *mlx)
{
	printf("Xuk\n");
	mlx_hook(mlx->win_ptr, 2, 0, key_press, mlx);
}