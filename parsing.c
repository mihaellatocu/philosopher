/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:07:38 by mtocu             #+#    #+#             */
/*   Updated: 2024/08/02 19:04:42 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/* .philo 5       800  200 200 [5] */
		//av[1] av[2] av[3] ...

//actual ns
//no int_max
//timestamps >60ms
//1) check for negatives
//2, check if the nr is legit 
// "   +77$%✅"
//"  +&%42"⛔
//3. check for INT_MAX, check for len 2,147,483.647, if len > 10 , > int_max!


static const char *valid_input(const char *str)
{
	int 		len;
	const char *number;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Please add only pozitive numbers");
	if (!ft_isdigit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}


static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit");
	return (num);
}

void    parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[2]) * 1e3;
	table->time_to_sleep = ft_atol(av[2]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		||table->time_to_sleep < 6e4)
		error_exit("Use timestamp major than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else 
		table->nbr_limit_meals = -1;
}