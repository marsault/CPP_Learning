---
title: "Lexique"
pre: '<span class="presection-icon">📑</span>'
---

{{% notice style=warning title="En construction" icon="hammer" %}}
Cette page est en construction. N'hésitez pas à suggérer des ajouts ou signaler ce qui vous semble faux ou étrange.
{{% /notice %}}

### Classe

- Classe **abstraite**: classe qui contient au moins une fonction-membre virtuelle pure; elle n'est donc pas instanciable.
- Classe **concrète**: classe qui n'est pas abstraite.
- Classe **instanciable**: classe dont on peut construire des instances, c'est-à-dire qui n'est donc pas abstraite et qui possède au moins un constructeur publique.
- Classe **copiable**: classe qui possède un constructeur de copie (publique).
- Classe **déplaçable**: classe qui possède un constructeur de déplacement (publique).
- Classe **_default-constructible_**: classe qui possède un constructeur par défaut (publique).
- Classe **stable en mémoire**: classe dont les données ne risquent pas de changement d'adresse mémoire.
- Classe **polymorphe**: fonction qui déclare ou hérite d'au moins une fonction virtuelle.

### Vie d'un objet

- **Allocation** d'un objet: réservation d'un segment de mémoire de la taille de l'objet
    - ~~`m`<p></p>`alloc` permet d'allouer de la mémoire~~, mais on ne l'utilisera pas.
- **Construction** d'un objet: appel d'un des constructeurs de la classe, ce qui va commencer par appeler un constructeur pour chacun des attributs.
- **Instanciation** d'un objet: allocation+construction
    - Le mot-clef `new` permet d'instancier un objet sur le tas.
- **Désallocation** d'un objet: réservation d'un segment de mémoire 
    - ~~`free` permet deséallouer de la mémoire~~, mais on ne l'utilisera pas.
- **Destruction** d'un objet: appel du destructeur de la classe, suite à quoi le destructeur des attributs qui ne sont pas des références sera appelé.
    - Par définition, la destruction d'un objet provoque la destruction des objets **owned**.
    - La destruction d'un pointeur brut **ne** provoque **pas** la destruction
- **Désinstanciation** d'un objet:destruction+désallocation
    - Le mot-clef `delete` permet de désinstancier un objet sur le tas.
- **Affectation** d'un objet (*assignment*): remplir le contenu d'un objet~`d` à partir celui d'un autre objet~`g` (en général du même type) grâce à un l'operateur d'affectation (`operator=`). `g` est à gauche du signe `=` et `d` est à droite.
    L'affectation peut soit copier le contenu de `d` dans `g` (affectation **par copie**) ou déplacer le contenu de `d` dans `g` (affectation **par déplacement**).
- **Copie** d'un objet: construction d'un nouvel objet en copiant le contenu d'un autre objet.
- **Déplacement** d'un objet: construction d'un nouvel objet en déplaçant le contenu d'un autre objet dans le nouvel objet. On peut souvent forcer le déplacement d'un objet avec `std::move`.
    

### Fonctions

- Fonction **libre**: fonction qui n'est pas dans une classe.
- **Fonction-membre** ou méthode: fonction dans une classe.
- Fonction-membre **virtuelle**: fonction-membre qui peut-être redéfinie dans une classe dérivée. Dès lors qu'une fonction est virtuelle, la résolution d'appel est dynamique.
- Fonction-membre **virtuelle pure**: fonction-membre virtuelle qui n'a pas d'implémentation du tout. Usuellement, on l'implémente dans les classe filles.
- **Prototype** d'une fonction ou fonction-membre: informations données au compilateur lors de la **déclaration** d'une fonction.
- **Signature** d'une fonction ou fonction-membre: la partie du prototype qui est prise en compte pour la surcharge. Notamment le type de retour ne fait pas partie de la signature mais les qualificatifs (le `const` éventuel à droite d'une fonction-membre) en fait partie.  On peut pas avoir deux fonctions ou fonctions avec la même signature.
- **Corps** d'une fonction: partie de la fonction entre `{}`.
- **Déclaration** d'une fonction: indication au compilateur de l'existence d'une fonction et de son prototype, sans corps. On peut déclarer plusieurs fois une fonction.
- **Définition** d'une fonction:  écriture du corps de la fonction. On ne peut pas définir deux fois une fonction.  On peut définir et déclarer une fonction en même temps, mais pour les fonction-membres ce doit être dans la déclaration de la classe.

### Statique vs Dynamique

|**Statique** = au moment de la compilation| **Dynamique** = seulement au moment de l'exécution|
|-|-|
|**Type statique**: type d'une variable tel que déclaré dans le code ou d'une expression telle que calculé par le compilateur. |**Type dynamique**: type réel d'un objet à l'éxecution. Ne peut pas toujours être connu au moment de la compilation.|
|**Appel statique**: la fonction appelée est choisie au moment de la compilation.  Il y a un choix en cas de surcharge.  La résolution d'un appel statique se fait à partir des types statiques des paramètres. | **Appel dynamique:** la fonction appelée n'est pas connue au moment de la compilation. Il s'agit toujours de l'appel à une fonction-membre virtuelle `fct(..)` sur un objet `o`. La résolution d'un appel dynamique se fait à partir du type dynamique de `o`.|
|**Allocation sur la pile**. Les variables locales sont allouées sur la pile et la taille pour stocker leur type doit donc être connue par le compilateur. | **Allocation sur la tas** ou allocation dynamique. Allocation via `new` ~~(ou `m`<p></p>`alloc` )~~ ou implicitement par l'utilisation d'un type de la bibliothèque standard (`std::vector<MaClasse>` alloue des `MaClasse` sur le tas). La taille du segment allouée peut être spécifié à l'exécution. |

Attention le mot-clef `static` ne correspond pas entièrement à l'utilisation de l'adjectif *statique*. Il fait référence à la zone-mémoire `static` qui fait partie du code compilé (et qui n'est ni sur la pile ni sur le tas).

### Types

- **Type fondamentaux**: booléens (`bool`), les types de caractères (`char`, unsigned `char`, etc), les types d'entiers (`int`, `unsigned`, `uint16`, etc), et les types de nombres flottants (`float`, `double`, etc).
    - `size_t` est un alias vers un type d'entiers signé, donc un type fondamental.
- **Liste** ou Liste chainée ou liste doublement chainée: instance de `std::list`
- **Tableau dynamique** ou vecteur ou parfois simplement tableau: instance de `std::vector`
- **Tableau statique**: instance de `std::array`
- **Ensemble**: instance de `std::set` (*tree-set*) ou `std::unordered_set` (*hash-set*).
- **Dictionnaire**: instance de `std::map` (*tree-map*) ou `std::unordered_map`  (*hash-map*).
- **Tuple**: instance de type `std::tuple`
- **Pointeur brut** ou pointeur nu (*raw pointer*): un pointeur "normal" comme en C, c'est-à-dire dont le type est `un_type*`.
- **Unique-pointeur** (*unique pointer*): une instance de `std::unique_ptr<...>`.
- **Pointeur nul**: le pointeur brut ou le unique-pointeur indiquant qu'aucun objet n'est pointé.
- **Déréfencer** un pointeur: suivre un pointeur (typiquement si `ptr` est un pointeur `*ptr` déréférence ce pointeur).
- **Référence**: alias vers un segment mémoire, c'est-à-dire dont le type est `un_type&`.
    - Référence **constante**: référence qui pointe vers un type qualifiée avec `const`, c'est-à-dire dont le type est `const un_type&` ou `un_type const&`.
- **Qualificatif** (*qualifier*): Les types et prototype de fonctions peuvent contenir des qualificatifs.  Dans ce cours, on ne verra que le qualificatif `const`.  Les qualificatifs font partie du type et le qualificatif d'une fonction-membre fait partie de sa signature (et permet donc à la )
