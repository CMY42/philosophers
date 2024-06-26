/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:39:32 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/21 20:13:16 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_forks(t_Simulation *sim)
{
	free(sim->forks);
	return (1);
}

int	error_philo(t_Simulation *sim)
{
	free(sim->forks);
	free(sim->philosophers);
	return (1);
}

int	ft_error(char *str, int code)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (code);
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
