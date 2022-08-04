#include "minirt_struct.h"
#include "math_utils.h"
#include "tuple.h"
#include "matrix.h"
#include <math.h>

static inline t_vec3 compute_normal(t_object *obj, t_point3 t)
{
	t_vec3	obj_normal;
	t_vec3	world_normal;

	obj_normal = t;
	obj_normal.y = 0;
	world_normal = vec_norm(matrix4_tmul(obj->M_inv_trans, obj_normal));
	world_normal.w = 0;
	return (world_normal);
}

bool	intersect_cylinder(t_object *obj, t_ray *ray, t_rayhit *rayhit)
{
	t_ray	nray;
	double	t[2];
	double	y[2];
	double halfh = obj->p.cylinder.height / 2;

	nray = ray_transform(*ray, obj->M_inv);
	if (solve_quadratic(
				nray.dir.x * nray.dir.x + nray.dir.z * nray.dir.z,
				2 * (nray.org.x * nray.dir.x) + 2 * (nray.org.z * nray.dir.z),
				(nray.org.x * nray.org.x)  + (nray.org.z * nray.org.z) - 1, t))
	{
		if (t[1] < 0)
			return (false);
		y[0] = nray.org.y + nray.dir.y * t[0]; 
		y[1] = nray.org.y + nray.dir.y * t[1]; 
		if (y[0] > -halfh && y[0] < halfh)
			rayhit->t = t[0];
		else if (y[1] > -halfh && y[1] < halfh)
			rayhit->t = t[1];
		else
			return (false);
		rayhit->intersect_p = get_ray_point(*ray, rayhit->t);
		rayhit->intersect_p_local = get_ray_point(nray, rayhit->t);
		rayhit->normal = compute_normal(obj, rayhit->intersect_p_local);
		return (true);
	}
	return (false);
}
