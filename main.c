/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-24 14:07:10 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-24 14:07:10 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* The main is a TL;DR of the program */ 
// .philo 5 800 200 200 [5]
int main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		//correct input
		//1)errors checking, filling table
		parse_input(&table, av);

		//2) 
		data_init(&table);
		//3)
		dinner_start(&table);
		//4)No-leaks-> philos full| 1 philo died
		clean(&table);
	}
	else
	{
		//error
		error_exit("Wrong input: \n"
		G"Correct is ./philo 5 800 200 200 [5]"RST);
	}

}