/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:25:37 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/05/15 11:26:08 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	*get_start_time(void)
{
	static unsigned long	start_time;

	return (&start_time);
}

unsigned long	get_current_time(void)
{
	return (get_timestamp_ms() - *get_start_time());
}
