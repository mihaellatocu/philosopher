/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:06:21 by mtocu             #+#    #+#             */
/*   Updated: 2024/08/03 17:20:54 by mtocu            ###   ########.fr       */
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


/* Ascii colors  */
#define RST	"\033[0m"  		/* Reset to default color */
#define RED	"\033[1;31m" 	/* Red */
#define G	"\033[1;32m" 	/* Green */
#define Y 	"\033[1;33m" 	/* Yellow */
#define B	"\033[1;34m" 	/* Blue */
#define M	"\033[1;35m" 	/* Magenta */
#define C	"\033[1;36m" 	/* Cyan */
#define W	"\033[1;37m" 	/* White */

//for write fction macro
#define DEBUG_MODE 0

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

typedef enum	e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}			t_time_code;


/* Philo states*/
typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

/* code more readable */
typedef pthread_mutex_t	t_mtx;

/* IOU for compiler */
typedef struct s_table	t_table;

/* Fork */
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}        	t_fork;

typedef struct		s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; //time to pass from the last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;//a philo is a thread
	t_mtx		philo_mutex;
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
	bool	all_threads_ready; //synco philos
	long	threads_running_nbr;
	pthread_t	monitor;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks; //array of forks🍴
	t_philo	*philos; // array of philos

}               t_table;
 
// #ifndef PHILO_H
// # define PHILO_H

// #endif

/* PROTOTYPES */

/* utils */
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

/* parsing */
void    parse_input(t_table *table, char **av);

/* init */
void	data_init(t_table *table);

/* safe functions */
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);


/*Setters and getters */
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

/* Syncro utils */
void	wait_all_threads(t_table *table);
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	increase_long(t_mtx *mutex, long *value);

void	dinner_start(t_table *table);
void	*monitor_dinner(void *data);
bool	all_threads_runnig(t_mtx *mutex, long *threads, long philo_nbr);
