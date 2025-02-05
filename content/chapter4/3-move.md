---
title: "Déplacement"
pre: '<span class="presection-icon">🚚</span>'
weight: 3
---

Sur cette page vous allez apprendre ce qu'est le déplacement en C++.
En un mot, il s'agit de permettre de vider un objet pour en construire un autre ailleurs, et on utilise pour cela la fonction `std::move`.


### Usage de la fonction `std::move` sur un exemple

Considérons le [bout de code](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIABwA7KSuADJ4DJgAcj4ARpjEIGYAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5gDMEcjeWADUJrtuThPEmKxn2CYaAIJ7B0eYp%2BcAbpgOJHcPjwA9IDjqCweCIZDQcomAoFExgO80q1jp8xJgNgDgVCcbjIZ8CYSiZ8AZ9UHh0McqBAJugQCBvr9iGc3LT6VcIsA7scWABPAD6qAA7gx%2BegmC1lqcniZAlYnuD%2BMRjhAmF4iOZkscFMcQDyBcLReLJQCcWyUOsCB83CzTikdSzbeYzHazGd5UCQXicSYAKz3f1Yr3eyEAeQYxyYVBoyAQ71oYA4THQ1zh7ywOtjTAimB1J1ExCYDhMbl2Jke/lTprB5rQ6uttvNrlo7oBsoAIm2nhErSxswwIFK23Lq6DzYyiMzzuaOUZucamB926cR2YzAAJeq0VDO0iugDqJFo6F3rrAYGdHdbCprBDpFvrjvOrse0bwWcRxw0eq2xwAjl4iZ0McvKRsc4oMHmEpMM6DbPk2DDoC2uweoqJAqmqGopNqurgdByyjhCtaWnBbh2skDrnE6a6utejzgsRj5UfBd70s2dGEYxVpPmRCFIaRL5vh%2B7xcHqfKCiKYrQdqhg6uaLCoN8sE8dqrEgOxKGEdSC4EShxzAvQmYIP2ubarIpyluWGjgaZyapkoOosCWZaPAAnApeDXOBeDRs55audcgi5l29G3vedbccxvFqc2AnOq%2BMbGZ%2BZhiQakkLpGjKqfeClKTRKl8chqFgtS8mKZgEA6bpFj6SChnHFmOZyeZaqqDyfmPI8bA6nZuYOe1lluR5XkAYmHXWQmSZCUl7waCFDFqRFAmFXFa4Je%2BM3HLsP7vKNHDAamBDprJeEtMpUXZWxiFFVp6GquqO7YTqeo6bVp2Lrmvb9kdzCCKiFKYHuxB4IwxyRNqiZRolmCEQt4UkSpmqUTaz7KWuHE3qCwKhKZaLA0wsT1duoj1Qo5knoNrkEMQXiEKZlUCMgxyg8ibTvl4tAg8qOnDu2HCrLQnC%2BrwfgcFopCoJwNqWNYZkbL%2Bew8KQBCaPzqwANYgL6Gj6Jwki8CwEgaDrovi5LHC8AoIA6yrYv86QcCwEgmCqD8D1kBQqrEMACgwpEtBCAghqcEraAsGkdASjkfv1IHwd26QYcR/QiTAFIZiJ6g4d0AkUSsNsvBJznxChuqcciqrISu8gjze1bFtVz8zT4KLvD8IIIjohI0jt/IShqJXuhcPohjGNY1j6HgsRW5AqyoGkjT15b6ybOww%2B0hEMcB0HFfcLwQqFmkIf24LHDC6Qpu8Ob2DV%2B7xyqP4yQALTJJIxzAMgTNSAAdC6EDS1YSwe5cCEHQorZYvBbZaGWKsOMyZRiDlIJrbWusOD6wvpXc2ltrbK1VjA1BZgRaYM4JAvBqxvjECyM4SQQA) ci-dessous.
```cpp
#include <iostream>
#include <vector>
//                       Passage par valeur
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
    std::cout << "Affichage 0: ce qu'il y a dans data" << std::endl;
    for (auto& s : data)
        std::cout << &s << " ";
    std::cout << std::endl;

    std::cout << std::endl << "Affichage 1: my_own_data sans std::move" << std::endl;
    f(data); //les chaines sont à des adresses mémoire différentes

    std::cout << std::endl << "Affichage 2: my_own_data avec std::move" << std::endl;
    f(std::move(data)); // les chaines sont aux mêmes adresses mémoire qu'à l'affichage 0

    std::cout << std::endl << "Affichage 3: ce qu'il reste dans data" << std::endl;
    for (auto& s : data) // data est maintenant vide, rien ne s'affiche
        std::cout << &s << " ";

    //Les variables locales sont détruites (donc en particulier data)
}
```

Dans le code au dessus, la fonction `f` prend son argument par valeur.  C'est un peu stupide car rien ne le justifie, mais c'est pour l'exemple.

Lors du premier appel à `f`, le compilateur copie `data` pour construire `my_own_data`. Les chaînes de caractères dans `my_own_data` sont des copies de celles de `data`, elles sont donc à des adresses mémoires différentes de celles de `data`.

Lors du deuxième appel à `f`, on sait qu'on n'aura plus besoin de `data` dans `main` (elle va être détruite juste après). 
Vu que `f` a apparemment besoin de sa propre copie de `data`, on décide de **déplacer** `data` dans `my_own_data`.
Cela signifie que cette fois, le compilateur va prendre les ressources de `data` pour construire `my_own_data`. 
Les chaînes de caractères dans `my_own_data` sont en fait exactement les mêmes que celles qui étaient dans `data` à l'affichage 0: elles ont juste été réattribuées à `my_own_data`.

Le tableau dynamique `data` est vide à l'affichage 3, car ses données ont été prise par `my_own_data`.  En revanche, après le `std::move`, `data` est toujours un objet valide: on peut itérer dessus ou rajouter de nouveaux éléments.

Rappelez-vous qu'un `std::vector` est un tableau dynamique, donc ses éléments sont en fait sur le tas,
et ce sont elles qui vont être copiées ou réattribuées à `my_own_data`, comme le montrent les deux diagrammes en dessous.

#### Effet sur la mémoire du premier appel à `f` (copie)
![test](../memory_copy.svg)

#### Effet sur la mémoire du deuxième appel à `f` (déplacement)
![test](../memory_move.svg)


### Constructeur de déplacement

Maintenant qu'on a compris le principe du déplacement, encore faut-il pouvoir définir comment se déplacent
nos propres classes.  Etant donné une classe `MaClasse` le constructeur de déplacement a le prototype suivant.

```cpp
//               Attention à la double & 
//               vv
MaClasse(MaClasse&& other) 
{
    /* ... */
}
```

La notation `MaClasse&&` (avec **deux** `&`) signifie **R-value-reference**. Le type `MaClasse&` (avec **une** `&`) que l'on appelle couramment une **réference**
est en fait une **L-value-reference**.

{{% notice tip %}}
Le compilateur génère une implémentation par défaut pour le constructeur de déplacement et elle fait ce qu'il faut dans la plupart des cas.
Dans d'autres cas, le compilateur ne va pas la générer mais elle est quand même très bien. On peut demander explicitement au compilateur de le générer avec `MaClasse(MaClasse&& other) = default;`.
{{% /notice %}}

Quand on déplace un objet (et donc quand on implémente un constructeur de déplacement à la main), il faut faire attention à laisser l'objet d'origine dans un état valide.\
Pourquoi?  Parce que l'objet d'origine va sans doute être supprimé juste après, donc il faut faire attention qu'il ne supprime pas les ressources qu'on lui a pris. Il est aussi possible qu'il soit réutilisé juste après



### Quand le constructeur de déplacement est-il appelé?

Pour faire court: quand le compilateur doit construire un nouvel objet à partir d'une R-value du même type (et que le compilateur ne fait pas d'élusion de déplacement, voir plus bas).

En pratique, c'est surtout quand on utilise `std::move` en effet, c'est une fonction qui permet de transformer une L-value en R-value et dit donc au compilateur d'utiliser le constructeur de déplacement plutôt que le constructeur de copie.

#### Exercice

On considère que `MyClass` est une classe avec un constructeur par défaut et des constructeurs de copies et de déplacements;
Dans chacun des bouts de code ci-dessous: combien de fois le constructeur de **copie** de MyClass est-il appelé? (On ne demande pas le nombre de fois où le constructeur de déplacement est appelé à cause de l'élusion de déplacement que l'on verra plus bas.)

```cpp
/*1*/
MyClass a = MaClass{};
```
{{% hidden-solution %}}
Le constructeur de copie ne sera pas appelé.
{{% /hidden-solution %}}

---

```cpp
/*2*/
void f(MyClass a) {/* ... */}
int main() 
{
    MyClass a;
    f(a);
}
```
{{% hidden-solution %}}
Le constructeur de copie sera appelé une fois.
{{% /hidden-solution %}}

---

```cpp
/*3*/
void f(MyClass a) {/* ... */}
int main() 
{
    MyClass a;
    f(std::move(a));
}
```
{{% hidden-solution %}}
Le constructeur de copie ne sera pas appelé car `std::move(a)` est une R-value.
{{% /hidden-solution %}}

---

```cpp
/*4*/
void f(MyClass a) {/* ... */}
int main() 
{
    f(MyClass{});
}
```
{{% hidden-solution %}}
Le constructeur de copie ne sera pas appelé car `MyClass{}` est une R-value.
{{% /hidden-solution %}}

---


Dans la suite, on considère le code suivant pour `MyOtherClass`.
```cpp
MyOtherClass
{
public:
    MyClass _att;
    MyOtherClass() = default;
    MyOtherClass(MyClass arg) : _att{arg} {}
}
```


Combien de fois le constructeur de copie de `MyClass` est-il appelé par chacun des bouts de code suivants.

```cpp
/*5*/
int main {
    MyClass x;
    MyOtherClass y{x};
}   
```
{{% hidden-solution %}}
Le constructeur de copie sera appelé deux fois: une fois pour construire `arg` et une fois pour construire `_att` à partir de `arg`.
{{% /hidden-solution %}}

```cpp
/*6*/
int main {
    MyOtherClass x;
    MyOtherClass y = x;
}   
```
{{% hidden-solution %}}
Le constructeur de copie de `MyClass` sera appelé une fois.
En effet, l'implémentation par défaut du constructeur de copie appelle le constructeur de copie pour chaque attribut.
{{% /hidden-solution %}}

```cpp
/*7*/
int main {
    MyOtherClass x;
    MyOtherClass y{x._att}
}   
```

{{% hidden-solution %}}
Le constructeur de copie sera appelé deux fois.
`x._att` est une L-value donc il est appelé une première fois pour construire `arg` et une seconde fois pour construire `_att` à partir de `arg`.
{{% /hidden-solution %}}

```cpp
/*8*/
int main {
    MyOtherClass x;
    MyOtherClass y = MyOtherClass{MyOtherClass{MyOtherClass{std::move(x)}}};
}   
```

{{% hidden-solution %}}
Aucun constructeur de copie n'est appelé.
En effet toutes les expressions suivantes sont des R-value:
- `std::move(x)`
- `MyOtherClass{std::move(x)}`
- `MyOtherClass{MyOtherClass{std::move(x)}}`
- `MyOtherClass{MyOtherClass{MyOtherClass{std::move(x)}}}`
{{% /hidden-solution %}}


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

Dans le code en dessous, le compilateur peut effectuer une élusion de déplacement (mais n'est pas obligé).

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
Ensuite, dans le `main`, l'expression `f()` est une R-value donc le constructeur de déplacement devrait être appelé pour construire `n`.
En fait, suivant le contenu de `f`, le compilateur peut décider de ne pas allouer de mémoire pour `x` et de construire directement le `MyClass` dans la mémoire allouée pour `m`.
