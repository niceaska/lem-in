/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:11:03 by jschille          #+#    #+#             */
/*   Updated: 2019/06/23 18:22:33 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static t_mlx	*set_data(t_env *env)
{
	t_mlx	*mlx;
	int		i;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		err_out(0, NULL, env);
	mlx->bpp = 4;
	mlx->size_line = WIDTH;
	mlx->alpha = 1;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HIGHT, "map");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HIGHT);
	mlx->img_data = (unsigned int*)mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp), &(mlx->size_line), &(mlx->alpha));
	mlx->env = env;
	i = -1;
	while (++i < 4)
		mlx->extrem[i] = 0;
	return (mlx);
}

static void		DrawPoint(unint *data, int x, int y, unint clr)
{
	data[x * WIDTH + y] = clr;
	//printf("a.clt = %x	b.clt = %x\n", *clr_a, *clr_b);
}

static void		draw_circle(unint *data, int x0, int y0, int R, unint clr)
{
	int x = R;
    int y = 0;
    int radiusError = 1 - x;
    while (x >= y && x0 >= R && y0 >= R && x0 < (HIGHT - R) && y0 < (WIDTH - R))
    {
        DrawPoint(data, x + x0, y + y0, clr);
        DrawPoint(data, y + x0, x + y0, clr);
        DrawPoint(data, -x + x0, y + y0, clr);
        DrawPoint(data, -y + x0, x + y0, clr);
        DrawPoint(data, -x + x0, -y + y0, clr);
        DrawPoint(data, -y + x0, -x + y0, clr);
        DrawPoint(data, x + x0, -y + y0, clr);
        DrawPoint(data, y + x0, -x + y0, clr);
        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void			trace_point(t_env *env, t_mlx *mlx)
{
	t_list	*lst;
	t_list	*tmp;
	t_room	*room;
	t_point	a;
	t_point	b;

	lst = env->list;
	while (lst)
	{
		//printf("X %d\n", ((t_room*)lst->content)->coords[0]);
		draw_circle(mlx->img_data, ((t_room*)lst->content)->coords[0], ((t_room*)lst->content)->coords[1],
					10, ((t_room*)lst->content)->clr);
		room = (t_room*)lst->content;
		tmp = room->links;
		a.x = room->coords[1];
		a.y = room->coords[0];
		while (tmp)
		{
			
			b.x = ((t_room*)tmp->content)->coords[1];
			b.y = ((t_room*)tmp->content)->coords[0];
			printf("a.x %d	a.y %d	b.x %d	b.y %d\n", a.x, a.y, b.x, b.y);
			draw_line(mlx->img_data, a, b);
			tmp = tmp->next;
		}
		lst = lst->next;
	}
}

void	display_out(t_env *env)
{
	t_mlx	*mlx;

	mlx = set_data(env);
	trace_point(env, mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	//mlx_hook(mlx->win_ptr, 2, 0, key_press, &dd);
	hooker(mlx);
	mlx_loop(mlx->mlx_ptr);
	
}