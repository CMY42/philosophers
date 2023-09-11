/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:28 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/11 22:25:52 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Mort d'un philo
void	philo_die(void *arg)
{
	t_Philosopher	*philosopher;

	philosopher = (t_Philosopher *)arg;
	pthread_mutex_lock(&(philosopher->sim->someone_died_mutex));
	philosopher->sim->someone_died = 1;
	pthread_mutex_unlock(&(philosopher->sim->someone_died_mutex));
	print_message(philosopher, "died");
    /*t_Philosopher *philosopher = (t_Philosopher *)arg;

    pthread_mutex_lock(&(philosopher->sim->someone_died_mutex));
    if (!philosopher->sim->someone_died) {
        philosopher->sim->someone_died = 1;
        pthread_mutex_unlock(&(philosopher->sim->someone_died_mutex));
        print_message(philosopher, "died");
    } else {
        pthread_mutex_unlock(&(philosopher->sim->someone_died_mutex));
    }*/
}

// Routine
void	*philosopher_thread(void *arg)
{
	t_Philosopher	*ph;

	ph = (t_Philosopher *)arg;
	gettimeofday(&(ph->start_time), NULL);
	while (!ph->sim->someone_died)
	{
		gettimeofday(&(ph->curt), NULL);
		ph->time_diff = (((ph->curt.tv_sec - ph->lmt->tv_sec) * 1000)
				+ ((ph->curt.tv_usec - ph->lmt->tv_usec) / 1000) * 0.9 + 1);
		if (ph->time_diff >= ph->time_to_die || ph->sim->num_philosophers == 1)
		{
			philo_die(arg);
			break ;
		}
		print_message(ph, "is thinking");
		take_forks(ph);
		print_message(ph, "has taken a fork");
		print_message(ph, "is eating");
		gettimeofday((ph->lmt), NULL);
		ph->meals_eaten++;
		usleep(1000 * ph->time_to_eat);
		put_forks(ph);
		if (ph->sim->mueat > 0 && ph->meals_eaten == ph->sim->mueat)
			return (NULL);
		if (ph->sim->someone_died)
			break ;
		print_message(ph, "is sleeping");
		usleep(1000 * ph->time_to_sleep);
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

int	main(int argc, char **argv)
{
	t_Simulation	sim;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong numbers of arguments.\n");
		return (EXIT_FAILURE);
	}
	if (!init_simulation(&sim, argv))
	{
		fprintf(stderr, "Error: Failed to initialize simulation.\n");
		return (EXIT_FAILURE);
	}
	create_philosophers(&sim);
	if (sim.num_philosophers < 1)
	{
		fprintf(stderr, "Number of philosophers must be greater than 0.\n");
		return (1);
	}
	start_simulation(&sim);
	cleanup_simulation(&sim);
	return (0);
}
