/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:07:11 by irodrigo          #+#    #+#             */
/*   Updated: 2021/11/13 14:14:40 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static int	iterate(char *nptr, long *num)
{
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (-1);
		*num = (*num) * 10 + *nptr - '0';
		nptr++;
	}
	return (0);
}

int	ft_atoi(char *nptr)
{
	long	num;
	int		status;
	short	sign;

	status = 0;
	num = 0;
	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	status = iterate(nptr, &num);
	if ((sign * num) > INT_MAX || (sign * num) < INT_MIN || (sign * num) <= 0
		|| status < 0)
		return (0);
	return ((int)(sign * num));
}

void	ft_write_phil_st(int work, t_philo *my_philo)
{
	int	num;

	if (my_philo->my_env->philo_died)
		return ;
	pthread_mutex_lock(my_philo->my_env->mt_print);
	num = (my_philo->my_env)->lim_meat;
	if (work == END)
		printf ("%s", EAT02);
	else
	{
		if (my_philo->my_env->philo_died)
			return ;
		printf ("[%lu] ", (my_gettime() - (my_philo->my_env)->init_time));
		printf ("%s%d", GEN01, my_philo->pos);
		if (work == TAKE_FORK)
			printf ("%s", FORK01);
		if (work == EAT)
			printf ("%s %d time\n", EAT01, my_philo->meal_num);
		if (work == SLEEP)
			printf ("%s", SLEEP01);
		if (work == THINK)
			printf ("%s", THINK01);
		if (work == DEAD)
		{
			printf ("%s", DIED01);
			my_philo->my_env->philo_died = TRUE;
		}
	}
	pthread_mutex_unlock(my_philo->my_env->mt_print);
}

void	ft_rounds(int num)
{
	if (num == 1)
		printf (" %s", GEN02);
	else
		printf (" %s", GEN03);
}
