/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:49 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 14:19:09 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int				get_exact_time(void)
// {
// 	struct timeval time;

// 	gettimeofday(time);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

// int				ft_usleep(int time_to_wait)
// {
// 	return (0);
// }

void	*routine(void *data)
{
	t_data *arg = (t_data *)data;

   	pthread_mutex_lock(arg->m_printf);
    printf("has taken right fork\n");
	pthread_mutex_unlock(arg->m_printf);
    
   	pthread_mutex_lock(arg->m_printf);
    printf("has taken left fork\n");
	pthread_mutex_unlock(arg->m_printf);
    
   	pthread_mutex_lock(arg->m_printf);
    printf("is eating\n");
	pthread_mutex_unlock(arg->m_printf);
    
   	pthread_mutex_lock(arg->m_printf);
    printf("is sleeping\n");
	pthread_mutex_unlock(arg->m_printf);
    
   	pthread_mutex_lock(arg->m_printf);
    printf("is thinking\n");
	pthread_mutex_unlock(arg->m_printf);
    return (NULL);
}
