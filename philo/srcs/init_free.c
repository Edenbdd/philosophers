/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:56:07 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 12:06:52 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wrong_arg_msg(void)
{
	char	*msg;
	int		len;

	msg = "Wrong arguments.\nExpected input:\n(positive int only)\n\
			unsigned in number_of_philosophers\n\
			time_to_die\n\
			time_to_eat\n\
			time_to_sleep\n\
			optional: number_of_times_each_philosopher_must_eat\n";
	len = 0;
	while (msg[len])
		len++;
	write(STDERR_FILENO, msg, len);
	return (-1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (wrong_arg_msg());
	data->number_of_philo = parsing(argv[1]);
    data->time_to_die = parsing(argv[2]);
    data->time_to_eat = parsing(argv[3]);
	data->time_to_sleep = parsing (argv[4]);
	if (argc == 6)
		data->nb_of_meals = parsing(argv[5]);
	else
		data->nb_of_meals = -2;
	if (data->number_of_philo == -1
		|| data->time_to_die == -1
		|| data->time_to_eat == -1
		|| data->time_to_sleep == -1)
		return (wrong_arg_msg());
	data->dead_flag = 0;
	data->end_flag = 0;
	data->philo = (pthread_t *)malloc(sizeof(pthread_t)
		* data->number_of_philo);
	data->m_right_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->m_left_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->m_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->m_sleep = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->m_think = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	return (0);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(data->m_eat, NULL))
		return (-1);
	if (pthread_mutex_init(data->m_right_forks, NULL))
		return (-1);
	if (pthread_mutex_init(data->m_left_forks, NULL))
		return (-1);
	if (pthread_mutex_init(data->m_sleep, NULL))
		return (-1);
	if (pthread_mutex_init(data->m_think, NULL))
		return (-1);
	return (0);
}

int	free_mutex(t_data *data)
{
	if (pthread_mutex_destroy(data->m_eat))
		return (-1);
	if (pthread_mutex_destroy(data->m_right_forks))
		return (-1);
	if (pthread_mutex_destroy(data->m_left_forks))
		return (-1);
	if (pthread_mutex_destroy(data->m_sleep))
		return (-1);
	if (pthread_mutex_destroy(data->m_think))
		return (-1);
	return (0);
}

int	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->philo[i])
	{
		free((void *)data->philo[i]);
		i++;
	}
	free(data->m_right_forks);
	free(data->m_left_forks);
	free(data->m_eat);
	free(data->m_sleep);
	free(data->m_think);
	return (0);
}
