/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:50:13 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/11 16:35:17 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LST_H
# define LINKED_LST_H

typedef enum tokens
{
	WHATEVER = 0,
	QUOTE = 1,
	S_QUOTE = 2,
	WORD = 3,
	PIPE = 4,
	RE_OUT = 5,
	RE_IN = 6,
	RE_APPEND = 7,
	HERE_DOC = 8,
	ESP = 9,
	DLR = 10,
	DB_DLR = 11,
	QST_MARK = 12
}	t_etoken;

typedef struct s_exit
{
	int		exit_status;	
	pid_t	pid[1024];
	pid_t	pid_p;
	int		len;
	int		killed;
	int		size;
	int		exit;
}t_exit;

t_exit	g_global_exit;

typedef struct token
{
	char		*str;
	t_etoken	token;
}t_token;

typedef struct s_list
{
	t_token			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list	*ft_lstnew(t_token *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
