/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:13:51 by ali               #+#    #+#             */
/*   Updated: 2024/01/08 12:47:04 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <linux/limits.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
// "\x1b[31m\x1b[1m" 
// ANSI escape code for red text
#define ANSI_COLOR "\x1b[1;34m"
// ANSI escape code to reset text color
#define ANSI_COLOR_RESET "\x1b[0m"

#define REDIR_INPUT 1
#define REDIR_OUTPUT 2
#define REDIR_HEREDOC 3
#define REDIR_APPEND 4

#define CMD_LEN 10

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_quotes_status
{
	int in_dobule;
	int in_single;
} t_quotes_status;

typedef struct s_redirection
{
	int				type;
	char			*file_name;
	struct s_redirection	*next;
}					t_redirection;

typedef struct s_input
{
	char			**args;
	t_redirection	*redirect;
	struct s_input	*next;
}					t_input;

typedef struct s_data
{
	t_env *env_list;
	t_env *export_list;
	int	exit_status;
	int syntax_error;
	int	stdin;
	int stdout;
	int stderr;
} t_data;


void    redir(t_redirection *redirections);
void    open_herdocs(t_input *input);
void    free_exit(unsigned char status, t_data *data, t_input *input);
char**  env_to_array(t_env *env);
int run_cmd(t_input *input, t_data *data);
int	to_join_values(char *key, int equal_index);
void join_env(char* key, char* newvalue, t_data *data , int to_join);
int exit_shell(t_data *data, t_input *input);
int export(t_input *input, t_data *data);
int	valid_var_name(char *name);
int	unset(t_data *data, t_input *input);
int	arg_count(char **args);
int	cd(t_input cmd, t_data *data);
t_env *get_env_list(char **env);
t_input *parser(char *input, t_data *data);
char **get_args(char *input);
void execution(t_input *input_list, t_data *data);
int is_whit_sp(char c, int in_dq, int in_sq);
char* evaluate_quotes(char* word, t_data *data, int re_type);
int is_pipe(char c, int inside_double_quotes, int inside_signle_quotes);
char* get_value_from_env(const char *name, t_env *env);
char	*expand_variable(char **word, t_env *env);
char 	*get_redirection_string(int type);
t_redirection* get_redirections(char *input, t_data *data);
void process_double_quotes(t_quotes_status *qt);
void process_single_quotes(t_quotes_status *qt);
int is_redirection(char *input);
void skip_redirections(char **input);
int	is_valid_identifier_char(char c, int cur_i);
char *free_and_join(char *s1, char *variable_name, int origin_len, int* result_index);
void proccess_both_quotes(char c, t_quotes_status *qt);
char **ft_strsdup(char **strs);
char *get_var_name(char *env_var);
char *get_var_value(char *env_var);
t_env *get_env_list(char **env);
t_env *get_export_list(char **env);
void parse_free(t_input *lst);
void unexpected_token_error (t_data *data, char* near);
void unexpected_eof_error(t_data *data);
void init_qt(t_quotes_status *qt);
void copy_char_to_string(char *str, char c, int *at);
void	move_ptr_to_redir(char **input, int *redir, t_quotes_status *qt);
int	move_ptr_to_filename(char **input, int redir, t_quotes_status *qt, 
	t_data *data);
void	move_ptr_to_endfilename(char **input, t_quotes_status *qt);
int	alloc_new_redir(t_redirection **begin, t_redirection **red_list, int redir);
char	*move_ptr_and_alloc(char **input, int redir, t_quotes_status *qt,
		t_data *data);
char *evaluate(char *word, t_data *data, int r_type);
char	**from_list_to_array(t_env *env);
void	free_strs(char **strs);
void	print_env_list(t_env *env);
void	print_export_list(t_env *export);
void	print_env_array(char** env);
int		add_env(t_env **head, const char *name, const char *value);
void	delete_env(t_env **head, const char *name);
int     add_export(t_env **head, const char *name, const char *value);
void	delete_export(t_env **head, const char *name);
void	increase_shlvl(t_env *list);
void	free_env_list(t_env *head);
int		echo(char **args);
int		cd(t_input cmd, t_data *data);
int		pwd(void);
int		env(t_env *env);

#endif 
