/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:29 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/24 18:17:07 by miduarte         ###   ########.fr       */
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
	int			len;
	int			rows = 0;
	t_line_node	*head = NULL;
	t_line_node	*tail = NULL;
	char		**map;
	int			i;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error: non .ber file attempted to be read!\n");
		return (NULL);
	}
		

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

	// Step 3: Transfer lines from list → array, stripping GNL’s trailing '\n'
	i = 0;
	while (head)
	{
		// strip newline
		int len = ft_strlen(head->line);
		if (len > 0 && head->line[len - 1] == '\n')
			head->line[len - 1] = '\0';

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

