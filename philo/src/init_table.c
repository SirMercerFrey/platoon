/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:18:20 by mcharret          #+#    #+#             */
/*   Updated: 2025/12/18 15:53:39 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sub_init_table(t_table *table, int argc, char **argv)
{
	table->philo_nbr = ft_atoi(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5]);
	else
		table->meals_required = -1;
	table->stop_simulation = 0;
	table->start_time = now_ms();
	table->forks = NULL;
	table->forks_init = 0;
	table->print_init = 0;
	table->death_init = 0;
	table->meal_init = 0;
}

int	init_table(t_table *table, int argc, char **argv)
{
	int		i;

	sub_init_table(table, argc, argv);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (cleanup_table(table), 1);
		++table->forks_init;
		++i;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (cleanup_table(table), 1);
	table->print_init = 1;
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
		return (cleanup_table(table), 1);
	table->death_init = 1;
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (cleanup_table(table), 1);
	table->meal_init = 1;
	return (0);
}

int	init_philos(t_table *table, t_philo **philos)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!*philos)
		return (1);
	memset(*philos, 0, sizeof(t_philo) * table->philo_nbr);
	i = 0;
	while (i < table->philo_nbr)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal_time = table->start_time;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].left_fork = &table->forks[i];
		(*philos)[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
		if (i % 2 == 0)
		{
			(*philos)[i].left_fork = &table->forks[(i + 1) % table->philo_nbr];
			(*philos)[i].right_fork = &table->forks[i];
		}
		(*philos)[i].table = table;
		++i;
	}
	return (0);
}
