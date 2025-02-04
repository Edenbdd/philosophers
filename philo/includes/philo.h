/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:27:10 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/04 10:59:52 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo t_philo;
typedef struct s_data t_data;

struct	s_philo
{
	pthread_t		philo;
	int				philo_id;
	int				timestamp_last_meal;
	int				birth_time;
	int				time_to_die;
    int				time_to_eat;
	int				time_to_sleep;
	int				max_nb_of_meals;
	int				meals_eaten;
	int				*end_flag;
	pthread_mutex_t	*m_printf;
};

struct	s_data
{
	t_philo			*philo;
	pthread_t		butler;
	int				number_of_philo;
    int				time_to_die;
    int				time_to_eat;
	int				time_to_sleep;
	int				max_nb_of_meals;
	int				end_flag;
	pthread_mutex_t	*m_printf;
};

/*PARSING.C*/
int				is_space(char c);
int				only_digit_sign(char *arg);
int				parsing(char *arg);
long long		ft_atoll(char *str);
int				too_big(long long nb);

/*ROUTINE.C*/
int				eating(t_philo *curr);
void			*routine(void *data);


/*INIT.C*/
int				init_data(t_data *data, int argc, char **argv);
int				init_mutex(t_data *data);
int				init_philo(t_data *data);
int				thread_setup(t_data *data);

/*FREE.C*/
int				destroy_mutex(t_data *data);
int				free_destroy_all(t_data *data);

/*MONITOR.C aka the butler*/
void			*monitoring(void *data);

/*UTILS.C*/
int				get_exact_time(void);
int				ft_usleep(int time_to_wait, t_philo *curr);
int				print_formatter(char *str, t_philo *curr);
int				wrong_arg_msg(void);

#endif