/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:36:33 by dangonza          #+#    #+#             */
/*   Updated: 2022/02/28 15:01:55 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory_allocated;

	memory_allocated = (void *) malloc(count * size);
	if (!memory_allocated)
		return (NULL);
	ft_bzero(memory_allocated, size * count);
	return (memory_allocated);
}
