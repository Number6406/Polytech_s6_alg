# Compte-rendu ALG | TP01 - Arbres Binaires de Recherche
__Abonnenc Alicia / Bonhoure Gilles__

> # Présentation du sujet de TP
Le but de ce TP était de se familiariser avec les ABR, et de réaliser certaines fonctionnalités telles que des calculs de nombres de feuilles, rotations et équilibrages. Nous n'avions pas à nous intéresser à l'optimisation du code, mais bien à son fonctionnement.

## Présentation des fonctionnalités réalisées
Nous avons réalisé la totalité des fonctionnalités qui nous étaient demandées :
* La __hauteur__ d'un arbre A : nous avons récursivement calculé le maximum de chaque sous-arbre pour obtenir la hauteur du plus grand sous-arbre de A en partant de sa racine
* Le __nombre de noeuds__ d'un arbre A : calcule récursivement les noeuds internes de l'arbres. Si le noeud est une feuille (s'il a au moins un enfant), il est comptabilisé comme un noeud interne.
* Le __nombre de feuilles__ d'un arbre A : calcule récursivement le nombre de noeuds qui n'ont pas d'enfant.
* La __somme__ des clefs de l'arbre A : effectue récursivement la somme des racines et des leurs enfants
* La __rotation à droite__ d'un arbre A : le fils gauche direct (GD) de A devient la nouvelle racine, A est branché en tant que fils droit direct de GD. Si GD avait un fils droit, celui-ci est branché à la gauche de l'ancienne racine A.
* La __rotation à gauche__ d'un arbre A : fonctionne de la façon inverse. Le fils droit direct (DD) de A devient la nouvelle racine. Si DD a un fils gauche, il devient le fils droit de la racine A et A devient le fils gauche de DD.
* L' __équilibrage__ de l'arbre A, qui en fonction de la hauteur des fils gauche et droit d'une racine va effectuer une rotation jusqu'à ce que les sous-arbres de A soient parfaitement équilibrés.

Nous avons également ajouté quelques fonctions intermédiaires nous permettant de faciliter certaines actions utiles pour les fonctions principales, et également des fonctions d'affichage :
* Une fonction permettant de __créer un arbre__ vide
* Une fonction qui __ajoute à un arbre une nouvelle clef__, et qui tient compte de la nature "binaire de recherche"
* Une fonction qui __initialise un ABR__ à partir d'un tableau créé un arbre vide, et utilisa la fonction d'ajout de nouvelle clef en parcourant le tableau
* Une fonction qui __libère__ l'espace alloué à la création d'un arbre, en libérant récursivement chaque noeud et ses enfants
* Une fonction donnant __les informations concernant un ABR__ uniquement utilisé pour réaliser un affichage rapide pour effectuer des tests

## Utilisation du programme

>Pour utiliser le programme, dans le but de vérifier que les fonctions sont réalisées correctement, il suffit de compiler le fichier de tests via la commande :
`gnatmake test_abr.adb`
Cette commande va permettre d'obtenir un fichier exécutable, qui faudra lancer avec la commande `./test_abr`.
Une fois le programme lancé, si suffit de suivre les instructions pour créer simplement un ARB, et effectuer les opérations sur celui-ci.

## Série de tests :

>Nous avons réalisé quelques tests pour vérifier que nos fonctions étaient effectives. Voici la trace de notre fichier test initial :

### Test dans le cadre d'un ABR déjà équilibré
```
Programme de manipulation d'Arbres Binaires de Recherche.
Que voulez vous faire ?
1 - Creer un arbre.
2 - Equilibrer un arbre déséquilibré à droite.
3 - Equilibrer un arbre déséquilibré à gauche.
4 - Tourner un arbre quelconque.
1
------------------------
Taille ? 5
Ajouter : 5
Ajouter : 8
Ajouter : 6
Ajouter : 4
Ajouter : 9
         9
     8<
         6
 5<
     4

Informations sur l'ABR.
Hauteur :  3 Noeuds :  2 Feuilles :  3 Somme :   32
Arbre équilibré :
         9
     8<
         6
 5<
     4

Informations sur l'ABR.
Hauteur :  3 Noeuds :  2 Feuilles :  3 Somme :   32

```

### Test sur un ABR déséquilibré à droite

```
Programme de manipulation d'Arbres Binaires de Recherche.
Que voulez vous faire ?
1 - Creer un arbre.
2 - Equilibrer un arbre déséquilibré à droite.
3 - Equilibrer un arbre déséquilibré à gauche.
4 - Tourner un arbre quelconque.
2
------------------------
                                                                                                                    30
                                                                                                                29<
                                                                                                            28<
                                                                                                        27<
                                                                                                    26<
                                                                                                25<
                                                                                            24<
                                                                                        23<
                                                                                    22<
                                                                                21<
                                                                            20<
                                                                        19<
                                                                    18<
                                                                17<
                                                            16<
                                                        15<
                                                    14<
                                                13<
                                            12<
                                        11<
                                    10<
                                 9<
                             8<
                         7<
                     6<
                 5<
             4<
         3<
     2<
 1<

Informations sur l'ABR.
Hauteur : 30 Noeuds : 29 Feuilles :  1 Somme :  465
Arbre équilibré :
                    30
                29<
                    28
            27<
                26
        25<
                24
            23<
                22
    21<
                20
            19<
                18
        17<
            16
15<
                14
            13<
                12
        11<
            10
     9<
                     8
                 7<
                     6
             5<
                     4
                 3<
                     2
         1<

Informations sur l'ABR.
Hauteur :  6 Noeuds : 15 Feuilles : 15 Somme :  465

```

### Test sur un ABR déséquilibré à gauche

```
Programme de manipulation d'Arbres Binaires de Recherche.
Que voulez vous faire ?
1 - Creer un arbre.
2 - Equilibrer un arbre déséquilibré à droite.
3 - Equilibrer un arbre déséquilibré à gauche.
4 - Tourner un arbre quelconque.
3
------------------------
29<
    28<
        27<
            26<
                25<
                    24<
                        23<
                            22<
                                21<
                                    20<
                                        19<
                                            18<
                                                17<
                                                    16<
                                                        15<
                                                            14<
                                                                13<
                                                                    12<
                                                                        11<
                                                                            10<
                                                                                 9<
                                                                                     8<
                                                                                         7<
                                                                                             6<
                                                                                                 5<
                                                                                                     4<
                                                                                                         3<
                                                                                                             2<
                                                                                                                 1<
                                                                                                                     0

Informations sur l'ABR.
Hauteur : 30 Noeuds : 29 Feuilles :  1 Somme :  435
Arbre équilibré :
        29<
                    28
                27<
                    26
            25<
                    24
                23<
                    22
    21<
            20
        19<
                18
            17<
                16
15<
            14
        13<
                12
            11<
                10
     9<
                 8
             7<
                 6
         5<
                 4
             3<
                     2
                 1<
                     0

Informations sur l'ABR.
Hauteur :  6 Noeuds : 15 Feuilles : 15 Somme :  435

```

### Rotation sur un ABR quelconque généré par le programme

```
Programme de manipulation d'Arbres Binaires de Recherche.
Que voulez vous faire ?
1 - Creer un arbre.
2 - Equilibrer un arbre déséquilibré à droite.
3 - Equilibrer un arbre déséquilibré à gauche.
4 - Tourner un arbre quelconque.
4
------------------------
    10
 9<
                 8
             7<
                 6
         5<
             4
     3<
         2<
             1

Informations sur l'ABR.
Hauteur :  5 Noeuds :  5 Feuilles :  5 Somme :   55
Arbre tourné à droite :
        10
     9<
                 8
             7<
                 6
         5<
             4
 3<
     2<
         1

Arbre tourné à gauche :
10<
     9<
                     8
                 7<
                     6
             5<
                 4
         3<
             2<
                 1

```
