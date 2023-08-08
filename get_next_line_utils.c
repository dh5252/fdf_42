/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:27:03 by cahn              #+#    #+#             */
/*   Updated: 2022/11/27 20:11:36 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memndup(char *target, int n)
{
	int		index;
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (n + 1));
	if (new_str == 0)
		return (0);
	index = 0;
	while (index < n)
	{
		new_str[index] = target[index];
		index++;
	}
	new_str[index] = 0;
	return (new_str);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*_dst;
	unsigned char	*_src;
	size_t			i;

	_dst = (unsigned char *)dst;
	_src = (unsigned char *)src;
	if (_dst == _src)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			*(_dst + len - 1) = *(_src + len - 1);
			len--;
		}
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		*(_dst + i) = *(_src + i);
		i++;
	}
	return (dst);
}

void	ft_lstadd_back(t_fd_list **lst, t_fd_list *new)
{
	t_fd_list	*p;

	if (lst == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next != 0)
		p = p->next;
	p->next = new;
	new->prev = p;
}

t_fd_list	*ft_del_one(t_fd_list *lst, t_fd_list *obj)
{
	if (lst == obj)
	{
		if (lst->next != 0)
			lst = lst->next;
		else
			lst = 0;
		free(obj);
		return (lst);
	}
	obj->prev->next = obj->next;
	if (obj->next != 0)
		obj->next->prev = obj->prev;
	free(obj);
	return (lst);
}

int	is_last_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == 0)
		return (1);
	if (str[i - 1] == '\n')
		return (0);
	return (1);
}
