/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:47:08 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/08 04:16:51 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONCATE_H
# define CONCATE_H

char		*concate_strings(t_list **command);
int			concate_all(t_token *mytoken, t_list **expander,
				t_cmds **mynode_cmd);
int			fill_mylist(t_list **expander, t_cmds **mynode_cmd);
t_voidlst	*bash_concate(t_list *expander);

#endif