/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:11 by flfische          #+#    #+#             */
/*   Updated: 2024/07/06 16:09:36 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// Includes
# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
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
	t_vector3		*origin;
	t_vector3		*direction;
	int				depth;
}					t_ray;

// n: normal, p: point, t: distance
typedef struct s_hit
{
	double			t;
	t_vector3		p;
	t_vector3		n;
	t_vector3		uvn;
	t_ray			*ray;
	t_object		*obj;
	t_color			local_color;
}					t_hit;

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_program
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_vector2		img_size;
	t_object		*objs;
	int				objs_len;
	int				current_sample;
	int				max_samples;
	int				bounces;
	uint32_t		colors_avgs[WIN_WIDTH * WIN_HEIGHT];
	pthread_t		threads[MAX_THREADS];
	int				thread_samples[MAX_THREADS];
	pthread_mutex_t	*stop;
	t_bool			stop_threads;
	int				thread_count;
	uint32_t		void_color;
	t_color			ambient_base;
}					t_program;

// FUNCTIONS
t_program			*ft_get_program(void);
void				ft_init_rt(t_program *program);
void				join_threads(t_program *program);
void				ft_debug_message(char *message);

// MLX
int					ft_mlx_init(char *filename);
void				ft_render(void *param);
void				ft_key_hook(mlx_key_data_t key_data, void *param);
void				ft_render_multithread(void *param);

// RAYTRACER
void				loop_pixels(t_program *program, int min_x, t_vector2 *max,
						int sample);
uint32_t			ft_send_ray(int x, int y, t_object *camera);
uint32_t			ft_trace_ray(t_ray *ray);
void				ft_ray_init(t_ray *ray, t_vector3 *origin,
						t_vector3 *direction);

// OBJECT HIT FUNCTIONS
t_bool				ft_hit(t_ray *ray, t_object *obj, t_hit *hit);

typedef double		(*t_hit_func)(t_object *sphere, t_ray *ray);
typedef int			(*t_normal_func)(t_hit *hit, t_ray *ray);
typedef int			(*t_uv_func)(t_hit *hit, t_vector2 *uv);
t_hit_func			*ft_get_hit_func(void);
t_normal_func		*ft_get_normal_func(void);
t_uv_func			*ft_get_uv_func(void);
double				ft_sphere_hit(t_object *sphere, t_ray *ray);
int					ft_sphere_uv(t_hit *hit, t_vector2 *uv);
double				ft_plane_hit(t_object *plane, t_ray *ray);
double				ft_cylinder_hit(t_object *cyl, t_ray *ray);
double				ft_cone_hit(t_object *cone, t_ray *ray);
double				ft_triangle_hit(t_object *triangle, t_ray *ray);
int					ft_sphere_normal(t_hit *hit, t_ray *ray);
int					ft_plane_normal(t_hit *hit, t_ray *ray);
int					ft_cylinder_normal(t_hit *hit, t_ray *ray);
int					ft_cone_normal(t_hit *hit, t_ray *ray);
int					ft_triangle_normal(t_hit *hit, t_ray *ray);

// OBJECT UTILS
t_object			*ft_get_first_obj(t_object_type type);
t_object			*ft_get_nth_obj(t_object_type type, int n);
void				ft_calculate_viewport(t_object *camera);
double				get_min(double t1, double t2, double t3, double t4);
double				hit_top_bot(t_object *obj, t_ray *ray, const double radius,
						t_object *cyl);

// CYLINDER UTILS
bool				inter_disk(t_ray *ray, t_object *disk_pl, double *t,
						double radius);
void				get_plane(t_object *cylinder, t_object *to_init_pl,
						bool is_top);
bool				is_sol_equation(double *abc, double *t0, double *t1);

// ERRORS
void				ft_print_error(const char *error);
void				print_err_extend(const char *msg1, char *msg2,
						int is_alloc);

// PARSING
int					is_valid_parsing(char *fname);
int					init_struct(char *fname, int len);
int					get_obj(char **tokens, t_object *obj);
int					is_valid_obj_nbr(t_object *objs);
void				ft_default_material(t_object *material);
void				ft_compute_if_reflective(t_object *material);

// PARSING UTILS
int					get_arr_len(char **arr);
void				print_rgb(uint32_t color);
void				print_objs(t_object *obj);

// PARSING UTILS2
int					is_int(char *str);
int					is_float(char *str);
int					get_vector(t_vector3 *vector, char *str);
int					in_range(t_vector3 *vector, double start, double end);
int					get_color(char *token, uint32_t *result);

// PARSING UTILS3
void				free_str_arr(char **arr);
int					get_nbr_of_lines(char *fname);
uint32_t			int_to_rgb(int red, int green, int blue);

// CUSTOM SPLIT
char				**ft_multi_split(char const *s, char *set);

// PARSING HANDLERS
int					get_a(char **tokens, t_object *obj);
int					get_c(char **tokens, t_object *obj);
int					get_l(char **tokens, t_object *obj);
int					get_sp(char **tokens, t_object *obj);
int					get_pl(char **tokens, t_object *obj);
int					get_tr(char **tokens, t_object *obj);

// PARSING HANDLERS2
int					get_co(char **tokens, t_object *obj);
int					get_cy(char **tokens, t_object *obj);

// COLORS
void				ft_color_to_float(uint32_t color, t_color *fcolor);
uint32_t			ft_color_from_float(t_color color);
double				ft_color_clamp(double color);
uint32_t			ft_avg_color(uint32_t *colors, size_t x);
uint32_t			ft_new_avg_color(uint32_t color, u_int32_t avg, int factor);
t_color				*ft_color_float_mult(t_color color, double ratio,
						t_color *result);
t_color				*ft_color_color_mult(t_color color1, t_color color2,
						t_color *result);
t_color				*ft_color_color_add(t_color color1, t_color color2,
						t_color *result);

// LIGHT
t_color				*ft_compute_lights(t_color *light_col, t_hit *hit,
						t_program *program);
t_color				*ft_compute_phong(t_color *phong_col, const t_object *light,
						const t_hit *hit, t_program *program);
t_color				*ft_compute_ambient(t_color *result, const t_color color);
void				ft_init_ambient_base(t_color *result);
t_color				*ft_compute_diffuse(t_color *diff_col, const t_hit *rec,
						const t_object *light, const t_vector3 *light_dir);
t_color				*ft_compute_specular(t_color *spec_col, const t_hit *rec,
						const t_object *light, const t_vector3 *light_dir);
t_color				*ft_compute_reflection(t_color *refl_col, const t_hit *rec,
						int depth);

// TEXTURES
t_bool				ft_assign_mat_tex(void);
void				ft_assign_own_tm(t_object *obj);
uint32_t			ft_checkerboard(t_object *material, const t_vector3 *point,
						t_color *result);
uint32_t			ft_checkerboard_uv(t_object *material, t_color *result,
						t_hit *hit);
t_bool				get_basic_mat(char **tokens, t_object *obj);
t_bool				get_adv_mat(char **tokens, t_object *obj);
t_bool				get_tex_checker(char **tokens, t_object *obj, t_bool UV);
t_bool				get_tex_file(char **tokens, t_object *obj);
t_bool				get_bump(char **tokens, t_object *obj);
t_bool				ft_check_dup_mat(void);
t_bool				ft_check_dup_tex(void);
t_bool				ft_check_dup_bump(void);
uint32_t			ft_texture_file(t_object *obj, t_hit *hit, t_color *result);
uint32_t			ft_get_pixel_color(mlx_texture_t *texture, int x, int y,
						t_color *result);

// MATHS
double				ft_randf(void);
double				ft_randf_range(double min, double max);
t_vector3			*ft_v3_add(const t_vector3 *a, const t_vector3 *b);
t_vector3			*ft_v3_add_ip(t_vector3 *a, const t_vector3 *b);
t_vector3			*ft_v3_crossprod(const t_vector3 *a, const t_vector3 *b);
t_vector3			*ft_v3_crossprod_ip(t_vector3 *a, const t_vector3 *b);
t_vector3			*ft_v3_copy(const t_vector3 *v);
t_vector3			*ft_v3_div(const t_vector3 *a, double scalar);
t_vector3			*ft_v3_div_ip(t_vector3 *a, double scalar);
double				ft_v3_dotprod(const t_vector3 *a, const t_vector3 *b);
t_vector3			*ft_v3_init(t_vector3 *v, double x, double y, double z);
double				ft_v3_len(const t_vector3 *a);
t_vector3			*ft_v3_new(double x, double y, double z);
t_vector3			*ft_v3_normal(const t_vector3 *a);
t_vector3			*ft_v3_normal_ip(t_vector3 *a);
t_vector3			*ft_v3_rand(void);
t_vector3			*ft_v3_rand_ip(t_vector3 *vec);
t_vector3			*ft_v3_rand_range(double min, double max);
t_vector3			*ft_v3_rand_range_ip(t_vector3 *vec, double min,
						double max);
t_vector3			*ft_v3_rand_unit(t_vector3 *vec);
t_vector3			*ft_v3_scalar(const t_vector3 *a, double scalar);
t_vector3			*ft_v3_scalar_ip(t_vector3 *a, double scalar);
t_vector3			*ft_v3_sub(const t_vector3 *a, const t_vector3 *b);
t_vector3			*ft_v3_sub_ip(t_vector3 *a, const t_vector3 *b);

#endif
