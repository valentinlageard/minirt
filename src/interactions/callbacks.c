/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:47:53 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/22 16:21:39 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_callback(int k, int *param)
{
	ft_printf("k : %d\n", k);
	if (k == 99)
		change_camera((t_prog *)(param));
	if (k == 65307)
		quit((t_prog *)(param));
	return (0);
}

int	exit_callback(int *param)
{
	quit((t_prog *)param);
	return (0);
}
