---
title: "Déplacement"
pre: '<span class="presection-icon">🚚</span>'
weight: 3
---

Sur cette page vous allez apprendre ce qu'est le déplacement en C++.
En un mot, il s'agit de permettre de vider un objet pour en construire un autre ailleurs, et on utilise pour cela la fonction `std::move`.


### Usage de la fonction `std::move` sur un exemple

```cpp
///                      Passage par valeur
//                              vvvvvvvvvvv
void f(std::vector<std::string> my_own_data) 
{
    for (auto& s : my_own_data)
        std::cout << &s << " ";
//                   ^^
//                   On affiche l'adresse des chaines de caractères
    std::cout << std::endl;
}

int main() 
{
    std::vector<std::string> data = {"Hello", "World", "!"};
    // Affichage 0
    for (auto& s : data)
        std::cout << &s << " ";
    std::cout << std::endl;

    // Affichage 1: les chaines sont à des adresses mémoire différentes
    f(data); 

    // Affichage 2: les chaines sont aux mêmes adresses mémoire qu'à l'affichage 0
    f(std::move(data)); 

    //Les variables locales sont détruites (donc en particulier data)
}
```

Dans le code au dessus, la fonction `f` prend son argument par valeur.  C'est un peu stupide car rien ne le justifie, mais c'est pour l'exemple.

Lors du premier appel à `f`, le compilateur copie `data` pour construire `my_own_data`. Les chaînes de caractères dans `my_own_data` sont des copies de celles de `data`, elles sont donc à des adresses mémoires différentes de celles de `data`.

Lors du deuxième appel à `f`, on sait qu'on n'aura plus besoin de `data` dans `main` (elle va être détruite juste après). 
Vu que `f` a apparemment besoin de sa propre copie de `data`, on décide de **déplacer** `data` dans `my_own_data`.
Cela signifie que cette fois, le compilateur va prendre les ressources de `data` pour construire `my_own_data`. 
Les chaînes de caractères dans `my_own_data` sont en fait exactement les mêmes que celles qui étaient dans `data` à l'affichage 0: elles ont juste été réattribuées à `my_own_data`.
Le tableau dynamique `data` est maintenant vide.

Rappelez-vous qu'un `std::vector` est un tableau dynamique, donc ses éléments sont en fait sur le tas,
et ce sont elles qui vont être copiées ou réattribuées à `my_own_data`, comme le montrent les deux diagrammes en dessous.

#### Effet sur la mémoire du premier appel à `f` (copie)
![test](../memory_copy.svg)

#### Effet sur la mémoire du deuxième appel à `f` (déplacement)
![test](../memory_move.svg)


### Constructeur de déplacement

Maintenant qu'on a compris le principe du déplacement, encore faut-il pouvoir définir comment se déplace
nos propres classes.  Etant donné une classe `MaClasse` le constructeur de déplacement a le prototype suivant.

```cpp
//               Attention à la double & 
//               vv
MaClasse(MaClasse&& other) 
{
    /* ... */
}
```

{{% notice tip %}}
    Le compilateur fournit une implémentation par défaut pour le constructeur de déplacement.
{{% /notice %}}


### Quand le constructeur de déplacement est-il appelé?

Pour faire court: quand le compilateur doit construire un nouvel objet à partir d'une R-value du même type (et que le compilateur ne fait pas d'élusion de déplacement, voir plus bas).

En pratique, c'est surtout quand on utilise `std::move` en effet, c'est une fonction qui permet de une L-value en R-value et dit donc au compilateur d'utiliser le constructeur de déplacement plutôt que le constructeur de copie.

### Elusion de déplacement (Copy/Move Elision)

L'élusion de déplacement est une optimisation consistant à éluder (=éviter) un déplacement en utilisant directement la mémoire où l'objet sera finalement stocké.
Dans certaines circonstances, le compilateur **doit** éluder le déplacement d'un objet;
et dans certaines circonstances, le compilateur **peut** éluder le déplacement d'un objet.
Nous ne décrirons pas ces circonstances dans le cours (détails sur {{% cppreflink "cpp/language/copy_elision" %}}), mais ne soyez pas surpris si le constructeur de déplacement n'est parfois pas appelé: c'est sans doute une élusion de déplacement.

Voici deux exemples.
 
---

Dans le code en dessous, le compilateur doit effectuer une élusion de déplacement.

```cpp 
int main() {
    MyClass m = MyClass();
}
```
Dans le code ci-dessus, l'expression `MyClass()` produit une R-value en utilisant le constructeur par défaut de MyClass.
Ensuite, le compilateur devrait construire le `MyClass` stocké dans `m` en utilisant le constructeur de déplacement.
En réalité, le constructeur de déplacement ne sera pas appelé: le constructeur par défaut sera directement utilisé pour instancier `m`.

---

Dans le code en dessous, le compilateur peut effectuer une élusion de déplacement.

```cpp 
MyClass f() {
    MyClass x;
    /* Des opérations sur x... */
    return x;
}

int main() {
    MyClass n = f();
}
```
Dans le code ci-dessus, la fonction `f` crée un `MyClass` sur la pile, fait des opérations dessus, puis retourne le `MyClass`.
Ensuite, dans le `main`, l'expression `f()` est une R-value donc le constructeur de déplacement devrai
t être appelé pour construire `n`.
En fait, suivant le contenu de `f`, le compilateur peut décider de ne pas allouer de mémoire pour `x` et de construire directement le `MyClass` dans la mémoire allouée pour `m`.
