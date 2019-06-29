/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 20:43:51 by dengstra          #+#    #+#             */
/*   Updated: 2018/12/14 18:23:24 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>

# define TINY_MAX_SIZE 0x1000
# define SMALL_MAX_SIZE 0x100000

typedef struct		s_header
{
	size_t			size;
	struct s_header	*next;
	char			is_free;
}					t_header;

typedef struct		s_mem
{
	t_header		*tiny;
	t_header		*small;
	t_header		*large;
}					t_mem;

extern t_mem		g_mem;

int					is_valid_mem(void *mem);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
void				*mmap_new_block(t_header **head, size_t size);

#endif
