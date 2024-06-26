/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:21 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/22 15:47:44 by cmansey          ###   ########.fr       */
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
# include <stdatomic.h>

// Structure pour représenter un philosophe
// Identifiant du philosophe
// Thread du philosophe
// Pointeur vers la fourchette de gauche
// Pointeur vers la fourchette de droite
// Délai avant la mort du philosophe
// Délai pour manger
// Délai pour dormir
// Repas mange
// temps de mort
// Mutex pour controler
typedef struct s_Philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	atomic_int			meals_eaten;
	atomic_llong		die_time;
	pthread_mutex_t		control;
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
// Indicateur si un philosophe est mort
// Combien de fois doivent manger
// Temps depart sim;
typedef struct s_Simulation
{
	pthread_mutex_t	*forks;
	t_Philosopher	*philosophers;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	print_mutex;
	atomic_int		someone_died;
	int				mueat;
	long long		start;
}	t_Simulation;

// Déclaration des fonctions
int			init_simulation(t_Simulation *sim, char **argv);
void		create_philosophers(t_Simulation *sim);
void		start_simulation(t_Simulation *sim);
void		cleanup_simulation(t_Simulation *sim);
void		*philosopher_thread(void *arg);
void		take_forks(t_Philosopher *philosopher);
void		put_forks(t_Philosopher *philosopher);
void		print_message(t_Philosopher *philosopher, const char *message);
int			error_forks(t_Simulation *sim);
int			error_philo(t_Simulation *sim);
int			ft_atoi(const char *str);
void		print_message(t_Philosopher *philosopher, const char *message);
void		ft_usleep(long long time_ms);
long long	get_time(void);
int			ft_error(char *str, int code);
size_t		ft_strlen(char const *str);
int			one_philo(t_Simulation *sim);
int			ft_check_args(int argc, char **argv);

#endif
