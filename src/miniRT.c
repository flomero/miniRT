/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 15:06:41 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO:
		- take care of camera with 0,0,0 instead of seg fault
		- make sure objects work good with negative and positive values at z
		- need to properly take care of 0 division, not just return INFINITY
		- make sure I don't modify vector values in obj functs
		- check for mem leaks
		- merge from master the new stuff
		- put at cylinder top and bottom cover
		- replace normalize func of cylinder with the one of flog
*/

#include "miniRT.h"

t_program	*ft_get_program(void)
{
	static t_program	program;

	return (&program);
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
		return (1);
	if (DEBUG)
		print_objs(NULL);
	program = ft_get_program();
	if (ft_mlx_init())
		return (1);
	ft_calculate_viewport(ft_get_first_obj(CAMERA));
	mlx_key_hook(program->mlx, ft_key_hook, program);
	mlx_loop_hook(program->mlx, ft_render, program);
	mlx_loop(program->mlx);
	return (0);
}
