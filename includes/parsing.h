#ifndef PARSING_H
# define PARSING_H

void	init_p(t_p *p);
int 	check_types(char **buff);
int		ft_parser(char **buff, t_p *p);
char	**ft_buffcopy(char *full);
int 	fill_tab(char *line, char **full);
int		checkfilename(char *s);
int		error_msg(int n, int line);
int		parse_resolution(char **buff, t_p *p);
int 	save_cam(char *buff, t_object *cam);
int		parse_cameras(char **buff, t_object *cam, t_p *p);
int 	parse_ambient(char **buff, t_p *p);
int		parse_lights(char **buff, t_object *light, t_p *p);
int 	save_light(char *buff, t_object *light);
int		parse_filters(char **buff, t_p *p);
int		parse_antialiasing(char **buff, t_p *p);
int 	parse_effects(char **buff, t_p *p);
int 	count_objects(char **buff);
int 	is_simple(char *buff, t_object *obj);
int		parse_objects(char **buff, t_object *obj, t_p *p);
int 	parse_simple(char *buff, t_object *obj, char type, t_p *p);
int 	parse_composed(char *buff, t_object *obj, char type, t_p *p);
int 	parse_cone(char *buff, t_object *obj, t_p *p);
int 	parse_triangle(char *buff, t_object *obj, t_p *p);
void	create_square(t_object *o);
int 	parse_square(char *buff, t_object *obj, t_p *p);
int 	parse_plane(char *buff, t_object *obj, t_p *p);
int 	parse_sphere(char *buff, t_object *obj, t_p *p);
void	create_cylinder(t_object *obj, t_p *p);
int 	parse_cylinder(char *buff, t_object *obj, t_p *p);
void	create_pyramid(t_object *obj, t_p *p);
int 	parse_pyramid(char *buff, t_object *obj, t_p *p);
void	create_square_fb(t_object *o);
void	create_square_lr(t_object *o);
void	create_cube(t_object *o, t_p *p);
int 	parse_cube(char *buff, t_object *obj, t_p *p);
int 	parse_textures(char *buff, t_object *obj, t_p *p);
int 	parse_uv_mapping(char *buff, t_object *obj, t_p *p);
int 	save_uv_mapping(char *buff, t_object *obj, t_p *p);

#endif