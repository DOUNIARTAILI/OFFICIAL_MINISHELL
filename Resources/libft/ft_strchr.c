/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:55:00 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/09 05:50:10 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	size_t	len;
	size_t	i;

	chr = (char)c;
	len = ft_strlen(s);
	if (len == 0)
		return NULL;
	i = 0;
	while (i <= len)
	{
		if (*s == chr)
			return ((char *)s);
		s++;
		i++;
	}
	return (NULL);
}
