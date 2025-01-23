---
title: "Spécialisations"
pre: '<span class="presection-icon">🤯</span>'
weight: 3
---

Cette section sera consacrée à la spécialisation de templates de fonctions et de classes.

Une spécialisation est la redéfinition d'une entitée templatée, qui va s'appliquer pour des paramètres particuliers.
Il y a de nombreux cas d'utilisation des spécialisation, l'un d'entre eux étant de définir de traiter des cas particuliers. 

---

### Spécialisation de fonctions

Soit la fonction templatée suivante, permettant d'afficher des valeurs dans le terminal :
```cpp
template <typename T> 
void print(const T& value)
{
    std::cout << value << std::endl;
}
```

Si on lui passe des booléens, cette fonction affichera 0 ou 1.\
On peut donc décider de spécialiser la fonction afin qu'elle écrive plutôt "false" ou "true".

Voici la syntaxe pour spécialiser la fonction `print` dans ce cas :
```cpp
template <>                     // on écrit des chevrons vides
void print(const bool& value)   // on écrit le type attendu (ici bool) à la place du T de la signature précédente
{
    std::cout << (value ? "true" : "false") << std::endl;
}
```

{{% notice note %}}
Notez que pour qu'une spécialisation puisse être utilisée, il faut que le compilateur trouve sa déclaration avant son usage.
S'il ne la trouve pas, alors il utilisera le template de base pour générer le code de la fonction, et vous pourrez vous retrouver au mieux avec des erreurs de compilation ou de link qui vous avertit du problème, au pire avec des bugs au runtime que vous aurez du mal à identifier.\
{{% /notice %}}

Supposons maintenant que notre template a plusieurs paramètres.\
```cpp
template <typename Animal, typename Food> 
void eat(const Animal& animal, const Food& food)
{
    std::cout << animal.name() << " eats " << food.name() << std::endl;
}
```

Pour spécialiser la fonction, on peut écrire quelque chose comme :
```cpp
template <> 
void eat(const Mosquito& mosquito, const CarnivorousPlant& plant)
{
    std::cout << plant.name() << " eats " << mosquito.name() << std::endl;
}
```

Sachez enfin que lorsqu'on spécialise une fonction, on doit forcément spécialiser l'entièreté des paramètres de template.
On parle de **spécialisation totale**.

On ne peut donc **pas** écrire :
```cpp
template <typename Food> 
void eat(const Mosquito& mosquito, const Food& food)
{
    std::cout << mosquito.name() << " maybe gets eatten by " << food.name() << std::endl;
}
```

---

### Spécialisation de classes

Contrairement aux fonctions, il est possible de spécialiser des classes aussi bien totalement que partiellement.\
Il est également possible de spécialiser seulement certaines fonctions à l'intérieur d'une classe template.

#### Spécialisation totale

Commençons par la spécialisation totale.
Celle-ci permet de redéfinir en intégralité la façon dont la classe est implémentée.
Cela signifie qu'il faut réécrire tous les champs et fonctions du template initial si vous souhaitez pouvoir vous en servir.

```cpp
template <typename T>
class Container
{
public:
    void add(const T& value)
    {
        _values.emplace_back(value);
    }

    void print_all() const
    {
        for (const auto& v: _values)
        {
            std::cout << v << std::endl;
        }
    }

private:
    std::vector<T> _values;
};

template <>             // on écrit des chevrons vides ici
class Container<char>   // on écrit à nouveau des chevrons, contenant les valeurs des paramètres spécialisés
{
public:
    void add(char c)
    {
        _string += c;
    }

    void print() const
    {
        std::cout << _string << std::endl;
    }

private:
    std::string _string;
}

int main()
{
    Container<char> ctn;
    ctn.add('h');
    ctn.add('e');
    ctn.add('y');
    ctn.print();     // --> "hey"
    ctn.print_all(); // --> Ne compile pas, print_all n'est pas définie dans Container<char>...

    return 0;
}
```

#### Spécialisation partielle

Supposons que vous ayiez N paramètres de template, mais que vous ne souhaitiez en spécialiser qu'un certain nombre.\
Voici la syntaxe à utiliser :
```cpp
template <typename T1, typename T2, typename T3, typename T4>
struct SomeTemplate
{
    ...
};

template <typename T2, typename T4>             // on réécrit uniquement les paramètres que l'on ne souhaite pas spécialiser 
struct SomeTemplate<bool, T2, std::string, T4>  // on écrit tous les paramètres entre chevrons, en remplaçant ceux que l'on a spécialisé 
{
    ...
};
```

En plus de pouvoir spécialiser seulement une partie des paramètres, la spécialisation partielle permet également de spécialiser une classe à partir d'autres classes template.
Par exemple, il est possible de spécialiser une classe-template pour un conteneur particulier, sans forcément spécifier le contenu du conteneur :
```cpp
template <typename Ctn>
class ManyContainers
{
public:
    void add(Ctn&& ctn)
    {
        _containers.emplace_back(std::move(ctn));
    }

    auto get(size_t ctn_idx, size_t inner_idx) const
    {
        return *std::next(_containers[ctn_idx].begin(), inner_idx);
    }

private:
    std::vector<Ctn> _containers;
};

template <typename Value>                   // le type contenu dans le vector reste générique
class ManyContainers<std::vector<Value>>    // et on utilise ce type pour écrire la spécialisation
{
public:
    void add(const std::vector<Value>& ctn)
    {
        _begins.emplace_back(_values.size());
        _values.insert(ctn.begin(), ctn.end());
    }

    auto get(size_t ctn_idx, size_t inner_idx) const
    {
        return _values[_begins[ctn_idx] + innner_idx];
    }

private:
    std::vector<Value>  _values;
    std::vector<size_t> _begins;
};
```

#### Spécialisation de fonction-membres

Supposons que vous ayiez une classe-template dont vous aimeriez redéfinir seulement certaines fonctions membres.
```cpp
template <typename T>
struct Printer
{
    void print(std::ostream& stream, const T& value) const
    {
        stream << value;
    }

    void print_line(std::ostream& stream, const T& value) const
    {
        print(stream, value);
        stream << std::endl;
    }

    template <typename BeginIt, typename EndIt>
    void print_many(std::ostream& stream, BeginIt it, const EndIt& end) const
    {
        while (it != end)
        {
            print(stream, *it);
            stream << ",";
            ++it;
        }
    }
};
```

Voici la syntaxe associée :
```cpp
template <>
void Printer<bool>::print(std::ostream& stream, const bool& value) const
{
    stream << (value ? "true" : "false");
}
```

{{% notice warning %}}
Comme pour la spécialisation de fonctions libres, il n'est pas possible de spécialiser partiellement des fonctions-membre.
{{% /notice %}}
