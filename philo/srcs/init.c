/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:56:07 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/04 10:30:10 by aubertra         ###   ########.fr       */
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
		data->max_nb_of_meals = parsing(argv[5]);
	else
		data->max_nb_of_meals = -2;
	if (data->number_of_philo == -1
		|| data->time_to_die == -1
		|| data->time_to_eat == -1
		|| data->time_to_sleep == -1)
		return (wrong_arg_msg());
	data->end_flag = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo)
		* data->number_of_philo);
	data->m_printf = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	return (0);
}

int	init_philo(t_data *data)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	while (i < data->number_of_philo)
	{
		current_philo = &(data->philo[i]);
		current_philo->philo = (pthread_t)malloc(sizeof(pthread_t));
		current_philo->philo_id = i + 1;
		current_philo->birth_time = get_exact_time();
		current_philo->timestamp_last_meal = get_exact_time();
    	current_philo->time_to_die = data->time_to_die;
    	current_philo->time_to_eat = data->time_to_eat;
		current_philo->time_to_sleep = data->time_to_sleep;
		current_philo->max_nb_of_meals = data->max_nb_of_meals;
		current_philo->end_flag = data->end_flag;
		current_philo->m_printf = data->m_printf;
		i++;
	}
	return (0);
}

int	thread_setup(t_data *data)
{
	int		i;
	t_philo	*current_philo;

	i = 0;
	pthread_create(&(data->butler), NULL, &monitoring, data);
	while (i < data->number_of_philo)
	{
		current_philo = &(data->philo[i]);
		dprintf(2, "in first while thread_setup i is %d\n", i + 1);
		if (pthread_create(&(current_philo->philo), NULL, &routine, current_philo))
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		dprintf(2, "in sec while thread_setup i is %d\n", i + 1);
		current_philo = &(data->philo[i]);
		pthread_join(current_philo->philo, NULL);
		i++;
		dprintf(2, "join of %d done\n", i + 1);
	}
	dprintf(2, "join all done\n");
	pthread_join(data->butler, NULL);
	dprintf(2, "butler joined\n");
	return (0);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(data->m_printf, NULL))
		return (-1);
	return (0);
}

