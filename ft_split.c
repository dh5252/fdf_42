/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:45:34 by cahn              #+#    #+#             */
/*   Updated: 2023/08/08 20:22:14 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	count_word(char const *str, char c)
{
	size_t	i;
	size_t	cnt;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
		}
		else
		{
			while (str[i] != c && str[i])
				i++;
			cnt++;
		}
	}
	return (cnt);
}

static size_t	pass_sep(char const *str, size_t i, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

static int	allocate_slted_str(char ***slt, size_t index, size_t len, size_t i)
{
	size_t	k;

	(*slt)[index] = (char *)malloc(sizeof(char) * (len - i + 1));
	if ((*slt)[index] == 0)
	{
		k = 0;
		while (k < index)
		{
			free(*(*slt + k));
			k++;
		}
		free(*slt);
		*slt = 0;
		return (0);
	}
	return (1);
}

static void	put_word(char const *str, char ***slt, char c)
{
	size_t	i;
	size_t	index;
	size_t	j;
	size_t	len;

	i = 0;
	index = 0;
	while (str[i])
	{
		if (str[i] == c)
			i = pass_sep(str, i, c);
		else
		{
			j = 0;
			len = i;
			while (str[len] != c && str[len])
				len++;
			if (!allocate_slted_str(slt, index, len, i))
				return ;
			while (str[i] != c && str[i])
				(*slt)[index][j++] = str[i++];
			(*slt)[index++][j] = 0;
		}
	}
	(*slt)[index] = 0;
}

char	**ft_split(char const *str, char c)
{
	size_t	word_cnt;
	char	**slt;

	word_cnt = count_word(str, c);
	slt = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (slt == 0)
		return (0);
	put_word(str, &slt, c);
	return (slt);
}
