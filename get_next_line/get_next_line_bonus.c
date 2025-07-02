/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:58:03 by miduarte          #+#    #+#             */
/*   Updated: 2025/05/09 12:39:00 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE];
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
	{
		if (fd > 0 && fd < FOPEN_MAX)
		{
			while (buffer[fd][i])
				buffer[fd][i++] = 0;
		}
		return (NULL);
	}
	line = NULL;
	while (*(buffer[fd]) || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_gnl(line, buffer[fd]);
		if (ft_reset(buffer[fd]))
			break ;
	}
	return (line);
}
