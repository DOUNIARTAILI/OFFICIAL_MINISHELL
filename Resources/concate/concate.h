/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:47:08 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/10 09:40:46 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONCATE_H
# define CONCATE_H

#include "../parsing.h"


char		*concate_strings(t_list **command);
int			concate_all(t_token *mytoken, t_list **expander,
				t_cmds **mynode_cmd);
int			fill_mylist(t_list **expander, t_cmds **mynode_cmd);
t_voidlst	*bash_concate_(t_list *expander);

#endif
