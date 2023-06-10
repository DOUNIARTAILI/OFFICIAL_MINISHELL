/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/10 09:32:01 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define  PARSING_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "linked_lst/linked_lst.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "gnl/get_next_line.h"
# include "new_linkedlist/list.h"
# include "compiler/compiler.h"
# include "tokenizer/tokenizer.h"
# include "utils/utils.h"
# include "../minishell.h"


# define PREV 0
# define NEXT 1
# define BOTH 2

/******** END TYPEDEF STRUCT */
typedef struct mylist
{
	char		**args;
	t_voidlst	*redirections;
}t_command;

typedef struct cmd
{
	t_voidlst	*commands;
	t_voidlst	*redirects;
}t_cmds;

//string_replace.c
char		*search_and_replace(t_token **mytoken, t_voidlst *myenv);
char		*replace_all(char *old_str, t_voidlst *myenv);
char		*var_string(char *str, int i, int start);
int			string_index(char *str, char c, int i);
char		*string_replace(char *phrase, char *oldstring, char *newstring);
int			ft_str_search_index(const char *haystack,
				const char *needle, size_t len);

//command.c
void		add_multi_nodes(t_list **origin, t_voidlst *newlist);
int			handle_cmd(t_list **newlist, t_list **head, t_voidlst *myenv);
t_cmds		*node_collecter(t_cmds args);
t_list		*bash_expander(t_list *tokenizer, t_voidlst *myenv);
int			is_redirect(int token);

//expander.c
char		*manage_others(char *str);
void		command_expansion(t_list **origin, t_list **head, t_voidlst *myenv);
// t_voidlst	*expander(t_list *head, t_voidlst *myenv);

//heredoc.c
void		manage_heredoc(t_list **head, int *fd, t_voidlst *myenv);
int			handle_heredoc(t_list **newlist, t_list **head, t_voidlst *myenv);

//token_db_quotes.c
t_list		*token_dbquotes(t_list *tokenizer);

//utils1.c
// t_env		*split_key_value(char *env);
void		free_all(char **tab);
t_voidlst	*take_env(char **env);
char		*search_for_key(char *str, t_voidlst *myenv);
void		ft_error(char *error, int error_val);

//utils2.c
t_token		*new_token(char *str, int token);
t_voidlst	*new_sublist(char **split, int token);
int			index_of_char(char *str, char c);
int			str_cmp(const char *s1, const char *s2);
t_list		*esc_sp_after_spechar(t_list *head);

//exit_status
char		*exit_status_value(char **string_key, int *index);
char		*get_string_value(char *old_str, int *index,
				char **string_key, t_voidlst *myenv);

#endif
