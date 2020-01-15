/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:47:58 by rturcey           #+#    #+#             */
/*   Updated: 2020/01/15 14:48:00 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

int		key_hook(int k, void *param);
int		key_normal(int k, void *param);
int		key_ct(int k, t_p *p);
int		key_effects(int k, t_p *p);
int		motion_hook(int x, int y, void *param);
int		motion_close(void *param);
int		mouse_hook(int button, int x, int y, void *param);
void	add_range(double *r, double d);
void	key_rotation(int k, t_p *p);
void	key_rotation_bis(int k, t_p *p);
void	key_translation(int k, t_p *p);
void	key_attribute(int k, t_p *p);

#endif
