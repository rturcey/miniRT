#ifndef SQUARES_H
# define SQUARES_H

void	init_square(t_vector o, t_vector r, double h, char effect);
int		intersquare(t_object r, t_object sq, double *t);
int		intersquarebis(t_object r, t_object sq, double *t);
int		intersquarebisbis(t_object r, t_object sq, double *t);

#endif
