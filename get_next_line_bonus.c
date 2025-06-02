/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:11:12 by dbouizem          #+#    #+#             */
/*   Updated: 2025/06/02 19:00:48 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_file(int fd, char *stock)
{
	char	*buff;
	ssize_t	bytes_read;

	if (stock && ft_strchr(stock, '\n'))
		return (stock);
	if (!stock)
		stock = ft_strdup("");
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
	{
		free(stock);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		buff[bytes_read] = '\0';
		stock = ft_strjoin_free(stock, buff);
		if (!stock)
		{
			free(buff);
			return (NULL);
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	if (bytes_read < 0)
	{
		free(stock);
		return (NULL);
	}
	return (stock);
}

static char	*ft_line(char *stock)
{
	size_t	len;
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
	ft_strlcpy(line, stock, len + 1);
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

void	remove_fdnode(t_fdlist **lst, int fd)
{
	t_fdlist	*curr;
	t_fdlist	*prev;

	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			free(curr->stock);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static char	*gnl_handle_node(t_fdlist **lst, t_fdlist *node, int fd)
{
	char	*line;

	node->stock = read_file(fd, node->stock);
	if (!node->stock || !*node->stock)
	{
		remove_fdnode(lst, node->fd);
		return (NULL);
	}
	line = ft_line(node->stock);
	if (!line)
	{
		remove_fdnode(lst, node->fd);
		return (NULL);
	}
	node->stock = ft_next(node->stock);
	if (!node->stock)
		remove_fdnode(lst, node->fd);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_fdlist	*lst;
	t_fdlist		*node;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_fdnode(&lst, fd);
	if (!node)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
	{
		remove_fdnode(&lst, fd);
		return (NULL);
	}
	ret = gnl_handle_node(&lst, node, fd);
	return (ret);
}
