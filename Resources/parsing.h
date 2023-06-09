/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:58:19 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/09 05:36:56 by drtaili          ###   ########.fr       */
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
# include "readline/get_next_line.h"
# include "new_linkedlist/list.h"
# include "compiler/compiler.h"
# include "tokenizer/tokenizer.h"
# include "utils/utils.h"
# include "expander/expander.h"
# include "concate/concate.h"
# include "parse_list/parser.h"

# define PREV 0
# define NEXT 1
# define BOTH 2

char		*search_and_replace(t_token **mytoken, t_voidlst *myenv);
char		*replace_all(char *old_str, t_voidlst *myenv);
char		*var_string(char *str, int i, int start);
int			string_index(char *str, char c, int i);
char		*string_replace(char *phrase, char *oldstring, char *newstring);
int			ft_str_search_index(const char *haystack,
				const char *needle, size_t len);


#endif
