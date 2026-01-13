---
title: "Enum"
pre: '<span class="presection-icon">⨀</span>'
weight: 7
hidden: true
---

En plus des enums du C (que l'on utilisera pas!) le C++ a introduit des `enum class`.


### Déclaration d'une enum C++
```C++
enum class Color {
    Red,
    Green,
    Blue
};
```

### Initialisation d'une enum

Les enum C++ sont généralement plus sécurisées.  En particulier les valeurs (par exemple `Red`) doivent être préfixé par le nom de l'enum (par exemple `Color::`). Par exemple, voici comment stocké la valeur d'une enum dans une variable locale.

```C++
Color my_color = Color::Red;
```

### Des switchs plus sûr

En C++ les enums ne peuvent avoir que les valeurs déclarées.  
Que se passe-til quand on compile suivante avec l'option `-Wall`.

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
Le compilateur indique que le switch est incomplet (probablement même qu'il manque exactement la valeur Bleu).
{{% /hidden-solution %}}


### Définition du type sous-jacent et des valeurs effectivement stockée

Pour avoir plus de contrôle, on peut choisir ce qui sera stockée effectivement en mémoire pour chaque valeur de l'enum.  On peut aussi spécifier la *taille* que prend une enum en mémoire, ou plutôt le type sous-jacent qui permettra de la stocker.

```C++
// Une Color est stocké dans un unsigned
//               vvvvvvvvvv
enum class Color : unsigned {
    None = 0u,
    //   ^^^^
    // On peut spécifier (ou non) la valeur
    //  vvvv
    Red = 1u ,
    Green = 2u,
    Blue = 3u
};
```


### Quel intérêt ?

Le but est de pouvoir caster de façon sûre notre enum dans un autre type.

```C++
std::vector<std::string> color_names= {"None", "Red", "Green", "Blue"};

std::ostream& operator<<(std::ostream& o, Color color) 
{
    return o << color_names[(unsigned)color];
}
```

En utilisant le vecteur  écrire une fonction `stoc` qui prend en argument une chaîne de caractère et qui renvoie l'enum appropriée ou `None` si c'est une autre.

{{% hidden-solution %}}
Color stoc(const std::string& target) {
    for (unsigned i = 0; i < color_names.size(); ++i)
        if (color_names[i] == target)
            return ((Color) i);
    return Color::None;
}
{{% /hidden-solution %}}

Cela permet aussi de définir une valeur spécifique de l'enum qui aura la valeur 0.   En castant l'enum en booléen, ça permet de l'utiliser dans les tests, comme le montre le code suivant.

```C++
if ((bool) Color::None)
    std::cout << "Hello" << std::endl;
if ((bool) Color::Red)
    std::cout << "World" << std::endl;
```

<!-- https://godbolt.org/z/15K6dGvPc -->