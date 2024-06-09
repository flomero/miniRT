/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:48:28 by flfische          #+#    #+#             */
/*   Updated: 2024/06/09 17:02:43 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
				// printf("hit: %f\n", hit);
				color = program->objects[i].color;
				closest = hit;
			}
		}
		i++;
	}
	return (color);
}

uint32_t	ft_send_ray(int x, int y, t_object *camera)
{
	t_ray		ray;
	uint32_t	color;
	float		u;
	float		v;

	ray.origin = camera->pos;
	u = (float)x / (float)(WIN_WIDTH - 1);
	v = (float)y / (float)(WIN_HEIGHT - 1);
	ray.direction = ft_v3_sub(ft_v3_add(ft_v3_add(camera->s_camera.lower_left_corner,
					ft_v3_scalar(camera->s_camera.horizontal, u)),
				ft_v3_scalar(camera->s_camera.vertical, v)), camera->pos);
	// if (x < 10)
	// 	printf("ray.direction: %f %f %f\n", ray.direction->x, ray.direction->y,
	// 		ray.direction->z);
	color = ft_trace_ray(&ray);
	free(ray.direction);
	return (color);
}
