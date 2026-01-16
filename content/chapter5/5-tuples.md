---
title: "Paires, tuples et options"
pre: '<span class="presection-icon">🍒</span>'
weight: 6
---

Vous avez déjà utilisé le type `pair` au cours d'exercices précédents. Nous allons maintenant vous présenter son cousin, la classe `tuple`.

---


Pour cet exercice, on partira du fichier [`5-tuples.cpp`](/chapter5/5-tuples.cpp).

---

### Micro point sur les `pair`

La classe `pair` est un type templaté avec deux paramètres :
```cpp
std::pair<int, float> such_a_nice_pair { 1, 3.f };
```

On accède aux éléments de la `pair` directement via ses attributs `first` et `second` (pas de getters) :
```cpp
int int_value     = such_a_nice_pair.first;
float float_value = such_a_nice_pair.second;
```

Enfin, pour créer des `pair` à la volée, c'est-à-dire sans définir de variables (passage à une fonction par exemple), on peut utiliser le code suivant :
```cpp
std::map<unsigned int, float> values;

// Si les valeurs sont correctement typées :
values.insert(std::make_pair(3u, 5.f));
values.insert(std::pair { 4u, 9.5f });

// Si les valeurs requièrent une conversion :
values.insert(std::make_pair<unsigned int, float>(2, 8));
values.insert(std::pair<unsigned int, float> { 12, -6.5 });
```

---

### Les tuples

Un `tuple`, c'est comme une `pair`, sauf qu'au lieu de ne contenir que deux éléments, elle peut en contenir autant qu'on veut.

Contrairement aux `pair`, on ne récupérera pas les valeurs avec `first`, `second`, `third`, etc. Il faudra utiliser la fonction libre `std::get` :
```cpp
std::tuple<std::string, int> named_value { "one", 1 };

auto name  = std::get<0>(named_value);
auto value = std::get<1>(named_value);
```

{{% notice note %}}
Pourquoi une fonction libre plutôt qu'une fonction-membre ? Aucune idée. Mais en tout cas, rappelez-vous que si vous écrivez `some_tuple.get(0)`, ça ne compilera pas.  
{{% /notice %}}

L'un des intérêts du `tuple`, c'est de pouvoir regrouper plusieurs valeurs dans une seule, sans avoir à définir de nouvelle classe.\
Lorsqu'une fonction devait vous retourner plusieurs valeurs, vous étiez souvent contraints d'ajouter des "paramètres de retour" à la fonction.\
Maintenant, vous saurez que vous pouvez utiliser des tuples.

Modifiez le code du fichier `5-tuples.cpp` afin d'appliquer ce principe.

{{% hidden-solution %}}
{{% highlight cpp "hl_lines=3 5 7 12 18 19 29 35 38 41 43 48 49 54 55 56 58" %}}
#include <iostream>
#include <string>
#include <tuple>

std::tuple<bool, int, int> parse_params(int argc, const char* const* argv)
{
    const std::tuple<bool, int, int> error { false, 0, 0 };

    if (argc != 3)
    {
        std::cerr << "Program expects 2 parameters!" << std::endl;
        return error;
    }

    std::string num_str = argv[1];
    std::string den_str = argv[2];
    
    int num = 0;
    int den = 0;

    try
    {
        num = std::stoi(num_str);
        den = std::stoi(den_str);
    }
    catch (const std::exception&)
    {
        std::cerr << "Program expects 2 integer parameters!" << std::endl;
        return error;
    }
    
    if (den == 0)
    {
        std::cerr << "Denominator cannot be null!" << std::endl;
        return error;
    }

    return std::tuple { true, num, den };
}

std::tuple<int, int> divide(int numerator, int denominator)
{
    return std::tuple { numerator / denominator, numerator % denominator };
}

int main(int argc, char** argv)
{
    const auto parse_res = parse_params(argc, argv);
    if (!std::get<0>(parse_res))
    {
        return 1;
    }

    const auto num = std::get<1>(parse_res);
    const auto den = std::get<2>(parse_res);
    const auto div_res = divide(num, den);

    std::cout << num << " = " << den << " * " << std::get<0>(div_res) << " + " << std::get<1>(div_res) << std::endl;   

    return 0;
}
{{% /highlight %}}
{{% /hidden-solution %}}

