/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:27:05 by lgigi             #+#    #+#             */
/*   Updated: 2019/06/07 19:01:57 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BFS_H
# define FT_BFS_H

typedef struct	s_bfs
{
	int			start;
	int			end;
	int			vrt;
	int			*p;
	int			*d;
}				t_bfs;

t_bfs			*init_bfs(int start, int end, int v);
int				*init_arr(int vert, char c);
int				*init_bfs_arr(t_bfs **bs);

#endif
