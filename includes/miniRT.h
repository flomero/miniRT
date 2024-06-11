/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:11 by flfische          #+#    #+#             */
/*   Updated: 2024/06/11 10:01:34 by flfische         ###   ########.fr       */
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

typedef struct s_ray
{
	t_vector3	*origin;
	t_vector3	*direction;
}				t_ray;

typedef enum e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct s_program
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_vector2	img_size;
	t_object	*objects;
	int			object_count;
	int			current_sample;
	uint32_t	colors_avgs[WIN_WIDTH][WIN_HEIGHT];
}				t_program;

// FUNCTIONS
t_program		*ft_get_program(void);

// MLX
int				ft_mlx_init(void);
void			ft_render(void *param);
void			ft_key_hook(mlx_key_data_t key_data, void *param);

// RAYTRACER
void			loop_pixels(t_program *program);
uint32_t		ft_send_ray(int x, int y, t_object *camera);
uint32_t		ft_trace_ray(t_ray *ray);

// OBJECT HIT FUNCTIONS
float			ft_sphere_hit(t_object *sphere, t_ray *ray);

// OBJECT UTILS
t_object		*ft_get_first_obj(t_object_type type);
void			ft_calculate_viewport(t_object *camera);

// ERRORS
void			ft_print_error(const char *error);

// COLORS
uint32_t		ft_avg_color(uint32_t *colors, size_t x);
uint32_t		ft_new_avg_color(uint32_t color, u_int32_t avg, int factor);

// MATHS
float			ft_randf(void);
t_vector3		*ft_v3_add(t_vector3 *a, t_vector3 *b);
t_vector3		*ft_v3_add_ip(t_vector3 *a, t_vector3 *b);
t_vector3		*ft_v3_crossprod(t_vector3 *a, t_vector3 *b);
t_vector3		*ft_v3_crossprod_ip(t_vector3 *a, t_vector3 *b);
t_vector3		*ft_v3_copy(t_vector3 *v);
t_vector3		*ft_v3_div(t_vector3 *a, float scalar);
t_vector3		*ft_v3_div_ip(t_vector3 *a, float scalar);
float			ft_v3_dotprod(t_vector3 *a, t_vector3 *b);
t_vector3		*ft_v3_init(t_vector3 *v, float x, float y, float z);
float			ft_v3_len(t_vector3 *a);
t_vector3		*ft_v3_new(float x, float y, float z);
t_vector3		*ft_v3_normal(t_vector3 *a);
t_vector3		*ft_v3_normal_ip(t_vector3 *a);
t_vector3		*ft_v3_scalar(t_vector3 *a, float scalar);
t_vector3		*ft_v3_scalar_ip(t_vector3 *a, float scalar);
t_vector3		*ft_v3_sub(t_vector3 *a, t_vector3 *b);
t_vector3		*ft_v3_sub_ip(t_vector3 *a, t_vector3 *b);

#endif
