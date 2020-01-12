#ifndef SPHERES_H
# define SPHERES_H

void	init_sphere(t_vector origin, double rayon, char effect);
int		intersphere(t_object r, t_object s, double *t);

#endif
