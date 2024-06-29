/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:49:15 by flfische          #+#    #+#             */
/*   Updated: 2024/06/28 18:32:51 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

// TYPEDEFS
typedef struct s_vector3
{
	double					x;
	double					y;
	double					z;
}							t_vector3;

typedef struct s_vector2
{
	double					x;
	double					y;
}							t_vector2;

typedef struct s_color
{
	double					r;
	double					g;
	double					b;
}							t_color;

typedef enum texture_type
{
	TEX_DEFAULT,
	TEX_CHECKER,
	TEX_UVCHECKER,
	TEX_FILE,
}							t_texture_type;

typedef enum e_object_type
{
	MATERIAL,
	TEXTURE,
	BUMP,
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	TRIANGLE,
	OBJECT_COUNT,
}							t_object_type;

typedef struct s_mat
{
	char					name[MAX_NAME_LEN];
	double					ambient;
	double					diffuse;
	double					specular;
	double					shininess;
	double					reflectivness;
}							t_mat;

typedef struct t_tex
{
	t_texture_type			type;
	char					name[MAX_NAME_LEN];
	union
	{
		struct
		{
			uint32_t		color1;
			uint32_t		color2;
			double			size;
		} s_checker;
		struct
		{
			uint32_t		color1;
			uint32_t		color2;
			double			size;
		} s_uvchecker;
		struct
		{
			char			path[MAX_NAME_LEN];
			t_color			*data;
			mlx_texture_t	*img;
			int				width;
			int				height;
		} s_custom;
	};
}							t_tex;

typedef struct s_bump
{
	char					name[MAX_NAME_LEN];
	char					path[MAX_NAME_LEN];
	mlx_texture_t			*img;
}							t_bump;

typedef struct s_object		t_object;

// s_cone.angle: half angle of conde in radians
typedef struct s_object
{
	uint32_t				color;
	t_color					color_f;
	t_vector3				pos;
	t_object_type			type;
	char					material_name[MAX_NAME_LEN];
	char					texture_name[MAX_NAME_LEN];
	char					bump_name[MAX_NAME_LEN];
	t_object				*material;
	t_object				*texture;
	t_object				*bump;
	t_tex					s_tex;
	t_mat					s_mat;
	t_bump					s_bump;
	union
	{
		struct
		{
			double			ratio;
		} s_ambient_light;
		struct
		{
			t_vector3		normal;
			double			fov;
			double			vp_width;
			double			vp_height;
			t_vector3		*ll_corner;
			t_vector3		*horizontal;
			t_vector3		*vertical;
			t_vector3		*look_at;
			double			focal_length;
		} s_camera;
		struct
		{
			double			brightness;
		} s_light;
		struct
		{
			double			diameter;
		} s_sphere;
		struct
		{
			t_vector3		normal;
		} s_plane;
		struct
		{
			double			diameter;
			double			height;
			t_vector3		normal;
		} s_cylinder;
		struct
		{
			double			angle;
			t_vector3		normal;
			double			min;
			double			height;
			double			radius;
		} s_cone;
		struct
		{
			t_vector3		points[3];
			t_vector3		edge1;
			t_vector3		edge2;
		} s_triangle;
	};
}							t_object;

#endif
