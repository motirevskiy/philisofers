/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgretche <cgretche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:01:55 by cgretche          #+#    #+#             */
/*   Updated: 2022/05/02 14:59:47 by cgretche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_lunch;
	long			time_last_lunch;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_obj
{
	int				flag;
	int				index;
	int				count;
	int				check_death;
	long			start_time;
	t_philo			*p;
	pthread_mutex_t	lock;
}	t_obj;

long	ft_get_time(void);

int		ft_atoi(const char *str);
int		ft_init_philos(t_obj *o, int argc, char **argv);
int		ft_start_sim(pthread_t *thread, t_obj *o);
int		ft_free_all(t_obj *o, int flag, pthread_t *thread);

void	ft_usleep(int time);
void	*ft_start_live(void *data);
void	*ft_check_die(void *data);

#endif
