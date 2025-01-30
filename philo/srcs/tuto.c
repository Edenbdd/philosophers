/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:46 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/30 12:20:17 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct {
	int				*mails;
	pthread_mutex_t	*mutex;
} thread_data_t;


void	*routine(void *data)
{
	thread_data_t *arg = (thread_data_t *)data;
	int	i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(arg->mutex);
		(*(arg->mails))++;
		pthread_mutex_unlock(arg->mutex);
		i++;
	}
	return (NULL);
}


int main(int argc, char **argv)
{
	pthread_mutex_t mutex;
	thread_data_t	data;
	int				mails;
	int				nb_of_philo;
	int				i;
	(void)argc;
	(void)argv;
	pthread_t		t1;
	
	i = 1;
	nb_of_philo = 4;
	pthread_t		th[nb_of_philo];
	data.mails = &mails;
	data.mutex = &mutex;
	pthread_mutex_init(&mutex, NULL); //allocates memory
	pthread_create(&t1, NULL, &routine, &data);
	while (i <= nb_of_philo)
	{
		if (pthread_create(th + i, NULL, &routine, &data))
			return (-1);
		dprintf(STDERR_FILENO, "thread %d has started\n", i);
		i++;
	}
	i = 1;
	while (i <= nb_of_philo)
	{
		if (pthread_join(th[i], NULL))
				return (-2);
		dprintf(STDERR_FILENO, "thread %d has ended\n", i);
		i++;
	}
	pthread_join(&t1, NULL);
	pthread_mutex_destroy(&mutex); // free memory
	printf("number of mails: %d\n", mails);
    return (0);   
}
