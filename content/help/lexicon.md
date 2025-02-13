---
title: "Lexique"
pre: '<span class="presection-icon">🤕</span>'
---




##### Classe

- Classe **abstraite**: classe qui contient au moins une fonction-membre virtuelle pure; elle n'est donc pas instanciable
- Classe **concrète**: classe qui n'est pas abstraite
- 

#### Fonction

- Fonction **libre**: fonction qui n'est pas dans une classe 
- **Fonction-membre**: fonction dans une classe
- Fonction-membre **virtuelle**: fonction-membre qui peut-être redéfinie dans une classe dérivée
- Fonction-membre **virtuelle pure**: fonction-membre virtuelle qui n'a pas d'implémentation du tout dans la classe de base.

#### Statique vs Dynamique

|---------|----------|
|---------|----------|
|**Statique**: au moment de l'execution| **Dynamique**: seulement au moment de l'exécution|
|**Type statique**: type déclaré dans le code |**Type dynamique**: type réel à l'éxecution (ne peut pas toujours être connu)|
|**Appel statique**: la fonction appelée est connue au moment de la compilation | **Appel dynamique:** la fonction appelée n'est pas connue au moment de la compilation (typiquement une fontion virtuelle) |


#### Type

- Liste ou Liste chainée ou liste doublement chainée: instance de `std::list`
- Tableau dynamique: instance de `std::vector`
- Tableau statique: instance de type `std::array`
- Tuple: instance de type `std::tuple`
- Stable en mémoire: qui ne risque pas de changer d'emplacement en mémoire