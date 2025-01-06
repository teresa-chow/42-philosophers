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

SRC		= $(addprefix $(SRC_DIR)/, main.c)
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
CFLAGS	= -Wall -Wextra -Werror
CFLAGS	+= -fsanitize=address -fsanitize=thread -g

MAKE	= make -C

RM	= rm -rf
MKDIR	= mkdir -p


# ============================================================================ #
# RULES                                                                        #
# ============================================================================ #

##@ COMPILATION RULES

all: $(NAME)	## Compile philo

$(NAME): $(BUILD_DIR) $(OBJS)
	@printf "$(GRN)>> Generated object files$(RES)\n\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GRN)>> Compiled philo$(RES)\n\n"


$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(RES)\n\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


##@ CLEAN-UP RULES

clean:	## Remove object files
	$(RM) $(BUILD_DIR)
	@printf "$(GRN)>> Removed object files$(RES)\n\n"

fclean: clean	## Remove executable files
	$(RM) $(NAME)
	@printf "$(GRN)>> Removed executable files$(RES)\n\n"

re: fclean all	## Purge and recompile


##@ STANDARD COMPLIANCE CHECK

norm:	## Execute norminette
	norminette $(INC_DIR)/philosophers.h
	norminette $(SRC_DIR)


##@ 

#valgrind:	## Run valgrind
#	valgrind --tool=helgrind
#	valgrind --tool=drd


##@ TOOL INSTALLATION

install: ## Install norminette and valgrind
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette
	sudo apt install valgrind -y


##@ HELP

help:	## Display this help info
	@awk 'BEGIN { \
		FS = ":.*##"; \
		printf "\n$(WHI_B)USAGE$(RES)\n\t$(YEL)make$(RES)$(CYA)\t \
		<target>$(RES)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
		printf "\t$(CYA_B)%-15s$(RES) %s\n", $$1, $$2 } \
		/^##@/ { printf "\n$(WHI_B)%s$(RES)\n", \
		substr($$0, 5) } ' Makefile
	@printf "\n"

.PHONY: all clean fclean re norm install help


# ============================================================================ #
# UTILS: SHELL FORMATTING                                                      #
# ============================================================================ #

# Reset to default
RES = \033[0m

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
