/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:49:26 by dbouizem          #+#    #+#             */
/*   Updated: 2025/05/29 03:30:32 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *stock)
{
	char		*buff;
	ssize_t		bytes_read;

	if (!stock)
		stock = ft_strdup("");
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			free(stock);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		stock = ft_strjoin(stock, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (stock);
}

static char	*ft_line(char *stock)
{
	size_t	len;
	char	*line;

	len = 0;
	if (!*stock || *stock == '\0')
		return (NULL);
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
	size_t	rest_len;

	newline = ft_strchr(stock, '\n');
	if (!newline)
	{
		free(stock);
		return (NULL);
	}
	rest_len = ft_strlen(newline + 1);
	if (rest_len == 0)
	{
		free(stock);
		return (NULL);
	}
	rest = ft_strdup(newline + 1);
	free(stock);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stock)
		{
			free(stock);
			stock = NULL;
			return (NULL);
		}
		return (NULL);
	}
	stock = read_file(fd, stock);
	if (!stock)
		return (NULL);
	if (*stock == '\0')
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	line = ft_line(stock);
	stock = ft_next(stock);
	return (line);
}
