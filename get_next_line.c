/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:49:26 by dbouizem          #+#    #+#             */
/*   Updated: 2025/05/29 20:53:10 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *stock)
{
	char	*buff;
	ssize_t	bytes_read;

	if (!stock)
		stock = ft_strdup("");
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(stock), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		buff[bytes_read] = '\0';
		stock = ft_strjoin_free(stock, buff);
		if (!stock || ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	if (bytes_read < 0 || !stock)
		return (free(stock), NULL);
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
	if (!*rest)
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

static char	*clean_stock(char **stock)
{
	if (*stock)
	{
		free(*stock);
		*stock = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (clean_stock(&stock));
	stock = read_file(fd, stock);
	if (!stock || !*stock)
		return (clean_stock(&stock));
	line = ft_line(stock);
	if (!line)
		return (clean_stock(&stock));
	stock = ft_next(stock);
	return (line);
}
