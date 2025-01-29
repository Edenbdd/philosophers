/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:46 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/29 16:32:10 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mails = 0;

void	*routine()
{
	int	i = 0;
	while (i < 20000000)
	{
		mails++;
		i++;
	}
	return (NULL);
}


int main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	(void)argc;
	(void)argv;
	if (pthread_create(&t1, NULL, &routine, NULL))
		return (-1);
	if (pthread_create(&t2, NULL, &routine, NULL))
		return (-2);
	if (pthread_join(t1, NULL))
		return (-3);
	if (pthread_join(t2, NULL))
		return (-4);
	printf("number of mails: %d\n", mails);
    return (0);   
}