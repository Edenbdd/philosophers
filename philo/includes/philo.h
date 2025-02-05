/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:27:10 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 15:17:48 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

// # define RED_TEXT "\033[31m"
// # define RESET_TEXT "\033[0m"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct					s_philo
{
	pthread_t			philo_thread;
	int					philo_id;
	int					timestamp_last_meal;
	int					birth_time;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_nb_of_meals;
	int					number_of_philo;
	int					meals_eaten;
	int					*end_flag;
	pthread_mutex_t		*m_printf;
	pthread_mutex_t		*m_eating;
	pthread_mutex_t		*m_end;
	pthread_mutex_t		*m_forks;
};

struct					s_data
{
	t_philo				*philo;
	pthread_t			butler;
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_nb_of_meals;
	int					end_flag;
	pthread_mutex_t		*m_printf;
	pthread_mutex_t		*m_eating;
	pthread_mutex_t		*m_end;
	pthread_mutex_t		*m_forks;
};

/*PARSING.C*/
int						is_space(char c);
int						only_digit_sign(char *arg);
int						parsing(char *arg);
long long				ft_atoll(char *str);
int						too_big(long long nb);

/*ROUTINE.C*/
int						even_routine(t_philo *curr, int time);
int						uneven_routine(t_philo *curr, int time);
void					*routine(void *data);

/*EATING.C*/
int						even_forks(t_philo *curr, int right_fork_id,
							int left_fork_id);
int						picking_forks(t_philo *curr, int right_fork_id,
							int left_fork_id);
int						eating(t_philo *curr);

/*INIT.C*/
int						init_data(t_data *data, int argc, char **argv);
int						init_mutex(t_data *data);
int						init_philo(t_data *data);
int						alloc_mutex(t_data *data);

/*THREADS.C*/
int						philo_generator(t_data *data);
int						thread_setup(t_data *data);

/*FREE.C*/
int						destroy_mutex(t_data *data);
int						free_destroy_all(t_data *data);

/*MONITOR.C aka the butler*/
int						check_meals_eaten(t_data *monitor);
int						check_death(t_data *monitor);
void					*monitoring(void *data);

/*UTILS.C*/
int						get_exact_time(void);
int						ft_usleep(int time_to_wait, t_philo *curr);
int						print_formatter(char *str, t_philo *curr);
int						wrong_arg_msg(void);
int						lonely_death(t_philo *curr);

#endif
