---
title: "Parcours et recherches"
pre: '<span class="presection-icon">🔍</span>'
weight: 1
---

### Parcours de plages

Pour parcourir une plage d'éléments, vous devriez normalement déjà savoir qu'il faut utiliser une boucle `for` ou foreach.
Les boucles `while` et `do-while` ne sont en effet pas vraiment adaptées à ce type d'usage.

Vous trouverez quelques conseils dans cette partie pour rendre votre code plus lisible, concis et fiable.

---

##### Boucle foreach

Lorsqu'on itère sur un conteneur avec une boucle foreach, il faut faire attention à si l'on souhaite récupérer une copie de l'élément ou une référence.

Lorsque l'on ne souhaite pas modifier le contenu du conteneur et que les éléments sont légers à copier (primitives par exemple) : 
```cpp
for (auto e : ctn)
{
    std::cout << e << std::endl;
}
```

Lorsque l'on ne souhaite pas modifier le contenu du conteneur et que la copie des éléments peut être coûteuse : 
```cpp
for (const auto& e : ctn)
{
    std::cout << e << std::endl;
}
```

Lorsque l'on souhaite modifier le contenu du conteneur :
```cpp
for (auto& e : ctn)
{
    e = compute_next();
}
```

Certains conteneurs stockent leurs éléments sous forme de tuples.
Par exemple, les `std::map` et les `std::unordered_map` contiennent des `std::pair<key, value>`.\
Lorsque c'est le cas, il est aussi possible d'utiliser un **structured binding** pour rendre le contenu de la boucle plus lisible.

```cpp
// Sans structured binding
for (const auto& kv : map)
{
    std::cout << "Key: " << kv.first << " Value: " << kv.second << std::endl;
}

// Avec structured binding
for (const auto& [key, value] : map)
{
    std::cout << "Key: " << key << " Value: " << value << std::endl;
}
```

---

##### Boucle for avec indice

Il est possible d'utiliser une boucle `for` pour itérer sur un conteneur disposant d'un `operator[]` attendant un entier (`int`, `unsigned int`, `size_t`).

{{% notice tip %}}
Il est préférable de ne les utiliser que lorsque l'on ne cherche pas à ajouter ou supprimer des éléments du conteneur (`for` avec itérateur est plus adapté dans ce cas), et que l'indice est utilisé pour autre chose que l'accès à l'élément (foreach suffit alors).
{{% /notice %}}

```cpp
for (size_t i = 0, end = ctn.size(); i != end; ++i)
{
    std::cout << ctn[i] << " is at index " << i << std::endl;
}
```

{{% notice tip %}}
Lorsque le processeur essaye de mettre une valeur dans un registre dans lequel elle ne peut pas tenir (valeur trop grande ou trop petite), on parle d'overflow.
Pour éviter ce type de problème, il faut prendre comme type d'indice celui renvoyé par `ctn.size()`.
C'est aussi une des bonnes raisons de préférer les boucles foreach ou `for` avec itérateurs aux boucles `for` avec indice.
{{% /notice %}}

{{% notice tip %}}
Il est préférable de calculer l'indice de fin dans la zone d'initialisation du `for`, plutôt qu'au niveau de la condition.
Si vous ne pouvez pas le faire car celui-ci n'est pas constant (car vous ajoutez ou retirez des éléments dans le corps de la boucle), cela signifie qu'il serait judicieux de remplacer votre boucle par un `for` avec itérateurs. 
{{% /notice %}}

---

##### Boucle for avec itérateurs

La boucle `for` avec itérateurs est la boucle la plus adaptée pour ajouter ou supprimer les éléments d'un conteneur pendant qu'on le parcourt.\
En effet, les autres types de parcours permettent rarement de traiter correctement l'invalidation des itérateurs.

```cpp
// Retire les éléments pairs.
for (auto it = ctn.begin(); it != ctn.end(); )
{
    if (*it % 2 == 0)
    {
        // ctn.erase(it) invalide it.
        // On ne peut donc pas utiliser it après cet appel : on ne pourrait ni écrire *it, ni ++it.
        // C'est pour cela que la fonction erase renvoie un nouvel itérateur, valide, sur l'élément suivant celui qui a été retiré.
        // En écrivant it = ctn.erase(it), on peut donc à nouveau utiliser la variable it.
        it = ctn.erase(it);
    }
    else
    {
        ++it;
    }
}
```

```cpp
// Ajoute une copie de chaque élément au tableau.
for (auto it = ctn.begin(); it != ctn.end(); it += 2)
{
    // ctn.insert(it, ...) invalide
    it = ctn.insert(it, *it);
}
```

---

##### Boucle std::for_each

Il est également possible d'utiliser la fonction `std::for_each` de `<algorithm>` pour itérer sur une plage de valeurs.\
L'intérêt de cette fonction, par rapport au foreach classique, c'est que l'on peut passer les itérateurs de début et de fin de notre choix.

```cpp
#include <algorithm>
#include <iostream>

void display_single(int v)
{
    std::cout << v << std::endl;
}

void display_many(const std::vector<int>& values)
{
    // On peut passer une fonction libre avec le bon prototype.
    std::for_each(values.begin() + 1, values.end() - 1, display_single);

    // On peut aussi passer une lambda.
    std::for_each(values.begin(), values.end(), [](int v) { display_single(v); });
}
```

---

### Recherche d'éléments

Parlons maintenant de comment retrouver un ou des éléments à l'intérieur d'une plage.
Vous pourriez bien sûr faire une boucle et recherchez ce dont vous avez besoin manuellement.\
Mais pourquoi s'embêter à écrire des boucles, lorsque tout un tas de fonctions existent déjà pour nous éviter d'avoir à le faire.

---

##### Recherche de la première occurrence d'un élément

Pour rechercher un élément bien précis dans une plage quelconque, vous pouvez utiliser `std::find` de `<algorithm>`.

```cpp
const auto searched = 8;
const auto it = std::find(ctn.begin(), ctn.end(), searched);

// Si la valeur n'est pas trouvée, `it` prend la même valeur que le 2e argument passé à std::find.
const auto found = (it != ctn.end());
std::cout << searched << (found ? "found" : "not found") << "in ctn." << std::endl;

if (found)
{
    const auto half_begin = ctn.begin();
    const auto half_end = std::next(half_begin, ctn.size() / 2);
    const auto half_it = std::find(half_begin, half_end, searched);
    if (half_it != half_end)
    {
        std::cout << searched << "found in first half of ctn." << std::endl;
    }
}
```

{{% notice tip %}}
Certains conteneurs, comme `set`, `unordered_set`, `map` ou `unordered_map`, proposent une fonction de recherche ayant une meilleure complexité que `std::find` (qui est en O(n)).
Afin d'implémenter des programmes efficaces, regardez donc toujours si vos conteneurs ne disposent pas de fonctions-membre permettant d'effectuer des opérations plus efficacement que les fonctions de `<algorithm>`.
{{% /notice %}}

---

##### Recherche inversée

`std::find` renvoie toujours l'itérateur sur la première occurrence qu'il trouve.
Si vous souhaitez rechercher la dernière occurrence, il est donc nécessaire de fournir des itérateurs permettant de parcourir la plage à l'envers.

Pour cela, il faut :
- transformer les itérateurs permettant d'avancer en itérateurs permettant de reculer : `std::make_reverse_iterator(it)` dans `<iterator>`
- les inverser dans l'appel à `std::find`.

```cpp
const auto searched = 8;
const auto reversed_begin = std::make_reverse_iterator(ctn.end());
const auto reversed_end = std::make_reverse_iterator(ctn.begin());

const auto it = std::find(reversed_begin, reversed_end, searched);

// Il faut toujours comparer au 2e argument de find, c'est-à-dire reversed_end et non pas ctn.end().
if (it != reversed_end)
{
    const auto pos = std::distance(reversed_begin, it);
    std::cout << pos << "-th element from the end of ctn is a " << searched << "." << std::endl;
}
```

{{% notice note %}}
Il n'est pas toujours possible de parcourir une plage à l'envers.
Seuls les itérateurs bidirectionnels peuvent être passés à la fonction `std::make_reverse_iterator`.
{{% /notice %}}

---

##### Recherche du premier élément appartenant à un groupe

Dans certains cas, on recherche la première occurrence parmi un ensemble.\
Par exemple, pour retrouver dans un texte le premier mot parmis `cheval`, `dodo`, `chien` et `bernard-l'ermite`, il faudrait faire 4 recherches si l'on utilisait `std::find`.

Afin d'effectuer cette recherche en une seule passe, il est possible d'utiliser `std::find_first_of`.
```cpp
std::vector<std::string> text = get_text();
std::vector<std::string> keywords { "horse", "dodo", "dog", "hermit crabs" };

const auto it = std::find_first_of(text.begin(), text.end(), keywords.begin(), keywords.end());
if (it != text.end())
{
    std::cout << "The first interesting animal we're talking about in this text is " << *it << "." << std::endl;
}
else
{
    std::cout << "The author didn't seem to like animals." << std::endl;
}
```

---

##### Recherche du premier élément vérifiant un prédicat

C'est bien beau tout ça, mais comment faire pour récupérer le premier élément pair dans un tableau ?
Vous n'allez pas pouvoir utiliser `find_first_of`, puisqu'il faudrait que la deuxième plage contienne une infinité d'éléments.

Heureusement, il y a `find_if`. Comme toutes les fonctions de `<algorithm>` (ou presque), `find_if` attend déjà les deux itérateurs bornant la plage d'éléments.\
Ensuite, vous devez lui fournir un **foncteur** acceptant un unique paramètre du type des éléments de la plage (par valeur ou const-ref), et renvoyant un booléen.

Un foncteur, c'est soit une fonction libre, soit une instance de classe avec un `operator()`, soit une lambda.

```cpp
// Fonction libre
bool is_even(int value) { return value % 2 == 0; }
...

const auto it = std::find_if(values.begin(), values.end(), is_even);


// Objet-fonction
struct IsEven
{
    bool operator()(int value) const { return value % 2 == 0; }
};
...

const IsEven is_even_obj;
const auto it = std::find_if(values.begin(), values.end(), is_even_obj);


// Lambda
const auto it = std::find_if(values.begin(), values.end(), [](int value) { return value % 2 == 0; });
```

{{% notice tip %}}
On désigne par **prédicats** les foncteurs retournant un booléen. En fonction du nombre de paramètres acceptés, on parlera de prédicat unaire, binaire, ternaire, etc.
{{% /notice %}}

Sachez qu'il existe aussi `find_if_not` pour récupérer le premier élément qui ne ne vérifie pas un prédicat.\
Il est intéressant de s'en servir lorsque vous avez déjà une fonction libre ou un objet-fonction vérifiant l'inverse de ce que vous recherchez.\
Utiliser `find_if_not` évite alors d'écrire une nouvelle fonction ou une nouvelle classe.

```cpp
bool is_even(int value) { return value % 2 == 0; }
...

const auto first_odd_it = std::find_if_not(values.begin(), values.end(), is_even);
```

---

### Vérification globale de prédicats

Lorsque l'on veut savoir si un prédicat est vérifié par l'ensemble des éléments d'une plage, on peut utiliser `std::all_of`, dans `<algorithm>`.
On a également `std::any_of` et `std::none_of`, permettant respectivement de savoir si au moins un élément vérifie le prédicat, ou si aucun élément ne vérifie le prédicat.

{{% notice note %}}
Petit rappel de logique propositionnelle : le résultat de `none_of` est l'inverse du résultat de `any_of`, pas de celui de `all_of`.  
{{% /notice %}}

Comme `find_if`, ces trois fonctions attendent deux itérateurs et un prédicat. Elles retournent par contre un booléen.

```cpp
bool is_even(int value) { return value % 2 == 0; }
...

const auto it_begin = values.begin();
const auto it_end = values.end();

if (std::all_of(it_begin, it_end, is_even))
{
    std::cout << "All values are even!" << std::endl;
}
else if (std::none_of(it_begin, it_end, is_even))
{
    // Pour avoir l'inverse d'un prédicat, on peut utiliser not_fn de <functional>. 
    assert(std::all_of(it_begin, it_end, std::not_fn(is_even)));

    std::cout << "All values are odd!" << std::endl;
}
else
{
    assert(std::any_of(it_begin, it_end, is_even));
    assert(std::any_of(it_begin, it_end, std::not_fn(is_even)));
    
    std::cout << "Some values are even, and some are odd!" << std::endl;
}
```

---

### Compter des éléments

Une des opérations courantes à réaliser sur une plage de valeurs, c'est de compter le nombre d'occurrence d'un élément.
Pour cela, il y a la fonction `std::count`, encore une fois dans `<algorithm>`.
Il y a également `std::count_if`, si vous souhaitez compter le nombre d'éléments vérifiant un prédicat, plutôt que le nombre d'occurrences d'un élément précis.

```cpp
const auto nb_1    = std::count(values.begin(), values.end(), 1);
const auto nb_even = std::count_if(values.begin(), values.end(), is_even);
const auto nb_odd  = std::count_if(values.begin(), values.end(), std::not_fn(is_even));
```

---

### Min et max

##### Comparer deux éléments

Vous le savez peut-être déjà, mais plutôt qu'écrire une ternaire pour déterminer le minimum ou le maximum de deux valeurs, vous pouvez utiliser les fonctions `std::min` et `std::max` (oui, toujours dans `<algorithm>`).
Ce que vous ne savez peut-être pas, c'est qu'il est possible de passer un **comparateur** à cette fonction.

Un comparateur, c'est un foncteur qui accepte deux paramètres de même type, et qui renvoie un booléen.
```cpp
// Si on ne passe pas de comparateur, le compilateur essaye d'utiliser operator< entre value1 et value2.
const auto max_value = std::max(value1, value2);

// Comme on n'a pas forcément envie que Person::operator< se base sur la taille, on peut passer un autre comparateur à std::min.
const auto compare_by_height = [](const Person& p1, const Person& p2) { return p1.height < p2.height; };
const auto shortest_person = std::min(person1, person2, compare_by_height);
```

Si vous n'utilisez pas tout à fait les mêmes types, par exemple, en mélangeant des `size_t` et des `unsigned int`, les appels à `std::min` et `std::max` ne pourront pas compiler.
En effet, la fonction ne saura pas quel type utilisé pour le résultat.
Pour désambiguifier la situation, il faudra donc indiquer clairement le type utilisé avec `std::min<T>(...)` ou `std::max<T>(...)`.
```cpp
// Par défaut, écrire "0" créé un élément de type int, alors que values.size() et expected_size sont de type size_t.
const auto new_size = std::max<size_t>(0, values.size(), expected_size);
```

Parfois, on veut récupérer à la fois le minimum et le maximum. Dans ce cas là, plutôt que d'avoir un appel à `min` et un appel à `max`, c'est-à-dire deux comparaisons, on peut utiliser la fonction `std::minmax`.
Celle-ci retourne un objet de type `std::pair<T, T>`, contenant le minimum pour premier élément et le maximum pour second élément.
Et ici aussi, plutôt que de faire `result.first` et `result.second` pour accéder au contenu de la paire, on peut utiliser un structured binding pour récupérer le résultat.
```cpp
const auto compare_by_height = [](const Person& p1, const Person& p2) { return p1.height < p2.height; };
const auto [shortest, tallest] = std::minmax(person1, person2, compare_by_height);
```

---

##### Comparer N éléments

Les trois fonctions `std::min`, `std::max` et `std::minmax` disposent de surcharges acceptant une `initializer_list`.
On peut ainsi récupérer le minimum et le maximum d'un ensemble de valeurs.
```cpp
const auto min_value = std::min({ 0, value1, value2, value3 });

const auto compare_by_height = [](const Person& p1, const Person& p2) { return p1.height < p2.height; };
const auto [shortest, tallest] = std::minmax({ person1, person2, person3 }, compare_by_height);
```

{{% notice info %}}
Attention cependant, en passant des éléments par `initializer_list`, ces éléments sont forcément copiés.
Dans le code plus haut, cela signifie que `shortest` est un nouvel objet, et non pas une référence sur l'un des objets `person#`.
Si vous voulez vraiment récupérer des références, vous pouvez créer des références wrappers à la volée, avec l'appel suivant :\
`const auto [shortest, tallest] = std::minmax<const Person&>({ std::cref(person1), std::cref(person2), std::cref(person3) }, compare_by_height };`
{{% /notice %}}

---

##### Comparer les éléments d'une plage

Il n'est pas possible de créer des `initializer_list` à partir d'un autre conteneur.

Du coup, si l'on veut récupérer l'élément minimum dans un `vector`, `<algorithm>` fournit la fonction `std::min_element`.
On retrouve bien sûr aussi `std::max_element` et `std::minmax_element`.

```cpp
const auto min_value = std::min_element(values.begin(), values.end());

const auto compare_by_height = [](const Person& p1, const Person& p2) { return p1.height < p2.height; };
const auto [shortest, tallest] = std::minmax_element(persons.begin(), persons.end(), compare_by_height);
```

---

##### Bornes inférieure et supérieure

Dans une plage d'éléments triée en selon un ordre donné, il est possible d'extraire le premier élément à être supérieur ou égal (par rapport à l'ordre choisi pour le conteneur) à une valeur donnée.
Par exemple, si on a [0, 3, 5, 6, 8, 10], alors le premier élément supérieur ou égal à 5 est 5, et le premier élément supérieur ou égal à 2 est 3.

La fonction `std::lower_bound` permet de récupérer cet élément :
```cpp
const std::vector<int> values { 0, 3, 5, 6, 8, 10 };
const auto it = std::lower_bound(values.begin(), values.end(), 2); // *it should be 3.

const std::vector<std::string> names { "Johnny halliday", "Jack L'Eventreur", "Denver Le Dernier Dinosaure", "Anne hidalgo" };
// Si la plage n'est pas ordonnée selon operator<, on doit passer à lower_bound un comparateur respectant l'ordre de la plage.
const auto it = std::lower_bound(names.begin(), names.end(), "Ji", std::greater {}); // *it should be "Jack L'Eventreur"
```

Si on veut maintenant récupérer le dernier élément inférieur ou égal à une valeur, on peut utiliser `upper_bound` :
```cpp
const std::vector<int> values { 0, 3, 5, 6, 8, 10 };
const auto it = std::upper_bound(values.begin(), values.end(), 2); // *it should be 0.

const std::vector<std::string> names { "Johnny Halliday", "Jack L'Eventreur", "Denver Le Dernier Dinosaure", "Anne hidalgo" };
const auto it = std::upper_bound(names.begin(), names.end(), "Ji", std::greater {}); // *it should be "Johnny Halliday"
```

{{% notice info %}}
Assurez-vous bien que votre plage d'éléments soit triée lorsque vous utilisez `std::lower_bound` ou `std::upper_bound`.
{{% /notice %}}

---

### Comparaison de plages

Nous allons maintenant vous présenter quelques fonctions (faisant toutes partie de `<algorithm>`) permettant de comparer des plages d'éléments entre elles.

---

##### Egalité ou équivalence

Pour commencer, pour savoir si deux plages d'éléments sont égales, vous pouvez utiliser `std::equal`.

```cpp
const auto begin = values.begin();
const auto end = values.end();
const auto half = std::next(begin, std::distance(begin, end) / 2);
if (std::equals(begin, half, half, end))
{
    std::cout << "The first half of values contains the same elements as its second half." << std::endl;
}

if (std::equals(my_dogs_names.begin(), my_dogs_names.end(), your_dogs_names.begin(), your_dogs_names.end()))
{
    std::cout << "Stop calling your dogs the same way I do!" << std::endl;
}
```

Vous pouvez passer un comparateur à la fonction, en particulier si vous ne traitez pas des plages du même type.
```cpp
const std::vector<Dog> dogs { Dog { "medor" }, Dog { "dagobert" }, Dog { "nonoss" } };
const std::vector<Cat> cats { Cat { "medor" }, Cat { "dagobert" }, Cat { "nonoss" } };

const auto compare_names = [](const Dog& dog, const Cat& cat) { return dog.name() == cat.name(); }
if (std::equals(dogs.begin(), dogs.end(), cats.begin(), cats.end(), compare_names))
{
    std::cout << "Why would you ever name your cats this way?" << std::endl;
}
```

Enfin, il est possible de vérifier si deux plages contiennent les mêmes éléments, mais pas forcément dans le même ordre, en utilisant `std::is_permutation`.

```cpp
const std::vector<unsigned int> my_numbers { 16, 1, 32, 33, 21 };
const std::vector<unsigned int> winning_numbers { 1, 16, 21, 32, 33 };

if (std::is_permutation(my_numbers.begin(), my_numbers.end(), winning_numbers.begin(), winning_numbers.end()))
{
    std::cout << "WOUHHHHHH OOOOOOOOOOOOOOUUUUUUUUHHHHHHHHHH!!!!!!!!!!!" << std::endl;
}
```

{{% notice note %}}
Il est possible de passer un comparateur à `equals`, et c'est également possible de le faire avec `is_permutation`, ainsi qu'avec toutes les autres fonctions présentées dans cette section.
{{% /notice %}}

---

##### Comparaison lexicographique

Comparer lexicographiquement deux chaînes de caractères revient à d'abord comparer les premières lettres, puis si elles sont égales, les deuxièmes, puis si elles sont égales aussi, les troisièmes, et ainsi de suite jusqu'à trouver deux lettres qui ne sont pas identique.

Ce procédé peut se généraliser à n'importe quels types de plages d'éléments en utilisant la fonction `std::lexicographical_compare`.
```cpp
std::array<Pokemon, 6> my_pokemons { ... };
std::array<Pokemon, 6> your_pokemons { ... };

if (std::lexicographical_compare(my_pokemons.begin(), my_pokemons.end(), your_pokemons.begin(), your_pokemons.end()))
{
    std::cout << "You win the duel." << std::end;
}
else
{
    std::cout << "I win the duel." << std::endl;
}
```
