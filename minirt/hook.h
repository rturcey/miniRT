#ifndef HOOK_H
# define HOOK_H

void	add_range(double *r, double d);
void	key_rotation(int keycode);
void	key_rotation_bis(int keycode);
void	key_translation(int keycode);
void	key_attribute(int keycode);
int 	key_rainbow(int keycode);
int 	key_hook(int keycode, void *param);
int 	motion_hook(int x, int y, void *param);
int		motion_close(void *param);
int		mouse_hook(int button, int x, int y, void *param);
int		key_effects(int keycode);

#endif
