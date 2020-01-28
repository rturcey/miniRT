# miniRT, un (mini) Raytracer en C

Il s'agit de l'un des premiers projets menés à 42, et le premier avec la minilibX (librairie utilisée à l'école pour les projets graphiques).

## Utilisation

Le programme a été conçu pour MacOS.
Clonez le dépôt, et lancez la commande `make`, puis `./miniRT [nomdufichier.rt]`.
Voir plus bas pour la syntaxe du fichier de scène. Par défaut, l'image générée s'affiche dans une nouvelle fenêtre aux dimensions de la résolution indiquée. Pour exporter l'image au format BMP, ajoutez l'argument `-save`.

## Fonctionnalités

**Formes**
- basiques (plan, carré, triangle, sphère, cylindre, cône)
- composées (cube, pyramide)

**Lumières**

- multispots
- lumières colorées
- lumière d'ambiance
- ombres

**Effets**

- perturbation de la normale avec sin
- perturbations de la couleur (effet arc-en-ciel, damier)
- effet miroir
- textures sur les sphères (UV mapping)
- filtres de couleur (R/G/B, sépia, noir et blanc)
- antialiasing (réglable de 1 à 6)

**Autres**

- disques au bout des cylindres
- rendu multithreadé
- export BMP

## Interactions clavier/souris

Les keybind peuvent être modifiés dans `sources/interactions/`. Ils ont été prévus pour une utilisation pratique sur les claviers de l'école.

**Navigation**

*La majorité des actions donne lieu à une réduction de la qualité et de la taille de l'image, par souci de fluidité. Il suffit d'appuyer sur* `espace` *pour générer l'image définitive résultant des changements.*
*La navigation se fait à l'aide d'un compteur et d'un objet courant. Lorsque vous changez d'objet, et que le compteur dépasse le nombre d'objets de ce type, il revient à 0.*
- `ocl` : sélectionne le type de l'objet à modifier (forme, caméra, lumière)
- `=` : incrémente le compteur.

**Transformations**
*Les transformations (quand elles sont possibles) s'appliquent aussi bien aux formes qu'aux lumières et caméras.*

- `flèches directionnelles` : translation
- `wasd` : rotation (excepté pour les sphères, triangles et lumières)
- `[ ]` : diminution / augmentation de la propriété n° 1
- `' \` : diminution / augmentation de la propriété n° 2, s'il y a lieu

**Effets**

- `rgb`, `n`, `p` : filtres RGB, noir et blanc, sépia
- `1 à 6` antialiasing (génère automatiquement une nouvelle image)
- `page up/down` augmente / diminue l'intensité de la lumière ambiante

**Souris**

*La souris permet de faire bouger la caméra. Chaque action est à effectuer dans le quart supérieur gauche de la fenêtre.*
- `molette` zoom/dézoom de la caméra
- `bouton 3 (clic molette)` active la rotation de la caméra selon les mouvements de la souris
- `clic gauche / droit` accélère ou décélère la vitesse de la rotation

## Fichiers .rt

Le parsing détecte les éventuelles erreurs des fichiers .rt et les signale explicitement. En voici la syntaxe. 
/!\ à bien différencier les `.` des `,`
Tous les vecteurs admettent des `double`. La couleur prend trois nombres entiers allant chacun de 0 à 255 (r,g,b).

**Paramètres uniques**

`R 1440 900` Résolution : paramètre obligatoire, largeur & hauteur, minimum 1 pour chacun. Si la résolution dépasse celle de l'écran actuelle, elle s'aligne sur la résolution maximale.

`A 0.2 255,0,255` Lumière d'ambiance : paramètre unique mais facultatif, intensité de la lumière de 0 à 1, puis sa couleur.

`aa 3` Antialiasing : paramètre unique mais facultatif, entre 1 (aucun) et 6 (maximum).

`f p` Filtre de couleur : paramètre unique mais facultatif, r/g/b/n/p.

**Objets**

`c 0,0,300 0,0,0 60` Caméras : au moins une, coordonnées de l'origine, vecteur d'orientation (range [-1,1]), puis FOV (champ de vue) de 0 à 180.

`l 0,100,50 0.8 255,255,255` Lumières : coordonnées de la source, intensité de la lumière de 0 à 1, couleur de la lumière.

`sp 0,0,0 40 255,255,255` Sphère : origine, rayon, couleur.

`pl 0,-200,0 0,1,0 255,0,255` Plan : coordonnées d'un point par lequel il passe, vecteur d'orientation (range [-1,1]), couleur.

`sq 50,0,0 1,0,0 30.5 255,0,0` Carré : coordonnées du centre, vecteur d'orientation (range [-1,1]), taille des côtés, couleur.

`tr -50,0,0 0,50,0 0,-50,0 255,0,0` Triangle : coordonnées des trois points, couleur.

`cy 0,100,0 1,0,0 10 30 255,255,255` Cylindre : origine, vecteur d'orientation (range [-1,1]), diamètre, hauteur, couleur.

`co 0,100,0 1,0,0 10 30 255,255,255` Cône : origine, vecteur d'orientation (range [-1,1]), courbe, hauteur, couleur.

`cu 250,0,0 1,0,0 30.5 255,0,0` Cube : coordonnées du centre, vecteur d'orientation (range [-1,1]), taille des côtés, couleur.

`py 0,-100,0 0,1,0 40 50 255,255,255` Cône : origine, vecteur d'orientation (range [-1,1]), taille des côtés de la base, hauteur, couleur.

**Options**

Chaque forme peut subir des effets. Il suffit d'ajouter, après la couleur de l'objet, l'un des effets suivants (si applicable) : 

`d 0,0,0 20` Damier : deuxième couleur, taille des carreaux. Applicable sur les surfaces planes (instable sur le reste).

`r 0.002` Arc-en-ciel : la couleur de l'objet est remplacée par un dégradé de couleurs, dont on fixe la densité. Applicable sur toutes les formes.

`b "nomdufichier.xpm"` UV mapping : applicable uniquement sur les sphères. Indiquer le chemin d'une image XPM.

`m` Miroir : applicable sur toutes les formes.

`A-Z` Perturbation de la normale : cumulable avec n'importe quel effet (passer la lettre en majuscule), ou de façon autonome avec une majuscule lambda, la normale est perturbée à l'aide de sin.


## Exemples

*Les fichiers .rt générant les images ci-dessous sont disponibles dans le dossier* `scenes`.

![sc1](https://raw.githubusercontent.com/harner1/miniRt/master/images/basics.bmp?token=ALOEVZ67JDYHWCACFNP6WGC6F22XY)
![sc2](https://raw.githubusercontent.com/harner1/miniRt/master/images/composed.bmp?token=ALOEVZ7LEH4Q64KMIGMMFHS6F22ZI)
![sc3](https://raw.githubusercontent.com/harner1/miniRt/master/images/bonus.bmp?token=ALOEVZ5I7AYLKPAWXWCINUC6F223I)
