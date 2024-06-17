/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:49:15 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 15:36:38 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

// TYPEDEFS
typedef struct s_vector3
{
	float				x;
	float				y;
	float				z;
}						t_vector3;

typedef struct s_vector2
{
	float				x;
	float				y;
}						t_vector2;

typedef struct s_material
{
	float				ambient;
	float				diffuse;
	float				specular;
	float				shininess;
	float				reflectivness;
}						t_material;

typedef enum e_object_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	OBJECT_COUNT,
}						t_object_type;

typedef struct s_color
{
	float				r;
	float				g;
	float				b;
}						t_color;

typedef struct s_object
{
	uint32_t			color;
	t_color				color_f;
	t_vector3			pos;
	t_object_type		type;
	t_material			material;
	union
	{
		struct
		{
			float		ratio;
		} s_ambient_light;
		struct
		{
			t_vector3	normal;
			float		fov;
			float		vp_width;
			float		vp_height;
			t_vector3	*ll_corner;
			t_vector3	*horizontal;
			t_vector3	*vertical;
			t_vector3	*look_at;
			float		focal_length;
		} s_camera;
		struct
		{
			float		brightness;
		} s_light;
		struct
		{
			float		diameter;
		} s_sphere;
		struct
		{
			t_vector3	normal;
		} s_plane;
		struct
		{
			float		diameter;
			float		height;
			t_vector3	normal;
		} s_cylinder;
	};
}						t_object;

#endif
