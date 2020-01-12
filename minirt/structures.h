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
	int 			x;
	int				y;
}					t_mapping;

typedef	struct		s_object
{
	char			type;
	t_vector		origin;
	t_vector		true_origin;
	t_vector		origin1;
	t_vector		origin2;
	double			rayon;
	double			h;
	double			s;
	double			dist;
	t_vector		col;
	t_vector		col1;
	t_vector		col2;
	t_vector		center;
	t_vector		rot;
	t_vector		s1;
	t_vector		s2;
	t_vector		dir;
	double			intensity;
	t_color_db		color;
	int				composed;
	int 			nobjs;
	char			effect;
	int 			rb;
	int 			disks;
	double 			rainbow;
	double 			fov;
	int 			ch;
	t_mapping		uvmap;
}					t_object;

typedef struct		s_params
{
	t_object		*o;
	t_object		*l;
	t_object		*r;
	int 			w;
	int 			h;
	int 			nbcams;
	int 			nblights;
	int 			nobjs;
	double			fov;
	int				x;
	t_object		ray;
	t_object		ray_m;
	t_vector		p;
	t_vector		n;
	t_vector		ambient;
	double			amb_int;
	t_color_db		color;
	int 			aa;
	char			filter;
	void 			*mlx_p;
	void 			*mlx_i;
	void 			*mlx_w;
	int 			threads;
	t_color_db		*buffer;
}					t_p;

#endif