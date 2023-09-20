/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:13:26 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/20 16:23:42 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Voir si les arg sont OK
static int	ft_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] == ' ')
		i++;
	if (argv[i] == '+')
		i++;
	while (argv[i] >= '0' && argv[i] <= '9')
		i++;
	while (argv[i] == ' ')
		i++;
	if (argv[i] != 0)
		return (0);
	return (1);
}

//Voir si les args sont OK
int	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_arg(argv[i]) == 0 || ft_atoi(argv[i]) > 2147483647
			|| ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}
