/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:46 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 14:24:04 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data		data;

	if (init_data(&data, argc, argv))
		return (-1);
	dprintf(2, "Parsing done!\n");
	if (init_mutex(&data))
		return (-1);
	dprintf(2, "Mutex set up!\n");
	if (init_philo(&data))
		return (-1);
	dprintf(2, "t_philo set up!\n");
	if (thread_setup(&data))
		return (-1);
	dprintf(2, "thread created and joined!\n");
	if (free_destroy_all(&data))
		return (-1);
	dprintf(2, "Data freed!\n");
	dprintf(2, "Program ended sucessfully\n");
    return (0);
}
