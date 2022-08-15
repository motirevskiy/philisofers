/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgretche <cgretche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:59:21 by cgretche          #+#    #+#             */
/*   Updated: 2022/05/02 15:00:36 by cgretche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_all(t_obj *o, int flag, pthread_t *thread)
{
	int	i;

	i = -1;
	if (o->p)
	{
		while (++i < o->count - 1)
			pthread_mutex_destroy(&(o->p[i].mutex));
		free(o->p);
		if (thread)
			free(thread);
		if (flag == 0)
			return (0);
		write(1, "Error\n", 6);
	}
	return (1);
}

int	ft_init_philos(t_obj *o, int argc, char **argv)
{
	int	i;

	i = -1;
	o->flag = 0;
	o->check_death = 0;
	o->count = ft_atoi(argv[1]);
	o->p = malloc(sizeof(t_philo) * o->count);
	if (!o->p || pthread_mutex_init(&o->lock, NULL) != 0)
		return (1);
	while (++i < o->count)
	{
		if (pthread_mutex_init(&o->p[i].mutex, NULL) != 0)
			return (1);
		o->p[i].id = i + 1;
		o->p[i].time_to_die = ft_atoi(argv[2]);
		o->p[i].time_to_eat = ft_atoi(argv[3]);
		o->p[i].time_to_sleep = ft_atoi(argv[4]);
	}
	if (argc == 5)
		return (0);
	o->flag = 1;
	i = -1;
	while (++i < o->count)
		o->p[i].count_of_lunch = ft_atoi(argv[5]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_obj		o;
	pthread_t	check;
	pthread_t	*thread;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60 || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (write(1, "Error\n", 6), 1);
	if (ft_init_philos(&o, argc, argv))
		return (1);
	thread = malloc(sizeof(pthread_t *) * o.count);
	if (!thread || (pthread_create(&check, NULL, ft_check_die, &o) != 0)
		|| ft_start_sim(thread, &o) == 1)
		return (ft_free_all(&o, 1, 0));
	o.index = 0;
	while (o.index < o.count && o.count > 1)
		pthread_join(thread[o.index++], NULL);
	pthread_join(check, NULL);
	ft_free_all(&o, 0, thread);
	return (0);
}
