/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:22:28 by cmansey           #+#    #+#             */
/*   Updated: 2023/04/25 15:31:40 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *text)
{
	printf("Thread [%s]\n", (char *)text);
	sleep(2);
	printf("Thread finish\n");
	return (NULL);
}

int	init_thread(void)
{
	pthread_t	t1;
	pthread_t	t2;
	char		*test;
	char		*test2;

	test = "Hello World";
	test2 = "Goodbye World";
	pthread_create(&t1, NULL, &routine, test);
	pthread_create(&t2, NULL, &routine, test2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
