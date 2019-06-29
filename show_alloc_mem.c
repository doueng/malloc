/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:02:34 by dengstra          #+#    #+#             */
/*   Updated: 2018/12/14 17:08:04 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_pointer(void *p)
{
	char	*base;
	char	p_value[9];
	int		i;
	size_t	value;

	i = 9;
	value = (size_t)p;
	base = "0123456789ABCDEF";
	write(1, "0x", 2);
	while (i--)
	{
		p_value[i] = base[value % 16];
		value /= 16;
	}
	write(1, p_value, 9);
}

static void		print_size_t(size_t value)
{
	char		*base;

	if (!value)
		return ;
	base = "0123456789";
	print_size_t(value / 10);
	write(1, &base[value % 10], 1);
}

static size_t	print_mem(t_header *head)
{
	void	*end;
	size_t	total;

	total = 0;
	while (head)
	{
		if (head->is_free == 0)
		{
			end = (void*)(((char*)head) + sizeof(t_header) + head->size - 1);
			print_pointer(head + 1);
			write(1, " - ", 3);
			print_pointer(end);
			write(1, " : ", 3);
			print_size_t(head->size);
			write(1, " bytes\n", 7);
			total += head->size;
		}
		head = head->next;
	}
	return (total);
}

static size_t	print_mem_block(char *type, int type_len, void *headers)
{
	write(1, type, type_len);
	print_pointer(headers);
	write(1, "\n", 1);
	return (print_mem(headers));
}

void			show_alloc_mem(void)
{
	size_t total;

	total = 0;
	total += print_mem_block("TINY : ", 7, g_mem.tiny);
	total += print_mem_block("SMALL : ", 8, g_mem.small);
	total += print_mem_block("LARGE : ", 8, g_mem.large);
	print_size_t(total);
	write(1, " bytes\n", 7);
}
