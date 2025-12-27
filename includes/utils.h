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

char				**split_lines(char *s);
char	    		*read_file(char *file_path);
char 				**split_one_time(char *str);
size_t				skip_spaces(char *str, size_t i);
size_t				skip_spaces(char *str, size_t i);
int					count_char(const char *s, char c);
bool				check_if_match(char *sep, char c);
char				*join_two_strings(char *s1, char *s2,
						char *delemiter);

#endif
