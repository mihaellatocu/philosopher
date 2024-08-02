/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:49:26 by mtocu             #+#    #+#             */
/*   Updated: 2024/08/02 19:30:26 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Cronometer */
//time_code ->SECONDS, MILISECONDS MICROSECONDS

long	gettime(t_time_code time_code)
{
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (1337);
}


/* Precise uslepp */

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec) //spinlock
				;
		}
	}	
}

void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}