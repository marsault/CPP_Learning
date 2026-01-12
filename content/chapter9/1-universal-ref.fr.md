---
title: "Référence universelle"
pre: '<span class="presection-icon">🤨</span>'
weight: 1
---

Dans cette première section, nous commencerons par introduire les concepts de L-value et R-value.\
Cela nous conduira à vous présenter la notion de référence universelle.
Nous vous expliquerons ensuite quand et comment vous en servir dans votre code.

---


### Surcharge par L-value ou R-value

Rappel: on peut surcharger une fonction et ce sera l'une ou l'autre qui sera utilisée suiant si on lui passe R-value ou une L-value.

Voici la syntaxe :
```cpp
void fcn(const std::string& str)
{
    std::cout << "L-value contains " << str << std::endl;
}

void fcn(std::string&& str)
{
    std::cout << "R-value contains " << str << std::endl;
}

int main()
{
    std::string str = "toto";
    fcn(str);                       // => fcn(const std::string&)
    fcn(std::string { "tata" });    // => fcn(std::string&&)
    return 0;
}
```

Bien sûr, si vous retirez la surcharge `fcn(std::string&&)`, le programme continuera de compiler puisque jusqu'ici, vos programmes ont compilés (enfin j'espère) sans que vous ayiez eu besoin d'écrire `&&`.
En effet, si le compilateur ne trouve pas de surcharge acceptant une `T&&`, alors il se rabattera sur une surcharge acceptant un `T` ou un `const T&`.

Bien qu'une R-value puisse être convertie en const L-value, sachez que l'inverse n'est pas possible.
Si le seul overload de votre fonction attend une R-value, vous ne pourrez pas compiler un appel fournissant une L-value.
Essayez donc de commenter la surcharge `fcn(const std::string&)` dans le snippet de code ci-dessus.
L'instruction `fcn(str)` ne devrait plus compiler, alors que `fcn(std::string { "tata" })` ne posera pas de problème.


---

### Référence universelle et perfect-forwarding

Revenons maintenant à nos moutons et parlons template !

Supposons que vous avez cette superbe fonction, permettant d'insérer une valeur dans un conteneur disposant d'une fonction `emplace_back` :
```cpp
template <typename Ctn, typename T>
void generic_emplace(Ctn& ctn, T value)
{
    ctn.emplace_back(value);
}
```

Voici différents appels à cette fonction, ainsi que le code généré par le compilateur pour chacun d'entre eux :
```cpp
// Cas 1:
std::list<int> values;
generic_emplace(values, 3);
// Provoque l'instanciation suivante: aucun problème
//
//      void generic_emplace(std::list<int>& ctn, int value)
//      {
//          ctn.emplace_back(value);
//      }

// Cas 2:
std::vector<std::string> names;
const std::string str = "toto";
generic_emplace(names, str);
// Provoque l'instanciation suivante: copie inutile à l'appel de emplace_back
//
// void generic_emplace(std::vector<std::string>& ctn, std::string value)
// {
//     ctn.emplace_back(value);
// } 

// Cas 3:
std::deque<std::unique_ptr<int>> ptrs;
generic_emplace(ptrs, std::make_unique<int>(3));
// Provoque l'instanciation suivante: ne compile pas 
//
// void generic_emplace(std::deque<std::unique_ptr<int>>& ctn, std::unique_ptr<int> value)
// {
//     ctn.emplace_back(value);
// }
```

Ce qu'on aimerait idéalement avoir au moment de la génération, c'est donc plutôt cela :
```cpp
std::list<int> values;
generic_emplace(values, 3);
// void generic_emplace(std::list<int>& ctn, int value)
// {
//     ctn.emplace_back(value);
// }

std::vector<std::string> names;
const std::string str = "toto";
generic_emplace(names, str);
//                                    const-ref pour économiser une copie
//                                                     vvvvvvvvvvvvvvvvvv
// void generic_emplace(std::vector<std::string>& ctn, const std::string& value)
// {
//     ctn.emplace_back(value);
// }

std::deque<std::unique_ptr<int>> ptrs;
generic_emplace(ptrs, std::make_unique<int>(3));
//                                                   R-value pour voler le unique_ptr
//                                                                                 vv
// void generic_emplace(std::deque<std::unique_ptr<int>>& ctn, std::unique_ptr<int>&& value)
// {
//     ctn.emplace_back(std::move(value));
// } //                 ^^^^^^^^^
//   //  std::move pour transmettre la R-value                         
```

Afin de pouvoir arriver à un comportement approximativement similaire, il faut utiliser des références universelles d'une part, et du perfect-forwarding de l'autre.

Commençons par les références universelles.
Voici la syntaxe :
```cpp
template <typename Ctn, typename T>
void generic_emplace(Ctn& ctn, T&& value) // <- on ajoute && sur T
{
    ctn.emplace_back(value);
}
```

**Heeeeeein ? Mais on a vu que `&&`, ça sert à faire des R-value !** 

Et bah pas dans ce cas...\
Si vous mettez `&&` sur un type précis, comme `int&&` ou `std::string&&`, vous êtes effectivement en train d'attendre qu'on vous passe une R-value de ce type.\
En revanche, si vous mettez `&&` sur un type générique défini comme argument de template de la fonction, vous êtes en train de définir une référence universelle.\
Cela signifie que **votre fonction pourra attendre n'importe quoi, qu'il s'agisse d'une ref, d'une const-ref ou d'une R-value.**

Personnellement, il s'agit d'un des pire choix de réutilisation de syntaxe qui a été fait en C++...
D'une part, ça fait qu'il n'est pas possible d'utiliser `T&&` pour restreindre l'usage d'une fonction-template à une R-value.
Et d'autre part, c'est le troll ultime du mec qu'a décidé que le C++, fallait que ça soit dur.
Déjà que c'est pas simple de comprendre la différence entre L-value et R-value, que c'est pas simple non plus d'apprendre à faire des templates, il fallait en plus qu'ils choisissent la même syntaxe pour exprimer deux notions complètement différentes, mais qui sont un peu liées quand même... 

{{% notice important %}}
En bref, retenez que si vous écrivez `T&&` dans le cas où `T` est un argument de template de la fonction, alors c'est une référence universelle (c'est-à-dire que `T&&` sera remplacé par le type exact de l'expression passée en paramètre à la fonction) et donc pas nécéssairement une R-value.
{{{% /notice %}}

Revenons au code précédent.
```cpp
template <typename Ctn, typename T>
void generic_emplace(Ctn& ctn, T&& value)
{
    ctn.emplace_back(value);
}
```

Voici les fonctions qui seront maintenant générées par chacun des appels :
```cpp
std::list<int> values;
generic_emplace(values, 3);
// Comme on passe `3` qui est une R-value, la référence universelle est transformée en R-value reference
// void generic_emplace(std::list<int>& ctn, int&& value)
// {
//     ctn.emplace_back(value);
// }

std::vector<std::string> names;
const std::string str = "toto";
generic_emplace(names, str);
// Comme on passe `str` qui est une L-value constante, la référence universelle est transformée en const-ref
// void generic_emplace(std::vector<std::string>& ctn, const std::string& value)
// {
//     ctn.emplace_back(value);
// }

std::deque<std::unique_ptr<int>> ptrs;
generic_emplace(ptrs, std::make_unique<int>(3));
// Comme on passe `std::make_unique<int>(3)` qui est une R-value, la référence universelle est transformée en R-value
// void generic_emplace(std::deque<std::unique_ptr<int>>& ctn, std::unique_ptr<int>&& value)
// {
//     ctn.emplace_back(value);
// }
```

Le premier appel compile toujours.
Le second appel compile lui aussi, et on a réussi à économiser la copie inutile que l'on faisait avant.\
En revanche, le troisième appel ne toujours compile pas, car bien que la signature de `generic_emplace` ait changée, une fois à l'intérieur de la fonction, c'est toujours le constructeur de copie de `unique_ptr` que le compilateur tente d'utiliser.

Eh oui, même si `value` est déclarée comme `std::unique_ptr<int>&&`, rappelez vous que l'expression `value` est une L-value (contre-intuitif n'est-ce pas ? 🤪).
Et oui, `value` a bel et bien une adresse en mémoire.

Du coup, pour en revenir à `generic_emplace`, lorsqu'on écrit `ctn.emplace_back(value)`, on appelle le copy-constructor de `unique_ptr` au lieu du move-constructor, car l'expression `value` est une L-value et non pas une R-value. 

Afin de transformer cette L-value en R-value, on utilise une technique nommée **perfect-forwarding**, reposant sur l'utilisation de la fonction `std::forward` définie dans `<utility>`.
```cpp
template <typename T>
void perfect_forwarder(T&& universal_ref)
{
    // std::forward, c'est un peu comme std::move, si ce n'est qu'il faut rajouter <T> (sans les &&) à l'appel.
    do_something(std::forward<T>(universal_ref));
}
```

Le comportement de `std::forward` est le suivant :
- si `universal_ref` est de type `const T&`, alors l'expression `std::forward<T>(universal_ref)` est une L-value de type `const T&`,\
- si `universal_ref` est de type `T&`, alors l'expression `std::forward<T>(universal_ref)` est une L-value de type `T&`,\
- si `universal_ref` est de type `T&&` (au sens R-value reference et pas référence universelle), alors l'expression `std::forward<T>(universal_ref)` est une R-value de type `T&&`.

Du coup, on peut réécrire `generic_emplace` de cette manière :
```cpp
template <typename Ctn, typename T>
void generic_emplace(Ctn& ctn, T&& value)
{
    ctn.emplace_back(std::forward<T>(value));
}
``` 

Ainsi, le code généré sera le suivant, et il n'y aura plus d'erreur de compilation :
```cpp
std::list<int> values;
generic_emplace(values, 3);
// void generic_emplace(std::list<int>& ctn, int&& value)
// {
//     ctn.emplace_back(static_cast<int&&>(value));
//     -> Le static_cast ne change rien ici, vu que int est un type primitif
//        Il n'y a effectivement pas de move-constructor ni de copy-constructor, juste le processeur qui change la valeur des octets en mémoire
// }

std::vector<std::string> names;
const std::string str = "toto";
generic_emplace(names, str);
// void generic_emplace(std::vector<std::string>& ctn, const std::string& value)
// {
//     ctn.emplace_back(static_cast<const std::string&>(value));
//     -> Le static_cast ne change rien ici non plus, mais pour une autre raison.
//        `value` est déjà une L-value de type `const std::string&`, ce qui est aussi le cas de `static_cast<const std::string&>(value)`.
// }

std::deque<std::unique_ptr<int>> ptrs;
generic_emplace(ptrs, std::make_unique<int>(3));
// void generic_emplace(std::deque<std::unique_ptr<int>>& ctn, std::unique_ptr<int>&& value)
// {
//     ctn.emplace_back(static_cast<std::unique_ptr<int>&&>(value));
//     -> Le static_cast permet ici d'appeler `unique_ptr(unique_ptr&&)` plutôt que `unique_ptr(const unique_ptr&)`.
//        `value` est une L-value de type `std::unique_ptr<int>&&`, alors que `static_cast<std::unique_ptr<int>&&>` est une R-value de type `std::unique_ptr<int>&&`.
// }
```

---

### Conclusion


Lorsque que dans une fonction-template, vous souhaitez transmettre à une autre fonction l'un de vos paramètres par L-value si on vous l'avait passé par L-value, et par R-value si on vous l'avait passé par R-value, il faut :
1. utiliser une référence universelle pour définir ce paramètre,
2. passer ce paramètre à l'autre fonction en utilisant `std::forward`.

```cpp
#include <utility>

template <typename Plat>
void passe_plat(Serveur& serveur, Plat&& plat)
{
    serveur.recoit(std::forward<Plat>(plat));
}
```
