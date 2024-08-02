/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:29:41 by mtocu             #+#    #+#             */
/*   Updated: 2024/08/02 20:09:32 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//if no meanls , return [0]
//1, if only 1 philo ad hoc fction
//2. create all threads
//3. create a monitor thread
//4, syncronyze the beginning of the simulation
//pthread_create-> philo start running, every philo start simulstaneosly
//4 join everyone

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}    

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
		
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	
	wait_all_threads(philo->table);
	
	// set last_meal time 
	while (!simulation_finished(philo->table))
	{
		//1) am I full?
		if (philo->full)
			break;
		// 2 eat
		eat(philo);
		
		//3 sleep write status & precise usleep
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (0 == table->nbr_limit_meals)
		return ; //back to main, clean
	else if (1 == table->philo_nbr)
		;//todo
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
	}

	//start of simulation
	table->start_simulation = gettime(MILISECOND);

	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	//wait for everyone

	i = -1;

	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

	//if we manage to reach here all philos are full!
	set_bool(&table->table_mutex, &table->end_simulation, true);
	
		
}