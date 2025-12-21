/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 08:41:01 by yjaafar           #+#    #+#             */
/*   Updated: 2025/08/22 06:52:33 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_list_info
{
	t_list			*list;
	t_list			*tail;
	size_t			size;
}					t_list_info;

char				**split_lines(char *s);
t_list				*creat_node(void *content);
char	    		*read_file(char *file_path);
t_list_info			*init_list_info_struct(void);
size_t				skip_spaces(char *str, size_t i);
size_t				skip_spaces(char *str, size_t i);
int					count_char(const char *s, char c);
bool				check_if_match(char *sep, char c);
char				*join_two_strings(char *s1, char *s2,
						char *delemiter);
char				**lst_to_arr(t_list_info *list_info);
char				*join_list_content(t_list *list, char *del,
						size_t len);
void				re_init_list_info_struct(t_list_info *list_info);
void				join_list(t_list_info *lst_1, t_list_info *lst_2);
void				list_add_back(t_list_info *list_info, t_list *node);

#endif
