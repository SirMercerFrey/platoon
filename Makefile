NAME		= philo

CC			= cc 
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
OBJ_DIR		= obj

GREEN		= \033[0;32m
GREY		= \033[2;37m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

SRC_FILES	=	init_table.c\
				monitor.c\
				print_actions.c\
				parsing.c\
				ft_atoil.c\
				routine.c\
				state_utils.c\
				time_utils.c\
				cleanup.c\
				main.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


all : $(NAME)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREY)Creating object directory...$(RESET)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./include -c $< -o $@
	@echo "$(YELLOW)Compiling $(RESET)$<" 

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Build successful: $(NAME)$(RESET)"

clean :
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(RESET)"
	
fclean : clean
	@rm -f $(NAME)
	@echo "$(RED)Executable removed$(RESET)"

re : fclean all

.PHONY: all clean fclean re
