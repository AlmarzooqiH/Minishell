/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:36:37 by hamalmar          #+#    #+#             */
/*   Updated: 2024/10/02 13:28:55 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_and_free(char *buf1, char *buf2)
{
	char	*new_buf;

	if (!buf1 || !buf2)
		return (NULL);
	new_buf = ft_strjoin(buf1, buf2);
	if (!new_buf)
		return (free(new_buf), NULL);
	return (free(buf1), new_buf);
}

char	*read_line(int fd, char *buf)
{
	char	*temp;
	size_t	bytes_read;

	if (!buf)
		buf = ft_strdup("");
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (free(buf), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		temp[bytes_read] = '\0';
		if (check_for_n(temp))
			break ;
		buf = join_and_free(buf, temp);
	}
	if (bytes_read <= 0)
	{
		if (bytes_read == 0 && buf[0] != '\0')
			return (free(temp), buf);
		return (free(temp), free(buf), NULL);
	}
	buf = join_and_free(buf, temp);
	return (free(temp), buf);
}

char	*copy_after_n(char *buf)
{
	char	*new_buf;
	size_t	i;

	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			break ;
		i++;
	}
	i++;
	new_buf = ft_substr(buf, i, ft_strlen(buf) - i);
	if (!new_buf)
		return (NULL);
	free(buf);
	return (new_buf);
}

int	check_for_n(char *buf)
{
	size_t	i;

	if (!buf)
		return (0);
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || \
		read(fd, 0, 0) < 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = 0;
		}
		return (NULL);
	}
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	temp = copy_before_n(buffer);
	buffer = copy_after_n(buffer);
	return (temp);
}
