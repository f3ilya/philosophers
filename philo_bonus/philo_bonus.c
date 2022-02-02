/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:49:36 by                   #+#    #+#             */
/*   Updated: 2022/01/31 21:22:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_args(t_args *p, int argc, char **argv)
{
	p->count = ft_atoi(argv[1]);
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_sleep = ft_atoi(argv[4]);
	p->me = -1;
	if (argc == 6)
		p->me = ft_atoi(argv[5]);
	p->threads = malloc(sizeof(pthread_t) * p->count);
	p->ph = malloc(sizeof(t_philo) * p->count);
	p->pid = malloc(sizeof(pid_t) * p->count);
	if (!p->threads || !p->ph || !p->pid)
		exit(EXIT_FAILURE);
	sem_unlink("sem_fork");
	sem_unlink("sem_pr");
	p->sem_fork = sem_open("sem_fork", O_EXCL | O_CREAT, 0666, p->count);
	p->sem_pr = sem_open("sem_pr", O_EXCL | O_CREAT, 0666, 1);
	p->i = -1;
	while (++p->i < p->count)
		p->ph[p->i].name = p->i + 1;
}

void	*fatality(void *args)
{
	t_args	*p;

	p = (t_args *)args;
	while (1)
	{
		usleep(2000);
		if (p->time_die < (time_now() - p->ph[p->i].time_e))
		{
			sem_wait(p->sem_pr);
			printf("%ld %d died\n", time_now() - p->st, p->ph[p->i].name);
			exit(1);
		}
	}
}

void	forks(t_args *p)
{
	sem_wait(p->sem_fork);
	sem_wait(p->sem_pr);
	printf("%ld %d has taken a fork\n", time_now() - p->st, p->ph[p->i].name);
	sem_post(p->sem_pr);
	sem_wait(p->sem_fork);
	sem_wait(p->sem_pr);
	printf("%ld %d has taken a fork\n", time_now() - p->st, p->ph[p->i].name);
	printf("%ld %d is eating\n", time_now() - p->st, p->ph[p->i].name);
	sem_post(p->sem_pr);
	usleep(p->time_eat * 1000);
	p->ph[p->i].time_e = time_now();
	sem_post(p->sem_fork);
	sem_post(p->sem_fork);
}

void	eat(t_args *p)
{
	int	i;

	i = -1;
	if (p->ph[p->i].name % 2 != 0)
		usleep((p->time_eat - (p->time_eat / 10)) * 1000);
	pthread_create(&p->threads[p->i], NULL, &fatality, p);
	while (++i < p->me || p->me == -1)
	{
		forks(p);
		sem_wait(p->sem_pr);
		printf("%ld %d is sleeping\n", time_now() - p->st, p->ph[p->i].name);
		sem_post(p->sem_pr);
		usleep(p->time_sleep * 1000);
		sem_wait(p->sem_pr);
		printf("%ld %d is thinking\n", time_now() - p->st, p->ph[p->i].name);
		sem_post(p->sem_pr);
		usleep(10);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_args	p;
	int		status;

	if (argc != 5 && argc != 6)
		ft_error("Wrong count of arguments!\n");
	init_args(&p, argc, argv);
	p.st = time_now();
	p.i = -1;
	while (++p.i < p.count)
	{
		p.ph[p.i].time_e = p.st;
		p.pid[p.i] = fork();
		if (p.pid[p.i] == 0)
			eat(&p);
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
			break ;
	}
	my_exit(&p);
}
