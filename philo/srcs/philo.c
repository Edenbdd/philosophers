/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:46 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/29 17:04:38 by aubertra         ###   ########.fr       */
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
	pthread_t		t1;
	pthread_t		t2;
	pthread_mutex_t mutex;
	thread_data_t	data;
	int				mails;
	(void)argc;
	(void)argv;
	
	data.mails = &mails;
	data.mutex = &mutex;
	pthread_mutex_init(&mutex, NULL); //allocates memory
	if (pthread_create(&t1, NULL, &routine, &data))
		return (-1);
	if (pthread_create(&t2, NULL, &routine, &data))
		return (-2);
	if (pthread_join(t1, NULL))
		return (-3);
	if (pthread_join(t2, NULL))
		return (-4);
	pthread_mutex_destroy(&mutex); // free memory
	printf("number of mails: %d\n", mails);
    return (0);   
}
