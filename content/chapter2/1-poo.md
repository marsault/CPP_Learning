---
title: "C'est quoi un objet déjà ?"
pre: '<span class="presection-icon">🤔</span>'
weight: 1
---

Commençons par quelques piqûres de rappel à propos des notions de POO que vous avez pu voir l'an dernier.

---

#### Objet

Dans un programme, un **objet** est un élément constitué d'un **état**, et disposant d'une **interface** permettant d'intéragir avec cet état.

#### Classe

Un objet est généralement créé à partir d'un modèle, que l'on appelle **classe**. Un objet créé à partir d'une classe constitue une **instance** de cette classe.

#### Etat

L'état d'un objet est composé de valeurs, pouvant ou non varier au cours de l'exécution du programme.

#### Attributs

Les **attributs** sont les propriétés définies par une classe à partir desquelles on construit l'état des instances.  
Si une classe `Personne` définit deux attributs `nom` et `age`, alors l'état de chaque instance de `Personne` sera composé d'une valeur pour le nom, et d'une valeur pour l'âge.

#### Interface

L'interface est l'ensemble des procédés permettant d'accéder à l'état d'un objet ou de le modifier.  
Selon les langages, elle ne se présente pas de la même manière. En C++, elle se compose des **fonctions-membres** de la classe (appelées **méthodes** en Java), ainsi que de ses éventuels attributs publics.

#### Invariant de classe

Un **invariant de classe** est une condition que toutes les instances de cette classe doivent vérifier. Par exemple :
- Pour la classe `Carré`, l'un des invariants stipule que les quatre côtés d'une instance doivent toujours avoir la même longueur.
- Dans le cas de la classe `Fraction`, un invariant essentiel est que le dénominateur de chaque instance ne peut jamais être nul.
- Pour la classe `ListeCroissante`, le tri des éléments par ordre croissant constitue un invariant.

Lorsqu'une fonction-membre publique est appelée, on peut toujours supposer qu'à son entrée, les invariants sont garantis.
En contre-partie, il faut que l'implémentation de la fonction garantisse également qu'à la sortie, les invariants seront toujours vrais.  
Par exemple, la fonction `ListeCroissante::insert()` n'a pas besoin de vérifier que la liste est triée au début, car on part du principe que l'invariant est forcément vrai dès l'entrée.
On peut donc utiliser la recherche dichotomique pour trouver où doit être inséré le nouvel élément, ce qui est moins coûteux que si on avait à faire une recherche linéaire.  
L'invariant permet donc ici de gagner en temps de calcul.

#### Encapsulation

L'**encapsulation** est le principe stipulant que pour pour accéder à l'état d'un objet ou le modifier, il faut passer par des "routines" (fonction-membre en C++, méthode en Java, ...).
Ce principe s'accompagne souvent du masquage de l'état des objets, c'est-à-dire de la déclaration des attributs dans la partie privée de la classe.  
Respecter le principe d'encapsulation permet de garantir les invariants de classe plus facilement.

Reprenons l'exemple de la classe `ListeCroissante`.
On ne laissera pas l'utilisateur accéder directement au tableau contenant les valeurs.
En effet, il pourrait ajouter un élément à la fin, ce qui aurait de grandes chances de briser l'invariant de classe.
S'il veut ajouter un élément, on le forcera à passer par notre fonction-membre qui fera respecter cet invariant.
