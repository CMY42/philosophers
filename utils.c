/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:39:32 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/31 17:46:48 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_forks(t_Simulation *sim)
{

	free(sim->forks);
	exit(EXIT_FAILURE);
	return (0);

}

int	error_philo(t_Simulation *sim)
{
	free(sim->forks);
	free(sim->philosophers);
	exit(EXIT_FAILURE);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	atoi;
	int	sign;

	i = 0;
	atoi = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		atoi *= 10;
		atoi += str[i] - 48;
		i++;
	}
	return (atoi * sign);
}

void	print_message(t_Philosopher *philosopher, const char *message)
{
	struct timeval	time;
	long long		timestamp_ms;

	gettimeofday(&time, NULL);
	timestamp_ms = ((time.tv_sec - philosopher->start_time.tv_sec) * 1000
			+ (time.tv_usec - philosopher->start_time.tv_usec) / 1000);
	pthread_mutex_lock(&(philosopher->sim->print_mutex));
	printf("%lld %d %s\n", timestamp_ms, philosopher->id + 1, message);
	pthread_mutex_unlock(&(philosopher->sim->print_mutex));
}
