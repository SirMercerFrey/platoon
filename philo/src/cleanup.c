/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:18:07 by mcharret          #+#    #+#             */
/*   Updated: 2025/12/18 15:54:28 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_philo *philos, t_table *table)
{
	free(philos);
	cleanup_table(table);
}

void	cleanup_table(t_table *table)
{
	int		i;

	if (table->forks)
	{
		i = 0;
		while (i < table->forks_init)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	if (table->print_init)
		pthread_mutex_destroy(&table->print_mutex);
	if (table->death_init)
		pthread_mutex_destroy(&table->death_lock);
	if (table->meal_init)
		pthread_mutex_destroy(&table->meal_lock);
}
