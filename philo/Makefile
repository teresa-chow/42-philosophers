# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 10:46:29 by tchow-so          #+#    #+#              #
#    Updated: 2025/01/06 15:31:44 by tchow-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

# ============================================================================ #
# FILES                                                                        #
# ============================================================================ #

SRC		= $(addprefix $(SRC_DIR)/, main.c input_check.c input_info.c \
	handle_err.c sim_init.c sim_init_utils.c handle_pthread.c sim_routines.c \
	sim_actions.c sim_actions_forks.c sim_end.c setters_getters.c \
	time_management.c)
OBJS	 	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))


# ============================================================================ #
# PATHS                                                                        #
# ============================================================================ #

INC_DIR		= include
SRC_DIR 	= src
BUILD_DIR	= .build


# ============================================================================ #
# COMPILER, FLAGS & COMMANDS                                                   #
# ============================================================================ #

CC	= cc
CFLAGS	=  -Wall -Wextra -Werror -pthread
#CFLAGS	+=  -fsanitize=thread -g
#CFLAGS	+= -fsanitize=address

MAKE	= make -C

RM	= rm -rf
MKDIR	= mkdir -p


# ============================================================================ #
# RULES                                                                        #
# ============================================================================ #

##@ COMPILATION RULES

all: $(NAME)	## Compile philo

$(NAME): $(BUILD_DIR) $(OBJS)
	@printf "$(GRN)>> Generated object files$(NC)\n\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GRN)>> Compiled philo$(NC)\n\n"


$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(NC)\n\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


##@ CLEAN-UP RULES

clean:	## Remove object files
	$(RM) $(BUILD_DIR)
	@printf "$(GRN)>> Removed object files$(NC)\n\n"

fclean: clean	## Remove executable files
	$(RM) $(NAME)
	@printf "$(GRN)>> Removed executable files$(NC)\n\n"

re: fclean all	## Purge and recompile


##@ STANDARD COMPLIANCE CHECK

norm:	## Execute norminette
	norminette $(INC_DIR)/philosophers.h
	norminette $(SRC_DIR)


##@ MEMORY MANAGEMENT & THREADING DEBUG

helgrind:	## Run helgrind (export ARG & compile without fsanitize flags)
	valgrind --tool=helgrind ./$(NAME) 200 400 200 200 5

drd:	## Run drd (export ARG & compile without fsanitize flags)
	valgrind --tool=drd ./$(NAME) 200 400 200 200 5


##@ TOOL INSTALLATION

install: ## Install norminette and valgrind
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette
	sudo apt install valgrind -y


##@ HELP

help:	## Display this help info
	@awk 'BEGIN { \
		FS = ":.*##"; \
		printf "\n$(WHI_B)USAGE$(NC)\n\t$(YEL)make$(NC)$(CYA)\t \
		<target>$(NC)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
		printf "\t$(CYA_B)%-15s$(NC) %s\n", $$1, $$2 } \
		/^##@/ { printf "\n$(WHI_B)%s$(NC)\n", \
		substr($$0, 5) } ' Makefile
	@printf "\n"

.PHONY: all clean fclean re norm helgrind drd install help


# ============================================================================ #
# UTILS: SHELL FORMATTING                                                      #
# ============================================================================ #

# Reset to default
NC = \033[0m

# Regular text colors
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYA = \033[0;36m
WHI = \033[0;37m

# Bold text colors
RED_B = \033[1;31m
GRN_B = \033[1;32m
YEL_B = \033[1;33m
BLU_B = \033[1;34m
MAG_B = \033[1;35m
CYA_B = \033[1;36m
WHI_B = \033[1;37m
