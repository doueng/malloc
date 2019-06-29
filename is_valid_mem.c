/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:02:18 by dengstra          #+#    #+#             */
/*   Updated: 2018/12/14 17:03:24 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	check_mem(t_header *head, void *mem)
{
	while (head)
	{
		if (mem == head + 1)
			return (1);
		head = head->next;
	}
	return (0);
}

int			is_valid_mem(void *mem)
{
	return (check_mem(g_mem.tiny, mem)
			|| check_mem(g_mem.small, mem)
			|| check_mem(g_mem.large, mem));
}
