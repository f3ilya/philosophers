/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:49:38 by                   #+#    #+#             */
/*   Updated: 2022/01/31 21:08:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>

typedef struct s_philo {
	int		name;
	long	time_e;
}	t_philo;

typedef struct s_args {
	int				i;
	int				count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				me;
	unsigned long	st;
	pthread_t		*threads;
	t_philo			*ph;
	pid_t			*pid;
	sem_t			*sem_fork;
	sem_t			*sem_pr;
}	t_args;

int		ft_atoi(const char *str);
long	time_now(void);
void	my_exit(t_args *p);
void	ft_error(char *str);

#endif
