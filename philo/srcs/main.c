/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:46 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/30 17:19:54 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data		data;
	int		i;

	if (init_data(&data, argc, argv))
		return (-1);
	dprintf(2, "Parsing done, all good!\n");
	i = 0;
	while (i++ < data.number_of_philo)
	{
		dprintf(2, "in first while main i is %d\n", i);
		pthread_create(&data.philo[i], NULL, &routine, &data);
	}
	i = 0;
	while (i++ < data.number_of_philo)
	{
		dprintf(2, "in sec while main i is %d\n", i);
		pthread_join(data.philo[i], NULL);
	}
	pthread_create(&data.butler, NULL, &monitoring, &data);
	pthread_join(data.butler, NULL);
	dprintf(2, "Program ended sucessfully\n");
    return (0);
}
