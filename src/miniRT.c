/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 15:14:55 by flfische         ###   ########.fr       */
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
	ft_init_rt(program);
	ft_get_first_obj(SPHERE)->material.type = CHECKER;
	ft_get_first_obj(SPHERE)->material.s_checker.color1 = 0x00FF00FF;
	ft_get_first_obj(SPHERE)->material.s_checker.color2 = 0x0000FFFF;
	ft_get_first_obj(SPHERE)->material.s_checker.size = 1;
	ft_get_first_obj(SPHERE)->material.reflectivness = 0;
	ft_get_nth_obj(SPHERE, 1)->material.type = UVCHECKER;
	ft_get_nth_obj(SPHERE, 1)->material.s_checker.color1 = 0x00FF00FF;
	ft_get_nth_obj(SPHERE, 1)->material.s_checker.color2 = 0x0000FFFF;
	ft_get_nth_obj(SPHERE, 1)->material.s_checker.size = 20;
	ft_get_nth_obj(SPHERE, 1)->material.reflectivness = 0;
	mlx_key_hook(program->mlx, ft_key_hook, program);
	if (program->thread_count < 2)
		mlx_loop_hook(program->mlx, ft_render, program);
	else
		mlx_loop_hook(program->mlx, ft_render_multithread, program);
	mlx_loop(program->mlx);
	join_threads(program);
	return (0);
}
