#ifndef CONES_H
# define CONES_H

void	init_cone(t_vector origin, t_vector r, double h, double rayon, char effect);
int		intercone(t_object r, t_object co, double *t);
double	quadracone(t_object r, t_object co, double *a);

#endif
