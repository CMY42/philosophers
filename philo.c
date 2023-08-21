/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:28 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/21 17:35:31 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	*philosopher_thread(void *arg)
{
	t_Philosopher	*philosopher;

	philosopher = (t_Philosopher *)arg;
	while (!philosopher->sim->someone_died)
	{
		print_message(philosopher, "is thinking");
		usleep(1000 * philosopher->time_to_sleep);
		take_forks(philosopher);
		print_message(philosopher, "has taken a fork");
		print_message(philosopher, "is eating");
		usleep(1000 * philosopher->time_to_eat);
		put_forks(philosopher);
	}
	pthread_mutex_lock(&(philosopher->sim->someone_died_mutex));
	philosopher->sim->someone_died = 1;
	pthread_mutex_unlock(&(philosopher->sim->someone_died_mutex));
	return (NULL);
}
void *philosopher_thread(void *arg)
{
    t_Philosopher *philosopher = (t_Philosopher *)arg;

    printf("Thread %d started\n", philosopher->id);

    while (!philosopher->sim->someone_died)
    {
		        printf("Thread %d evaluating condition: !someone_died = %d\n", philosopher->id, !philosopher->sim->someone_died);
        printf("Thread %d is thinking\n", philosopher->id);
struct timespec sleep_time;
sleep_time.tv_sec = philosopher->time_to_sleep / 1000;
sleep_time.tv_nsec = (philosopher->time_to_sleep % 1000) * 1000000;
nanosleep(&sleep_time, NULL);


        printf("Thread %d is trying to take forks\n", philosopher->id);
        take_forks(philosopher);

        printf("Thread %d is eating\n", philosopher->id);
struct timespec eat_time;
eat_time.tv_sec = philosopher->time_to_eat / 1000;
eat_time.tv_nsec = (philosopher->time_to_eat % 1000) * 1000000;
nanosleep(&eat_time, NULL);


        printf("Thread %d is putting forks\n", philosopher->id);
        put_forks(philosopher);
    }

    pthread_mutex_lock(&(philosopher->sim->someone_died_mutex));
    philosopher->sim->someone_died = 1;
    pthread_mutex_unlock(&(philosopher->sim->someone_died_mutex));

    printf("Thread %d finished\n", philosopher->id);

    return NULL;
}*/

void	*philosopher_thread(void *arg)
{
	t_Philosopher	*philosopher;
	struct timeval	last_meal_time;
	struct timeval	current_time;
	long long		time_diff;

	philosopher = (t_Philosopher *)arg;
	gettimeofday(&last_meal_time, NULL);

	while (!philosopher->sim->someone_died)
	{
		print_message(philosopher, "is thinking");

		gettimeofday(&current_time, NULL);
		time_diff = (current_time.tv_sec - last_meal_time.tv_sec) * 1000 +
		            (current_time.tv_usec - last_meal_time.tv_usec) / 1000;

		if (time_diff >= philosopher->time_to_die)
		{
			pthread_mutex_lock(&(philosopher->sim->someone_died_mutex));
			philosopher->sim->someone_died = 1;
			pthread_mutex_unlock(&(philosopher->sim->someone_died_mutex));
			print_message(philosopher, "died");
			break;
		}
		if (philosopher->sim->num_philosophers == 1)
		{
			pthread_mutex_lock(&(philosopher->sim->someone_died_mutex));
			philosopher->sim->someone_died = 1;
			pthread_mutex_unlock(&(philosopher->sim->someone_died_mutex));
			print_message(philosopher, "died");
			break;
		}
		take_forks(philosopher);
		print_message(philosopher, "has taken a fork");
		print_message(philosopher, "has taken a fork");
		print_message(philosopher, "is eating");
		usleep(1000 * philosopher->time_to_eat);
		put_forks(philosopher);

		gettimeofday(&last_meal_time, NULL);

		print_message(philosopher, "is sleeping");
		usleep(1000 * philosopher->time_to_sleep);
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
/*void take_forks(t_Philosopher *philosopher)
{
    int left_fork;
    int right_fork;

    left_fork = philosopher->id;
    right_fork = (philosopher->id + 1) % philosopher->sim->num_philosophers;

    printf("Thread %d is trying to take forks: left = %d, right = %d\n", philosopher->id, left_fork, right_fork);

    pthread_mutex_lock(&(philosopher->sim->forks[left_fork]));
    printf("Thread %d took left fork\n", philosopher->id);
    pthread_mutex_lock(&(philosopher->sim->forks[right_fork]));
    printf("Thread %d took right fork\n", philosopher->id);
}*/


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
/*void put_forks(t_Philosopher *philosopher)
{
    int left_fork;
    int right_fork;

    left_fork = philosopher->id;
    right_fork = (philosopher->id + 1) % philosopher->sim->num_philosophers;

    printf("Thread %d is putting forks: left = %d, right = %d\n", philosopher->id, left_fork, right_fork);

    pthread_mutex_unlock(&(philosopher->sim->forks[left_fork]));
    printf("Thread %d released left fork\n", philosopher->id);
    pthread_mutex_unlock(&(philosopher->sim->forks[right_fork]));
    printf("Thread %d released right fork\n", philosopher->id);
}*/


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
