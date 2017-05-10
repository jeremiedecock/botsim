# TODO

Exemple de qualité physique et visuelle à atteindre: https://www.youtube.com/watch?v=BGAwRKPlpCw

## Version 2.0.2

- [ ] Vérifier si le projet compile sur MacOSX et essayer de reprendre le
      développement sur xcode.
- [ ] Être capable de détecter et pénaliser les explosions de simulation ; la
      pénalité doit être graduelle et non pas binaire pour ne pas perturber les
      algorithmes d'optimisation. Soustraire au score ces pénalités (pondérées par un
      certain facteur fixé).
    - [ ] Créer la classe "Valuer" qui fait ces calculs: un Listener (comme les log) du
          tronc du robot (instance de Part donné en argument). RobudogValuer hérite
          de l'interface "Valuer". RobudogValuer est instancié dans la fonction "main",
          les autres modules n'ont pas besoin de connaitre cette classe.
          C'est RobudogValuer qui va calculer la distance parcourue par le tronc,
          les pénalités à appliquer et le score final pour la simulation.
    - [ ] 1er terme de pénalité: le robot a souvent tendance à voler après une
          explosion => compter le nombre de secondes (ou de ticks ou
          de timesteps) durant lesquelles le robot est au dessus d'un certain plan (ie
          combien de temps il "vole" suite à une/des explosion(s) dans la simulation)
          -> simple, graduel
    - [ ] 2e terme de pénalité: faire la somme de tous les mouvements de
          rotations (en radiant) du tronc sur chacun des 3 axes.
          -> simple, graduel et favorise en plus les robots qui marchent droit
- [ ] Permettre de passer les paramètres du contrôleur (constantes des
      sinusoides, poids des neurones d'un réseau de neurones, etc.) des
      actuateurs au simulateur via un fichier de configuration (Texte, CSV,
      JSON ou autre) et récupérer la fitnesse dans un autre fichier. L'idée
      étant de déporter la partie optimisation/ML/expériences/analyse/... en
      dehors de l'executable, dans des scripts Python (afin de bénéficier des
      nombreux avantages de Python dans ces domaines et pour
      assouplir/accélérer le développement du projet).  L'executable ne serait
      plus que la fonction de fitness. Dans un second temps, envisager de faire
      un vrai binding Python.

## Version 2.0.3

- [ ] Régler correctement les constantes physiques (mass, friction, couple des moteurs, ...)
- [ ] How to setup hinge torques ? The torque is infinite so far ? (google : "bullet physics hinge torque")
- [ ] Motor: set limits (contraindre les angles)
- [ ] Reécrire ground -> plus grand, en plusieurs parties

## Version 2.0.4

- [ ] Régler le problème de vectorisation d'Eigen3 sur certaines plates-formes:
      http://eigen.tuxfamily.org/dox-devel/group__TopicUnalignedArrayAssert.html

## Version 2.0.5

- [ ] Améliorer le rendu graphique: régler correctement les matériaux.
      Faire une appli dédiée OSG_Qt_Lab (ex: http://www.it.hiof.no/~borres/j3d/explain/light/p-mated.html )

## Version 2.1

- [ ] Compléter le fichier README: décrire les principales features, ajouter des vidéos, ...

## Version 2.2

- [ ] Reécrire la classe Part sur le model de la class Object: Part n'est plus
      héritée, les PhysicsShapes deviennent des attributs.
    - [ ] Créer une classe core/PhysicsShape et ses dérivées
    - [ ] Dans Part, un attribut pyhsicsShape remplace la spécialisation actuelle (Box, Sphere, ...)
    - [ ] Ajouter un attribut stlFile dans Part. Utiliser cet attribut pour
          l'affichage graphique du composant dans OSGEnv.
    - [ ] Déplacer la gestion du rendu des Parts dans BulletEnvironment ; Part
          ne doit plus du tout dépendre d'OSG ; OSG devient optionnel au moment de
          la compilation (ajouter une option cmake pour activer ou non OSG et un
          DEFINE).

## Version 2.3

- [ ] modifier l'API de sorte que les paramètres puissent aussi déterminer 
      la configuration physique du robot (angles de départ des actuateurs, etc.)
      et pas seulement son contrôle. Comment distinguer/répartir proprement
      les paramètres physique et les paramètres de contrôle ?

## Version 2.4

- [ ] Les instances de Part, Object et Scene peuvent être chargées dynamiquement depuis un fichier XML
    - [ ] Écrire un fichier XSD pour ces 3 types de fichier XML
    - [ ] Écrire un classe utilitaire chargée de générer les instances depuis les fichier XML
- [ ] Les scènes étant désormais définies dans des fichiers XML, il n'y a plus qu'un seul exécutable
- [ ] Corriger les fuites mémoire restant dans "scenes" et "builtinXXX"

## Version 2.4.1

- [ ] Permettre d'afficher les boites englobantes attachées à chaque
      PhysicShapes plutôt que le fichier STL des Parts.

## Version 2.4.2

- [ ] Écrire un grand nombre de démos (scènes) pour régler plus finement les
      constantes physiques (mass, friction, couple des moteurs, ...).

## Version 2.?

- Eigen3 / OpenSceneGraph license compatibility with MIT ??? -> ça ne pose problème que dans le cas de la redistribution des binaires with link static ???
  - changer de licence ??? ((L)GPL ? CeCILL ? ou MIT ?)

- "ConstantController" et "SinusoidController" prend en paramètre une map
  std::map<Actuator *, UnObjetOuUneStructureQuiContientLesParamPourLActuateurEnClé>
  pour donner un jeu de paramètres différent à chaque actuateur ?
  Pour ConstantController: la valeur du signal.
  Pour SinusoidController: les paramètres amplitude, fréquence et phase.
- mettre les attributs std::set<...> de Controller, BulletEnvironment et Object en public const (et supprimer les getters) ?
  But: supprimer toute ambigüité sur le fait qu'ils soit constant -> ces
  attributs sont traités dans le constructeur, les modifier après coup est sans
  effet.
  Pb: Le constructeur de la classe Object modifie les partsSet (et jointSet
  ?)... -> faire en sorte que le set commun parts+objects::parts ne soit plus
  qu'une variable locale (et non plus un attribut) utilisée pour initialiser
  btDynamicWorld ?
~ Créer une classe Controler: foncteur qui prend en entrée des percepts (temps, position, ...) et retourne une commande pour le/les actuateurs qu'il contrôle
    -> Controler: attaché à un Actuator ou un Objet complet (ie plusieurs actuateurs) ?
  Contrôleurs: classe "Controler" -> pattern listener ? : écoute les sensors et agit sur les actuators
    -> + permettre le contrôle des actuateurs depuis un processus distant ? (socket, rpc, ...)
- Servomoteurs: classe "Actuator" qui hérite de la classe "HingeJoint" ???

+ improve shadow technics ( http://trac.openscenegraph.org/projects/osg//wiki/Support/ProgrammingGuide/osgShadow )


## Optimisation/IA

- Créer des contrôleurs
  - SAES + sinusoïdes
  - SAES + convolution de sinusoïdes
  - SAES + neural net (?)
  - PID (pendule inversé)
  - Reinforcement learning
  - Contrôle manuel via un joypad (pour les robots à roues)
- Modéliser, créer les objets et créer les contrôleurs pour des robots
  - Créer un robot à 4 roues
  - Créer un robot à 2 roues (pendule inversé)
  - Créer un robot à 4 pattes
  - Créer un robot à 6 ou 8 pattes
- Optimisation les contrôleurs -> quelle "interface" dans l'API ?
  - Permettre d'optimiser les contrôleurs de manière répartie (MPI, OpenMP, ...)
- Controleur robuste
  - ajouter du bruit dans les commandes
    créer une classe "Filter" / "Noise" appliquée aux senseurs/aux actuateurs
    pour simuler la transposition à la réalité -> pattern wrapper ?
  - modifier les constantes physiques à chaque génération (friction, mass, ...
    pour ne pas dépendre d'une mauvaise configuration du moteur)


## Petits ajouts faciles et utiles

+ boost::Program_options: logs...
  --log_bullet    filename.dat            or   filename.json
  --log_part      partname,filename.dat   or   partname,filename.json
  --log_part_tick partname,filename.dat   or   partname,filename.json
+ harmoniser les noms
  x "substeps" vs "ticks" (bullet env + logs)
  + "callback" vs "handler"
+ Fichiers Dat: pour la 1ere colonne, préciser dans l'entête si il s'agit du "simulation_time" ou du "user_time"
+ scripts plot génériques
  plot_part    --key key [--key key, ...] FILE [FILE, ...]   [--list_keys] -> list available keys
  plot_bullet  --key key FILE   [--list_keys] -> list available keys
  plot_3d_path
  .dat  -> cf. DVS
  .json -> cf. PCP
- ajouter joints slider + actuateur correspondant (linearmotor)
- Le module "src/part/ground.*" doit être supprimé et
  remplacé par un module équivalant dans "src/builtin_objects" (chaque dalle =
  1 part "Box" ?).
+ compléter l'interface de Joint et Actuator : ajouter des propriétés physiques
  telles que "joint_min_limit", "joint_max_limit", etc.
+ set damping, ... per parts
  http://stackoverflow.com/questions/8289653/bouncing-ball-in-bullet
  http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?t=6783
  see also blender physics part.
  Regarder les bulles d'aide Blender pour la documentation en ligne.
- boost::Program_options:
  - set OSG resolution
  - set OSG MSAA on/off
  - set OSG shadow on/off
  - set OSG gauraud shading on/off
- check memleak with Valgrind + check code with lint-like static analysers (cppcheck, llvm, ...)
- ajouter une méthode getCenterOfMassPosition() pour Part et Object
- ajouter une méthode getMass() pour Object
- nettoyer Clock : devient un observer de bulletEnv tick events ?
~ Senseurs -> créer une interface (ou une classe abstraite) "Sensor" ?
  -> accéléromètre (facile ?)
  -> position absolue/pseudo GPS (facile ?)
  -> odomètre (facile ?)
  -> gyroscope (facile ?)
  -> position angulaire des actuateurs (facile ?)
  -> caméra (difficile ?)
  -> capteurs de force/de contact/de pression (difficile ?)
  -> capteur de distance IR/ultrasons (difficile ?)
- Permettre de sauvegarder les données des senseurs (au format JSON ?) -> appliquer le pattern listener sur les hinge et actuators


## Communication

- créer le site web botsim.org (utiliser le moteur Pelican ?)
- créer une "main features" list sur le site web (et sur jdhp.org)
- créer un tutoriel utilisateur de l'utilisation de la librarie sur le site web
- faire en sorte que la bibliothèque compile et soit utilisable sur Windows et MacOS X + tester/adapter le tutoriel sur ces pates-formes
- compléter la doc en ligne (doxygen)
- rendre optionnel OpenSceneGraph à la compilation
- créer une manpage
- créer un paquet Debian
- créer un paquet RPM (?)


## Adaptation de l'architecture -> botsim v3 ?

- Ajouter des objets: sphere, cylindre, etc. + faire des démos
- Objets STL (balle de golf, charnières 1DOF, charnières 2DOF, ...) + ceiling + faire des démos
~ Supprimer le lien fort qui lie les Parts et OSG + clarification du rôle des classes "Part" et "Object" -> Botsim v3.0 ?:
  Il ne doit plus y avoir le moindre code OSG dans les classes Part.
  La classe "Part" = formes pour le moteur physique seulement !
                     correspond à une primitives Bullet: box, sphère, capsule, ... avec des propriétés physiques (largeur, longueur, profondeur pour un box, masse, etc.).
                     La description graphique des Part est dynamique (pas fixée à la compilation), elle est définie par un fichier STL et par diverses propriétés numériques (propriétas GL_MATERIAL, ...) qui est transmis au constructeur de la classe Part
                     mais les Part on quand même une description graphique par défaut qui correspond exactement leur forme physique (un box aux bonnes dimensions pour un box physique, ...) dans le cas où on ne transmet pas de fichier STL.
                     Un Objet et un Part doit pouvoir être entièrement décrit par un fichier XML (+ STL)... => remetre en cause l'utilisation de sous-classes box, sphere, ... et utiliser un enum pour l'argument "physicsShape" de Part ??? ou simplement faire en sorte que ce soit le parseur XML qui appelle le bon constructeur ?
                       -> qu'est-ce qui différencie les box, sphere, ... hors mis les propriétés dimension (largeur-profondeur-hauteur vs rayon vs ...) ? est-ce suffisant pour justifier ces sous classes ?
                          -> quelque soit la réponse, le code de ces classes DOIT être factorisé (via des fonctions d'aide pour le constructeur dans la classe mère Part par ex.), il y a très peu de différences entre ces classes hors mis les noms de variable... !!!
                     Ces fichier XML pourraient être réutilisés par les moteurs de rendu externes pour un rendu graphique offline (Blender, Sunflow, Yafaray, ...).
  Permettre aux "Objet" d'être chargés dynamiquement sous la forme de plugins
  -> objets décrits en XML 


## Divers

- Créer un OSG_Bullet_Qt_Lab pour tester interactivement les propriétés physique des objets et du simulateur (des widgets permettent de "voir" immédiatement l'impact sur la simulation de la modification de certains paramètres)
  -> charnières: impulsions, mesure du couple appliqué, mesure de l'énergie donné en entrée/dissipée/etc., résistance, autres forces (centrifuge, ...)
  -> friction, frottements, ...
  -> énergie des objets (cinétique, potentielle, ...) + forces appliquées
  -> absorption/restitution de l'énergie lors des chocs
  -> soft bodies
  -> mesurer les vraies propriétés physique des charnières et des servo moteurs, les retranscrire sur les modèles numériques et comparer les simulations à la réalité sur des objets simples
  -> ...

- Key reset -> ajouter une méthode "reset()" dans "BulletEnvironment"
- get OSG FPS
- Renommer correctement les variables (p_...) + utiliser les smart pointers sur tous les objets OSG + détruire correctement les autre objets
- Scale units factor (mm ?, kg ?, ...)
- Afficher les vecteurs force, etc. ac. OSG

- Vérifier à la main une simulation simple (calculer à la main l'équation d'un objet qui tombe et comparer avec bullet)

- Améliorer le rendu: fog + LOD
- Améliorer le rendu: GLSL (shaders)
- Améliorer le rendu: motion blur

- Utiliser d'autres moteurs de rendu => créer une couche d'abstraction neutre pour la partie graphique de botsim:
  - luxrender : directement via l'api C ou via l'export de fichiers scene luxrender (ascii) pour un rendu "offline"
                http://www.luxrender.net/en_GB/developer_api
                http://www.luxrender.net/wiki/API_Usage_example
                http://www.luxrender.net/wiki/LuxCore
                http://www.luxrender.net/wiki/Scene_file_format#Introduction
                http://www.luxrender.net/wiki/Frequently_Asked_Questions
                http://www.luxrender.net/wiki/LuxRays
                http://www.luxrender.net/wiki/Main_Page
    d'importer les fichiers STL (ce que ne semble pas faire Yafaray et ce que
    Povray ne peut faire qu'à l'aide d'un outil externe...): http://www.luxrender.net/wiki/New_in_0-8 .
  - sunflow : http://sunflow.sourceforge.net/index.php?pg=feat
  - PBRT : http://www.pbrt.org/index.php
  - yafaray : directement via l'api C++ (ne semble pas vraiment prévu pour ?)
              ou via l'export de fichiers scene yafaray XML pour un rendu "offline"
              http://www.yafaray.org/documentation/userguide
              http://www.yafaray.org/documentation/tutorials
  - povray : directement via l'api C++ (ne semble pas vraiment prévu pour ?) ou
             via l'export de fichiers scene PovRay (ascii) pour un rendu "offline"
  À priori, luxrender est à privilégier, il dispose bien d'une
  API conçue pour faciliter l'intégration à d'autres projets et permet
  en plus d'importer des fichiers STL.
  Sunflow et PovRay sont les seuls disponibles directement dans Debian Jessie.
  En revanche, le développement de sunflow est arrêté depuis 2008 ! (le dernier
  commit date de 2008 et le site web n'a pas été mis à jours depuis 2007)
  À noter aussi que sunflow est écrit en Java et non en C++ et son API semble
  tournée uniquement vers Java.
  => nécessite de distinguer:
     - le rendu temps réel "à l'écran" (OpenGL, OSG, ...) => la boucle
       principale est dans l'API graphique (osgenvironment.run() par exemple) +
       callback pour le moteur physique à chaque frame
     - le rendu offline "sur fichiers" (luxrender, yafaray, povray, OSG(?),
       blender, ...) => la boucle principale est dans l'API physique
       (bulletenvironment.run()) + implémenter un callback pour le moteur de
       rendu à chaque "timestep"
         => distinguer également:
            - le rendu *d'images* offline (luxrender, yafaray, povray, ...)
            - l'export *de scenes* (fichiers texte) offline (luxrender, yafaray, povray, ...)
  => il faut déléguer le rendu de chaque part (material, textures, ...) dans
     des méthodes à appeler dans le callback de rendu. Pour permettre le rendu
     d'une instance d'une classe fille de "Part", la classe correspondant doit
     implémenter l'interface "PartX" avec "X" le nom du moteur (ex: "Box" doit
     implémenter "PartPovray" pour être rendu avec Povray, "PartOSG" pour être
     rendu dans OSG, ...). => permet de supprimer toute dépendance à OSG dans le
     module "Part".  Ces interfaces ("PartOSG", "PartPovray", ...) déclarent une
     seul méthode (appelée par le callback de rendu).
     Seul le maillage de la pièce (un fichier STL) est commun à tous les moteurs
     de rendu et donc défini directement dans "Part" => ça permet de pouvoir
     faire quand même un rendu de "Box" avec OSG (par exemple) même s'il
     n'implémente pas l'interface "PartOSG": seules les les textures,
     matérials, etc. seront ignorées (car non défini pour le moteur de
     rendu utilisé...).

- Rendu offline avec Blender:
  il y a une API en Python mais pas en C/C++ ("Blender n'est pas une librairie") cf. http://www.blender.org/forum/viewtopic.php?t=27482&sid=b6f1c87a8c54ca3d3b24eea7787efc0c .
  L'API python:
  - Old <= 2.49
  - New >= 2.5
  Les 2 versions (old / new) sont incompatibles.
  Execution d'un script python blender sans lancer l'interface blender : option "--background"
     http://www.blender.org/api/blender_python_api_2_61_0/info_tips_and_tricks.html#don-t-use-blender 
     http://wiki.blender.org/index.php/Doc:2.6/Manual/Render/Command_Line
     blender --background --python myscript.py
     ou
     blender myscene.blend --background --python myscript.py
  Render and saving images:
     http://stackoverflow.com/questions/14982836/rendering-and-saving-images-through-blender-python
     bpy.data.scenes['Scene'].render.filepath = '/home/user/Documents/image.jpg'
     bpy.ops.render.render( write_still=True )

     http://wiki.blender.org/index.php/Dev:2.5/Py/Scripts/Cookbook/Code_snippets/World_view_renderer
     render = bpy.context.scene.render
     render.resolution_x = 720
     render.resolution_y = 576
     render.resolution_percentage = 100
     render.fps = 24    
     render.use_raytrace = False
     render.use_color_management = True
     render.use_sss = False
  Create objects:
     http://wiki.blender.org/index.php/Dev:2.5/Py/Scripts/Cookbook/Code_snippets/Three_ways_to_create_objects
  Manual http://wiki.blender.org/index.php/Doc:2.6/Manual/Extensions/Python
         http://www.blender.org/api/blender_python_api_2_74_0/
  Import STL files: http://stackoverflow.com/questions/25083566/import-stl-script-blender
     bpy.ops.import_mesh.stl(filepath="C://Users//Dom//Documents//DomCorp.//mymodel.stl", filter_glob="*.stl",  files=[{"name":"mymodel.stl", "name":"mymodel.stl"}], directory="C://Users//Dom//Documents//DomCorp.")

- Singleton OSG / Bullet ? -> bof... retire la possibilité de faire du multithread...
- Txt infos (hinge constraints, ...)

- Faire une interface graphique pour construire les robots, lancer les simulations et récupérer les résultats interactivement (ie rendre le logiciel utilisable pour le "grand public")
  -> robots décrits en XML (format de sauvegarde)


## DONE (pseudo changelog)

- [x] Utiliser eigen pour les vecteur donnés aux constructeurs des Objets
- [x] MSAA
- [x] Black background
- [x] Light (directional ?)
- [x] Ajouter et utiliser asseseurs dans Objects
- [x] Ajouter des fonctions wrapper vec3_eigen_to_bullet, ...
- [x] Renommer Objects -> Parts
- [x] Séparer les modules
- [x] Ombres
- [x] Caméra
- [x] Ajouter les fichiers AUTHORS et COPYING
- [x] Remplacer le makefile par un cmakelist -> Créer une arborescence et des modules .h/.cpp
- [x] Ajouter des matériaux pour les objets "Part"
- [x] Key print camera coordinates
- [x] Key take screenshot
- [x] Key start/stop recording -> screencast
- [x] Add OSG fog
- [x] Doxygen
- [x] Permettre de configurer le refresh rate ou de passer en mode "temps réel" (-1)
- [x] Améliorer le réalisme des simulations physiques
- [x] Renommer le répertoire "simulation" -> "scenes"
      adapter le cmakelist pour créer plusieurs scenes co. ds metis (chaque scene = 1 exe)
- [x] Exporter un fichier stat (dat ou json ?)
- [x] Permettre de lancer une simulation sans interface graphique (sans osg)
      ajouter une méthode run(time) dans BulletEnvironment qui ne fait qu'appeler autant de fois que nécessaire this->stepSimulation()
      cette fonction membre doit prendre en paramètre le temps que doit durer la simulation (utiliser boost pour transmettre cette valeur à l'appel de l'executable (~=getopt))
- [x] Ajouter le "part" sphere (ou ball ?)
- [x] Ajouter une scene avec seulement une sphere qui tombe pour vérifier les logs
- [x] Screencast : ajouter un option pour permettre de capturer les images à un framerate constant (de 25fps).
      créer une classe fille de osgViewer::ScreenCaptureHandler::WriteToFile avec un compteur de temps (attention: pas le temps réel mais le temps de la simulation)...
      ou + simple, cf. src/osgViewer/Viewer.cpp "--run-max-frame-rate" ("frame rate capping")
    - https://groups.google.com/forum/#!topic/osg-users/MgMCDb2qv4c
    - http://forum.openscenegraph.org/viewtopic.php?t=2364
    - http://alphapixel.com/content/what-are-all-openscenegraph-environment-variables
    - http://comments.gmane.org/gmane.comp.graphics.openscenegraph.user/58547
- [x] Part est une classe abstraite, elle ne devrait pas pouvoir être instanciée -> au moins une fonction virtuelle pure (constructeur ?)
- [x] Assesseurs pour les attributs des objets "Part", "BulletEnvironment" et "OSGEnvironment".
      Ajouter des assesseurs pour les propriétés physiques des objets "Part", "BulletEnvironment"
- [x] Fonctions virtuelles pures dans Parts et Objects (Part et Object ne devraient pas être instanciables)
- [x] Rétablir "Clock" sensor (rétablir le pointeur vers BulletEnv)
- [x] Tester l'identité de l'instance du sensor dans SinusoidController:
    - [x] Si il n'y a pas exactement 1 instance de Clock dans sensorSet, throw exception
    - [x] Extraire le temps du vecteur "percept"
    - [x] Afficher le temps (de simulation) dans le contrôleur à la place du message "update actuator".
- [x] SinusoidController : calculer et afficher la valeur du signal (a * sin(t * ...))
      (écrire une fonction membre qui retourne la valeur du signal en fonction du temps)
- [x] Créer le répertoire "src/builtin_objects" : contient des modules, 1 module
      par objet. Ces modules contiennent une fonction "build_object(...)" et
      éventuellement une structure "..._build_data". Les fonctions "build_object"
      prennent en entrée des paramètres et retournent une instance d'"Object". Chacun
      de ces modules jouent le même rôle que les futurs fichiers XML servant à la
      description des objets.
- [x] Idem pour "src/builtin_parts"...
- [x] Créer le RobudogJD et RobudogRH dans "src/builtin_objects/robudog.*"
- [x] Tester l'identité de l'instance des actuators dans les 2 Controller:
      si il n'y a pas exactement "N" instances de Motor dans actuatorSet, throw exception
      envoyer le signal aux actuateurs
- [x] Corriger l'erreur de segmentation
