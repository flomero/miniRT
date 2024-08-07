/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:29:22 by flfische          #+#    #+#             */
/*   Updated: 2024/07/06 23:09:22 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# ifndef DEBUG
#  define DEBUG 0
# endif

// IMAGE
# define WIN_TITLE "miniRT"
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1200
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 800
# endif

// COMPUTATION
# define DEFAULT_THREADS 1
# define MAX_THREADS 32
# define EPSILON 1e-6

// VIEWPORT
# define VIEWPORT_WIDTH 2.0
# define FOCAL_LENGTH 1.0
# define DEFAULT_SAMPLES 100
# define BACKGROUND_FACTOR 0.2

// INPUT
# define MAX_NAME_LEN 50
# define MAX_PATH_LEN 50

// LIGHT
# define DEFAULT_BOUNCES 3
# define DEFAULT_SPECULAR 0.1
# define DEFAULT_SHININESS 5
# define DEFAULT_DIFFUSE 0.9
// # define DEFAULT_SPECULAR 0.4
// # define DEFAULT_SHININESS 10
// # define DEFAULT_DIFFUSE 0.7
# define DEFAULT_REFLECTIVNESS 0.0
# define BUMP_SCALE 10

// TERMINAL COLORS
# define RESET "\033[0m"
# define RED "\033[31m"
# define BOLD "\033[1m"
# define CYAN "\033[36m"

#endif
