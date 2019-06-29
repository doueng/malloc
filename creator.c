/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 20:43:41 by dengstra          #+#    #+#             */
/*   Updated: 2018/12/14 20:21:26 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	get_block_size(size_t alloc_size)
{
	size_t	pages;
	int		page_size;

	page_size = getpagesize();
	pages = (alloc_size + sizeof(t_header)) / page_size;
	return ((pages + 1) * page_size);
}

void			*mmap_new_block(t_header **head, size_t size)
{
	t_header	*new_block;
	size_t		block_size;

	block_size = get_block_size(size);
	new_block = (t_header*)mmap(NULL,
								block_size,
								PROT_READ | PROT_WRITE,
								MAP_ANON | MAP_PRIVATE,
								-1,
								0);
	if (new_block == MAP_FAILED)
	{
		write(2, "mmap failed\n", 13);
		return (NULL);
	}
	new_block->size = block_size - sizeof(t_header);
	new_block->next = *head;
	new_block->is_free = 1;
	*head = new_block;
	return (*head);
}
