/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:50:22 by dbouizem          #+#    #+#             */
/*   Updated: 2025/05/19 14:57:43 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}
//---------------
char	*ft_strchr(const char *str, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((unsigned char)*str == uc)
			return ((char *)str);
		str++;
	}
	if (uc == '\0')
		return ((char *)str);
	return (NULL);
}
//---------------
char	*ft_strcpy(char *dst, const char *src)
{
	char	*ret;

	if (!dst || !src)
		return (NULL);
	ret = dst;
	while (*src)
		*ret++ = *src++;
	*ret = '\0';
	return (dst);
}

char	*ft_strcat(char *dst, const char *src)
{
	char	*ret;

	ret = dst;
	if (!dst || !src)
		return (NULL);
	while (*ret)
		ret++;
	while (*src)
		*ret++ = *src++;
	*ret = '\0';
	return (dst);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	if (!str)
		retunr (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}
//-------------------

char	*strdup(const char *s)
{
	char	*dup;
	char	*ret;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ret = dup;
	while (*s)
		*ret++ = *s++;
	*ret = '\0';
	return (dup);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;
	char	*ret;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	ret = sub;
	while (len--)
		*ret++ = s[start++];
	*ret = '\0';
	return (sub);
}
