/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:11 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 15:09:35 by klamprak         ###   ########.fr       */
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
typedef struct s_ray
{
	t_vector3	*origin;
	t_vector3	*direction;
}				t_ray;

typedef struct s_hit
{
	float		t;
	t_vector3	p;
	t_vector3	n;
	t_ray		*ray;
	t_object	*obj;
}				t_hit;

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
	t_object	*objs;
	int			objs_len;
	int			current_sample;
	uint32_t	colors_avgs[WIN_WIDTH][WIN_HEIGHT];
	t_hit		hit;
	t_object	*ambient_light;
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
void			ft_ray_init(t_ray *ray, t_vector3 *origin,
					t_vector3 *direction);

// OBJECT HIT FUNCTIONS
t_bool			ft_hit(t_ray *ray, t_object *obj, t_hit *hit);

typedef float	(*t_hit_func)(t_object *sphere, t_ray *ray);
typedef int		(*t_normal_func)(t_hit *hit, t_ray *ray);
t_hit_func		*ft_get_hit_func(void);
t_normal_func	*ft_get_normal_func(void);
float			ft_sphere_hit(t_object *sphere, t_ray *ray);
float			ft_plane_hit(t_object *plane, t_ray *ray);
float			ft_cylinder_hit(t_object *cyl, t_ray *ray);
int				ft_sphere_normal(t_hit *hit, t_ray *ray);
int				ft_plane_normal(t_hit *hit, t_ray *ray);
int				ft_cylinder_normal(t_hit *hit, t_ray *ray);


// OBJECT UTILS
t_object		*ft_get_first_obj(t_object_type type);
void			ft_calculate_viewport(t_object *camera);

// ERRORS
void			ft_print_error(const char *error);
void			print_err_extend(const char *msg1, const char *msg2);

// PARSING
int				is_valid_parsing(char *fname);
int				init_struct(char *fname, int len);
int				get_obj(char **tokens, t_object *obj);
int				is_valid_obj_nbr(t_object *objs);

// PARSING UTILS
int				get_arr_len(char **arr);
void			print_rgb(uint32_t color);
void			print_objs(t_object *obj);

// PARSING UTILS2
int				is_int(char *str);
int				is_float(char *str);
int				get_vector(t_vector3 *vector, char *str);
int				in_range(t_vector3 *vector, float start, float end);
int				get_color(char *token, uint32_t *result);

// PARSING UTILS3
void			free_str_arr(char **arr);
// void			free_obj_arr(t_object **arr);
int				get_cy(char **tokens, t_object *obj);
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

// COLORS
void			ft_color_to_float(uint32_t color, t_color *fcolor);
uint32_t		ft_color_from_float(t_color color);
float			ft_color_clamp(float color);
uint32_t		ft_avg_color(uint32_t *colors, size_t x);
uint32_t		ft_new_avg_color(uint32_t color, u_int32_t avg, int factor);
t_color			*ft_color_float_mult(t_color color, float ratio,
					t_color *result);
t_color			*ft_color_color_mult(t_color color1, t_color color2,
					t_color *result);
t_color			*ft_color_color_add(t_color color1, t_color color2,
					t_color *result);

// LIGHT
t_color			*ft_compute_lights(t_color *light_col, const t_hit *hit,
					t_program *program);
t_color			*ft_compute_phong(t_color *phong_col, const t_object *light,
					const t_hit *hit, t_program *program);
t_color			*ft_compute_ambient(t_color *result, const t_color color);
t_color			*ft_compute_diffuse(t_color *diff_col, const t_hit *rec,
					const t_object *light, const t_vector3 *light_dir);
t_color			*ft_compute_specular(t_color *spec_col, const t_hit *rec,
					const t_object *light, const t_vector3 *light_dir);

// MATHS
float			ft_randf(void);
float			ft_randf_range(float min, float max);
t_vector3		*ft_v3_add(const t_vector3 *a, const t_vector3 *b);
t_vector3		*ft_v3_add_ip(t_vector3 *a, const t_vector3 *b);
t_vector3		*ft_v3_crossprod(const t_vector3 *a, const t_vector3 *b);
t_vector3		*ft_v3_crossprod_ip(t_vector3 *a, const t_vector3 *b);
t_vector3		*ft_v3_copy(const t_vector3 *v);
t_vector3		*ft_v3_div(const t_vector3 *a, float scalar);
t_vector3		*ft_v3_div_ip(t_vector3 *a, float scalar);
float			ft_v3_dotprod(const t_vector3 *a, const t_vector3 *b);
t_vector3		*ft_v3_init(t_vector3 *v, float x, float y, float z);
float			ft_v3_len(const t_vector3 *a);
t_vector3		*ft_v3_new(float x, float y, float z);
t_vector3		*ft_v3_normal(const t_vector3 *a);
t_vector3		*ft_v3_normal_ip(t_vector3 *a);
t_vector3		*ft_v3_rand(void);
t_vector3		*ft_v3_rand_ip(t_vector3 *vec);
t_vector3		*ft_v3_rand_range(float min, float max);
t_vector3		*ft_v3_rand_range_ip(t_vector3 *vec, float min, float max);
t_vector3		*ft_v3_rand_unit(t_vector3 *vec);
t_vector3		*ft_v3_scalar(const t_vector3 *a, float scalar);
t_vector3		*ft_v3_scalar_ip(t_vector3 *a, float scalar);
t_vector3		*ft_v3_sub(const t_vector3 *a, const t_vector3 *b);
t_vector3		*ft_v3_sub_ip(t_vector3 *a, const t_vector3 *b);

#endif
