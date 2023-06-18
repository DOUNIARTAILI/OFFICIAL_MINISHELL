/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 08:35:46 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/18 22:01:47 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static int	word_count(const char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
		{
			count++;
			while (str[i] != ' ' && str[i] != '\t' && str[i])
				i++;
		}
	}
	return (count);
}

static char	*get_word_len(const char *s1, int *index)
{
	char	*copy;
	size_t	word_len;
	int		i;

	while (s1[*index] && (s1[*index] == ' ' || s1[*index] == '\t'))
		(*index)++;
	i = *index;
	word_len = 0;
	while (s1[i] != ' ' && s1[i] != '\t' && s1[i])
	{
		word_len++;
		i++;
	}
	copy = malloc(sizeof(char) * (word_len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[*index] && s1[*index] != ' ' && s1[*index] != '\t')
		copy[i++] = s1[(*index)++];
	copy[i] = '\0';
	return (copy);
}

char	**ft_split_1(char const *s)
{
	char	**arr;
	int		index;
	int		wc;
	int		i;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	wc = word_count(s);
	arr = (char **) malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	arr[wc] = NULL;
	while (i < wc)
	{
		arr[i] = get_word_len(s, &index);
		if (!arr[i])
			return (free_all(arr));
		i++;
	}
	return (arr);
}
