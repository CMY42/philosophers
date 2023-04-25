/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:21 by cmansey           #+#    #+#             */
/*   Updated: 2023/04/25 16:33:25 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR						0
# define ERROR_MALLOC				-2
# define ERROR_OPEN					-3
# define ERROR_INVALID_MAP			-4
# define ERROR_WALL					-5
# define ERROR_INVALID_MAP_PARAMS	-6
# define ERROR_MAP_SIZE				-7
# define ERROR_INVALID_SYMBOLS		-8
# define ERROR_USAGE				-9
# define ERROR_MLX					-10

// STRUCTS

typedef struct s_philo
{
	int				num;
	int				state;
	int				nb_meal;
	long int		last_eat_time;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_t		thread;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_table	*table;
	t_times			*times;
}	t_philo;

typedef struct s_table
{
	int		philo_dead;
	int		nb_philo;
	int		error_parsing;
	t_times	*times;
	t_philo	*first_philo;
}	t_table;

typedef struct s_times
{
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			number_of_meals;
	long int	start_time;
}	t_times;

// FUNCTIONS

#endif
