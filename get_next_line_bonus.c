/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:11:12 by dbouizem          #+#    #+#             */
/*   Updated: 2025/06/02 21:54:20 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_file(int fd, char *stock)
{
	char	*buff;
	ssize_t	br;

	if (stock && ft_strchr(stock, '\n'))
		return (stock);
	if (!stock)
		stock = ft_strdup("");
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(stock), NULL);
	br = 1;
	while (br > 0 && !ft_strchr(stock, '\n'))
	{
		br = read(fd, buff, BUFFER_SIZE);
		if (br < 0)
			break ;
		buff[br] = 0;
		stock = ft_strjoin_free(stock, buff);
		if (!stock)
			break ;
	}
	free(buff);
	if (br < 0 || !stock)
		return (free(stock), NULL);
	return (stock);
}

static char	*ft_line(char *stock)
{
	size_t	len;
	size_t	i;
	char	*line;

	if (!stock || !*stock)
		return (NULL);
	len = 0;
	while (stock[len] && stock[len] != '\n')
		len++;
	if (stock[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_next(char *stock)
{
	char	*newline;
	char	*rest;

	if (!stock)
		return (NULL);
	newline = ft_strchr(stock, '\n');
	if (!newline)
	{
		free(stock);
		return (NULL);
	}
	rest = ft_strdup(newline + 1);
	free(stock);
	if (!rest)
		return (NULL);
	if (rest[0] == '\0')
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

t_fdlist	*get_fdnode(t_fdlist **lst, int fd)
{
	t_fdlist	*curr;

	curr = *lst;
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	curr = malloc(sizeof(t_fdlist));
	if (!curr)
		return (NULL);
	curr->fd = fd;
	curr->stock = (NULL);
	curr->next = *lst;
	*lst = curr;
	return (curr);
}

char	*get_next_line(int fd)
{
	static t_fdlist	*lst;
	t_fdlist		*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_fdnode(&lst, fd);
	if (!node)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
		return (remove_fdnode(&lst, fd), NULL);
	node->stock = read_file(fd, node->stock);
	if (!node->stock || !*node->stock)
		return (remove_fdnode(&lst, fd), NULL);
	line = ft_line(node->stock);
	if (!line)
		return (remove_fdnode(&lst, fd), NULL);
	node->stock = ft_next(node->stock);
	if (!node->stock)
		remove_fdnode(&lst, fd);
	return (line);
}
