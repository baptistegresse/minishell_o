/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:00:16 by bgresse           #+#    #+#             */
/*   Updated: 2023/03/01 17:32:32 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define SQUOTE 39
# define DQUOTE 34
# define DOLLAR 36
# define TILDE 126
# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"

typedef int	t_pid;

typedef struct s_cmdlist
{
	char				**full_cmd;
	int					infile;
	int					outfile;
	int					here_doc;
	int					here_doc_pipe[2];
	char				*limiter;
	t_pid				cmd_pid;
	struct s_cmdlist	*next;
}						t_cmdlist;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	char		**paths;

	t_cmdlist	*cmds;
	t_env		*head_env;

	char		**envp;
	char		**argv;
	int			argc;

	int			end[2];
}				t_minishell;

int			g_status;

char		**ft_pathfinder(t_env **head);
char		**ft_expand_var(t_env **head, char **cmds);
void		ft_parse_env(t_env **head, char **envp);
char		**ft_expand_path(t_env **head, char **cmds);
char		*ft_check_key(t_env *head, char *key);
char		*ft_remove_quote_in_string(char *string, bool quote, bool dquote);
char		*ft_strjoin_char(char const *s1, char c);

t_env		*add_node(t_env *head, char *key, char *value);
char		*ft_get_env(t_env **head_env, char *key);
int			ft_list_size(t_env *head);

t_cmdlist	*ft_cmdlist(char *cmd_line, t_minishell *data);
void		ft_print_cmdlist(t_cmdlist *cmds);

void		pipex(t_minishell *data);

int			ft_error(char **parsed_line, int i);

/* Built-ins */

void		ft_built_in_cd(char **full_cmd);
void		ft_built_in_exit(void);
void		ft_built_in_env(t_env **head);
void		ft_built_in_pwd(void);
void		ft_built_in_export(t_env **head, char **full_cmd);
void		ft_built_in_unset(t_env **head, char *key);

#endif
