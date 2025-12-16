/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:18:07 by mcharret          #+#    #+#             */
/*   Updated: 2025/11/29 18:18:11 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_philo *philos, t_table *table)
{
	int		nbr;
	int		i;

	nbr = table->philo_nbr;
	free(philos);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->meal_lock);
	i = 0;
	while (i < nbr)
		pthread_mutex_destroy(&table->forks[i++]);
	free(table->forks);
}
