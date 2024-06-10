/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:28:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/10 16:58:02 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

uint32_t	int_to_rgb(int red, int green, int blue)
{
	return (((uint32_t)red << 16) | ((uint32_t)green << 8) | (uint32_t)blue);
}

/**
 * @brief free an NULL terminated array of char pointers properly
 * ex. arr = ["El1", "el2", NULL]
 *
 * @param arr
 */
void	free_str_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/**
 * @brief free an NULL terminated array of t_object pointers properly
 * ex. arr = ["El1", "el2", NULL]
 *
 * @param arr
 */
void	free_obj_arr(t_object **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
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
		if (objs[i]->type == 0)
			printf("Type: Ambient lightning\nRatio: %.2f\n", \
			objs[i]->s_ambient_light.ratio);
		else if (objs[i]->type == 1)
		{
			printf("Type: Camera\nFOV: %.2f\n", \
			objs[i]->s_camera.fov);
			printf("Normal: %.2f %.2f %.2f\n", objs[i]->s_camera.normal.x, \
			objs[i]->s_camera.normal.y, objs[i]->s_camera.normal.z);
		}
		else if (objs[i]->type == 2)
			printf("Type: Light\nBrightness: %.2f\n", \
			objs[i]->s_light.brightness);
		else if (objs[i]->type == 3)
			printf("Type: Sphere\nDiameter: %.2f\n", \
			objs[i]->s_sphere.diameter);
		else if (objs[i]->type == 4)
		{
			printf("Type: Plane\n");
			printf("Normal: %.2f %.2f %.2f\n", objs[i]->s_plane.normal.x, \
			objs[i]->s_plane.normal.y, objs[i]->s_plane.normal.z);
		}
		else if (objs[i]->type == 5)
		{
			printf("Type: Cylinder\nDiameter: %.2f\nHeight: %.2f\n", \
			objs[i]->s_cylinder.diameter, objs[i]->s_cylinder.height);
			printf("Normal: %.2f %.2f %.2f\n", objs[i]->s_cylinder.normal.x, \
			objs[i]->s_cylinder.normal.y, objs[i]->s_cylinder.normal.z);
		}
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