/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:29 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 10:33:27 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_line_list(t_line_node *head)
{
	t_line_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

t_line_node	*create_line_node(char *line)
{
	t_line_node	*node;

	node = malloc(sizeof(t_line_node));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = NULL;
	return (node);
}

t_line_node	*read_lines_to_list(int fd, int *rows)
{
	t_line_node	*head;
	t_line_node	*tail;
	t_line_node	*node;
	char		*line;

	head = NULL;
	*rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		node = create_line_node(line);
		if (!node)
		{
			free_line_list(head);
			return (NULL);
		}
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		(*rows)++;
		line = get_next_line(fd);
	}
	return (head);
}

char	**list_to_map_array(t_line_node *head, int rows)
{
	char		**map;
	int			i;
	int			len;
	t_line_node	*tmp;

	map = malloc(sizeof(char *) * (rows + 1));
	i = 0;
	if (!map)
		return (NULL);
	while (head)
	{
		len = ft_strlen(head->line);
		if (len > 0 && head->line[len - 1] == '\n')
			head->line[len - 1] = '\0';
		map[i] = head->line;
		i++;
		tmp = head;
		head = head->next;
		free(tmp);
	}
	map[i] = NULL;
	return (map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	free(map);
}
