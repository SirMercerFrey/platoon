/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:26:34 by mcharret          #+#    #+#             */
/*   Updated: 2025/11/29 18:39:51 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	printf("%ld\t%d has taken a fork\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	print_meal(t_philo *philo, long meal_time)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	printf("%ld\t%d is eating\n", meal_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!simulation_running(philo))
	{	
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	printf("%ld\t%d is sleeping\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	printf("%ld\t%d is thinking\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
