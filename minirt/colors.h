#ifndef COLORS_H
# define COLORS_H

t_color				utd_colors(double x, double y, double z);
t_color_db			utd_colors_db(double x, double y, double z);
t_vector			mult_col_vec(t_color_db color, t_vector v);
t_vector			utd_colors_object(double r, double g, double b);
t_color				final_color(t_color_db c2);
t_color_db			add_colors(t_color_db c1, t_color_db c2);
t_color				*final_buffer(t_color *buffer);
t_color_db			minmax_px(t_vector px);
t_color_db			minmax_px_lite(t_vector px);

#endif
