#ifndef VECTORS_H
# define VECTORS_H

t_vector		utd_v(double x, double y, double z);
t_vector		add_v(t_vector v1, t_vector v2);
t_vector		min_v(t_vector v1, t_vector v2);
t_vector		mult_v(double mult, t_vector v);
t_vector		div_v(double mult, t_vector v);
double			scal_v(t_vector v1, t_vector v2);
double			norm_v(t_vector v);
t_vector		normed(t_vector v);
t_vector		cross_v(t_vector v1, t_vector v2);
t_vector		div_each_v(t_vector v1, t_vector v2);
t_vector		rot_x(t_vector v, double r);
t_vector		rot_y(t_vector v, double r);
t_vector		rot_z(t_vector v, double r);
t_vector		rot_xyz(t_vector v, t_vector r);
t_vector		rot_zyx(t_vector v, t_vector r);
void			rot_p(t_vector *axes, double val, int axis);
void			rot_p_x(t_vector *axes, double val);
void			rot_p_y(t_vector *axes, double val);
void			rot_p_z(t_vector *axes, double val);

#endif
