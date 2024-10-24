/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/07/11 13:26:34 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program	*ft_get_program(void)
{
	static t_program	program;

	return (&program);
}

void	ft_free_all(void)
{
	t_program	*program;
	int			i;

	i = 0;
	program = ft_get_program();
	while (i < program->objs_len)
	{
		if (program->objs[i].type == TEXTURE
			&& program->objs[i].s_tex.type == TEX_FILE)
			mlx_delete_texture(program->objs[i].s_tex.s_custom.img);
		if (program->objs[i].type == BUMP)
			mlx_delete_texture(program->objs[i].s_bump.img);
		i++;
	}
	if (program->objs)
		free(program->objs);
}

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc != 2)
		return (ft_print_error("Only 1 argument should be given."), 0);
	if (!is_valid_parsing(argv[1]))
		return (1);
	if (DEBUG)
		print_objs(NULL);
	program = ft_get_program();
	if (!ft_assign_mat_tex() || !ft_init_rt(program))
		return (ft_free_all(), 1);
	if (ft_mlx_init(argv[1]))
		return (ft_free_all(), 1);
	mlx_key_hook(program->mlx, ft_key_hook, program);
	mlx_close_hook(program->mlx, ft_program_exit, program);
	if (program->thread_count < 2)
		mlx_loop_hook(program->mlx, ft_render, program);
	else
		mlx_loop_hook(program->mlx, ft_render_multithread, program);
	mlx_loop(program->mlx);
	join_threads(program);
	ft_free_all();
	return (0);
}
