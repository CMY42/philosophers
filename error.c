/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:39:32 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/28 17:58:25 by cmansey          ###   ########.fr       */
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
