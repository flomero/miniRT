/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:28:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/10 22:50:03 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	print_pl_cy_sp(t_object *obj);
static void	print_a_c_l(t_object *obj);

int	get_arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	print_rgb(uint32_t color)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	printf("RGB(%d, %d, %d)\n", red, green, blue);
}

void	print_objs(void)
{
	t_object	**objs;
	int			i;

	objs = ft_get_program()->objs;
	if (!objs)
		return ;
	i = 0;
	while (objs[i])
	{
		printf("Object %d:\nID: %d\n", i, objs[i]->type);
		print_a_c_l(objs[i]);
		print_pl_cy_sp(objs[i]);
		if (objs[i]->type != 0)
			printf("Position: %.2f %.2f %.2f\n", objs[i]->pos.x, \
			objs[i]->pos.y, objs[i]->pos.z);
		if (objs[i]->type != 1)
		{
			printf("Color: %d, ", objs[i]->color);
			print_rgb(objs[i]->color);
		}
		printf("\n---------------- --------------------\n");
		i++;
	}
}

static void	print_a_c_l(t_object *obj)
{
	if (obj->type == 0)
		printf("Type: Ambient lightning\nRatio: %.2f\n", \
		obj->s_ambient_light.ratio);
	else if (obj->type == 1)
	{
		printf("Type: Camera\nFOV: %.2f\n", \
		obj->s_camera.fov);
		printf("Normal: %.2f %.2f %.2f\n", obj->s_camera.normal.x, \
		obj->s_camera.normal.y, obj->s_camera.normal.z);
	}
	else if (obj->type == 2)
		printf("Type: Light\nBrightness: %.2f\n", \
		obj->s_light.brightness);
}

static void	print_pl_cy_sp(t_object *obj)
{
	if (obj->type == 3)
		printf("Type: Sphere\nDiameter: %.2f\n", \
		obj->s_sphere.diameter);
	else if (obj->type == 4)
	{
		printf("Type: Plane\n");
		printf("Normal: %.2f %.2f %.2f\n", obj->s_plane.normal.x, \
		obj->s_plane.normal.y, obj->s_plane.normal.z);
	}
	else if (obj->type == 5)
	{
		printf("Type: Cylinder\nDiameter: %.2f\nHeight: %.2f\n", \
		obj->s_cylinder.diameter, obj->s_cylinder.height);
		printf("Normal: %.2f %.2f %.2f\n", obj->s_cylinder.normal.x, \
		obj->s_cylinder.normal.y, obj->s_cylinder.normal.z);
	}
}
