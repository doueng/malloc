/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:02:14 by dengstra          #+#    #+#             */
/*   Updated: 2018/12/14 17:03:45 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		remove_large(void)
{
	t_header **large_mems;
	t_header *tmp;

	large_mems = &(g_mem.large);
	while (*large_mems)
	{
		tmp = *large_mems;
		if (tmp->is_free)
		{
			(*large_mems) = tmp->next;
			munmap(tmp, tmp->size + sizeof(t_header));
			break ;
		}
		large_mems = &((*large_mems)->next);
	}
}

void			free(void *mem)
{
	t_header *header;

	if (mem == NULL || 0 == is_valid_mem(mem))
		return ;
	header = mem - sizeof(t_header);
	header->is_free = 1;
	if (header->size > SMALL_MAX_SIZE)
		remove_large();
}
