/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/11 10:34:06 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO:
		- replace pointers in malloc with arrays to improve speed
*/

#include "miniRT.h"

t_program	*ft_get_program(void)
{
	static t_program	program;

	return (&program);
}

void	dummy_data(t_program *program)
{
	program->object_count = 4;
	program->objects = malloc(sizeof(t_object) * program->object_count);
	program->objects[0].type = CAMERA;
	program->objects[0].pos = ft_v3_new(0.0, 0.0, 0.0);
	program->objects[0].s_camera.fov = 70.0;
	program->objects[0].s_camera.orientation = ft_v3_new(0.0, 0.0, 1.0);
	ft_v3_normal_ip(program->objects[0].s_camera.orientation);
	program->objects[0].s_camera.focal_length = 1.0;
	program->objects[1].type = SPHERE;
	program->objects[1].color = 0x00FF00FF;
	program->objects[1].pos = ft_v3_new(0.0, 0.0, -4.0);
	program->objects[1].s_sphere.diameter = 3.0;
	program->objects[2].type = SPHERE;
	program->objects[2].color = 0x0000FFFF;
	program->objects[2].pos = ft_v3_new(0.0, 0.0, -1.0);
	program->objects[2].s_sphere.diameter = 0.5;
	program->objects[3].type = SPHERE;
	program->objects[3].color = 0xFF0000FF;
	program->objects[3].pos = ft_v3_new(1.5, 0.0, -2.0);
	program->objects[3].s_sphere.diameter = 1.0;
}

void	leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char **argv)
{
	t_program	*program;

	if (DEBUG)
		atexit(leaks);
	if (argc != 2)
		return (0);
	if (!is_valid_parsing(argv[1]))
		printf("Parsing is not valid\n");
	else
		printf("Parsing is valid\n");
	if (DEBUG)
		print_objs();
	program = ft_get_program();
	if (ft_mlx_init())
		return (1);
	dummy_data(program);
	ft_calculate_viewport(&program->objects[0]);
	mlx_key_hook(program->mlx, ft_key_hook, program);
	mlx_loop_hook(program->mlx, ft_render, program);
	loop_pixels(program);
	mlx_loop(program->mlx);
	return (0);
}
