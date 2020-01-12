#ifndef PLANES_H
# define PLANES_H

void	init_plane(t_vector origin, t_vector range, char effect);
int		interplane(t_object r, t_object pl, double *t);

#endif
