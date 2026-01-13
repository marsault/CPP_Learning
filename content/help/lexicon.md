---
title: "Lexique"
pre: '<span class="presection-icon">📑</span>'
---



### Classe

- Classe **abstraite**: classe qui contient au moins une fonction-membre virtuelle pure; elle n'est donc pas instanciable.
- Classe **concrète**: classe qui n'est pas abstraite.
- Classe **instanciable**: classe dont on peut construire des instances, c'est-à-dire qui n'est donc pas abstraite et qui possède au moins un constructeur publique.
- Classe **copiable**: classe qui possède un constructeur de copie (publique).
- Classe **déplaçable**: classe qui possède un constructeur de déplacement (publique).
- Classe **_default-constructible_**: classe qui possède un constructeur par défaut (publique).
- Classe **stable en mémoire**: classe dont les données ne risquent pas de changement d'adresse mémoire.

### Fonction

- Fonction **libre**: fonction qui n'est pas dans une classe.
- **Fonction-membre**: fonction dans une classe.
- Fonction-membre **virtuelle**: fonction-membre qui peut-être redéfinie dans une classe dérivée.
- Fonction-membre **virtuelle pure**: fonction-membre virtuelle qui n'a pas d'implémentation du tout dans la classe de base.
- **Prototype** d'une fonction ou fonction-membre: information donné au compilateur lors de la **déclaration** d'une fonction.
- **Signature** d'une fonction ou fonction-membre: la partie du prototype qui est prise en compte pour la surcharge. Notamment le type de retour ne fait pas partie de la signature mais l'attribut `const` à droite d'une fonction-membre en fait partie.  On peut pas avoir deux fonctions ou fonctions-membre avec la même signature.

### Statique vs Dynamique

|**Statique** = au moment de l'execution| **Dynamique** = seulement au moment de l'exécution|
|-|-|
|**Type statique**: type déclaré dans le code |**Type dynamique**: type réel à l'éxecution (ne peut pas toujours être connu)|
|**Appel statique**: la fonction appelée est connue au moment de la compilation | **Appel dynamique:** la fonction appelée n'est pas connue au moment de la compilation (typiquement une fonction virtuelle) |

Attention le mot-clef `static` ne fait pas référence à l'utilisation de l'adjectif *statique*

### Type

- **Liste** ou Liste chainée ou liste doublement chainée: instance de `std::list`
- **Tableau dynamique**: instance de `std::vector`
- **Tableau statique**: instance de type `std::array`
- **Tuple**: instance de type `std::tuple`



### Autre

- **Déréfencer**: suivre un pointeur (typiquement si `ptr` est un pointeur `*ptr` déréférence ce pointeur).