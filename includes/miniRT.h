/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:41:11 by flfische          #+#    #+#             */
/*   Updated: 2024/06/07 15:02:35 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// Includes
# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

// HEADERS
# include "config.h"
# include "objects.h"

// TYPEDEFS
typedef struct s_vector3
{
	float		x;
	float		y;
	float		z;
}				t_vector3;

typedef struct s_vector2
{
	float		x;
	float		y;
}				t_vector2;

typedef struct s_program
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_vector2	img_size;
}				t_program;

// FUNCTIONS
t_program		*ft_get_program(void);

// MLX
int				ft_mlx_init(void);
void			ft_key_hook(void *param);

// ERRORS
void			ft_print_error(const char *error);

#endif
