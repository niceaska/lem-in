/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:11:11 by jschille          #+#    #+#             */
/*   Updated: 2019/06/23 17:14:38 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

#define HIGHT 1080
# define WIDTH 1920

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

# define unint unsigned int

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;


typedef struct		s_room
{
	char			*name;
	unint			index;
	t_list			*links;
	int				coords[2];
	unint			clr;
}					t_room;

typedef struct		s_env
{
	unint			ants;
	t_list			*list;
	t_list			*start;
	t_list			*end;
}					t_env;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	unint	*img_data;
	t_env	*env;
	int		bpp;
	int		size_line;
	int		alpha;
	/*
	**	x_min x_max y_min y_max
	*/
	int		extrem[4];
}				t_mlx;
t_env			*parser(void);
void			ft_error(t_env *e);
t_room	*get_room(char *line, t_env **env, short comm);
void	set_links(char *line, t_env **env);
void	set_ants(char *line, t_env **env);
void	parser_comment(char *line, t_env **env);
void	set_rooms(char *line, t_env **env, unint clr);
void			err_out(int e, char *line, t_env *env);
void	display_out(t_env *env);
void			draw_line(unint *data, t_point a, t_point b);
void	hooker(t_mlx *mlx);
void			trace_point(t_env *env, t_mlx *mlx);

#endif