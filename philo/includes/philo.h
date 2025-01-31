/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:27:10 by aubertra          #+#    #+#             */
/*   Updated: 2025/01/31 11:46:28 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;

struct	s_data
{
	pthread_t		*philo;
	pthread_t		butler;
	int				number_of_philo;
    int				time_to_die;
    int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	int				dead_flag;
	int				end_flag;
	pthread_mutex_t	*m_right_forks;
	pthread_mutex_t	*m_left_forks;
	pthread_mutex_t	*m_eat;
	pthread_mutex_t	*m_sleep;
	pthread_mutex_t	*m_think;
};

/*PARSING.C*/
int				is_space(char c);
int				only_digit_sign(char *arg);
int				parsing(char *arg);
long long		ft_atoll(char *str);
int				too_big(long long nb);

/*ROUTINE.C*/
void			*routine(void *data);


/*INIT.C*/
int				wrong_arg_msg(void);
int				init_data(t_data *data, int argc, char **argv);
int				init_mutex(t_data *data);


/*MONITOR.C aka the butler*/
void			*monitoring(void *data);


#endif