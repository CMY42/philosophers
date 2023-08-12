/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:09:23 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/12 20:26:00 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Créer les threads pour chaque philosophe
void	create_philosophers(t_Simulation *sim)
{
	t_Philosopher	*philo;
	int				i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		philo = &(sim->philosophers[i]);
		if (pthread_create(&(philo->thread), NULL, philosopher_thread, philo)
			!= 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	start_simulation(t_Simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
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

void	init_philo(t_Simulation *sim)
{
	t_Philosopher	*philosopher;
	int				i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		philosopher = &(sim->philosophers[i]);
		philosopher->id = i + 1;
		philosopher->left_fork = &(sim->forks[i]);
		philosopher->right_fork = &(sim->forks[(i + 1)
				% sim->num_philosophers]);
		philosopher->time_to_die = sim->time_to_die;
		philosopher->time_to_eat = sim->time_to_eat;
		philosopher->time_to_sleep = sim->time_to_sleep;
		philosopher->sim = sim;
		i++;
	}
}

// Allouer et initialiser les ressources nécessaires (fourchettes, mutex, etc.)
int	init_simulation(t_Simulation *sim, char **argv)
{
	int	i;

	sim->num_philosophers = atoi(argv[1]);
	sim->time_to_die = atoi(argv[2]);
	sim->time_to_eat = atoi(argv[3]);
	sim->time_to_sleep = atoi(argv[4]);
	sim->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* sim->num_philosophers);
	if (sim->forks == NULL)
		error_forks(sim);
	sim->philosophers = (t_Philosopher *)malloc(sizeof(t_Philosopher)
			* sim->num_philosophers);
	if (sim->philosophers == NULL)
		error_philo(sim);
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_init(&(sim->forks[i]), NULL);
		i++;
	}
	init_philo(sim);
	pthread_mutex_init(&(sim->print_mutex), NULL);
	return (1);
}
