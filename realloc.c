/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:02:24 by dengstra          #+#    #+#             */
/*   Updated: 2018/12/14 17:05:54 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *addr, size_t size)
{
	t_header	*header;
	t_header	*new_mem;
	size_t		i;

	if (addr == NULL)
		return (malloc(size));
	if (!is_valid_mem(addr))
		return (NULL);
	header = ((t_header*)addr) - 1;
	if (header->is_free == 1)
		return (NULL);
	new_mem = (t_header*)addr;
	if (NULL == (new_mem = (t_header*)malloc(size)))
		return (NULL);
	i = 0;
	while (i < header->size && i < size)
	{
		((char*)new_mem)[i] = ((char*)addr)[i];
		i++;
	}
	free(addr);
	return (new_mem);
}
