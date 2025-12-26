/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:27:17 by mcharret          #+#    #+#             */
/*   Updated: 2025/11/29 18:31:22 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *philo_ptr)
{
	t_philo		*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->table->philo_nbr == 1)
	{
		only_one_philo(philo);
		return (NULL);
	}
	while (simulation_running(philo))
	{
		eat(philo);
		if (check_meal(philo) || !simulation_running(philo))
			break ;
		sleepx(philo);
		if (!simulation_running(philo))
			break ;
		think(philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	long	meal_time;

	pthread_mutex_lock(philo->left_fork);
	if (!simulation_running(philo))
		return (pthread_mutex_unlock(philo->left_fork), (void)0);
	print_fork(philo);
	pthread_mutex_lock(philo->right_fork);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_fork(philo);
	meal_time = timestamp_from_start(philo);
	print_meal(philo, meal_time);
	pthread_mutex_lock(&philo->table->death_lock);
	philo->last_meal_time = now_ms();
	pthread_mutex_unlock(&philo->table->death_lock);
	ft_sleep(philo->table->time_to_eat, philo);
	pthread_mutex_lock(&philo->table->meal_lock);
	++philo->meals_eaten;
	pthread_mutex_unlock(&philo->table->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleepx(t_philo *philo)
{
	print_sleep(philo);
	ft_sleep(philo->table->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	print_think(philo);
	ft_sleep(philo->table->time_to_think, philo);
}

void	only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_fork(philo);
	pthread_mutex_unlock(philo->left_fork);
	ft_sleep(philo->table->time_to_die, philo);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d died\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	set_end_simulation(philo);
}
