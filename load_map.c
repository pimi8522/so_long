/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:39:03 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/11 15:39:19 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h" 

char	**load_map(const char *filename)
{
    int fd;
    int len;
    int rows;
    t_line_node *head;
    char **map;

    len = ft_strlen(filename);
    if (len < 5 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
    {
        ft_printf("Error: non .ber file attempted to be read!\n");
        return (NULL);
    }
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    head = read_lines_to_list(fd, &rows);
    close(fd);
    if (!head)
        return (NULL);
    map = list_to_map_array(head, rows);
    if (!map)
        free_line_list(head);
    return (map);
}
