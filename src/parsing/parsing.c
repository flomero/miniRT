/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:15:15 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/09 16:30:07 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
 * @brief Get the nbr of lines, count how many lines there are in a file,
 * skipping empty lines
 *
 * @param fname the file which will read and count how many lines it contains
 * @return int -1 if its an error opening-closing file, nbr of lines otherwise
 */
int	get_nbr_of_lines(char *fname)
{
	char	*line;
	int		count;
	int		fd;
	char		**tokens;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		line = ft_strjoin("Error opening file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), -1);
	}
	line = get_next_line(fd);
	count = 0;
	while(line)
	{
		tokens = ft_split(line, ' ');
		if (!(line[0] == '\n' && !line[1]) || !tokens || !tokens[0])
			count++;
		free(line);
		if (tokens)
			free_str_arr(tokens);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		line = ft_strjoin("Error closing file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), -1);
	}
	return (count);
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
	t_object **objs;
	int		i;
	char	*line;
	int		fd;
	char	**tokens;

	objs = malloc(sizeof(t_object *) * (len + 1));
	if (!objs)
		return (ft_print_error("Memory allocation failed"), 0);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		line = ft_strjoin("Error opening file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), 0);
	}
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		tokens = ft_split(line, ' ');
		if (!(line[0] == '\n' && !line[1]) || !tokens || !tokens[0])
		{
			free(line);
			if (tokens)
				free_str_arr(tokens);
			line = get_next_line(fd);
			continue ;
		}
		objs[i] = get_obj(tokens);
		free(line);
		free_str_arr(tokens);
		if (!objs[i])
			return (free_obj_arr(objs), 0);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		line = ft_strjoin("Error closing file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), 0);
	}
	ft_get_program()->objs = objs;
	return (1);
}

/**
 * @brief Get the obj creates an object from a line of file .rt
 *
 * @param tokens null terminated array of strings after reading a line from .rt
 * ex. ["A", "0.2", "255,255,255", NULL]
 * @return t_object* the new object created from tokens
 */
t_object	*get_obj(char **tokens)
{
	if (!ft_strcmp("A", tokens[0]))
		return (get_A(tokens));
	else if (!ft_strcmp("C", tokens[0]))
		return (get_C(tokens));
	else if (!ft_strcmp("L", tokens[0]))
		return (get_L(tokens));
	else if (!ft_strcmp("sp", tokens[0]))
		return (get_sp(tokens));
	else if (!ft_strcmp("pl", tokens[0]))
		return (get_pl(tokens));
	else if (!ft_strcmp("cy", tokens[0]))
		return (get_cy(tokens));
	ft_print_error("Not valid object identifier");
	return (NULL);
}
