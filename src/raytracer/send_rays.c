/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:48:28 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 14:14:14 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Traces a ray and returns the color of the closest object hit.
 *
 * @param ray The ray to trace.
 * @return The color of the closest object hit.
 */
uint32_t	ft_trace_ray(t_ray *ray)
{
	int			i;
	float		closest;
	float		hit;
	uint32_t	color;
	t_program	*program;

	i = 0;
	closest = INFINITY;
	program = ft_get_program();
	color = BACKGROUND_COLOR;
	while (i < program->objs_len)
	{
		if (program->objs[i].type == SPHERE)
			hit = ft_sphere_hit(&program->objs[i], ray);
		if (program->objs[i].type == PLANE)
			hit = ft_plane_hit(&program->objs[i], ray);
		if (program->objs[i].type == CYLINDER)
			hit = ft_cylinder_hit(&program->objs[i], ray);
		if (hit < ft_get_first_obj(CAMERA)->s_camera.focal_length)
			hit = INFINITY;
		if (hit < closest)
			color = program->objs[i].color;
		if (hit < closest)
			closest = hit;
		i++;
	}
	return (color);
}

/**
 * Sends a ray for a pixel.
 *
 * @param x The x coordinate of the pixel.
 * @param y The y coordinate of the pixel.
 * @param camera The camera.
 * @return The color of the pixel.
 */
uint32_t	ft_send_ray(int x, int y, t_object *camera)
{
	t_ray		ray;
	uint32_t	color;
	float		u;
	float		v;
	t_vector3	temp_vec;

	ray.origin = &camera->pos;
	u = ((float)x + ft_randf()) / (float)(WIN_WIDTH - 1);
	v = 1 - ((float)y + ft_randf()) / (float)(WIN_HEIGHT - 1);
	ray.direction = &(t_vector3){camera->s_camera.ll_corner->x,
		camera->s_camera.ll_corner->y, camera->s_camera.ll_corner->z};
	ft_v3_init(&temp_vec, camera->s_camera.horizontal->x * u,
		camera->s_camera.horizontal->y * u, camera->s_camera.horizontal->z * u);
	ft_v3_add_ip(ray.direction, &temp_vec);
	ft_v3_init(&temp_vec, camera->s_camera.vertical->x * v,
		camera->s_camera.vertical->y * v, camera->s_camera.vertical->z * v);
	ft_v3_add_ip(ray.direction, &temp_vec);
	ft_v3_sub_ip(ray.direction, &camera->pos);
	color = ft_trace_ray(&ray);
	return (color);
}
