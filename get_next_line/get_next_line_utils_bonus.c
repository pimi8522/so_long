/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:57:30 by miduarte          #+#    #+#             */
/*   Updated: 2025/05/09 12:38:42 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *line, char *bag)
{
	char	*final;
	size_t	i;
	size_t	j;

	if (!bag)
		return (NULL);
	final = malloc(ft_strlen_gnl(line) + ft_strlen_gnl(bag) + 1);
	if (!final)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		final[i] = line[i];
		i++;
	}
	j = 0;
	while (bag[j] && bag[j] != '\n')
		final[i++] = bag[j++];
	if (bag[j] == '\n')
		final[i++] = '\n';
	final[i] = '\0';
	free(line);
	return (final);
}

int	ft_reset(char *buffer)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (buffer[i])
	{
		if (flag == 1)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			flag = 1;
		buffer[i] = 0;
		i++;
	}
	return (flag);
}
