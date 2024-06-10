/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:11 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 16:56:11 by klamprak         ###   ########.fr       */
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
	t_object	**objs;
}				t_program;

// FUNCTIONS
t_program		*ft_get_program(void);

// MLX
int				ft_mlx_init(void);
void			ft_key_hook(void *param);

// ERRORS
void			ft_print_error(const char *error);

// PARSING
int				is_valid_parsing(char *fname);
int				get_nbr_of_lines(char *fname);
int				init_struct(char *fname, int len);
t_object		*get_obj(char **tokens);
int				is_valid_obj_nbr(t_object	**objs);

// PARSING UTILS
void			free_str_arr(char **arr);
void			free_obj_arr(t_object **arr);
uint32_t		int_to_rgb(int red, int green, int blue);
int				get_arr_len(char **arr);
void			print_rgb(uint32_t color);
void			print_objs(void);

// PARSING UTILS2
int				is_int(char *str);
int				is_float(char *str);
int				get_vector(t_vector3 *vector, char *str);
int				in_range(t_vector3 *vector, float start, float end);
int				get_color(char *token, uint32_t *result);

// PARSING HANDLERS
t_object		*get_a(char **tokens);
t_object		*get_c(char **tokens);
t_object		*get_l(char **tokens);
t_object		*get_sp(char **tokens);
t_object		*get_pl(char **tokens);
t_object		*get_cy(char **tokens);

#endif
