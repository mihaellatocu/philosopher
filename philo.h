/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-24 14:06:21 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-24 14:06:21 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //write, usleep
#include <stdio.h>
#include <stdlib.h> //malloc
#include <stdbool.h>
#include <pthread.h> //mutex: init dstroy lock unlock
					//threads: create join detach
#include <sys/time.h> //gettimeofday
#include <limits.h> //INT_MAX
#include <errno.h>
#include "lib/libft.h"

// ctrl + alt + down - to modify multiple fields
// win + ; to emoji

/* Shift + Alt + A - comment multiple rows
./philo 5 800 200 200 [5]
*/

/* OPCODE for mutex | thread functions */

typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}		t_opcode;


/* Ascii colors  */
#define RST  "\033[0m"  /* Reset to default color */
#define RED  "\033[1;31m" /* Red */
#define G  "\033[1;32m" /* Green */
#define Y  "\033[1;33m" /* Yellow */
#define B  "\033[1;34m" /* Blue */
#define M  "\033[1;35m" /* Magenta */
#define C  "\033[1;36m" /* Cyan */
#define W  "\033[1;37m" /* White */

/* code more readable */
typedef pthread_mutex_t	t_mtx;

/* IOU for compiler */
typedef struct s_table	t_table;

/* Fork */
typedef struct s_fork
{
	t_mtx	a;
	t_mtx	fork;
	int		fork_id;
}        t_fork;

typedef struct		s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; //time to pass from the last meal
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;//a philo is a thread
	t_table		*table;
}					t_philo;

/* Table */
typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals; //[5]  flag if -1
	long	start_simulation;
	bool	end_simulation; // a philo dies or all philos full
	t_fork	*forks; //array of forks🍴
	t_philo	*philos; // array of philos

}               t_table;
 
// #ifndef PHILO_H
// # define PHILO_H

// #endif

/* PROTOTYPES */

void	error_exit(const char *error);
void    parse_input(t_table *table, char **av);
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);