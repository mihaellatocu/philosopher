/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 18:41:57 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-31 18:41:57 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	data_init(t_table *table)
{
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
}