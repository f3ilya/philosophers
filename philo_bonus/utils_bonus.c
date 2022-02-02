/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:20:11 by                   #+#    #+#             */
/*   Updated: 2022/01/31 21:08:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

void	ft_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}

long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int			i;
	int			k;
	long int	n;

	i = 0;
	k = 1;
	n = 0;
	if (str[i] == '-')
		k = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < 48 || str[i] > 57)
		ft_error("Invalid arguments!\n");
	while (str[i] > 47 && str[i] < 58)
	{
		n = n * 10 + k * (str[i++] - 48);
		if (n < -2147483648 || n > 2147483647)
			ft_error("Invalid arguments!\n");
	}
	if ((str[i] < 48 || str[i] > 57) && str[i] != '\0')
		ft_error("Invalid arguments!\n");
	if (n <= 0)
		ft_error("Invalid arguments!\n");
	return (n);
}

void	my_exit(t_args *p)
{
	p->i = -1;
	while (++p->i < p->count)
		kill(p->pid[p->i], SIGKILL);
	free(p->threads);
	free(p->ph);
	free(p->pid);
	sem_close(p->sem_pr);
	sem_close(p->sem_fork);
	exit(EXIT_SUCCESS);
}
