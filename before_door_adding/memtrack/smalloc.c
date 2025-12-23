/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:27:34 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/22 05:27:35 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtrack.h"

void	*smalloc(size_t size)
{
	void	*pointer;

	pointer = malloc(size);
	if (!pointer)
	{
		error_exit("Memory allocation failure");
	}
	return (pointer);
}
