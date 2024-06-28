/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:15:15 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/28 16:07:48 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	proccess_line(int fd, t_object *objs);

/**
 * @brief does the whole parsing and validation check, that consists of these:
 * 1. checking filename if end with .rt
 * 2. checking if file is not empty or only empty lines
 * 3. check if all mandadory object occurs exact 1 time A, C, L
 * 4. takes every object of .rt file and initilize with it program's struct
 *
 * @param fname name of the file to parse
 * @return int 0 in case of error, 1 otherwise
 */
int	is_valid_parsing(char *fname)
{
	int	len;

	if (!fname || ft_strlen(fname) < 4)
		return (ft_print_error("Not valid filename"), 0);
	len = ft_strlen(fname);
	if (fname[len - 1] != 't' || fname[len - 2] != 'r' || fname[len - 3] != '.')
		return (ft_print_error("Not valid filename"), 0);
	len = get_nbr_of_lines(fname);
	if (len == 0)
		return (ft_print_error("Empty file"), 0);
	return (init_struct(fname, len));
}

/**
 * @brief reads each object from .rt file and initialize the program's struct
 *
 * @param fname name of .rt file
 * @param len number of lines-objects inside .rt file
 * @return int 0 in case of error, 1 otherwise
 */
int	init_struct(char *fname, int len)
{
	t_object	*objs;
	int			fd;

	objs = malloc(sizeof(t_object) * (len));
	ft_get_program()->objs_len = len;
	if (!objs)
		return (ft_print_error(ALLOC_ERR), 0);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (print_err_extend("Error opening file: ", strerror(errno), 0),
			0);
	if (!proccess_line(fd, objs))
		return (0);
	ft_get_program()->objs = objs;
	if (close(fd) == -1)
		return (print_err_extend("Error closing file: ", strerror(errno), 0),
			0);
	return (is_valid_obj_nbr(objs));
}

/**
 * @brief it reads line by line and initialize one object at a time
 *
 * @param fd
 * @param objs
 * @return int 1 on success, 0 otherwise
 */
static int	proccess_line(int fd, t_object *objs)
{
	char	*line;
	char	**tokens;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		tokens = ft_multi_split(line, " \t");
		free(line);
		if (!tokens || !tokens[0] || tokens[0][0] == '#')
		{
			line = get_next_line(fd);
			free_str_arr(tokens);
			continue ;
		}
		if (!get_obj(tokens, &objs[i++]))
			return (print_err_extend("Invalid object ", ft_itoa(i), 1),
				free_str_arr(tokens), free(objs), 0);
		free_str_arr(tokens);
		line = get_next_line(fd);
	}
	return (1);
}

static int	get_obj2(char **tokens, t_object *obj)
{
	if (!ft_strcmp("MA", tokens[0]))
		return (get_adv_mat(tokens, obj));
	else if (!ft_strcmp("TF", tokens[0]))
		return (get_tex_file(tokens, obj));
	else if (!ft_strcmp("TC", tokens[0]))
		return (get_tex_checker(tokens, obj, FALSE));
	else if (!ft_strcmp("TUC", tokens[0]))
		return (get_tex_checker(tokens, obj, TRUE));
	else if (!ft_strcmp("B", tokens[0]))
		return (get_bump(tokens, obj));
	return (0);
}

/**
 * @brief Get the obj creates an object from a line of file .rt
 *
 * @param tokens null terminated array of strings after reading a line from .rt
 * ex. ["A", "0.2", "255,255,255", NULL]
 * @return t_object* the new object created from tokens
 */
int	get_obj(char **tokens, t_object *obj)
{
	if (!ft_strcmp("A", tokens[0]))
		return (get_a(tokens, obj));
	else if (!ft_strcmp("C", tokens[0]))
		return (get_c(tokens, obj));
	else if (!ft_strcmp("L", tokens[0]))
		return (get_l(tokens, obj));
	else if (!ft_strcmp("sp", tokens[0]))
		return (get_sp(tokens, obj));
	else if (!ft_strcmp("pl", tokens[0]))
		return (get_pl(tokens, obj));
	else if (!ft_strcmp("cy", tokens[0]))
		return (get_cy(tokens, obj));
	else if (!ft_strcmp("co", tokens[0]))
		return (get_co(tokens, obj));
	else if (!ft_strcmp("tr", tokens[0]))
		return (get_tr(tokens, obj));
	else if (!ft_strcmp("M", tokens[0]))
		return (get_basic_mat(tokens, obj));
	return (get_obj2(tokens, obj));
}
