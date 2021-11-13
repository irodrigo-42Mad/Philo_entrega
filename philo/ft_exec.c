/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:50:20 by irodrigo          #+#    #+#             */
/*   Updated: 2021/11/13 14:11:47 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

/*
** dentro de cada funcion verificamos que no hayamos muerto antes
** de su inicio.
*/
void	*ft_life(void *my_philo)
{
	t_philo	*philo;

	philo = my_philo;
	pthread_create(&philo->state, NULL, ft_ch_phil, philo);
	while (!philo->death && !philo->my_env->philo_died)
	{
		ft_philo_eat(philo);
		if (philo->meal_num == philo->my_env->lim_meat)
			return (NULL);
		ft_philo_sleep(philo);
		ft_philo_think(philo);
	}
	return (NULL);
}

void	*ft_philo_eat(t_philo *my_philo)
{
	if (!my_philo->death)
	{
		if (my_philo->left == my_philo->right)
			return (NULL);
		if (my_philo->my_env->lim_meat < 0
			|| my_philo->meal_num < my_philo->my_env->lim_meat)
		{
			if (my_philo->pos % 2)
				ft_take_fork(1, my_philo);
			else
				ft_take_fork(2, my_philo);
			my_philo->meal_num++;
			my_philo->start = my_gettime();
			ft_write_phil_st(EAT, my_philo);
			my_sleep(my_philo->my_env->t_eat);
			pthread_mutex_unlock(my_philo->left);
			pthread_mutex_unlock(my_philo->right);
		}
	}
	return (NULL);
}

void	*ft_philo_sleep(t_philo *my_philo)
{
	if (!my_philo->death)
	{
		ft_write_phil_st(SLEEP, my_philo);
		my_sleep(my_philo->my_env->t_sleep);
	}
	return (NULL);
}

void	*ft_philo_think(t_philo *my_philo)
{
	ft_write_phil_st(THINK, my_philo);
	return (NULL);
}

void	*ft_ch_phil(void *data)
{
	t_philo	*my_philo;

	my_philo = ((t_philo *)data);
	while (!my_philo->death && !my_philo->my_env->philo_died)
	{
		ft_check_meals(my_philo);
		if ((t_time_ms)(my_gettime() - my_philo->start)
				> (t_time_ms)my_philo->my_env->t_die)
		{
			my_philo->death = TRUE;
			if (my_philo->my_env->lim_meat != -1)
			{
				if (my_philo->my_env->lim_meat > my_philo->meal_num)
					ft_write_phil_st(DEAD, my_philo);
			}
			else
				ft_write_phil_st(DEAD, my_philo);
		}
	}
	return (NULL);
}
