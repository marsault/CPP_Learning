---
title: "Affectation"
pre: '<span class="presection-icon">📝</span>'
weight: 4
---


Les constructeurs de copie et de déplacement sont appelés quand il faut instancier un nouvel objet.
Sur cette page, on va parler des opérateurs d'affectations, c'est-à-dire, quand on remplit un objet qui existe déjà.

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

### Opérateur d'affectation par copie

Lorsqu'on rédéfinit le constructeur de copie, il est souvent nécessaire de redéfinir également l'opérateur d'assignation.\
"Redéfinir", car ici encore, le compilateur fournit une implémentation par défaut de cette fonction.

Ajoutez le code suivant à votre `main`:
```cpp
Person assigned_clone { "Batman", "2" };
std::cout << assigned_clone << std::endl;

assigned_clone = batman;
std::cout << assigned_clone << std::endl;
```

Si vous essayez de compiler, vous devriez constater que ça ne fonctionne pas...\
Rappelez-vous, nous avions modifié les variables membres `_name` et `_surname` afin d'indiquer qu'elles étaient constantes.\
Puisque l'on veut maintenant avoir la possibilité de réassigner le contenu d'une personne, il faut commencer par retirer les const sur ses variables membre.

{{% notice tip %}}
Vous vous dites peut-être que ce n'est pas très gentil de vous faire ajouter des const pour les retirer ensuite.\
En réalité, il est préférable de toujours réadapté le code au besoin que nous avons à un instant T, c'est-à-dire ne pas trop anticipé.\
C'est seulement au moment où le besoin évolue (ici, on décide que l'on veut maintenant pouvoir réassigner une personne) que l'on doit mettre à jour le code et si besoin modifier les invariants (désormais, le nom et le prénom d'une personne peuvent changer au cours de l'exécution du programme).  
{{% /notice %}}

Recompilez et lancez le programme. Vous devriez constater que l'âge de `assigned_clone` est de 23 ans.

Pour être cohérent avec ce que nous avons fait précédemment, nous allons dire que l'âge d'une instance de `Person` n'est pas modifiée au moment de sa réassignation.\
Seul son nom change. 
Puisque l'**implémentation par défaut de l'opérateur d'assignation** modifie l'âge de notre instance, nous allons le redéfinir.

Voici le code permettant de redéfinir l'opérateur d'assignation d'une classe :
```cpp
ClassName& operator=(const ClassName& other)
{
    if (this != &other)
    {
        _attribute_1 = /* probably other._attribute_1; */
        _attribute_2 = /* probably other._attribute_2; */
        ...
    }

    return *this;
}
```

**Qui est `this` ?**\
Comme en Java, `this` fait référence à l'instance courante de la classe. Attention cependant, en C++, `this` est un pointeur. C'est d'ailleurs pour cela qu'on renvoie `*this` et non `this`.

**Pourquoi la comparaison entre `this` et `&other` ?**\
Il est très important de réaliser cette comparaison, en particulier dans le cas ou l'un des attributs de la classe est un objet alloué dynamiquement.\
En effet, pour réaliser la copie de `other._attr`, vous allez devoir allouer de la mémoire supplémentaire et stocker son pointeur dans `this->_attr`. Sauf que si `this` et `other` font référence au même objet, en modifiant `this->_attr`, vous allez également écraser `other._attr` et donc perdre l'adresse du bloc alloué dans `other._attr`.\
C'est comme ça qu'on se retrouve avec des fuites de mémoire et un PC qui rame.

Implémentez l'opérateur d'assignation de manière à ne copier que les attributs `_name` et `_surname`. Testez que le programme fonctionne comme prévu.

{{% expand "Solution" %}}
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
{{% /expand %}}