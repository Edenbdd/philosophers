/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:27:10 by aubertra          #+#    #+#             */
/*   Updated: 2025/02/05 10:39:01 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TESTS TO DELETE BEFORE PUSHING*/
/*
    Do not test with more than 200 philosophers.
    Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
    Test 1 800 200 200. The philosopher should not eat and should die.
    Test 5 800 200 200. No philosopher should die.
    Test 5 800 200 200 7. No philosopher should die and the simulation should stop when
	every philosopher has eaten at least 7 times.
    Test 4 410 200 200. No philosopher should die.
    Test 4 310 200 100. One philosopher should die.
    Test with 2 philosophers and check the different times: a death delayed by more than 10 ms
	is unacceptable.
    Test with any values of your choice to verify all the requirements. Ensure philosophers die
	at the right time, that they don't steal forks, and so forth.
*/

#ifndef PHILO_H

# define PHILO_H

#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo t_philo;
typedef struct s_data t_data;

struct	s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				timestamp_last_meal;
	int				birth_time;
	int				time_to_die;
    int				time_to_eat;
	int				time_to_sleep;
	int				max_nb_of_meals;
	int				number_of_philo;
	int				meals_eaten;
	int				*end_flag;
	pthread_mutex_t	*m_printf;
	pthread_mutex_t	*m_end;
	pthread_mutex_t	*m_forks;
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
	pthread_mutex_t	*m_end;
	pthread_mutex_t	*m_forks;
};

/*PARSING.C*/
int				is_space(char c);
int				only_digit_sign(char *arg);
int				parsing(char *arg);
long long		ft_atoll(char *str);
int				too_big(long long nb);

/*ROUTINE.C*/
int				picking_forks(t_philo *curr, int right_fork_id,
					int left_fork_id);
int				lonely_death(t_philo *curr);
int				eating(t_philo *curr);
int				sleeping(t_philo *curr);
void			*routine(void *data);


/*INIT.C*/
int				init_data(t_data *data, int argc, char **argv);
int				init_mutex(t_data *data);
int				init_philo(t_data *data);
int				philo_generator(t_data *data);
int				thread_setup(t_data *data);

/*FREE.C*/
int				destroy_mutex(t_data *data);
int				free_destroy_all(t_data *data);

/*MONITOR.C aka the butler*/
int				check_meals_eaten(t_data *monitor);
int				check_death(t_data *monitor);
void			*monitoring(void *data);

/*UTILS.C*/
int				get_exact_time(void);
int				ft_usleep(int time_to_wait, t_philo *curr);
int				print_formatter(char *str, t_philo *curr);
int				wrong_arg_msg(void);

#endif