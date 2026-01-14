---
title: "Enum"
pre: '<span class="presection-icon">🔠</span>'
weight: 7
---

En plus des enums du C, le C++ a introduit des `enum class`.
On les appelera plus simplement des *enum C++* ou juste *enum* parce qu'on n'utilisera **pas** les enum du C.

Une enum C++ est un type qui n'a qu'un nombre d'instances connus au moment de la compilation. Ça permet d'éviter d'utiliser une `std::string` qui coûte plus cher à manipuler, ou d'utiliser un entier qui n'est pas clair.


### Déclaration d'une enum C++

Une enum C++ se définit avec la syntaxe suivante.

```C++
enum class Color {
    Red,
    Green,
    Blue
};
```

### Construction d'une enum

Les enum C++ sont généralement plus sécurisées que les enum C.  En particulier les valeurs (par exemple `Red`) doivent être préfixé par le nom de l'enum (par exemple `Color::`). Par exemple, voici comment stocké la valeur d'une enum dans une variable locale.

```C++
Color my_color = Color::Red;
```

### Des switchs plus sûr

Les enums C++ ne peuvent avoir que les valeurs déclarées (ce qui n'est pas le cas des enums C).
Ceci permet au compilateur de faire des messages plus intelligents.  Par exemple, que se passe-t-l quand on compile suivante avec l'option `-Wall` ?

```C++
std::ostream& operator<<(std::ostream& o, Color color) 
{
    switch(color) {
        case Color::Red: o << "Red"; break;
        case Color::Green: o << "Green"; break;
    }
    return o;
}
```

{{% hidden-solution %}}
Le compilateur indique que le switch est incomplet (probablement même qu'il manque exactement la valeur `Blue`).
{{% /hidden-solution %}}


### Définition du type et des valeurs sous-jacentes

Pour avoir plus de contrôle, on peut choisir ce qui sera stockée effectivement en mémoire pour chaque valeur de l'enum.  On peut aussi spécifier la *taille* que prend une enum en mémoire, ou plutôt le type sous-jacent qui permettra de la stocker.

```C++
// Une ColorBis est stocké dans un unsigned
//                  vvvvvvvvvv
enum class ColorBis : unsigned {
    None = 0u,
    //   ^^^^
    // On peut spécifier la valeur
    //     vvvv
    Orange = 1u,
    Indigo = 2u,
    Violet = 3u
};
```


### Quel intérêt ?

Le but est de pouvoir caster de façon sécurisée notre enum dans un autre type, comme ce qui est fait dans le code suivant.

```C++
std::vector<std::string> color_names= {"None", "Orange", "Indigo", "Violet"};

std::ostream& operator<<(std::ostream& o, ColorBis color) 
{
    return o << color_names[(unsigned)color];
}
```

En utilisant le tableau dynamique ` color_names` écrire une fonction `stoc` qui prend en argument une chaîne de caractère et qui renvoie la `ColorBis` appropriée, ou `None` si c'est une autre.

{{% hidden-solution %}}
```C++
ColorBis stoc(const std::string& target) {
    for (unsigned i = 0; i < color_names.size(); ++i)
        if (color_names[i] == target)
            return ((ColorBis) i);
    return ColorBis::None;
}
```
{{% /hidden-solution %}}

Cela permet aussi de définir une valeur spécifique de l'enum qui aura la valeur 0.   En castant l'enum en booléen, ça permet de l'utiliser dans les tests, comme le montre le code suivant.

```C++
if ((bool)ColorBis::None)
    std::cout << "Hello" << std::endl;
if ((bool)ColorBis::Indigo)
    std::cout << "World" << std::endl;
```


<!-- https://godbolt.org/z/1hEde8j16 -->