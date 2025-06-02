/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:10:59 by dbouizem          #+#    #+#             */
/*   Updated: 2025/06/02 15:54:29 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_fdlist
{
	int				fd;
	char			*stock;
	struct s_fdlist	*next;
}					t_fdlist;

char	*get_next_line(int fd);

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
