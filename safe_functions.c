#include "philo.h"

/* Module containing wrapper functions
with embeded controls on return */

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return (ret);
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the tread blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate enough memory to create another mutex.");
	else if ( status == EBUSY)
		error_exit ("Mutex is locked.");
}





/* MUTEX SAFE */
/* 
init
destroy
lock
unlock
 */

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong code for mutex to handle:");	
}	


/* To create threads errors */