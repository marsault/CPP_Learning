---
title: "Affectation"
pre: '<span class="presection-icon">📝</span>'
weight: 4
---


Les constructeurs de copie et de déplacement sont appelés quand il faut instancier un nouvel objet.
Sur cette page, on va parler des opérateurs d'affectations, c'est-à-dire, quand on remplit un objet qui existe déjà.

---


Par exemple, dans le cas d'un entier:
```cpp
int i = 0;  // Ici le compilateur alloue de la mémoire pour i et le remplit avec la valeur 0.
            // Il *instancie* un nouvel entier à partir de la valeur 0.

i = 42; // Ici, i existe déjà, le compilateur "remplit" la mémoire
        // Il *affecte*
```
Pour un objet, c'est similaire:
```cpp
std::string x {"quelque chose"};  // Ici un nouvel objet est alloué et construit.
x = "autre chose" ; // Ici un objet déjà existant est affecté.
```


---

### Affectation par copie

L'opérateur d'affectation par copie (*copy-assignment operator*) est l'équivalent du constructeur de copie
mais qui est appelé au moment de l'affectation.
Pour lui aussi, le compilateur fournit une implémentation par défaut dans la plupart des cas, et on va donc le redéfinir ici.

On reprend le fichier [Person.cpp](../Person.cpp).
Mettez le code suivant à votre `main`:
```cpp
Person assigned_clone { "Batman", "2" };
std::cout << assigned_clone << std::endl;

assigned_clone = batman;
std::cout << assigned_clone << std::endl;
```
Compilez et lancez le programme. Vous devriez constater que l'âge de `assigned_clone` est de 23 ans.

Pour être cohérent avec ce que nous avons précédemment fait dans le constructeur de copie, nous allons dire que l'âge d'une instance de `Person` n'est pas modifiée au moment de sa réaffectation.  Seul son nom doit changer. 


Voici le code permettant de redéfinir l'opérateur d'affectation d'une classe :
```cpp
ClassName& operator=(const ClassName& other)
{
    if (this != &other)
    {
        _attribute_1 = /* probably other._attribute_1 */ ;
        _attribute_2 = /* probably other._attribute_2 */ ;
        ...
    }

    return *this;
}
```

##### Qui est `this` ?
Comme en Java, `this` fait référence à l'instance courante de la classe. Attention cependant, en C++, `this` est un pointeur. C'est d'ailleurs pour cela qu'on renvoie `*this` et non `this`.

##### Pourquoi la comparaison entre `this` et `&other` ?
Il est très important de réaliser cette comparaison, en particulier dans le cas ou l'un des attributs de la classe est un objet alloué dynamiquement.\
En effet, pour réaliser la copie de `other._attr`, vous allez devoir allouer de la mémoire supplémentaire et stocker son pointeur dans `this->_attr`. Sauf que si `this` et `other` font référence au même objet, en modifiant `this->_attr`, vous allez également écraser `other._attr` et donc perdre l'adresse du bloc alloué dans `other._attr`.\
C'est comme ça qu'on se retrouve avec des fuites de mémoire et un PC qui rame.

Implémentez l'opérateur d'affectation par copie de manière à ne copier que les attributs `_name` et `_surname`. Testez que le programme fonctionne comme prévu.

{{% hidden-solution %}}
```cpp
Person& operator=(const Person& other)
{
    if (this != &other)
    {
        _name = other._name;
        _surname = other._surname;
    }

    return *this;
}
```
{{% /hidden-solution %}}

---

### Affectation par déplacement

On ne va pas s'attarder trop longtemps sur le deuxième opérateur d'affectation: l'opérateur d'affectation **par déplacement** (*move-assignment operator*).
En effet, c'est comme la différence entre les constructeurs de copie et de déplacement:
- l'opérateur d'affectation **par copie** est appelé quand ce qui est à droite du `=` est une **L-value**;
- l'opérateur d'affectation **par déplacement** est appelé quand ce qui est à droite du `=` est une **R-value**.

Voici son prototype:

```cpp
ClassName& operator=(ClassName&& other)
{
    if (this != &other)
    {
        _attribute_1 = /* probably std::move(other._attribute_1) */ ;
        _attribute_2 = /* probably std::move(other._attribute_2) */ ;
        ...
    }

    return *this;
}
```

Par exemple, l'opérateur d'affectation par déplacement de `Person` serait appelé avec le code suivant rajouté dans le `main`.

```cpp
Person assigned_clone { "Batman", "2" };
std::cout << assigned_clone << std::endl;

assigned_clone = std::move(batman);
std::cout << batman << std::endl;
```

A la fin du code ci-dessus, on remarque que `batman._name` et `batman._surname` contiennent tous les deux une chaîne vide.
En effet, l'implémentation par défaut de l'opérateur d'affectation par déplacement de `Person` les a déplacés vers `assigned_clone._name` et `assigned_clone._surname`, respectivement.

{{% notice warning %}}
Comme pour le constructeur de déplacement, quand on redéfinit l'opérateur d'affectation par déplacement, il faut laisser l'argument (appelé `other` plus haut) dans un état valide.\
Par exemple, on voit ci-dessus que celui de `std::string` laisse `other` à la chaîne vide; et non pas avec un pointeur nul ou qui pointe vers une ressource déplacée.
{{% /notice %}}