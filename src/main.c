/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:17:33 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/02 13:54:20 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void leaks() { system("leaks so_long"); }

int	main(int argc, char **argv)
{
	t_map	*map;
	atexit(leaks);

	check_args_errors(argc, argv);
	map = check_map_errors(argv[1]);
	return (0);
}
