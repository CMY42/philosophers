/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:09:23 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/20 18:02:41 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Monitorer les philos
//Voir sir mort ou a fini de manger ses repas
static void	ft_monitor(t_Simulation *sim)
{
	int	i;
	int	philos_done_eating;

	while (!sim->someone_died)
	{
		i = 0;
		philos_done_eating = 0;
		while (i < sim->num_philosophers && !sim->someone_died)
		{
			pthread_mutex_lock(&sim->philosophers[i].control);
			if (get_time() > sim->philosophers[i].die_time)
			{
				print_message(sim->philosophers, "die");
				sim->someone_died = 1;
			}
			if (sim->philosophers[i].meals_eaten >= sim->mueat)
				philos_done_eating++;
			pthread_mutex_unlock(&sim->philosophers[i].control);
			i++;
		}
		if (sim->mueat > 0 && philos_done_eating == sim->num_philosophers)
			sim->someone_died = 1;
	}
	if (sim->someone_died == 1)
		exit(0);
}

// Créer les threads pour chaque philosophe
void	create_philosophers(t_Simulation *sim)
{
	t_Philosopher	*philo;
	int				i;

	i = 0;
	sim->start = get_time();
	while (i < sim->num_philosophers)
	{
		philo = &(sim->philosophers[i]);
		sim->philosophers[i].die_time = sim->start
			+ sim->philosophers->time_to_die;
		if (pthread_create(&(philo->thread), NULL, philosopher_thread, philo)
			!= 0)
			exit(1);
		i++;
	}
	ft_monitor(sim);
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

//% pour etre sur que le dernier philo prenne la premiere fourchette
void	init_philo(t_Simulation *sim)
{
	t_Philosopher	*philosopher;
	int				i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		philosopher = &(sim->philosophers[i]);
		philosopher->id = i;
		philosopher->left_fork = &(sim->forks[i]);
		philosopher->right_fork = &(sim->forks[(i + 1)
				% sim->num_philosophers]);
		philosopher->time_to_die = sim->time_to_die;
		philosopher->time_to_eat = sim->time_to_eat;
		philosopher->time_to_sleep = sim->time_to_sleep;
		philosopher->sim = sim;
		philosopher->meals_eaten = 0;
		i++;
	}
}

// Allouer et initialiser les ressources nécessaires (fourchettes, mutex, etc.)
int	init_simulation(t_Simulation *sim, char **argv)
{
	int	i;

	sim->num_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->mueat = ft_atoi(argv[5]);
	sim->someone_died = 0;
	sim->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* sim->num_philosophers);
	if (sim->forks == NULL)
		error_forks(sim);
	sim->philosophers = (t_Philosopher *)malloc(sizeof(t_Philosopher)
			* sim->num_philosophers);
	if (sim->philosophers == NULL)
		error_philo(sim);
	i = -1;
	while (++i < sim->num_philosophers)
		pthread_mutex_init(&(sim->forks[i]), NULL);
	//pthread_mutex_init(&(sim->someone_died_mutex), NULL);
	init_philo(sim);
	pthread_mutex_init(&(sim->print_mutex), NULL);
	return (1);
}
