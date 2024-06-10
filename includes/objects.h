/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:49:15 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 13:13:31 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

typedef struct s_vector3	t_vector3;
typedef struct s_vector2	t_vector2;

typedef enum e_object_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	OBJECT_COUNT,
}							t_object_type;

typedef struct s_object
{
	uint32_t				color;
	t_vector3				*pos;
	t_object_type			type;
	union
	{
		struct
		{
			float			ratio;
		} s_ambient_light;
		struct
		{
			t_vector3		*orientation;
			float			fov;
			float			viewport_width;
			float			viewport_height;
			t_vector3		*ll_corner;
			t_vector3		*horizontal;
			t_vector3		*vertical;
			float			focal_length;
		} s_camera;
		struct
		{
			float			brightness;
		} s_light;
		struct
		{
			float			diameter;
		} s_sphere;
		struct
		{
			t_vector3		*normal;
		} s_plane;
		struct
		{
			float			diameter;
			float			height;
			t_vector3		*normal;
		} s_cylinder;
	};
}							t_object;

#endif
