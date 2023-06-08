/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:55:00 by drtaili           #+#    #+#             */
/*   Updated: 2022/11/13 00:15:14 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	size_t	len;
	size_t	i;

	chr = (char)c;
	len = ft_strlen(s);
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
