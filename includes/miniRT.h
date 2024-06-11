/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:11 by flfische          #+#    #+#             */
/*   Updated: 2024/06/11 09:45:31 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// Includes
# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

// HEADERS
# include "config.h"
# include "objects.h"

// TYPEDEFS
typedef struct s_program
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_vector2	img_size;
	t_object	*objs;
	int			objs_len;
}				t_program;

// FUNCTIONS
t_program		*ft_get_program(void);

// MLX
int				ft_mlx_init(void);
void			ft_key_hook(void *param);

// ERRORS
void			ft_print_error(const char *error);
void			print_err_extend(const char *msg1, const char *msg2);

// PARSING
int				is_valid_parsing(char *fname);
int				init_struct(char *fname, int len);
int				get_obj(char **tokens, t_object *obj);
int				is_valid_obj_nbr(t_object	*objs);

// PARSING UTILS
int				get_arr_len(char **arr);
void			print_rgb(uint32_t color);
void			print_objs(void);

// PARSING UTILS2
int				is_int(char *str);
int				is_float(char *str);
int				get_vector(t_vector3 *vector, char *str);
int				in_range(t_vector3 *vector, float start, float end);
int				get_color(char *token, uint32_t *result);

// PARSING UTILS3
void			free_str_arr(char **arr);
// void			free_obj_arr(t_object **arr);
int				get_cy(char **tokens, t_object	*obj);
int				get_nbr_of_lines(char *fname);
uint32_t		int_to_rgb(int red, int green, int blue);

// CUSTOM SPLIT
char			**ft_multi_split(char const *s, char *set);

// PARSING HANDLERS
int				get_a(char **tokens, t_object *obj);
int				get_c(char **tokens, t_object *obj);
int				get_l(char **tokens, t_object *obj);
int				get_sp(char **tokens, t_object *obj);
int				get_pl(char **tokens, t_object *obj);

#endif
