/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:31:50 by mcharret          #+#    #+#             */
/*   Updated: 2025/11/29 18:32:08 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	simulation_running(t_philo *philo)
{
	int		running;

	pthread_mutex_lock(&philo->table->death_lock);
	running = !philo->table->stop_simulation;
	pthread_mutex_unlock(&philo->table->death_lock);
	return (running);
}

int	check_meal(t_philo *philo)
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

void	set_end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	philo->table->stop_simulation = 1;
	pthread_mutex_unlock(&philo->table->death_lock);
}
