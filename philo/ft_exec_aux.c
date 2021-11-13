/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:47:46 by irodrigo          #+#    #+#             */
/*   Updated: 2021/11/13 11:51:33 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static int	ft_all_eating(t_philo *philo, t_envr *envr)
{
	int	i;

	i = 0;
	while (!philo[i].death)
	{
		if (philo[i].meal_num == envr->lim_meat)
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_take_fork(int type, t_philo *my_philo)
{
	if (my_philo->my_env->n_philos == 3)
	{
		pthread_mutex_lock(my_philo->left);
		ft_write_phil_st(TAKE_FORK, my_philo);
		pthread_mutex_lock(my_philo->right);
		ft_write_phil_st(TAKE_FORK, my_philo);
	}
	else
	{
		if (type == 1)
		{
			pthread_mutex_lock(my_philo->left);
			ft_write_phil_st(TAKE_FORK, my_philo);
			pthread_mutex_lock(my_philo->right);
			ft_write_phil_st(TAKE_FORK, my_philo);
		}
		else
		{
			pthread_mutex_lock(my_philo->right);
			ft_write_phil_st(TAKE_FORK, my_philo);
			pthread_mutex_lock(my_philo->left);
			ft_write_phil_st(TAKE_FORK, my_philo);
		}
	}
}

void	ft_check_meals(t_philo *my_philo)
{
	pthread_mutex_lock((my_philo->my_env)->mt_state);
	if (my_philo->meal_num == my_philo->my_env->lim_meat
		&& !my_philo->my_env->meal_finish)
	{
		my_philo->my_env->meal_finish = TRUE;
		my_philo->my_env->nphil_meals++;
		my_philo->meal_num++;
	}
	pthread_mutex_unlock((my_philo->my_env)->mt_state);
}

void	ft_check_all_eat(t_philo *philos, t_envr *my_envr)
{
	int	x;

	x = 0;
	while (!philos[x].death)
	{
		if (ft_all_eating(philos, my_envr))
		{
			if (!my_envr->philo_died)
				printf("All philos has eaten\n");
			break ;
		}
		x = (x + 1) % my_envr->n_philos;
	}
}
