#ifndef CYLINDERS_H
# define CYLINDERS_H

void	init_cylinder(t_vector origin, t_vector range, double h, double rayon, char effect);
void	init_disk(t_vector origin, t_vector r, double rayon, char effect);
int		interdisk(t_object r, t_object d, double *t);
int		intercylinder(t_object r, t_object cy, double *t);
int		quadracylinder(t_object r, t_object cy, double *d, double *t);

#endif
