/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:12:27 by mcharret          #+#    #+#             */
/*   Updated: 2025/11/29 18:44:16 by mcharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	int						philo_nbr;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	int						meals_required;
	int						stop_simulation;
	long					start_time;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			death_lock;
	pthread_mutex_t			meal_lock;
	int						forks_init;
	int						print_init;
	int						death_init;
	int						meal_init;
}	t_table;

typedef struct s_philo
{
	int						id;
	long					last_meal_time;
	int						meals_eaten;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_table					*table;
}	t_philo;	

void	sub_init_table(t_table *table, int argc, char **argv);
int		init_table(t_table *table, int argc, char **argv);
int		init_philos(t_table *table, t_philo **philos);
void	monitor_philos(t_philo *philos);
int		check_philos_meals(t_philo *philos);
int		check_philos_death(t_philo *philos);
int		philo_sated(t_philo *philo);
int		philo_starving(t_philo *philo);
void	print_fork(t_philo *philo);
void	print_meal(t_philo *philo, long meal_time);
void	print_sleep(t_philo *philo);
void	print_think(t_philo *philo);
int		check_args(int argc, char **argv);
int		check_atoi(char *str);
int		check_atol(char *str);
void	*philo_routine(void *philo_ptr);
void	eat(t_philo *philo);
void	sleepx(t_philo *philo);
void	think(t_philo *philo);
int		simulation_running(t_philo *philo);
int		check_meal(t_philo *philo);
void	only_one_philo(t_philo *philo);
long	timestamp_from_start(t_philo *philo);
long	now_ms(void);
void	ft_sleep(long ms, t_philo *philo);
void	set_end_simulation(t_philo *philo);
int		is_space(char c);
int		ft_atoi(char *str);
long	ft_atol(char *str);
void	free_all(t_philo *philos, t_table *table);
void	cleanup_table(t_table *table);
int		launch_threads(t_table *table, t_philo *philos);
void	join_threads(t_philo *philos, int count);

#endif
