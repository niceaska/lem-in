/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:22:16 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/01 12:37:07 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMMIN_H
# define FT_LEMMIN_H

# define HT_SIZE 10000
# define CURRIND(list) (list->data->index)
# define NXTIND(list) (list->next->data->index)
# define START bs->start->index
# define END bs->end->index
# define MIN_PATH ((int)list_size(p_arr[0]))

# define CHECK_FL (1 << 0)
# define FILE_FL (1 << 1)
# define ERROR_FL (1 << 2)
# define DEBUG_FL (1 << 3)
# define DEBUG_HT (1 << 4)
# define CHECK_NEG_FL (1 << 5)

# include <libft.h>
# include <limits.h>
# include <fcntl.h>

typedef unsigned int	t_unint;

typedef struct		s_data
{
	char			*name;
	int				index;
}					t_data;

typedef struct		s_node
{
	int				is_hold;
	t_data			*data;
	struct s_node	*next;
}					t_node;

typedef struct		s_queue
{
	struct s_node	*first;
	struct s_node	*last;
}					t_queue;

typedef struct		s_bfs
{
	t_data			*start;
	t_data			*end;
	int				stage;
	int				vrt;
	int				ants;
	int				*v;
	t_data			**p;
	t_node			**debug;
	int				*d;
}					t_bfs;

typedef struct		s_entry
{
	char			*key;
	t_data			*data;
	int				coords[2];
	struct s_entry	*next;
}					t_entry;

typedef struct		s_hashtable
{
	size_t			size;
	size_t			curr_size;
	struct s_entry	**tab;
}					t_hashtable;

typedef struct		s_room
{
	char			*name;
	t_unint			index;
	long			coords[2];
	short			comment;
}					t_room;

typedef struct		s_env
{
	int				fd;
	short			f;
	t_unint			ants;
	t_list			*list;
	t_list			*start;
	t_list			*end;
	t_list			*links;
	t_hashtable		*ht;
	t_hashtable		*coor_ht;
}					t_env;

void				err_out(int e, char *line, t_env *env);
t_env				*parser(int ac, char **argv);
void				set_rooms(char *line, t_env **env, short fl);
void				parser_comment(char *line, t_env **env);
void				set_ants(char *line, t_env **env);
void				set_links(char *line, t_env **env);
t_room				*get_room(char *line, t_env **env, short comm);
t_env				*env_init(int ac, char **argv);
t_bfs				*init_bfs(t_data *start, t_data *end, int v, int ants);
int					*init_arr(int vert, char c);
void				init_bfs_arr(t_bfs **bs);
t_node				**init_nodes_arr(int size);
void				refresh_bfs(t_node **p_arr, t_bfs **bs);
void				ft_find_path(t_node **p_arr, t_bfs *bs, int i);
t_node				**get_all_paths(t_node **p_arr, int i,
									t_node **arr, t_bfs *bs);
t_node				**get_paths_controller(t_node **arr, t_bfs *bs, int i);
void				free_bfs(t_bfs *bs);
int					bfs(t_node **arr, t_bfs *bs);
void				ft_enqueue(t_queue *queue, t_data *data);
t_data				*ft_dequeue(t_queue *queue);
t_data				*ft_peek_q(t_queue *queue);
int					is_empty_q(t_queue *queue);
t_queue				*init_queue(void);
t_queue				*init_queue_bfs(t_data *start);
int					list_empty(t_node *list);
int					push_back(t_node **node, t_data *data, short graph);
t_data				*list_pop(t_node **list);
void				list_push(t_node **node, t_data *data);
unsigned int		list_size(t_node *list);
void				free_list(t_node *list);
void				free_list_arr(t_node **arr, int size, short fl);
void				free_queue(t_queue *q);
void				free_hashtab(t_hashtable *map);
int					ft_addedge(t_node **arr, t_data *start, t_data *end);
t_data				*init_data(char *name, int index);
int					*init_rooms(int vrt, int start_index, int ants);
int					ft_set_htval(t_hashtable *hash_tab, const char *key,
													long *coor, int val);
t_hashtable			*init_hashtab(size_t size);
t_data				*get_entry(t_hashtable *hash_tab, const char *key);
void				print_res(t_env *e, t_node **p_arr, t_bfs *bs);
void				print_moves(t_node **p_arr, t_bfs *bs, int i, int j);
void				free_env(t_env *e);
void				ft_error(t_env *e);
void				bfs_controller(t_env *e, t_node **arr,
									t_node **p_arr, int size);
int					st_moves_ch(t_node **ants, int *rooms, t_bfs *bs, int *i);
void				set_is_hold(t_node *list, t_node **arr, int hold);
void				set_unaval(t_node *node, t_node *trav);
void				list_cmp(t_node *list1, t_node *list2, t_node **arr);
void				find_crosses(t_node **p_arr, t_node **arr);
int					find_min_index(int *paths, int p_count);
int					compare_double(t_bfs *bs, t_node *list1, t_node *list2);
t_node 				**find_doubles(t_bfs *bs, t_node **p_arr);
int					*check_unused_paths(t_node **p_arr, t_bfs *bs, int i, int j);
t_node				**choose_best_paths(t_bfs *bs, t_node **p1, t_node **p2);
t_node				**remove_unused_paths(t_bfs *bs, t_node **p_arr);
t_node				**realloc_paths(t_bfs *bs, t_node **p_arr);
t_node				*list_cpy(t_node *l);


/*
** Debug functions
*/

void				free_debug_arr(t_node **debug);
int					check_moves(t_node **moves, t_node **p_arr, int i, int j);
void				print_hash_val(t_hashtable *hash);
void				print_paths(t_node **p_arr, short fl);
void				debug_controller(t_bfs *bs, t_hashtable *ht,
										t_node **p_arr, short fl);

#endif
