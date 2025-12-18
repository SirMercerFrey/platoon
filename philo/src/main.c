/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:21:00 by mcharret          #+#    #+#             */
/*   Updated: 2025/12/18 15:52:50 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;
	int		created;

	if (!check_args(argc, argv))
		return (1);
	if (init_table(&table, argc, argv))
		return (1);
	if (init_philos(&table, &philos))
		return (cleanup_table(&table), 1);
	created = launch_threads(&table, philos);
	if (created < table.philo_nbr)
	{
		join_threads(philos, created);
		return (free_all(philos, &table), 1);
	}
	monitor_philos(philos);
	join_threads(philos, table.philo_nbr);
	free_all(philos, &table);
	return (0);
}

int	launch_threads(t_table *table, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			pthread_mutex_lock(&table->death_lock);
			table->stop_simulation = 1;
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		i++;
	}
	return (i);
}

void	join_threads(t_philo *philos, int count)
{
	while (count > 0)
	{
		count--;
		pthread_join(philos[count].thread, NULL);
	}
}
