/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:28 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/12 20:26:04 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_thread(void *arg)
{
	t_Philosopher	*philosopher;

	philosopher = (t_Philosopher *)arg;
	while (!philosopher->sim->someone_died)
	{
		print_message(philosopher, "is thinking");
		usleep(1000 * philosopher->time_to_sleep);
		take_forks(philosopher);
		print_message(philosopher, "is eating");
		usleep(1000 * philosopher->time_to_eat);
		put_forks(philosopher);
	}
	return (NULL);
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

void	print_message(t_Philosopher *philosopher, const char *message)
{
	struct timeval	current_time;
	long long		timestamp_ms;

	gettimeofday(&current_time, NULL);
	timestamp_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	pthread_mutex_lock(&(philosopher->sim->print_mutex));
	printf("%lld %d %s\n", timestamp_ms, philosopher->id + 1, message);
	pthread_mutex_unlock(&(philosopher->sim->print_mutex));
}

int	main(int argc, char **argv)
{
	t_Simulation	sim;

	if (argc < 4 || argc > 5)
	{
		printf("Wrong numbers of arguments.\n");
		return (EXIT_FAILURE);
	}
	if (!init_simulation(&sim, argv))
	{
		fprintf(stderr, "Error: Failed to initialize simulation.\n");
		return (EXIT_FAILURE);
	}
	start_simulation(&sim);
	cleanup_simulation(&sim);
	return (EXIT_SUCCESS);
}
