/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:56:07 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 14:55:15 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Initialize data struct, malloc and initialize mutexes*/

#include "philo.h"

/*Initialize the data struct (for the monitor)*/
int	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (wrong_arg_msg());
	data->number_of_philo = parsing(argv[1]);
	if (data->number_of_philo == 0)
		return (-1);
	data->time_to_die = parsing(argv[2]);
	data->time_to_eat = parsing(argv[3]);
	data->time_to_sleep = parsing(argv[4]);
	if (argc == 6)
		data->max_nb_of_meals = parsing(argv[5]);
	else
		data->max_nb_of_meals = -2;
	if (data->number_of_philo == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		return (wrong_arg_msg());
	data->end_flag = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philo || init_mutex(data))
		return (-1);
	return (0);
}

/*Initialize all the philo struct (one per philo)*/
int	init_philo(t_data *data)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	while (i < data->number_of_philo)
	{
		current_philo = &(data->philo[i]);
		current_philo->philo_id = i + 1;
		current_philo->birth_time = get_exact_time();
		current_philo->timestamp_last_meal = get_exact_time();
		current_philo->time_to_die = data->time_to_die;
		current_philo->time_to_eat = data->time_to_eat;
		current_philo->time_to_sleep = data->time_to_sleep;
		current_philo->meals_eaten = 0;
		current_philo->max_nb_of_meals = data->max_nb_of_meals;
		current_philo->number_of_philo = data->number_of_philo;
		current_philo->end_flag = &(data->end_flag);
		current_philo->m_printf = data->m_printf;
		current_philo->m_eating = data->m_eating;
		current_philo->m_end = data->m_end;
		current_philo->m_forks = data->m_forks;
		i++;
	}
	return (0);
}

int	alloc_mutex(t_data *data)
{
	data->m_printf = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->m_printf)
		return (-1);
	data->m_end = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->m_printf)
		return (-1);
	data->m_eating = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->m_eating)
		return (-1);
	data->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philo);
	if (!data->m_forks)
		return (-1);
	return (0);
}

/*Malloc and init all the mutexes except m_end malloc in init_data*/
int	init_mutex(t_data *data)
{
	int	i;

	if (alloc_mutex(data))
		return (-1);
	if (pthread_mutex_init(data->m_end, NULL))
		return (-1);
	if (pthread_mutex_init(data->m_printf, NULL))
		return (-1);
	if (pthread_mutex_init(data->m_eating, NULL))
		return (-1);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}
