---
title: "SFINAE"
pre: '<span class="presection-icon">🤪</span>'
weight: 4
---

Nous allons maintenant vous expliquer ce que signifie SFINAE, le besoin auquel ce mécanisme répond et comment le mettre en oeuvre dans votre code. 

---

### Le besoin

Supposons que nous souhaitions pouvoir récupérer une clef pour différents type à l'aide d'une fonction `get_key(const Type&)`, en utilisant des overloads.

```cpp
class Person
{
public:
    Person(const std::string& name)
    : _name { name }
    {}

    const std::string& get_name() const
    {
        return _name;
    }

private:
    const std::string _name;
};

// Overload pour notre classe Person.
const std::string& get_key(const Person& person)
{
    return person.get_name();
}

// Overload pour un type générique de la librairie standard.
template <typename First, typename Second>
const First& get_key(const std::pair<First, Second>& pair)
{
    return pair.first;
}

int main()
{
    Person charles { "Charles" };
    std::cout << get_key(charles) << std::endl; // --> Charles 

    std::pair<std::string, int> pair { "eight", 8 };
    std::cout << get_key(pair) << std::endl; // --> eight 

    return 0;
}
```

Supposons maintenant que l'on se trouve dans un projet dans lequel de nombreuses classes définissent déjà un getter constant `get_key()` permettant de renvoyer la clef correspondant à cet objet : 
```cpp
template <typename Key, typename Value>
struct KeyValue
{
    Key key = {};
    Value value = {};

    const Key& get_key() const { return key; }
};
```

Plutôt que de devoir définir manuellement l'overload pour chacuns de ces types, nous souhaiterions que la fonction `get_key(const T& obj)` puisse être automatiquement générée et appelle `obj.get_key()`.
On pourrait donc avoir quelque chose comme ça :
```cpp
#include <iostream>

template <typename T>
const auto& get_key(const T& obj)
{
    return obj.get_key();
} 

template <typename Key, typename Value>
struct KeyValue
{
    Key key = {};
    Value value = {};

    const Key& get_key() const { return key; }
};

int main()
{
    KeyValue<int, int> kv { 1, 2 };
    std::cout << get_key(kv) << std::endl; // --> 1 

    return 0;
}
```

Incroyable ! Ca fonctionne.

Essayons maintenant de rajouter l'overload pour les `std::pair`, ainsi que l'appel à la fonction `get_key()` sur une instance de `pair<std::string, int>`.
```cpp
#include <iostream>
#include <utility>

// Overload générique pour tous les types qui contiennent un getter get_key().
template <typename T>
const auto& get_key(const T& obj)
{
    return obj.get_key();
}

// Overload pour un type générique de la librairie standard.
template <typename First, typename Second>
const First& get_key(const std::pair<First, Second>& pair)
{
    return pair.first;
}

template <typename Key, typename Value>
struct KeyValue
{
    Key key = {};
    Value value = {};

    const Key& get_key() const { return key; }
};

int main()
{
    KeyValue<int, int> kv { 1, 2 };
    std::cout << get_key(kv) << std::endl; // --> 1

    std::pair<std::string, int> pair { "eight", 8 };
    std::cout << get_key(pair) << std::endl; // --> eight

    return 0;
}
```

Extra-ordinaire ! Ca fonctionne toujours !

Vous vous apercevez maintenant que dans l'une des dépendences externes de votre projet, vous disposez d'une classe polymorphe `Procedure` contenant une fonction `get_id()`.\
Comme vous êtes malin, vous vous dites que vous allez créer un overload pour `const Procedure&`, afin que l'on puisse passer n'importe quelle sous-classe à la fonction, et que celle-ci appelle `get_id()` pour déterminer la clef de l'objet.

```cpp
#include <iostream>

class Procedure // supposée hors du projet
{
public:
    virtual ~Procedure() = default;

    virtual int get_id() const = 0;
};

class ZeroProcedure: public Procedure
{
public:
    int get_id() const override { return 0; }
};

// Overload spécifique à Procedure et ses sous-classes.
int get_key(const Procedure& procedure)
{
    return procedure.get_id();
}

// Overload générique pour tous les types qui contiennent un getter get_key().
template <typename T>
const auto& get_key(const T& obj)
{
    return obj.get_key();
}

template <typename Key, typename Value>
struct KeyValue
{
    Key key = {};
    Value value = {};

    const Key& get_key() const { return key; }
};

int main()
{
    KeyValue<int, int> kv { 1, 2 };
    std::cout << get_key(kv) << std::endl;
    
    ZeroProcedure p;
    std::cout << get_key(p) << std::endl;

    return 0;
}
```

Et là, vous vous retrouvez avec cette erreur :
```b
error: 'const class ZeroProcedure' has no member named 'get_key'
```

Comment ça `ZeroProcedure` n'a pas de fonction `get_key` ??\
Elle n'a pas besoin d'une fonction `get_key`, puisse qu'on lui a créé un super overload qui utilise `Procedure::get_id()`...

---

### Best viable function

Pour vous convaincre que vous n'avez pas écrit n'importe quoi précédement, vous allez commenter la version générique de `get_key()`:
```cpp
#include <iostream>

class Procedure // supposée hors du projet
{
public:
    virtual ~Procedure() = default;

    virtual int get_id() const = 0;
};

class ZeroProcedure: public Procedure
{
public:
    int get_id() const override { return 0; }
};

// Overload spécifique à Procedure et ses sous-classes.
int get_key(const Procedure& procedure)
{
    return procedure.get_id();
}

// // Overload générique pour tous les types qui contiennent un getter get_key().
// template <typename T>
// const auto& get_key(const T& obj)
// {
//     return obj.get_key();
// }

template <typename Key, typename Value>
struct KeyValue
{
    Key key = {};
    Value value = {};

    const Key& get_key() const { return key; }
};

int main()
{
    // KeyValue<int, int> kv { 1, 2 };
    // std::cout << get_key(kv) << std::endl;
    
    ZeroProcedure p;
    std::cout << get_key(p) << std::endl;

    return 0;
}
```

Le code compile à nouveau.

Il semblerait donc que lors de l'étape de résolution des appels, si on passe un type `Child` a une fonction disposant :
- d'un overload entièrement générique : `template <Type> .. fcn(const Type&)`,
- d'un overload sur le type parent : `.. fcn(const Parent&)`,\
ce soit l'overload générique qui l'emporte systématiquement...

Cette fonction choisie par le compilateur s'appelle la **best viable function**.\
Les règles qui définissent ce choix étant relativement denses et complexes, nous ne rentrerons pas dans les détails.
Mais si un jour, vous avez besoin de vous y intéresser, vous pouvez les consulter sur [cette page](https://en.cppreference.com/w/cpp/language/overload_resolution).

Idéalement, pour résoudre notre problème, il faudrait trouver une astuce permettant de dire au compilateur d'ignorer l'overload générique afin d'appeler la fonction attendant la classe de base.
Cette astuce existe et porte un nom : **SFINAE**.

---

### SFINAE

SFINAE signifie : "substitution failure is not an error".

Cela veut dire que si le compilateur n'arrive pas à substituer les paramètres de template à partir des arguments passés à une fonction, il ne va pas générer d'erreur de compilation.
Il va simplement ignorer cette définition et tenter de trouver un autre overload à appeler.

Dans notre exemple, la fonction générique ne peut fonctionner que si l'objet passé en paramètre dispose d'un getter `get_key` n'acceptant pas de paramètre.
Nous allons donc utiliser SFINAE pour empêcher le compilateur de considérer `get_key(const Type&)` si `Type` ne définit pas ce getter.

```cpp
#include <type_traits>

template <typename T, typename Ret = decltype(std::declval<T>().get_key())>
Ret get_key(const T& obj)
{
    return obj.get_key();
}
```

Commençons tout d'abord par décortiquer : `typename Ret = decltype(std::declval<T>().get_key())`:
1. On définit un nouveau paramètre de template nommé `Ret`.
2. On lui assigne une valeur par défaut.
3. `std::declval<T>()` est une fonction de `<type_traits>` permettant d'instancier une variable de type `T` à la compilation (dans les paramètres de template par exemple).
4. On appelle `get_key()` sur cette instance.
5. On récupère le type de la valeur de retour à l'aide du mot-clef `decltype`.
6. La valeur par défaut de `Ret` correspond donc au type de retour de la fonction `T::get_key()`.

Essayez de compiler le code suivant, vous devriez constater qu'il n'y a plus d'erreur de compilation et que tout se passe comme attendu :
```cpp
#include <iostream>
#include <type_traits>

class Procedure // supposée hors du projet
{
public:
    virtual ~Procedure() = default;

    virtual int get_id() const = 0;
};

class ZeroProcedure: public Procedure
{
public:
    int get_id() const override { return 0; }
};

// Overload spécifique à Procedure et ses sous-classes.
int get_key(const Procedure& procedure)
{
    return procedure.get_id();
}

// Overload générique pour tous les types qui contiennent un getter get_key().
template <typename T, typename Ret = decltype(std::declval<T>().get_key())>
Ret get_key(const T& obj)
{
    return obj.get_key();
}

template <typename Key, typename Value>
struct KeyValue
{
    Key key = {};
    Value value = {};

    const Key& get_key() const { return key; }
};

int main()
{
    KeyValue<int, int> kv { 1, 2 };
    std::cout << get_key(kv) << std::endl;
    
    ZeroProcedure p;
    std::cout << get_key(p) << std::endl;

    return 0;
}
```

Ce qu'il s'est produit ici, c'est que lorsque le compilateur a regardé si l'overload générique de `get_key()` pouvait être utilisé avec `ZeroProcedure`, il n'a pas réussi à générer la signature de la fonction à partir des types fournis.\
En effet, il a pu remplacer `T` par `ZeroProcedure`.
Cependant, pour déterminer `Ret`, il a été obligé d'évaluer sa valeur par défaut, à savoir le type de retour de `ZeroProcedure::get_key()`.\
Comme cette fonction n'existe pas, la substitution a échouée, et le compilateur a donc sélectionné la fonction candidate suivante, à savoir `get_key(const Procedure&)`.

Pour déclencher des échecs de substitution, vous pouvez vous placer soit au niveau des paramètres de template (type ou valeur par défaut), soit au niveau de la signature de la fonction (type des paramètres ou leurs valeurs par défaut), soit au niveau du type de retour de la fonction.

Choisir ce dernier permet généralement d'utiliser `std::enable_if_t<condition, type>`, ainsi que de nombreux autres utilitaires définis dans `<type_traits>`.\
Voici par exemple une façon de définir une fonction qui n'existe que pour les types entiers :
```cpp
#include <type_traits>

// La substitution fonctionne seulement si T est entier.
// La fonction renvoie alors un T.
template <typename T>
std::enable_if_t<std::is_integer_v<T>, T>
add_two(const T value)
{
    return value + 2;
}

// La substitution fonctionne seulement si v1 et v2 sont de mêmes types.
// La fonction renvoie alors un booléen.
template <typename T1, typename T2>
std::enable_if_t<std::is_same_v<T1, T2>>, bool>
are_equal(const T1& v1, const T2& v2)
{
    return v1 == v2;
}
```
