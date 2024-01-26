SRC =  $(shell find . -type f -name "*.c")

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address 

all: 
	@$(MAKE) -C libft
	@cc $(CFLAGS) $(SRC) -o minishell -Llibft -lft -lreadline
	@echo "compiling minishell..."
fclean: 
	rm -f minishell
	@$(MAKE) -C ./libft 

re: fclean all 