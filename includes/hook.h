#ifndef HOOK_H
# define HOOK_H

int 	key_hook(int keycode, void *param);
int 	key_normal(int keycode, void *param);
int 	key_count(int keycode, t_p *p);
int		key_effects(int keycode, t_p *p);
int 	motion_hook(int x, int y, void *param);
int		motion_close(void *param);
int		mouse_hook(int button, int x, int y, void *param);
void	add_range(double *r, double d);
void	key_rotation(int keycode, t_p *p);
void	key_rotation_bis(int keycode, t_p *p);
void	key_translation(int keycode, t_p *p);
void	key_attribute(int keycode, t_p *p);

#endif
