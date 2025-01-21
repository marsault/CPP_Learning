---
title: "L-value vs R-value ⇄"
weight: 1
---

Pour comprendre comment le compilateur traîte les différentes expressions, 
il faut comprendre quelle est sa catégorie.





## L-value

Pour illustrer ce que sont les L-value, on utilisera le bout de code ci-dessous.
```cpp
class MyClass 
{
public:
  int my_att{};
};
 
int& my_func(const MyClass& y) { /* .. */ }

int main() 
{
    MyClass mon_instance;
//                  Expression 1
//                  vvvvvvvvvvvv
    int i = my_func(mon_instance);
//          ^^^^^^^^^^^^^^^^^^^^^
//          Expression 2 
//
//                 Expression 3
//          vvvvvvvvvvvvvvvvvvv
    return (mon_instance.my_att);
}
```

Les L-values sont des expressions dont la valeur est stockée quelque part en mémoire.
Etant donné une variable `a`, l'expression `a` est une L-value.
Ceci est vrai que `a` soit une variable locale ou globale, et quel que soit le type déclarée de `a`.
Par exemple, l'expression 1 `mon_instance` est une L-value dans le code ci-dessus.
En effet dans ce cas, `a` n'est rien d'autre que le nom donné à une case mémoire.  La plupart du temps, l'expression `a` ne va utiliser que la valeur stockée dans cette case
mais parfois, c'est l'adresse de cette case qui est utilisée, comme dans l'expression `&a`, ou si `a` est passé
par référence à une fonction (comme dans l'expression 2 `my_func(mon_instance)`).

Si un expression *E* est une L-value dont le type est une classe qui a un attribut `c`, alors *E*`.c` est aussi une L-value.
Par exemple, l'expression 3 `mon_instance.my_att` est une L-value dans le code
au dessus.
En effet, comme expliqué dans le [chapitre 3](chapter3) les attributs d'un objet sont stockées dans l'espace allouée pour l'objet lui-même donc on sait où est chaque attribut est stockée dès qu'on sait où l'objet est stockée.

L'expression `f(..)` est une L-value si la fonction  `f` renvoie une référence ou une référence constante, comme l'expression 3 `my_func(mon_instance)`.
C'est la même chose pour les fonction-membre ou les opérateurs.

Finalement, l'expression `*`*E* est une L-value dès lors que le type de *E* est un pointeur. 
En effet, on sait explicitement où cette valeur est stockée. 



## R-value

Pour illustrer ce que sont les L-values, on utilisera le bout de code ci-dessous.

```cpp
class MyClass 
{
public:
  int my_att = 41;
};

int my_func(int x, const MyClass& y) { return 1; }

int main() 
{
//        Expression 1  Expression 2
//                  vv  vvvvvvvvv
    int i = my_func(42, MyClass{});
//          ^^^^^^^^^^^^^^^^^^^^^
//          Expression 3
//
//                   Expression 4
//             vvvvvvvvvvvvvvvvvv
    return i + (MyClass{}).my_att;
//         ^^^^^^^^^^^^^^^^^^^^^^
//         Expression 5
}
```

Au contraire, les R-values sont les expressions qui n'ont pas d'adresse en mémoire.
Par exemple, un literal, comme l'expression 1 `42` dans le code ci-dessus, n'est stockée nulle-part en mémoire.
En fait, le compilateur la stockera directement dans la case mémoire
réservée pour l'argument `x` de la function `my_func`.
C'est la même chose pour l'expression 2 `MyClass{}`, il s'agit d'une
nouvelle instance de `MyClass` qui sera construite directement dans la case `y` de `my_func`.

Si un expression *E* est une R-value dont le type est une classe qui a un attribut `c`, alors *R*`.c` est aussi une R-value.
C'est pour cela que l'expression 4 `(MyClass{}).my_att` est une R-value.

L'expression `f(..)` est une R-value si la fonction  `f` ne renvoie pas
une référence, comme l'expression 3 `my_func(MyClass{}, 42)` dans le code ci-dessus.
C'est la même chose pour les fonctions-membres ou les opérateurs (par exemple
l'expression 5).

Finalement, nous verrons que `std::move` permet de transformer
une L-value en R-value dans la [section sur le déplacement](3-move) de ce chapitre. Donc `std::move(..)` est une R-value.


{{% notice note %}}
La catégorisation des expressions est en fait encore plus complexe que celle décrite ici.
Il existe en C++ des GL-value, PR-value et X-value, mais ces notions ne sont pas au programme du cours.
{{% /notice %}}


## Pourquoi L et R ?

Historiquement les L et R dans L-value et R-value signifient "left" et "right" en référence à la position du signe `=` lors d'une affectation.
Les R-value ne peuvent apparaître qu'à droite d'un `=` alors que les L-value peuvent apparaître à droite et à gauche d'un `=`.

Le bout de code ci-dessous illustre ceci pour les expressions `6`, `a` et `(a+6)`.
```cpp
int a;

a = 6; // Cette affectation a un sens
a = (6+a); // Cette affectation a un sens
6 = a; // Cette affectation n'a aucun sens
(a+6) = a; // Cette affectation n'a aucun sens

// a peut apparaître à gauche de = donc c'est une L-value
// 6 ne peut apparaître qu'à droite du signe = donc c'est une R-value
// (a+6) ne peut apparaître qu'à droite du signe = donc c'est une R-value
```

Cette explication par *left/right* est un bon moyen mnémotechnique, mais n'est plus parfaitement alignée avec ce qu'il se passe réellement en C++.
Référez-vous plutôt aux définitions ci-dessous.

{{% notice tip %}}
Pour comprendre cette histoire de stockage en mémoire d'une expression *E*, on peut se poser la question suivante : Est-ce que l'expression `&`*E* a un sens?

Par exemple, on voit bien que `&42` n'a pas de sens alors que `&a` oui.
{{% /notice %}}

## Exceptions


