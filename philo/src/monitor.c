/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:32:44 by mcharret          #+#    #+#             */
/*   Updated: 2025/11/29 18:38:36 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor_philos(t_philo *philos)
{
	int		dm;

	if (philos->table->philo_nbr == 1)
		return ;
	while (simulation_running(philos))
	{
		if (check_philos_meals(philos))
		{
			set_end_simulation(philos);
			pthread_mutex_lock(&philos->table->print_mutex);
			printf("J'ai bien mange et j'ai bien bu, merci petit Jesus.\n");
			pthread_mutex_unlock(&philos->table->print_mutex);
			return ;
		}
		dm = check_philos_death(philos);
		if (dm)
		{
			set_end_simulation(philos);
			pthread_mutex_lock(&philos->table->print_mutex);
			printf("%ld\t%d died\n", timestamp_from_start(&philos[dm - 1]), dm);
			pthread_mutex_unlock(&philos->table->print_mutex);
			return ;
		}
		usleep(500);
	}
}

int	check_philos_meals(t_philo *philos)
{
	int		i;
	int		sated;
	int		philo_fulled;

	if (philos->table->meals_required == -1)
		return (0);
	philo_fulled = 0;
	i = 0;
	while (i < philos->table->philo_nbr)
	{
		pthread_mutex_lock(&philos->table->meal_lock);
		if (philos[i].meals_eaten < philos->table->meals_required)
			sated = 0;
		else
			sated = 1;
		pthread_mutex_unlock(&philos->table->meal_lock);
		if (sated)
			++philo_fulled;
		++i;
	}
	if (philo_fulled == philos->table->philo_nbr)
		return (1);
	return (0);
}

int	check_philos_death(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos->table->philo_nbr)
	{
		if (!philo_sated(&philos[i]))
		{
			if (philo_starving(&philos[i]))
				return (philos[i].id);
		}
		++i;
	}
	return (0);
}

int	philo_sated(t_philo *philo)
{
	int		sated;

	if (philo->table->meals_required == -1)
		return (0);
	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->meals_eaten < philo->table->meals_required)
		sated = 0;
	else
		sated = 1;
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (sated);
}

int	philo_starving(t_philo *philo)
{
	long		current_time;

	pthread_mutex_lock(&philo->table->death_lock);
	current_time = now_ms();
	if (current_time - philo->last_meal_time >= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	return (0);
}
