---
title: "Exemples"
pre: '<span class="presection-icon">🐥</span>'
weight: 2
---

Nous allons maintenant rentrer dans le vif du sujet en vous présentant le code de différents templates.\
Nous détaillerons ensuite chacun des éléments de la syntaxe, afin que vous puissiez les comprendre pour les réutiliser dans votre propre code. 

---

### Premier exemple de classe-template

Cet exemple consiste en l'implémentation d'un tableau de taille statique (un peu comme la classe `std::array`).

```cpp
#include <algorithm>
#include <cassert>
#include <iostream>

template <typename ElementType, size_t Size>
class StaticArray
{
public:
    // Rappel: l'implémentation par défaut du constructeur par défaut disparaît lorsqu'on
    // définit explicitement un autre constructeur (ce qui est le cas ici).
    // Ecrire `Class() = default` permet de demander au compilateur de générer le constructeur
    // par défaut de Class, même si on a définit un autre constructeur.
    StaticArray() = default;
    
    StaticArray(const ElementType& element)
    {
        fill(element);
    }

    ElementType& operator[](size_t index)
    {
        assert(index < Size);
        return _elements[index]; 
    }

    const ElementType& operator[](size_t index) const
    { 
        assert(index < Size);
        return _elements[index];
    }

    void fill(const ElementType& element)
    {
        std::fill_n(_elements, Size, element);
    }

    size_t size() const { return Size; }

    const ElementType* begin() const { return _elements; }
    const ElementType* end() const { return _elements + Size; }

private:
    // Rappel: en écrivant {} sur un initializer de tableau statique C, cela permet d'initialiser tous les éléments
    // du tableau par défaut (0 pour les types primitifs). 
    ElementType _elements[Size] {};
};

int main()
{
    StaticArray<int, 3> array_of_3_ints;
    // [0, 0, 0]

    array_of_3_ints[1] = 3;

    for (const auto& e: array_of_3_ints)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    // -> '0 3 0'

    StaticArray<std::string, 5> array_of_5_strings { "toto" };
    // ["toto", "toto", "toto", "toto", "toto"]

    array_of_5_strings[1] = "est";
    array_of_5_strings[2] = "vraiment";
    array_of_5_strings[3] = "un";
    array_of_5_strings[4] = "feignant";

    for (const auto& e: array_of_5_strings)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    // -> 'toto est vraiment un feignant'

    return 0;
}
```

Décortiquons maintenant ce petit programme.

---

##### En-tête de la classe-template

L'en-tête se résume à :

```cpp
template <typename ElementType, size_t Size>
class StaticArray
{ ... };
```

Les deux premières lignes permettent de définir une classe-template `StaticArray`, paramétrée par un paramètre `ElementType` et un paramètre `Size`.

Tout comme les paramètres de fonction, les paramètres de template sont typés.
Ici, `ElementType` est de type `typename` et `Size` est de type `size_t`.\
Pour générer une classe à partir de `StaticArray`, il faudra donc d'abord fournir un nom de type.
Il peut s'agir d'un nom de classe ou structure (comme `Animal` ou `std::string`) ou bien d'un type primitif (comme `int`, `float` ou `char`).\
Il faudra également fournir une valeur de type `size_t`. 

Attention, lorsque vous fournissez des arguments à un template, il faut que leurs valeurs soit évaluables lors de la compilation.
C'est évident lorsque le paramètre est de type `typename`, puisque tous les noms de types sont forcément connus à la compilation.
En revanche, lorsque vous avez des paramètres de type "valeur" (`int`, `char` ou `size_t` comme ici), le compilateur doit être capable de calculer ce que vous lui envoyer.

```cpp
StaticArray<int, 3> array;
// Pas de problème, on passe un litéral en tant que deuxième paramètre.
// Le compilateur n'aura aucun souci pour évaluer sa valeur et générer la classe.

StaticArray<int, 3+5> array;
// Pas de problème non plus, car le compilateur est capable d'effectuer des opérations avec
// des litéraux.

size_t size = 3;
StaticArray<int, size> array;
// Ici en revanche, ça ne compilera pas. Bien qu'un humain soit clairement capable de dire
// qu'au moment d'instancier array, size vaut forcément 3, ce n'est pas le cas du compilateur.

constexpr size_t size = 3;
StaticArray<int, size> array;
// Ca fonctionne ici, car constexpr permet de définir des variables dont la valeur est évaluée à
// la compilation. Cela implique bien sûr que la variable est constante, mais aussi qu'on peut
// l'utiliser en tant qu'argument de template.
```

---

##### Utilisation des paramètres de template dans la classe

Vous pouvez utiliser les paramètres du template n'importe où dans le code de votre classe, aussi bien dans la définition des attributs, que dans le contenu des fonctions-membre ou de leur signature.

Par exemple, `ElementType` et `Size` ont tous les deux servis à définir l'attribut `_elements` :
```cpp
ElementType _elements[Size] {};
```

On définit un attribut `_elements` qui est un tableau statique C de taille `Size` et donc les éléments sont de type `ElementType`.
Si cette ligne vous a un peu dérouté, vous devriez remarquer qu'elle n'est en fait pas plus compliquée que `int _elements[3] {};`\
On a juste décidé d'avoir un tableau d'`ElementType` plutôt que d'entier, et de taille `Size` plutôt que `3`.

Le paramètre `Size` a été utilisé dans la définition de `operator[]`, pour vérifier que l'indice passé à la fonction est inférieur à la taille du tableau :
```cpp
assert(index < Size);
```

Toujours pour `operator[]`, `ElementType` a servi à spécifier le type de retour de chacune des surcharges :
```cpp
ElementType& operator[](size_t index)
const ElementType& operator[](size_t index) const
```

---

##### Un peu de pratique

Vous pouvez retrouver le code de `StaticArray` sur {{% open_in_new_tab "https://www.godbolt.org/z/aEcGxzn5b" "GodBolt" /%}}.

Essayez maintenant de définir une toute petite structure templatée `Triple`, contenant trois éléments `first`, `second` et `third` qui n'ont pas forcément le même type.
Il s'agira donc en quelque sorte d'une généralisation de `std::pair`.\
Votre classe devra comporter un constructeur par défaut, et un constructeur à trois paramètres permettant d'initialiser chacun des éléments du triplet.

Vous trouverez une solution {{% open_in_new_tab "https://www.godbolt.org/z/343bbYEas" "ici" /%}}.

---

### Premiers exemples de fonctions-template

##### Overloading

Un cas d'utilisation standard de fonction-template est d'éviter d'avoir à écrire tous les surcharges possibles et imaginables pour une fonction.
Voici par exemple comment écrire une fonction-template `add` qui accepte des paramètres de n'importe quel type (du moment qu'il est possible de les additionner avec `operator+`), et retourne le résultat converti dans n'importe quel type également. 

```cpp
template <typename Result, typename Param1, typename Param2>
Result add(const Param1& p1, const Param2& p2)
{
    return static_cast<Result>(p1 + p2);
}
```

Et voici différentes manières d'utiliser cette fonction-template.

```cpp
// En indiquant explicitement tous les paramètres de template.
auto r1 = add<int, float, float>(3.8, 6.5); // r1: int 10

// On peut aussi omettre le ou les derniers paramètres si ceux-ci peuvent être déduits des arguments passés à la fonction.
// Par exemple, ici, 3.8 et 6.5 sont des litéraux de type double, c'est donc add<int, double, double> qui est générée.
auto r2 = add<int>(3.8, 6.5);               // r2: int 10

// Si on omet des paramètres qui ne peuvent pas être déduits automatiquement, alors l'appel ne compilera pas.
// Ici, le premier paramètre sert à donner le type de retour de la fonction et il n'est pas déductible des arguments passés à
// la fonction. Le code suivant ne compile donc pas (même en indiquant explicitement le type de la variable dans lequel on
// récupère le résultat).
int r3 = add(3.8, 6.5);                     // ne compile pas
```

---

##### Polymorphisme

On peut également utiliser des templates pour faire du polymorphisme.

```cpp
enum class Category { Bird, Mammal, Mythical, Insect };

struct Chicken
{
    static constexpr Category category = Category::Bird; 
};

struct Dog
{
    static constexpr Category category = Category::Mammal; 
};

struct Pegasus
{
    static constexpr Category category = Category::Mythical; 
    
    bool can_fly() const { return true; }
};

struct Caterpillar
{
    static constexpr Category category = Category::Insect; 

    bool can_fly() const { return _is_butterfly; }
    void evolve() { _is_butterfly = true; }
    
    bool _is_butterfly = false;
};

template <typename Animal>
bool has_wings(const Animal& animal)
{
    if constexpr (Animal::category == Category::Bird)
    {
        return true;
    }
    else if constexpr (Animal::category == Category::Insect || Animal::category == Category::Mythical)
    {
        return animal.can_fly();
    }
    else 
    {
        return false;
    }
}
```

Dans l'exemple ci-dessus, on a une fonction-template `has_wings` paramétrée par le type `Animal`.
Ce type doit présenter un attribut statique `category`, et dans le cas où il vaut `Insect` ou `Mythical`, il faut pouvoir appeler une fonction `can_fly() -> bool` sur une instance d'`Animal`.

```cpp
int main()
{
    Chicken chicken;
    Dog dog;
    Pegasus pegasus;
    Caterpillar caterpillar;

    std::cout << has_wings(chicken) << std::endl; // -> 1
    std::cout << has_wings(dog) << std::endl;     // -> 0
    std::cout << has_wings(pegasus) << std::endl; // -> 1

    std::cout << has_wings(caterpillar) << std::endl; // -> 0
    caterpillar.evolve();
    std::cout << has_wings(caterpillar) << std::endl; // -> 1

    std::string animal = "animal";
    std::cout << has_wings(animal) << std::endl; // ne compile pas, car std::string n'a pas d'attribut statique `Category` !

    return 0;
}
```

Dans l'implémentation de `has_wings`, vous avez dû vous demander ce que signifiaient les `if constexpr`.\
Lors de la génération du code, ce `if` particulier permet de demander au compilateur de ne conserver et compiler que la branche qui serait évaluée dans le cas d'un `if` classique. 

Par exemple, le compilateur générera le code suivant pour la fonction `has_wings<Chicken>` :
```cpp
bool has_wings(const Chicken& animal)
{
    return true;
}
```

Si on avait utilisé des `if` non constexpr, alors, la fonction générée aurait été la suivante et on aurait eu une erreur de compilation :

```cpp
bool has_wings(const Chicken& animal)
{
    if (Chicken::category == Category::Bird)
    {
        return true;
    }
    else if (Chicken::category == Category::Insect || Chicken::category == Category::Mythical)
    {
        return animal.can_fly(); // Erreur : la classe Chicken n'a pas de fonction-membre `can_fly`.
    }
    else 
    {
        return false;
    }
}
```

L'intérêt d'utiliser des `if constexpr`, c'est donc de faire en sorte que le compilateur ne génère que le code vraiment nécessaire à chaque instantiation d'un template.\
La contrainte, c'est qu'il faut que la condition de ce type de `if` puisse être évaluée au moment de la compilation.
C'est notamment pour cela que nous avons dû spécifier l'attribut `category` comme étant `constexpr` dans les classes `Chicken`, `Dog`, `Pegasus` et `Caterpillar`.

---

##### Transfert de paramètres de template

Lorsqu'on veut écrire une fonction-template qui accepte en paramètre un objet dont le type est templaté, alors il peut être intéressant de templater la fonction avec les mêmes paramètres de template que cet objet. 

On pourrait par exemple définir l'`operator<<` de la classe-template `StaticArray` définie plus haut de la manière suivante : 
```cpp
template <typename ElementType, size_t Size>
std::ostream& operator<<(std::ostream& stream, const StaticArray<ElementType, Size>& array)
{
    for (const auto& e: array)
    {
        stream << e << " ";
    }

    return stream;
}

int main()
{
    StaticArray<int, 3> array_of_3_ints;
    array_of_3_ints[1] = 3;

    // Génération de operator<< <int, 3>(ostream&, const StaticArray<int, 3>&)
    std::cout << array_of_3_ints << std::endl;

    StaticArray<std::string, 5> array_of_5_strings { "toto" };
    array_of_5_strings[1] = "est";
    array_of_5_strings[2] = "vraiment";
    array_of_5_strings[3] = "un";
    array_of_5_strings[4] = "feignant";

    // Génération de operator<< <string, 5>(ostream&, const StaticArray<string, 5>&)
    std::cout << array_of_5_strings << std::endl;

    return 0;
}
```

---

##### Un peu de pratique

1. Implémentez une fonction qui prend deux conteneurs quelconques en paramètre et renvoie la somme de leurs tailles.
2. Implémentez une fonction concaténant deux chaînes de caractères, pouvant être de type `const char*`, `std::string` ou `std::string_view`.
Le résultat sera de type `std::string`.
3. Implémentez une fonction `convert_to_string` qui prend un paramètre de type quelconque, et si ce paramètre est un nombre (regardez les fonctions définies dans `<type_traits>`), convertissez-le en `std::string` à l'aide de `std::to_string`.
Autrement, renvoyez le paramètre tel quel.
Modifiez ensuite votre fonction de concaténation pour qu'elle puisse fonctionner avec des nombres également. 

Vous trouverez une solution {{% open_in_new_tab "https://www.godbolt.org/z/8f9aePnsh" "ici" /%}}.
