/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:36:05 by irodrigo          #+#    #+#             */
/*   Updated: 2021/11/13 14:37:49 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// if (nphil % 2 == 0)
// 	usleep(500);

void	ft_exec_philo(t_philo *my_philo, int nphil, t_envr *my_envr)
{
	my_philo[nphil].pos = nphil + 1;
	my_philo[nphil].meal_num = 0;
	if (nphil % 2 == 0)
	  	usleep(500);	
	my_philo[nphil].start = my_gettime();
	my_philo[nphil].my_env = my_envr;
	pthread_create(&my_philo[nphil].primary, NULL,
		ft_life, (void *)&my_philo[nphil]);
}
