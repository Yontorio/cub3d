/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtrack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:26:43 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/22 06:51:18 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef memtrack_H
# define memtrack_H

# include "cub3d.h"

# define CLOSE -1

typedef enum e_sid
{
	TEMPORARY,
	REMAINS
}						t_sid;

typedef struct s_section
{
	t_sid				section_id;
	void				**allocations;
	size_t				capacity;
	size_t				count;
	struct s_section	*next;
}						t_section;


void    				fd_storage(int fd);
t_section				**get_sections(void);
void					*smalloc(size_t size);
t_sid					*current_section(void);
void					destroy_everything(void);
void					clean_before_prompt(void);
void					add_allocation(void *pointer);
void					*allocate_memory(size_t size);
t_section				*create_section(t_sid section_id);
void					destroy_section(t_sid section_id);
int     				safe_open(const char *path, int flags);
void					clear_section_data(t_section *section);
t_section				*find_or_create_section(t_sid section_id);
void					set_current_section(t_sid updated_section_id);
void					*new_allocation(t_sid section_id, size_t size);
void					free_one_pointer(t_sid section_id, void *pointer);
void					*reallocate_memory(void *pointer, size_t old_size,
							size_t new_size);
t_section				*find_section(t_section *section, t_sid section_id);
void					add_allocation_to_section(t_sid section_id, void *ptr);

#endif