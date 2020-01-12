#ifndef INTER_H
# define INTER_H

double		interlight(t_object r, t_object *o, double *min);
int			interobj(t_object r, t_object *o, t_vector *p, t_vector *n);
int			inters(t_object r, t_object o, double *t);
t_vector	get_normal(t_object o, t_vector *p, t_object r, double t);

#endif
