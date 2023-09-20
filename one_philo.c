/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:12:30 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/20 16:23:40 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*unique_routine(void *args)
{
	t_Philosopher	*philo;

	philo = (t_Philosopher *)args;
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	ft_usleep(philo->time_to_die);
	print_message(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	one_philo(t_Simulation *sim)
{
	sim->start = get_time();
	sim->philosophers->die_time = sim->start + sim->philosophers->time_to_die;
	if (pthread_create(&(sim->philosophers->thread),
			NULL, &unique_routine, sim->philosophers))
		return (1);
	pthread_join(sim->philosophers->thread, NULL);
	return (0);
}
