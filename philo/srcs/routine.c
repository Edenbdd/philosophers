/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:53:49 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 11:52:29 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_data *arg = (t_data *)data;

   	pthread_mutex_lock(arg->m_right_forks);
    printf("has taken right fork\n");
	pthread_mutex_unlock(arg->m_right_forks);
    
   	pthread_mutex_lock(arg->m_left_forks);
    printf("has taken left fork\n");
	pthread_mutex_unlock(arg->m_left_forks);
    
   	pthread_mutex_lock(arg->m_eat);
    printf("is eating\n");
	pthread_mutex_unlock(arg->m_eat);
    
   	pthread_mutex_lock(arg->m_sleep);
    printf("is sleeping\n");
	pthread_mutex_unlock(arg->m_sleep);
    
   	pthread_mutex_lock(arg->m_think);
    printf("is thinking\n");
	pthread_mutex_unlock(arg->m_think);
    return (NULL);
}
