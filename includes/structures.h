/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:48:24 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:48:25 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef	struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_color
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	alpha;
}					t_color;

typedef struct		s_color_db
{
	double			blue;
	double			green;
	double			red;
	double			alpha;
}					t_color_db;

typedef struct		s_mapping
{
	void			*ptr;
	t_color			*img;
	int				x;
	int				y;
}					t_mapping;

typedef	struct		s_object
{
	char			t;
	t_vector		o;
	t_vector		true_o;
	t_vector		o1;
	t_vector		o2;
	double			rayon;
	double			h;
	double			intensity;
	double			dist;
	double			fov;
	t_vector		dir;
	t_vector		col;
	t_vector		col1;
	t_vector		col2;
	t_vector		ctr;
	t_vector		rot;
	t_vector		s1;
	t_vector		s2;
	t_color_db		color;
	int				cp;
	char			effect;
	int				rb;
	double			rainbow;
	int				ch;
	t_mapping		*uvmap;
}					t_object;

typedef struct		s_params
{
	t_object		*o;
	t_object		*l;
	t_object		*r;
	char			*filename;
	int				w;
	int				h;
	int				nbcams;
	int				nblights;
	int				nobjs;
	int				ct;
	t_object		*curr;
	double			fov;
	int				x;
	t_object		ray;
	t_object		ray_m;
	t_vector		p;
	t_vector		n;
	t_vector		ambient;
	double			amb_int;
	t_color_db		color;
	double			aa;
	char			filter;
	void			*mlx_p;
	void			*mlx_i;
	void			*mlx_w;
	int				threads;
	t_color_db		*bf;
	t_color			*endbf;
	int				aarainb;
	int				mouse;
	char			save;
	int				lite;
}					t_p;

#endif
