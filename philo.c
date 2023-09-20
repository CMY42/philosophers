/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:28 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/20 18:02:48 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Routine
void	*philosopher_thread(void *arg)
{
	t_Philosopher	*ph;

	ph = (t_Philosopher *)arg;
	while (!ph->sim->someone_died)
	{
		take_forks(ph);
		print_message(ph, "has taken a fork");
		pthread_mutex_lock(&(ph->control));
		print_message(ph, "is eating");
		ph->die_time = get_time() + ph->time_to_die;
		ph->meals_eaten++;
		if (!ph->sim->someone_died)
			ft_usleep(ph->time_to_eat);
		pthread_mutex_unlock(&(ph->control));
		put_forks(ph);
		print_message(ph, "is sleeping");
		if (!ph->sim->someone_died)
			ft_usleep(ph->time_to_sleep);
		print_message(ph, "is thinking");
	}
	return (0);
}

// Verrouiller les fourchettes dans l'ordre numérique pour éviter les deadlocks
void	take_forks(t_Philosopher *philosopher)
{
	int	left_fork;
	int	right_fork;

	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % philosopher->sim->num_philosophers;
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&(philosopher->sim->forks[left_fork]));
		pthread_mutex_lock(&(philosopher->sim->forks[right_fork]));
	}
	else
	{
		pthread_mutex_lock(&(philosopher->sim->forks[right_fork]));
		pthread_mutex_lock(&(philosopher->sim->forks[left_fork]));
	}
}

// Déverrouiller les fourchettes dans l'ordre inverse pour éviter les deadlocks
void	put_forks(t_Philosopher *philosopher)
{
	int	left_fork;
	int	right_fork;

	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % philosopher->sim->num_philosophers;
	if (left_fork < right_fork)
	{
		pthread_mutex_unlock(&(philosopher->sim->forks[right_fork]));
		pthread_mutex_unlock(&(philosopher->sim->forks[left_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(philosopher->sim->forks[left_fork]));
		pthread_mutex_unlock(&(philosopher->sim->forks[right_fork]));
	}
}

int	main(int argc, char **argv)
{
	t_Simulation	sim;

	if (argc < 5 || argc > 6)
		return (ft_error("Wrong numbers of arguments.", 1));
	if (ft_check_args(argc, argv))
		return (ft_error("Wrong type of arguments.", 1));
	if (!init_simulation(&sim, argv))
		return (ft_error("Error: Failed to initialize simulation.", 1));
	if (sim.num_philosophers < 1)
		return (ft_error("Number of philosophers must be greater than 0.", 1));
	if (ft_atoi(argv[1]) == 1)
		one_philo(&sim);
	else
	{
		create_philosophers(&sim);
		start_simulation(&sim);
	}
	cleanup_simulation(&sim);
	return (0);
}
