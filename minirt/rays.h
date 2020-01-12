#ifndef RAYS_H
# define RAYS_H

void		init_ray(double x, double y, double z, t_vector range);
t_object	dirch_ray(t_object ray, double x, double y, double z);
t_object	spray(t_p *p, double x, double y);

#endif
