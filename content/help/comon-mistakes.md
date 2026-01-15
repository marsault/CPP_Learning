---
title: "Erreur incompréhensible"
pre: '<span class="presection-icon">🤕</span>'
---

Voici une liste non-exhaustive d'erreurs dans le code qui peuvent provoquer des messages d'erreurs incompréhensibles.


##### Erreurs générales

- Oubli d'un `;` à la fin de la déclaration d'une classe
- Oubli du `#pragma once` au début d'un `.hpp`
- Oubli du `MyClass::` devant la définition d'une fonction dans le `.cpp`

##### Ce n'est pas la bonne fonction-membre qui est appelée dans un contexte d'héritage

- Oubli d'un `virtual`
- Typo dans le nom de la fonction membre dans la classe dérivée (majuscule qui devient une minuscule, etc)
- Changement d'un type; par exemple passage par référence dans la fonction-membre de la classe de base devient un passage par copie dans la fonction-membre de la classe dérivée
- Un `const` en trop ou qui manque dans la déclaration de la fonction-membre de la classe fille indiquant que la fonction-membre ne modifie pas l'objet courant

##### Le compilateur refuse de construire un objet de type `MyClass`

- L'ajout d'un constructeur (quel qu'il soit) a pu empêcher au compilateur de générer le constructeur par défaut.
- `MyClass` est devenu abstraite parce qu'une fonction virtuelle pure n'est pas ou plus implémentée (voir la section au dessus).
- `MyClass` n'est plus copiable parce qu'il contient des `std::unique_ptr` ou quelquechose qui contient un `std::unique_ptr`.

##### Des choses étranges se produisent quand `MaClass` est détruite (ou à la toute fin du programme)

- Oubli de déclarer le destructeur `virtual` pour une classe polymorphe.