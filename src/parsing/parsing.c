/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:15:15 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/10 15:28:19 by klamprak         ###   ########.fr       */
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
		if (!((line[0] == '\n' && !line[1]) || !tokens || !tokens[0]))
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
	i = -1;
	while (++i < len + 1)
		objs[i] = NULL;
	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		line = ft_strjoin("Error opening file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), 0);
	}
	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while(line)
	{
		tokens = ft_split(line, ' ');
		if ((line[0] == '\n' && !line[1]) || !tokens || !tokens[0])
		{
			free(line);
			if (tokens)
				free_str_arr(tokens);
			line = get_next_line(fd);
			if (line)
				line[ft_strlen(line) - 1] = '\0';
			continue ;
		}
		objs[i] = get_obj(tokens);
		free(line);
		free_str_arr(tokens);
		if (!objs[i++])
		{
			printf("Invalid obj %d\n", i);
			return (free_obj_arr(objs), 0);
		}
		line = get_next_line(fd);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
	}
	if (close(fd) == -1)
	{
		line = ft_strjoin("Error closing file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), 0);
	}
	if (is_valid_obj_nbr(objs))
		ft_get_program()->objs = objs;
	else
		return (free_obj_arr(objs), 0);
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

/**
 * @brief checks if exists exactly one A, C and L (Ambient lighting, Camera and Light)
 *
 * @param t_object **objs null terminated objs list which will be checked
 * @return int returns 1 if is valid number, 0 otherwise
 */
int	is_valid_obj_nbr(t_object	**objs)
{
	int			i;
	int			single_occur[3];

	i = -1;
	while (++i < 3)
		single_occur[i] = 0;
	if (!objs)
		return (0);
	i = -1;
	while (objs[++i])
		if (objs[i]->type < 3)
			single_occur[objs[i]->type]++;
	if (single_occur[0] != 1)
		return (ft_print_error("Should exists exact one A"), 0);
	if (single_occur[1] != 1)
		return (ft_print_error("Should exists exact one C"), 0);
	if (single_occur[2] != 1)
		return (ft_print_error("Should exists exact one L"), 0);
	return (1);
}
