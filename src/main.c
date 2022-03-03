/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:17:33 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/03 18:56:07 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	leaks(void)
{
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	t_map	*map;

	//atexit(leaks);
	if (argc < 2)
		clean_exit("Error\n-> A map file is needed.", NULL);
	if (ft_strncmp((ft_strrchr(argv[1], '\0')) - 4, ".ber", 4) != 0)
		clean_exit("Error\n-> Map must a '.ber' extension file.", NULL);
	map = check_map_errors(argv[1]);
	parse_map(map, argv[1]);
	printf("Everything OK");
	return (0);
}

int	ft_line_len(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (*(line + len - 1) == '\n')
		len--;
	return (len);
}
