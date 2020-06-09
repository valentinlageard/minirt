/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_maths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:34:06 by vlageard          #+#    #+#             */
/*   Updated: 2020/06/10 01:58:25 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3		*get_abc_cyl(t_ray *ray, t_vec3 *dp, t_vec3 *ca, double r)
{
	t_vec3	*abc;
	t_vec3	*vtmp1;
	t_vec3	*vtmp2;
	t_vec3	*vtmp3;

	abc = new_vec3(0,0,0);
	vtmp1 = new_vec3(
		ca->x * vec3_dot(ray->dir, ca),
		ca->y * vec3_dot(ray->dir, ca),
		ca->z * vec3_dot(ray->dir, ca));
	vtmp2 = vec3_sub(ray->dir, vtmp1);
	free(vtmp1);
	abc->x = vec3_dot(vtmp2, vtmp2);
	vtmp1 = new_vec3(
		ca->x * vec3_dot(dp, ca),
		ca->y * vec3_dot(dp, ca),
		ca->z * vec3_dot(dp, ca));
	vtmp3 = vec3_sub(dp, vtmp1);
	abc->y = 2.0 * vec3_dot(vtmp2, vtmp3);
	abc->z = vec3_dot(vtmp3, vtmp3) - r * r;
	free(vtmp1);
	free(vtmp2);
	free(vtmp3);
	return (abc);	
}

double		intersect_cyl(t_ray *ray, t_cyl *cyl)
{
	t_vec3	*abc;
	t_vec3	*dp;
	t_vec3	*ca;
	double	res;
	
	ca = get_cyl_axis(cyl);
	dp = vec3_sub(ray->orig, cyl->pos);
	abc = get_abc_cyl(ray, dp, ca, cyl->diameter / 2.0);
	free(dp);
	free(ca);
	res = get_min_quadratic_solution(abc->x, abc->y, abc->z);
	free(abc);
	return (res);
	// Need to check if inside the cylinder size...
}

t_vec3		*get_hit_point_cyl(t_ray *ray, t_cyl * cyl)
{
	double	t;
	double	hp_x;
	double	hp_y;
	double	hp_z;

	t = intersect_cyl(ray, cyl);
	hp_x = ray->orig->x + ray->dir->x * t;
	hp_y = ray->orig->y + ray->dir->y * t;
	hp_z = ray->orig->z + ray->dir->z * t;
	return (new_vec3(hp_x, hp_y, hp_z));
}

t_vec3		*get_normal_cyl(t_vec3 *hit_point, t_cyl *cyl)
{
	t_vec3	*hmp;
	t_vec3	*vtmp1;
	t_vec3	*vtmp2;
	double	cadhmp;

	hmp = vec3_sub(hit_point, cyl->pos);
	vtmp1 = get_cyl_axis(cyl);
	cadhmp = vec3_dot(vtmp1, hmp);
	vtmp2 = new_vec3(cadhmp * vtmp1->x, cadhmp * vtmp1->y, cadhmp * vtmp1->z);
	free(vtmp1);
	vtmp1 = vec3_sub(hmp, vtmp2);
	free(vtmp2);
	vtmp2 = vec3_normalize(vtmp1);
	free(hmp);
	free(vtmp1);
	return (vtmp2);
}

t_light_p	*get_light_p_cyl(t_ray *ray, t_object *obj)
{
	t_cyl		*cyl;
	t_vec3		*hit_point;
	t_vec3		*normal;
	t_vec3		*vcolor;

	cyl = (t_cyl *)obj->object;
	hit_point = get_hit_point_cyl(ray, cyl);
	normal = get_normal_cyl(hit_point, cyl);
	vcolor = coltovec3(cyl->color);
	return (new_light_p(hit_point, normal, vcolor, obj));
}