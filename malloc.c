/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:18:11 by dengstra          #+#    #+#             */
/*   Updated: 2018/12/14 18:32:05 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_mem g_mem = {NULL, NULL, NULL};

static void	*alloc_split(t_header *free_mem, size_t size)
{
	t_header *malloced;

	malloced = free_mem;
	free_mem = (t_header*)(((char*)free_mem) + sizeof(t_header) + size);
	free_mem->size = malloced->size - sizeof(t_header) - size;
	free_mem->is_free = 1;
	free_mem->next = malloced->next;
	malloced->next = free_mem;
	malloced->is_free = 0;
	malloced->size = size;
	return (malloced + 1);
}

static void	*alloc_remove(t_header *free_mem)
{
	free_mem->is_free = 0;
	return (free_mem + 1);
}

static void	*alloc(t_header **head, size_t size, size_t block_size)
{
	t_header *i_head;

	i_head = *head;
	while (i_head)
	{
		if (i_head->is_free && i_head->size >
				size + sizeof(t_header) + sizeof(t_header))
			return (alloc_split(i_head, size));
		else if (i_head->is_free && i_head->size == size)
			return (alloc_remove(i_head));
		i_head = i_head->next;
	}
	if (i_head == NULL)
	{
		if (!mmap_new_block(head, block_size))
			return (NULL);
		return (alloc(head, size, block_size));
	}
	return (NULL);
}

static void	*alloc_large(size_t size)
{
	t_header		*malloced;

	if (!mmap_new_block(&(g_mem.large), size))
		return (NULL);
	malloced = g_mem.large;
	malloced->is_free = 0;
	return (malloced + 1);
}

void		*malloc(size_t size)
{
	if (size == 0)
		return (NULL);
	if (size <= TINY_MAX_SIZE)
		return (alloc(&(g_mem.tiny), size, TINY_MAX_SIZE * 100));
	if (size <= SMALL_MAX_SIZE)
		return (alloc(&(g_mem.small), size, SMALL_MAX_SIZE * 100));
	return (alloc_large(size));
}
