/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 00:11:36 by                   #+#    #+#             */
/*   Updated: 2022/01/26 19:11:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *str, t_args *p)
{
	long int	n;

	p->i = 0;
	p->j = 1;
	n = 0;
	while (str[p->i] == '\t' || str[p->i] == '\n' || str[p->i] == '\v'
		|| str[p->i] == '\f' || str[p->i] == '\r' || str[p->i] == ' ')
		p->i++;
	if (str[p->i] == '-')
		p->j = -1;
	if (str[p->i] == '+' || str[p->i] == '-')
		p->i++;
	while (str[p->i] > 47 && str[p->i] < 58)
	{
		n = n * 10 + p->j * (str[p->i++] - 48);
		if (n < -2147483648 || n > 2147483647)
			return (-1);
	}
	if ((str[p->i] < 48 || str[p->i] > 57) && str[p->i] != '\0')
		return (-1);
	return (n);
}

int	check_arg(t_args *p, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong count of arguments!\n");
		return (0);
	}
	while (++i < argc)
	{
		if (ft_atoi(argv[i], p) <= 0)
		{
			printf("Invalid arguments!\n");
			return (0);
		}
	}
	return (1);
}

void	ft_free(t_args *p)
{
	free(p->threads);
	free(p->fork);
	free(p->ph);
	free(p->print);
}
