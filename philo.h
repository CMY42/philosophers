/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:21 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/12 19:42:56 by cmansey          ###   ########.fr       */
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

// Structure pour représenter un philosophe
typedef struct s_Philosopher
{
	int id; // Identifiant du philosophe
	pthread_t thread; // Thread du philosophe
	pthread_mutex_t *left_fork; // Pointeur vers la fourchette de gauche
	pthread_mutex_t *right_fork; // Pointeur vers la fourchette de droite
	int time_to_die; // Délai avant la mort du philosophe
	int time_to_eat; // Délai pour manger
	int time_to_sleep; // Délai pour dormir
	struct s_Simulation	*sim;
}	t_Philosopher;

// Structure pour représenter la simulation
typedef struct s_Simulation
{
	pthread_mutex_t *forks; // Tableau des fourchettes
	t_Philosopher *philosophers; // Tableau des philosophes
	int num_philosophers; // Nombre total de philosophes
	int time_to_die; // Délai avant la mort d'un philosophe
	int time_to_eat; // Délai pour manger
	int time_to_sleep; // Délai pour dormir
	pthread_mutex_t print_mutex; // Mutex pour l'affichage
	int someone_died; // Indicateur si un philosophe est mort
}	t_Simulation;

// Déclaration des fonctions
int		init_simulation(t_Simulation *sim, char **argv);
void	create_philosophers(t_Simulation *sim);
void	start_simulation(t_Simulation *sim);
void	cleanup_simulation(t_Simulation *sim);
void	*philosopher_thread(void *arg);
void	take_forks(t_Philosopher *philosopher);
void	put_forks(t_Philosopher *philosopher);
void	print_message(t_Philosopher *philosopher, const char *message);
int		error_forks(t_Simulation *sim);
int		error_philo(t_Simulation *sim);

#endif