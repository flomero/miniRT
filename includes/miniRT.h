/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:11 by flfische          #+#    #+#             */
/*   Updated: 2024/06/09 15:47:35 by klamprak         ###   ########.fr       */
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
typedef struct s_vector3
{
	float		x;
	float		y;
	float		z;
}				t_vector3;

typedef struct s_vector2
{
	float		x;
	float		y;
}				t_vector2;

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
void			free_str_arr(char **arr);
void			free_obj_arr(t_object **arr);

// PARSING HANDLERS
t_object		*get_A(char **tokens);
t_object		*get_C(char **tokens);
t_object		*get_L(char **tokens);
t_object		*get_sp(char **tokens);
t_object		*get_pl(char **tokens);
t_object		*get_cy(char **tokens);


#endif
