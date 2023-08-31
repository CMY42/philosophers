/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:21 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/31 17:43:51 by cmansey          ###   ########.fr       */
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
// Identifiant du philosophe
// Thread du philosophe
// Pointeur vers la fourchette de gauche
// Pointeur vers la fourchette de droite
// Délai avant la mort du philosophe
// Délai pour manger
// Délai pour dormir
// Nombre de repas mange
// Temps du dernier repas
// Temps actuel
// Temps au debut
// Différence de temps
typedef struct s_Philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_eaten;
	struct timeval		lmt;
	struct timeval		curt;
	struct timeval		start_time;
	long long			time_diff;
	struct s_Simulation	*sim;
}	t_Philosopher;

// Structure pour représenter la simulation
// Tableau des fourchettes
// Tableau des philosophes
// Nombre total de philosophes
// Délai avant la mort d'un philosophe
// Délai pour manger
// Délai pour dormir
// Mutex pour l'affichage
// Mutex pour mort
// Indicateur si un philosophe est mort
// Combien de fois doivent manger
typedef struct s_Simulation
{
	pthread_mutex_t	*forks;
	t_Philosopher	*philosophers;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	someone_died_mutex;
	int				someone_died;
	int				mueat;
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
int		ft_atoi(const char *str);
void	print_message(t_Philosopher *philosopher, const char *message);

#endif
