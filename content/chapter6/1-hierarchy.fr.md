---
title: "Hiérarchie professionnelle"
pre: '<span class="presection-icon">💼</span>'
weight: 1
---

Dans cette première partie, vous apprendrez comment définir des relations de parenté entre vos classes.\
Nous ne parlerons sur cette page que d'héritage dit "statique", c'est-à-dire que nous ne chercherons pas à modifier dans les **classes-fille** le comportement hérité de la **classe-mère**.

---

Pour cet exercice, on utilisera  vous modifierez les fichiers :
- `1-hierarchy/Boss.cpp`
- `1-hierarchy/Boss.h`
- `1-hierarchy/Staff.cpp`
- `1-hierarchy/Staff.h`
- `1-hierarchy/Intern.cpp`
- `1-hierarchy/Intern.h`

se trouvant dans [code.zip](../code.zip).

La cible à compiler est `hierarchy`.

---

### Définir une classe-mère

Commencez par jeter un coup d'oeil à chacun des fichiers fournis.\
Comme vous pouvez le constater, les différentes classes partagent beaucoup de code.

Vous allez commencer par créer une classe contenant l'ensemble du code dupliqué par les autres classes.
Placez-la dans un ou des fichiers séparés et modifiez le CMakeLists.txt (celui dans chap-04) pour qu'il les ajoute bien à la compilation de l'exécutable.
Pour le nom de la classe, essayez de trouver quelque chose qui soit digne de son contenu.

{{% hidden-solution %}}
Afin de pouvoir retourner le grade (`get_rank()`) de chaque employé, on ajoute un attribut `_rank` à la classe.\
Et on n'oublie pas de définir un constructeur pour initialiser chacun des membres de la nouvelle classe.

```cpp
#include "Rank.h"

#include <string>

class Employee
{
public:
    Employee(std::string name, std::string surname, unsigned int salary, Rank rank)
        : _name { std::move(name) }
        , _surname { std::move(surname) }
        , _salary { salary }
        , _rank { rank }
    {}

    const std::string& get_name() const { return _name; }
    const std::string& get_surname() const { return _surname; }

    unsigned int get_salary() const { return _salary; }
    void         increase_salary(unsigned int raise) { _salary += raise; }

    Rank get_rank() const { return _rank; }

private:
    const std::string _name;
    const std::string _surname;
    unsigned int      _salary;
    Rank              _rank;
};
```
{{% /hidden-solution %}}

Vous allez maintenant modifier la définition de la classe `Boss` afin de la faire hériter de votre nouvelle classe.
Pour cela, il faut écrire le code suivant :
```cpp
#include "Employee.h"
...

class Boss : public Employee
{
    ...
};
```

La deuxième étape est de supprimer l'ensemble des champs (attributs et fonctions-membres) déjà définies dans la **classe-mère**.\
Il ne devrait vous rester que ceci :
```cpp
class Boss : public Employee
{
public:
    Boss(std::string name, std::string surname, unsigned int salary, bool is_nice);

    void assign_task(Staff& staff) const;
    void ask_coffee(Intern& intern) const;

private:
    bool _is_nice;
};
```

Pour terminer, vous devez modifier l'implémentation du constructeur afin d'appeler le constructeur parent :
```cpp
Boss::Boss(std::string name, std::string surname, unsigned int salary, bool is_nice)
    : Employee { std::move(name), std::move(surname), salary, Rank::TopManagement }
    , _is_nice { is_nice }
{}
```

Comme vous pouvez le constater, c'est un peu la même syntaxe que lorsque vous souhaitez déléguer la construction à un autre constructeur, si ce n'est
que vous devez initialiser vos propres attributs à la suite de l'appel au constructeur de la classe-mère.

Refactorisez maintenant les deux autres classes `Staff` et `Intern` de manière à supprimer le code dupliqué en les faisant hériter de `Employee`.

{{% hidden-solution %}}
Staff.h:
```cpp
#include "Employee.h"

#include <string>

class Staff : public Employee
{
public:
    Staff(std::string name, std::string surname, unsigned int salary);

    void receive_task();
    void complete_task();

    unsigned int get_assigned_tasks() const { return _assigned_tasks; }
    unsigned int get_done_tasks() const { return _done_tasks; }

private:
    unsigned int _assigned_tasks = 0u;
    unsigned int _done_tasks = 0u;
};
```

Staff.cpp:
```cpp
#include "Staff.h"
#include "Rank.h"

Staff::Staff(std::string name, std::string surname, unsigned int salary)
    : Employee { std::move(name), std::move(surname), salary, Rank::Default }
{}

...
```

Intern.h:
```cpp
#include "Employee.h"

#include <string>

class Intern : public Employee
{
public:
    Intern(std::string name, std::string surname, unsigned int salary, bool is_clumsy);

    void fetch_coffee();

    unsigned int get_nb_broken_cups() const { return _nb_broken_cups; }

private:
    bool         _is_clumsy;
    unsigned int _nb_broken_cups = 0u;
};
```

Intern.cpp:
```cpp
#include "Intern.h"
#include "Rank.h"

Intern::Intern(std::string name, std::string surname, unsigned int salary, bool is_clumsy)
    : Employee { std::move(name), std::move(surname), salary, Rank::Slave }
    , _is_clumsy { is_clumsy }
{}

...
```
{{% /hidden-solution %}}

---

### Visibilité de la relation de parenté

Vous vous demandez peut-être pourquoi il fallait mettre `public` devant le nom de la classe-mère au moment de déclarer votre héritage.\
En fait, en C++, il est possible de définir la visibilité d'une relation d'héritage. Celle-ci peut aussi bien être privée que publique.

Par exemple, dans le cas suivant :
```cpp
class Child : private Parent
{
    ...
};
```

Si `Parent` déclare une fonction `get_parent_name()`, alors il ne sera possible d'utiliser cette fonction qu'à l'intérieur de la classe `Child`.\
C'est comme si tous les attributs et fonctions héritées de `Parent` étaient placés dans la partie privée de `Child`.

```cpp
// In member function of Child:
void Child::get_child_name() const
{
    // The following line compile.
    return get_parent_name();
}

// In main function:
int main()
{
    Child child;

    // The following line doesn't compile, because Child is "hiding" the fact that it inherits from Parent. 
    child.get_parent_name();

    return 0;
}
```

A part pour de très rares cas (comme des patterns de programmation un peu particuliers), il est déconseillé d'employer de l'héritage privé, car on peut alors généralement remplacer la relation "is-a" par une relation "has-a", c'est-à-dire une composition.

**Mais dans ce cas, pourquoi avoir aborder le sujet ?**

Tout simplement parce qu'en faisant de l'héritage, vous allez vous retrouver au moins une fois avec une erreur de ce type :
```bash
error: 'some variable or function' is inaccessible within this context
```

La visibilité par défaut dans une `class` est privée.
Cela signifie que si vous ne spécifiez par la visibilité au début de la définition de la classe, tout ce qui se trouve derrière est privée :
```cpp
class A
{
    int _a;                             // -> private by default
    int get_a() const { return _a; }    // -> private by default

public:
    int _b;                             // -> public
    int get_b() const { return _b; }    // -> public
    
private:
    int _b;                             // -> private
    int get_b() const { return _b; }    // -> private
}
```

En C++, on peut aussi utiliser des `struct`.
La seule différence syntaxique avec `class`, c'est que la visibilité par défaut est publique :
```cpp
struct B
{
    int _a;                             // -> public by default
    int get_a() const { return _a; }    // -> public by default

public:
    int _b;                             // -> public
    int get_b() const { return _b; }    // -> public
    
private:
    int _b;                             // -> private
    int get_b() const { return _b; }    // -> private
}
```

Cette visibilité par défaut s'applique également à la relation d'héritage.

```cpp
class A  : B {};    // private inheritance, because the default visibility for a class is 'private'
struct A : B {};    // public inheritance, because the default visibility for a struct is 'public'
```

Donc lorsque vous faites de l'héritage avec des `class`, **n'oubliez pas de placer le mot-clef `public` devant le nom de la classe-mère**.\
Autrement, la relation d'héritage sera privée et le compilateur ne vous laissera pas accéder aux fonctions-membres du parent en dehors de la classe.
