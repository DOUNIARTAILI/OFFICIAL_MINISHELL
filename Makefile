# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 20:30:29 by drtaili           #+#    #+#              #
#    Updated: 2023/06/14 18:41:12 by drtaili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

# Source files
SRC =	main.c \
		$(addprefix execution/,cd.c tools.c execute.c env_functions.c pwd.c exit.c \
		echo.c env.c unset.c is_builtin.c export.c \
		tools_env.c tools_env_.c check_arg_export.c export_tools.c valid_args_export.c \
		export_all_cases.c pipe.c redirections.c) \
		$(addprefix Resources/linked_lst/, ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c) \
		$(addprefix Resources/new_linkedlist/, list.c) \
		$(addprefix Resources/tokenizer/, tokenizer.c utils.c) \
		$(addprefix Resources/compiler/, compiler.c) \
		$(addprefix Resources/utils/,  free_functions.c functions_token_1.c functions_token_2.c utils.c check_syntax.c) \
		$(addprefix Resources/expander/, command.c expander.c heredoc.c utils1.c string_replace.c utils2.c exit_status_and_dbdollar.c env.c ) \
		$(addprefix Resources/concate/, concate.c ) \
		$(addprefix Resources/parsing/, parse_to_double_char.c parsing.c ) \
		$(addprefix Resources/gnl/, get_next_line.c get_next_line_utils.c)


# Object files
OBJS = $(SRC:.c=.o)

# Compiler
CC = cc -fsanitize=address -g

# Compiler flags
# FLAGS := -Wall -Wextra -Werror

BOLDGREEN=\033[1m\033[32m
RESET = \033[0m


# Readline flags
RLFLAGS := -lreadline
LFLAGSS := -L /Users/${USER}/goinfre/.brew/opt/readline/lib
IFLAGS := -I /Users/${USER}/goinfre/.brew/opt/readline/include

# LFLAGSS="-L/Users/mouaammo/.brew/opt/readline/lib"
# IFLAGS="-I/Users/mouaammo/.brew/opt/readline/include"

# Command-line utilities
RM := rm -rf

# Target executable
NAME := minishell

# Library dependencies
LIBFT := ./Resources/libft/libft.a 
PRINTF := ./ft_printf/libftprintf.a 
PATH_LIBFT := ./Resources/libft
PATH_PRINTF := ./ft_printf

# The default target
all: $(NAME)
	@printf "$(BOLDGREEN) __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
	@printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
	@printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
	@printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
	@printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"	
	@printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$(RESET)"                                                                                       
# Build the dependencies
$(LIBFT):
	@make -C $(PATH_LIBFT)
	@make -C $(PATH_PRINTF)

# Build the target executable
$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	@$(CC) $(FLAGS) $(RLFLAGS) $(LFLAGSS) $(OBJS) -o $(NAME) $(LIBFT) $(PRINTF)

# Build object files
%.o: %.c minishell.h
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

# Clean the object files and dependencies
clean:
	@$(RM) $(OBJS)
	@make clean -C $(PATH_LIBFT)
	@make clean -C $(PATH_PRINTF)

# Remove all generated files
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(PATH_LIBFT)
	@make fclean -C $(PATH_PRINTF)

# Clean and rebuild the target executable
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re bonus
