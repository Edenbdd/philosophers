/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:46 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 13:29:17 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv))
		return (-1);
	if (init_philo(&data))
		return (-1);
	if (thread_setup(&data))
		return (-1);
	if (free_destroy_all(&data))
		return (-1);
	return (0);
}
