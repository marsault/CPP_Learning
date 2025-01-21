---
title: "L-value vs R-value"
weight: 1
---


---

### L-value


- 

### R-value


### Pourquoi L et R ?

Historiquement les L et R dans l-value et r-value signifient "left" et "right" en référence à la position par rapport à
Les r-value ne peuvent apparaître qu'à droite d'un `=` alors que les l-value peuvent apparaître à droite et à gauche d'un `=`.

Le bout de code ci-dessous illustre ceci pour la r-value `6` et la l-value `a`.
```cpp
int a, b;

a = 6; // Cette affectation a un sens
b = a; // Cette affectation a un sens
6 = a; // Cette affectation n'a aucun sens

// a peut apparaître à gauche de = donc a est une l-value
// 6 ne peut apparaître qu'à droite du signe = donc 6 est une r-value
```

Cette explication par *left/right* est un bon moyen mnémotechnique, mais n'est plus parfaitement alignée avec ce qu'il se passe réellement en C++.
Référez-vous plutôt aux définitions ci-dessous.


{{% notice note %}}
Il y a en fait d'autres catégories de valeurs en C++: gl-value, pr-value, xvalue.
Ces notions ne sont pas au programme du cours.
{{% /notice %}}
