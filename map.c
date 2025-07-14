/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:29 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 11:19:04 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


/*
 * Load the .ber file into a NULL-terminated array of strings.
 */

typedef struct	s_line_node
{
	char				*line;
	struct s_line_node	*next;
}				t_line_node;

static void	free_line_list(t_line_node *head)
{
	t_line_node *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

char	**load_map(const char *filename)
{
	int			fd;
	char		*line;
	int			rows = 0;
	t_line_node	*head = NULL;
	t_line_node	*tail = NULL;
	char		**map;
	int			i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);

	// Step 1: Read lines into linked list
	while ((line = get_next_line(fd)) != NULL)
	{
		t_line_node *node = malloc(sizeof(t_line_node));
		if (!node)
		{
			free_line_list(head);
			close(fd);
			return (NULL);
		}
		node->line = line;
		node->next = NULL;
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		rows++;
	}
	close(fd);

	// Step 2: Allocate final array
	map = malloc(sizeof(char *) * (rows + 1));
	if (!map)
	{
		free_line_list(head);
		return (NULL);
	}

	// Step 3: Copy pointers, free nodes
	i = 0;
	while (head)
	{
		map[i++] = head->line;
		t_line_node *tmp = head;
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

