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

### Vie d'un objet

- **Allocation** d'un objet: réservation d'un segment de mémoire de la taille de l'objet
    - ~~`malloc` permet d'allouer de la mémoire~~, mais on ne l'utilisera pas.
- **Construction** d'un objet: appel d'un des constructeurs de la classe, ce qui va commencer par appeler un constructeur pour chacun des attributs.
- **Instanciation** d'un objet: allocation+construction
    - Le mot-clef `new` permet d'instancier un objet sur le tas
- **Désallocation** d'un objet: réservation d'un segment de mémoire 
    - ~~`free` permet deséallouer de la mémoire~~, mais on ne l'utilisera pas.
- **Destruction** d'un objet: appel du destructeur de la classe, suite à quoi le destructeur des attributs qui ne sont pas des références sera appelé.
    - Par définition, la destruction d'un objet provoque la destruction des objets **owned**.
    - La destruction d'un pointeur brut **ne** provoque **pas** la destruction
- **Désinstanciation** d'un objet:destruction+désallocation
    - Le mot-clef `delete` permet de désinstancier un objet sur le tas
- **Affectation** d'un objet: remplir le contenu d'un objet avec celui d'un autre objet (en général du même type) grâce à un l'operateur d'affectation (`operator=`).
    - L'affectation **par copie**
    - L'affectation **par déplacement**
    

### Fonction

- Fonction **libre**: fonction qui n'est pas dans une classe.
- **Fonction-membre**: fonction dans une classe.
- Fonction-membre **virtuelle**: fonction-membre qui peut-être redéfinie dans une classe dérivée.
- Fonction-membre **virtuelle pure**: fonction-membre virtuelle qui n'a pas d'implémentation du tout dans la classe de base.
- **Prototype** d'une fonction ou fonction-membre: informations données au compilateur lors de la **déclaration** d'une fonction.
- **Signature** d'une fonction ou fonction-membre: la partie du prototype qui est prise en compte pour la surcharge. Notamment le type de retour ne fait pas partie de la signature mais l'attribut `const` à droite d'une fonction-membre en fait partie.  On peut pas avoir deux fonctions ou fonctions-membre avec la même signature.

### Statique vs Dynamique

|**Statique** = au moment de l'execution| **Dynamique** = seulement au moment de l'exécution|
|-|-|
|**Type statique**: type déclaré dans le code |**Type dynamique**: type réel à l'éxecution (ne peut pas toujours être connu)|
|**Appel statique**: la fonction appelée est choisie au moment de la compilation (résolution de la surcharge) | **Appel dynamique:** la fonction appelée n'est pas connue au moment de la compilation (typiquement une fonction virtuelle) |

Attention le mot-clef `static` ne fait pas référence à l'utilisation de l'adjectif *statique*.

### Types standard

- **Type fondamentaux**: booléens (`bool`), les types de caractères (`char`, unsigned `char`, etc), les types d'entiers (`int`, `unsigned`, `long`, etc), et les types de nombres floatant (`float`, `double`, etc).
    - `size_t` est un alias vers un type d'entiers signé, donc un type fondamental.
- **Liste** ou Liste chainée ou liste doublement chainée: instance de `std::list`
- **Tableau dynamique** ou vecteurr: instance de `std::vector`
- **Tableau statique**: instance de type `std::array`
- **Tuple**: instance de type `std::tuple`
- **Pointeur brut** (*raw pointer*): un pointeur "normal" comme en C, c'est-à-dire dont le type est `un_type*`.
- **Un unique-pointeur** (*unique pointer*): une instance de `std::unique_ptr<un_type>`.
- **Pointeur nul** (*null pointer*): le pointeur brut ou le unique-pointeur indiquant qu'aucun objet n'est pointé.
- **Déréfencer** un pointeur: suivre un pointeur (typiquement si `ptr` est un pointeur `*ptr` déréférence ce pointeur).
- **Référence**: alias vers une autre case mémoire, c'est-à-dire dont le type est `un_type&`.
    - On ne fera pas la différence dans ce cours entre les *R-value reference* et les *L-value reference*.
