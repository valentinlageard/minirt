/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 16:22:27 by vlageard          #+#    #+#             */
/*   Updated: 2020/03/15 17:07:37 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	*vec3_rotateX(t_vec3 *vec3, double alpha)
{
	double	y;
	double	z;

	y = vec3->y * cos(PI * alpha) - vec3->z * sin(PI * alpha);
	z = vec3->y * sin(PI * alpha) + vec3->z * cos(PI * alpha);
	return (new_vec3(vec3->x, y, z));
}

t_vec3	*vec3_rotateY(t_vec3 *vec3, double beta)
{
	double	x;
	double	z;

	x = vec3->x * cos(PI * beta) + vec3->z * sin(PI * beta);
	z = vec3->x * -sin(PI * beta) + vec3->z * cos(PI * beta);
	return (new_vec3(x, vec3->y, z));
}

t_vec3	*vec3_rotateZ(t_vec3 *vec3, double gamma)
{
	double	x;
	double	y;

	x = vec3->x * cos(PI * gamma) - vec3->y * sin(PI * gamma);
	y = vec3->x * sin(PI * gamma) + vec3->y * cos(PI * gamma);
	return (new_vec3(x, y, vec3->z));
}

t_vec3	*vec3_rotateXYZ(t_vec3 *vec3, t_vec3 *ovec3)
{
	t_vec3	*rvec3;
	t_vec3	*tmp_x;
	t_vec3	*tmp_y;

	tmp_x = vec3_rotateX(vec3, ovec3->x);
	tmp_y = vec3_rotateY(tmp_x, ovec3->y);
	rvec3 = vec3_rotateZ(tmp_y, ovec3->z);
	free(tmp_x);
	free(tmp_y);
	return (rvec3);
}