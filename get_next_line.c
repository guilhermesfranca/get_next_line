/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfranca <gfranca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:55:42 by gfranca           #+#    #+#             */
/*   Updated: 2026/05/28 15:49:47 by gfranca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char *stash)
{
	char	*buf;
	int		ret;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	ret = 1;
	while (!ft_strchr(stash, '\n') && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (free(buf), free(stash), NULL);
		buf[ret] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (free(buf), NULL);
	}
	return (free(buf), stash);
}

static char	*extract_line(char *stash)
{
	size_t	len;

	if (!stash || !stash[0])
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	return (ft_substr(stash, 0, len));
}

static char	*update_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
	free(stash);
	if (new_stash && !new_stash[0])
		return (free(new_stash), NULL);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
