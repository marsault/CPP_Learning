---
title: "C'est quoi un objet déjà ?"
weight: 1
---

Commençons par donner quelques rappels des notions de POO que vous avez pu voir l'an dernier.

---

#### Objet

Dans un programme, un **objet** est un élément constitué d'un **état**, et disposant d'une **interface** permettant d'intéragir avec cet état.

#### Classe

Un objet est généralement créé à partir d'un modèle, que l'on appelle **classe**. Un objet créé à partir d'une classe constitue une **instance** de cette classe.

#### Etat

L'état d'un objet est composé de valeurs, pouvant ou non varier au cours de l'exécution du programme.

#### Attributs

Les **attributs** sont les propriétés définies par une classe à partir desquelles on construit l'état des instances.\
Si une classe Personne définit deux attributs `nom` et `âge`, alors l'état de chaque instance de Personne sera composée d'une valeur pour le nom, et d'une pour l'age.

#### Interface

L'interface est l'ensemble des procédés permettant d'accéder à l'état d'un objet ou de le modifier.\
Selon les langages, elle ne se présente pas de la même manière. En C++, elle se compose des **fonctions-membres** de la classe, ainsi que de ses éventuels attributs publiques.

#### Invariant de classe

Un **invariant de classe** est une condition que toutes les instances de cette classe doivent vérifier.\
Un des invariants de la classe Carré est qu'il faut qu'à tout moment, les 4 côtés d'une instance soient de même longueur.\
Un des invariants de la classe Fraction est que le dénominateur de chacune de ses instances ne peut pas être nul.\
Un des invariants de la classe ListeCroissante est que les éléments sont toujours par ordre croissant.

Chaque invariant de classe peut-être supposée réalisée au début de chaque fonction-membre (publique) et la fonction doit faire en sorte que l'invariant est de encore réalisé à la fin.  Ceci ne demande pas nécessairement de vérifier la condition.  Par exemple, la fonction qui ajoute un élément dans une ListeCroissante n'a pas besoin de vérifier que la liste est triée au début, et peut utiliser la recherche dichotomique pour trouver où doit être inséré le nouvel élément.  Si l'algorithme est écrit correctement, on n'aura pas besoin de faire un parcours complet de la liste pour vérifier qu'elle est toujours triée (ce test serait plus couteux que l'ajout).  Elle sera triée parce qu'on *a rien cassé*. 

#### Encapsulation

L'**encapsulation** est le principe déclarant que pour pour accéder/modifier l'état d'un objet, il faut passer par des "routines" (fonction-membre en C++, méthode en Java, ...). Il s'accompagne souvent du masquage de l'état des objets, c'est-à-dire que l'on déclare les attributs dans la partie privée de la classe.\
Respecter le principe d'encapsulation permet de garantir les invariants de classe plus facilement.

Reprenons l'exemple de la classe ListeCroissante.  On ne laissera pas l'utilisateur accéder directement au tableau contenant les valeurs.  Il pourrait ajouter un élément à la fin, ce qui aurait de grande chance de casser l'invariant de classe.  S'il veut ajouter un élément, on le forcera à utiliser notre fonction-membre qui fera respecter l'invariant de classe.