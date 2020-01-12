#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <pthread.h>
# include "libft/libft.h"
# include "structures.h"
# include "vectors.h"
# include "rays.h"
# include "colors.h"
# include "lights.h"
# include "spheres.h"
# include "inter.h"
# include "planes.h"
# include "triangles.h"
# include "squares.h"
# include "cylinders.h"
# include "pyracubes.h"
# include "cones.h"
# include "mapping.h"
# include "effects.h"
# include "hook.h"
# include "parsing.h"

void	put_img(t_p *p);
void	go_image_lite(t_p *p);
void	go_image(t_p *p);
void	create_threads_lite(t_p *p);
void	create_threads(double fov);

#endif
