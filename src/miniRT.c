/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/09 17:03:19 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program	*ft_get_program(void)
{
	static t_program	program;

	return (&program);
}

void	dummy_data(t_program *program)
{
	program->objects = malloc(sizeof(t_object) * 2);
	program->objects[0].type = CAMERA;
	program->objects[0].pos = ft_v3_new(0.0, 0.0, 0.0);
	program->objects[0].s_camera.fov = 90.0;
	program->objects[0].s_camera.orientation = ft_v3_new(0.0, 0.0, 1.0);
	ft_v3_normal_ip(program->objects[0].s_camera.orientation);
	program->objects[0].s_camera.focal_length = 1.0;
	program->objects[1].type = SPHERE;
	program->objects[1].color = 0x00FF00FF;
	program->objects[1].pos = ft_v3_new(0.0, 0.0, -1.0);
	program->objects[1].s_sphere.diameter = 1.0;
	program->object_count = 2;
}

void	loop_pixels(t_program *program)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color = ft_send_ray(x, y, &program->objects[0]);
			mlx_put_pixel(program->image, x, y, color);
			x++;
		}
		y++;
	}
}

void	calculate_viewport(t_object *camera)
{
	float	aspect_ratio;
	float	theta;

	aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	theta = camera->s_camera.fov * M_PI / 180.0;
	camera->s_camera.viewport_height = 2.0;
	camera->s_camera.viewport_width = aspect_ratio
		* camera->s_camera.viewport_height;
	camera->s_camera.horizontal = ft_v3_new(camera->s_camera.viewport_width,
			0.0, 0.0);
	camera->s_camera.vertical = ft_v3_new(0.0, camera->s_camera.viewport_height,
			0.0);
	camera->s_camera.lower_left_corner = ft_v3_sub(ft_v3_sub(ft_v3_sub(camera->pos,
					ft_v3_div_ip(camera->s_camera.horizontal, 2.0)),
				ft_v3_div_ip(camera->s_camera.vertical, 2.0)), ft_v3_new(0.0,
				0.0, camera->s_camera.focal_length));
	printf("lower_left_corner: %f, %f, %f\n",
		camera->s_camera.lower_left_corner->x,
		camera->s_camera.lower_left_corner->y,
		camera->s_camera.lower_left_corner->z);
	printf("horizontal: %f, %f, %f\n", camera->s_camera.horizontal->x,
		camera->s_camera.horizontal->y, camera->s_camera.horizontal->z);
	printf("vertical: %f, %f, %f\n", camera->s_camera.vertical->x,
		camera->s_camera.vertical->y, camera->s_camera.vertical->z);
	printf("viewport_width: %f\n", camera->s_camera.viewport_width);
	printf("viewport_height: %f\n", camera->s_camera.viewport_height);
	printf("focal_length: %f\n", camera->s_camera.focal_length);
}

int	main(void)
{
	t_program	*program;

	program = ft_get_program();
	if (ft_mlx_init())
		return (1);
	dummy_data(program);
	calculate_viewport(&program->objects[0]);
	mlx_loop_hook(program->mlx, ft_key_hook, program);
	loop_pixels(program);
	mlx_loop(program->mlx);
	return (0);
}
