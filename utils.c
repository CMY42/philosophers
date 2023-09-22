/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:39:32 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/22 15:44:54 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_usleep(long long time_ms)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time();
	current_time = start_time;
	while (current_time - start_time < time_ms)
	{
		usleep(50);
		current_time = get_time();
	}
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Libérer les mutex des fourchettes
// Libérer les ressources des philosophes
// Détruire le mutex pour l'affichage
void	cleanup_simulation(t_Simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_destroy(&(sim->forks[i]));
		i++;
	}
	free(sim->forks);
	free(sim->philosophers);
	pthread_mutex_destroy(&(sim->print_mutex));
}

void	print_message(t_Philosopher *philosopher, const char *message)
{
	long long		timestamp_ms;

	timestamp_ms = get_time() - philosopher->sim->start;
	pthread_mutex_lock(&(philosopher->sim->print_mutex));
	if (!philosopher->sim->someone_died && (philosopher->sim->mueat == 0
			|| philosopher->meals_eaten < philosopher->sim->mueat))
		printf("%lld \033[1;32m%d %s\n\033[0m",
			timestamp_ms, philosopher->id + 1, message);
	pthread_mutex_unlock(&(philosopher->sim->print_mutex));
}
