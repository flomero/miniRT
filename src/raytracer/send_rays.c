/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:48:28 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 14:01:09 by flfische         ###   ########.fr       */
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
	while (i < program->object_count)
	{
		if (program->objects[i].type == SPHERE)
		{
			hit = ft_sphere_hit(&program->objects[i], ray);
			if (hit < closest)
			{
				color = program->objects[i].color;
				closest = hit;
			}
		}
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

	ray.origin = camera->pos;
	u = ((float)x + ft_randf()) / (float)(WIN_WIDTH - 1);
	v = ((float)y + ft_randf()) / (float)(WIN_HEIGHT - 1);
	ray.direction = ft_v3_sub(ft_v3_add(ft_v3_add(camera->s_camera.ll_corner,
					ft_v3_scalar(camera->s_camera.horizontal, u)),
				ft_v3_scalar(camera->s_camera.vertical, v)), camera->pos);
	color = ft_trace_ray(&ray);
	free(ray.direction);
	return (color);
}
