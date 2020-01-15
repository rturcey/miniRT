/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:48:19 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:48:20 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

int			intercone(t_object r, t_object co, double *t);
double		quadracone(t_object r, t_object co, double *a);
t_vector	cone_normal(t_object o, t_vector p, t_object r, double t);
int			interdisk(t_object r, t_object d, double *t);
int			intercylinder(t_object r, t_object cy, double *t);
int			quadracylinder(t_object r, t_object cy, double *d, double *t);
t_vector	cylinder_normal(t_object o, t_vector p, t_object r, double t);
int			interplane(t_object r, t_object pl, double *t);
int			intersphere(t_object r, t_object s, double *t);
int			intersquarebis(t_object r, t_object sq, double *t);
int			intersquarebisbis(t_object r, t_object sq, double *t);
int			intersquare(t_object r, t_object sq, double *t);
t_vector	square_normal(t_object o, t_object r);
t_vector	triangle_normal(t_object o, t_object r);
int			intertriangle(t_object r, t_object tr, double *t);
void		create_square(t_object *o);
void		create_cube(t_object *o, t_p *p);
void		create_square_lr(t_object *o);
void		create_square_fb(t_object *o);
void		create_pyramid(t_object *obj, t_p *p);
void		create_cylinder(t_object *obj, t_p *p);

#endif
