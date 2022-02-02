/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 00:11:34 by                   #+#    #+#             */
/*   Updated: 2022/02/01 20:41:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int		name;
	int		left_fork;
	int		right_fork;
	long	time_e;
}	t_philo;

typedef struct s_args
{
	int				i;
	int				j;
	int				count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				me;
	int				stop;
	unsigned long	st;
	pthread_t		*threads;
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork;
	t_philo			*ph;
}	t_args;

int		ft_atoi(const char *str, t_args *p);
long	time_now(void);
int		check_arg(t_args *p, int argc, char **argv);
void	ft_free(t_args *p);

#endif
