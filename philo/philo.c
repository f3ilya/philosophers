/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:33:28 by                   #+#    #+#             */
/*   Updated: 2022/02/01 21:08:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init_philo(t_args *p, char **argv, int argc, int i)
{
	p->count = ft_atoi(argv[1], p);
	p->time_die = ft_atoi(argv[2], p);
	p->time_eat = ft_atoi(argv[3], p);
	p->time_sleep = ft_atoi(argv[4], p);
	p->stop = 0;
	p->me = -1;
	if (argc == 6)
		p->me = ft_atoi(argv[5], p);
	p->threads = malloc(sizeof(pthread_t) * p->count);
	p->fork = malloc(sizeof(pthread_mutex_t) * p->count);
	p->ph = malloc(sizeof(t_philo) * p->count);
	p->print = malloc(sizeof(pthread_mutex_t));
	if (!p->threads || !p->fork || !p->ph || !p->print)
		return (1);
	while (++i < p->count)
	{
		p->ph[i].name = i + 1;
		p->ph[i].left_fork = i;
		p->ph[i].right_fork = i + 1;
		if (i + 1 == p->count)
			p->ph[i].right_fork = 0;
		pthread_mutex_init(&p->fork[i], NULL);
	}
	pthread_mutex_init(p->print, NULL);
	return (0);
}

void	fork_lock(t_args *p, int n)
{
	pthread_mutex_lock(&p->fork[p->ph[n].left_fork]);
	pthread_mutex_lock(p->print);
	printf("%lu %d has taken a fork\n", time_now() - p->st, p->ph[n].name);
	pthread_mutex_unlock(p->print);
	pthread_mutex_lock(&p->fork[p->ph[n].right_fork]);
	pthread_mutex_lock(p->print);
	printf("%lu %d has taken a fork\n", time_now() - p->st, p->ph[n].name);
	printf("%lu %d is eating\n", time_now() - p->st, p->ph[n].name);
	pthread_mutex_unlock(p->print);
	usleep(p->time_eat * 1000);
	p->ph[n].time_e = time_now();
	pthread_mutex_unlock(&p->fork[p->ph[n].left_fork]);
	pthread_mutex_unlock(&p->fork[p->ph[n].right_fork]);
}

void	*eat(void *args)
{
	t_args	*p;
	int		n;
	int		i;

	p = (t_args *)args;
	n = p->i;
	i = -1;
	if (p->ph[n].name % 2 != 0)
		usleep(p->time_eat * 1000);
	while (++i < p->me || p->me == -1)
	{
		fork_lock(p, n);
		pthread_mutex_lock(p->print);
		printf("%lu %d is sleeping\n", time_now() - p->st, p->ph[n].name);
		pthread_mutex_unlock(p->print);
		usleep(p->time_sleep * 1000);
		pthread_mutex_lock(p->print);
		printf("%lu %d is thinking\n", time_now() - p->st, p->ph[n].name);
		pthread_mutex_unlock(p->print);
	}
	p->stop++;
	return (0);
}

void	fatality(t_args *p)
{
	p->j = 0;
	while (p->stop != p->count)
	{
		usleep(2000);
		if (p->time_die < (time_now() - p->ph[p->j].time_e))
		{
			pthread_mutex_lock(p->print);
			printf("%ld %d died\n", time_now() - p->st, p->ph[p->j].name);
			p->stop = p->count;
			p->i = -1;
			while (++p->i < p->count)
				pthread_detach(p->threads[p->i]);
			return ;
		}
		p->j++;
		if (p->j == p->count)
			p->j = 0;
	}
}

int	main(int argc, char **argv)
{
	t_args	p;

	if (check_arg(&p, argc, argv))
	{
		if (init_philo(&p, argv, argc, -1))
			return (0);
		p.st = time_now();
		p.i = -1;
		while (++p.i < p.count)
		{
			p.ph[p.i].time_e = p.st;
			pthread_create(&p.threads[p.i], NULL, eat, &p);
			usleep(50);
		}
		fatality(&p);
	}
	ft_free(&p);
	return (0);
}
