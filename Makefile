NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=thread #-g3 -gdwarf-3
RM		= rm -rf

SRCS	= $(wildcard *.c) #to correct

LIBFT		= ./lib
LIBFT_LIB	= $(LIBFT)/libft.a

OBJ_DIR		= ./obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) 


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C $(LIBFT)

clean:
	@make clean -C $(LIBFT)
	$(RM) $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
