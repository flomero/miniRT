/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:29:22 by flfische          #+#    #+#             */
/*   Updated: 2024/06/15 13:53:31 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# ifndef DEBUG
#  define DEBUG 0
# endif

// IMAGE
# define WIN_TITLE "miniRT"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

// VIEWPORT
# define VIEWPORT_WIDTH 2.0
# define FOCAL_LENGTH 1.0
# define SAMPLES 100
# define BACKGROUND_FACTOR 0.5

// LIGHT
# define BOUNCES 3
# define DEFAULT_SPECULAR 0.8
# define DEFAULT_SHININESS 32
# define DEFAULT_DIFFUSE 0.7
# define DEFAULT_REFLECTIVNESS 0.0

// TERMINAL COLORS
# define RESET "\033[0m"
# define RED "\033[31m"
# define BOLD "\033[1m"

// ERRORS
# define ALLOC_ERR "Memory allocation failed"

#endif
