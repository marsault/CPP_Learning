---
title: "Ownership"
pre: '<span class="presection-icon">🏘️</span>'
weight: 5
---

Jusqu'ici, nous vous avons expliqué que contrairement au Java, les données que vous instanciez ne restent pas magiquement en vie tant que vous en avez besoin.  
C'est donc à vous de garantir que vos données ne seront pas désinstanciées avant d'avoir fini de les utiliser.  
Sur cette page, nous allons introduire le concept d'**ownership**, qui vous aidera à mieux architecturer votre code pour éviter de vous retrouver avec des dangling-references.

---

### C'est quoi l'ownership ?

Littéralement, **ownership** signifie **propriété** (au sens de la possession de quelque chose).

En pratique, dans le domaine de la programmation, le **owner** (ou le **propriétaire**) d'une donnée est l'élément qui a la responsabilité de la désinstancier une fois qu'elle n'est plus utile au programme.

Nous allons vous montrer quelques exemples, afin que vous puissiez un peu mieux comprendre ce concept assez abstrait.  
Au fur et à mesure des exemples, nous établirons le **graphe d'ownership** correspondant, c'est-à-dire la représentation graphique illustrant les relations d'ownership présentes au sein du programme.

#### Variable locale

Une variable locale est désinstanciée lorsqu'on sort du bloc dans lequel elle est définie.

```cpp
void fcn()
{
    int a = 3;
}
```

Dans l'exemple ci-dessus, `a` est désinstanciée à la sortie de `fcn`.  
On pourra donc dire que la donnée portée par `a` est ownée par la fonction `fcn`, ou encore que `fcn` own `a`.

![Variable locale](/images/chapter3/ownership/01-local-var.svg)

#### Attribut-valeur

La donnée portée par un attribut-valeur est désinstanciée lorsque l'instance de la classe est détruite.

```cpp
struct MyStruct
{
    int value = 0;
};

int main()
{
    MyStruct s { 5 };
    return 0;
}
```

Ici, la donnée portée par l'attribut `value` de l'instance `s` est ownée par `s`.  
On peut dire plus simplement que `s` own `s.value`.

![Attribut-valeur](/images/chapter3/ownership/02-value-attribute.svg)

#### Attribut-référence

Ici, ça devient un peu plus compliqué !

```cpp
struct Driver
{
};

struct Car
{
    Driver& driver;
};

int main()
{
    Driver gontrand;
    Car clio { gontrand };

    return 0;
}
```

La donnée portée par `clio.driver` correspond à la variable `gontrand` définie dans le `main`.  
Le owner de `clio.driver` n'est donc pas `clio`, puisque la destruction de `clio` n'entrainera pas la destruction de `gontrand`.  
Dans ce cas précis, c'est la fonction `main` qui own le contenu de `clio.driver`.

![Attribut-référence](/images/chapter3/ownership/03-ref-attribute.svg)

#### Ressources gérées par une classe

Lorsque le cycle de vie d'une ressource (mémoire, fichier, connexion réseau, etc) stockée à l'intérieur d'un objet est orchestré par les fonctions-membres de cet objet, alors ces ressources sont ownées par l'objet.

Prenons ici l'exemple d'un `std::vector`.  
```cpp
std::vector<Driver> drivers;
drivers.emplace_back();
drivers.emplace_back();
drivers.emplace_back();
```

Chacun des `Driver` faisant partie du tableau est stocké sur un segment-mémoire alloué dynamiquement par l'objet `drivers`.  
Ce segment sera libéré à la destruction de `drivers` (ou plus tôt, en fonction des fonctions qu'on appelera sur l'objet), entraînant la désinstanciation des `Drivers`.  
On peut donc dire que `drivers` own chacun des éléments de type `Driver` ajoutés via l'appel à `emplace_back`.

![std::vector](/images/chapter3/ownership/04-vector.svg)



#### Pointeur(-observant)

Un **pointeur** n'est pas ownant.  Comme les références, ils servent simplement à référencer des données pré-existantes.  
Si un pointeur est désinstanciée, la donnée pointée ne l'est généralement pas !

Mais du coup, vous devez vous demander quel est leur intérêt, sachant qu'on a déjà les références...  
Eh bien les références ne permettent pas de faire autant de choses que les pointeurs.  
Par exemple, vous ne pouvez pas créer de référence qui ne référence rien, alors qu'un pointeur peut être vide :
```cpp
int& ref_on_nothing;
// => Aïe, ça compile pas

int* ptr_on_nothing = nullptr;
// => Ok
```
Une fois une référence définie, celle-ci référencera la même donnée pour toujours, tandis qu'un pointeur est réassignable :
```cpp
int& ref = data_1;
ref = data_2;
// => ref fait toujours référence à data_1, le contenu de data_2 a simplement été assigné à data_1 

int* ptr = &data_1;
ptr = &data_2;
// => data_1 n'a pas changé et ptr pointe désormais sur data_2
```

Comment pourriez-vous dessiner le graphe d'ownership du programme suivant, une fois arrivé à la ligne 8 :
```cpp {linenos=table}
int main()
{
    auto toto = Driver {};
    auto jacquot = Driver {};
    auto leon = Driver {};
 
    auto all_drivers = std::vector<const Driver*> { &toto, &jacquot, &leon };

    return 0;
}
```
<br/>
{{% hidden-solution %}}
Les éléments de `all_drivers` étant des pointeurs, on utilise un contour plein pour les cases du tableau.  
En revanche, comme ces pointeurs ne contrôlent pas le cycle de vie de chacun des `Drivers`, on les relie vers eux avec des flèches en pointillé.
![Pointeur-observant](/images/chapter3/ownership/06-observing-ptr.svg)
{{% /hidden-solution %}}

---
#### Pointeur-ownant

En C++, rien  n'est simple, et les pointeurs sont parfois des **pointer-ownant**, c'est-à-dire des pointeurs responsables de la ressource pointée.
C'est généralement déconseillé et on trouve ça plutôt dans le code légacy.  Si on veut un pointer qui own la ressource pointée, on utilise plutôt des `std::unique_ptr` que l'on verra dans le [chapitre 5](chapter5).

Un pointer est ownant s'il gère *manifestement* la donnée pointée.  Le problème avec cette phrase est le "manifestement", qui demande d'analyser le code en détail.

```cpp
int* get_int(int value)
{
    auto* ptr = new int { value };
    return ptr;
}

void calling_function()
{
    auto* five = get_int(5);
    std::cout << *five << std::endl; 
    delete five; // Doit-ton détruire five ou pas ?
}
```

Dans le code ci-dessus, à l'intérieur de la fonction `get_int`, `ptr` est un pointeur-ownant.
En effet, on l'a défini dans l'objectif de stocker l'adresse d'un bloc mémoire fraîchement alloué pour stocker un entier.
Il devrait par conséquent *manifestement* responsable du cycle de vie de cet entier.
Puisque `get_int` renvoie ce pointeur, c'est ensuite `calling_function` qui en devient *manifestement* responsable, puisqu'il détruit.

On voit bien que c'est une mauvaise pratique.  Imaginons que c'est à vous d'écrire `calling_function`. Pour savoir si vous devez détruire `five` ou on, il faut analyser le code de `get_int`.
Par exemple, si on implémente `get_int` comme en dessous, il ne faudrait pas.

```cpp
std::vector<int*> my_int_vect;

int* get_int(int value)
{
    for (auto p : my_int_vect) 
    {
        if (*p == value)
            return p
    }
    return nullptr;
}
```

Dans cette seconde implémentation, il est probable que c'est `my_int_vect` qui soit responsable de libérer le pointeur retourné par `get_int` (et ça n'a rien de manifeste).

{{% notice warning %}}
Sans preuve du contraire, il faut considérer un pointeur comme observant.
En effet, c'est le comportement par défaut: la destruction d'un pointeur n'entraine **pas** la destruction de la donnée pointée.
Pour qu'un pointeur soit ownant, il faut en avoir une preuve *manifeste*.
{{% /notice %}}

### Exercices pratiques

Nous allons maintenant vous présenter quelques petits bouts de code.  
Vous devrez dessiner le graphe d'ownership correspondant à l'état du programme aux instructions indiquées, et en déduire les éventuels problèmes s'il y en a.  
Si vous souhaitez dessiner vos graphes sur ordinateur, vous pouvez utiliser [draw.io](https://app.diagrams.net/).

<!-- Pour cela, vous pourrez vous appuyer sur les règles d'architecture suivantes :
- Chaque donnée doit avoir un seul et unique owner (=> une unique flèche pleine arrive sur chaque case)
- Toutes les références mènent à une donnée valide (=> pas de flèche qui pointe sur une case rouge)
- Si un pointeur est ownant, sa donnée sera correctement libérée **ou bien** il transfèrera l'ownership à un autre pointeur (pas les deux) -->

#### Cas n°1

```cpp {linenos=table}
int& get_max(int& a, int& b)
{
    return a < b ? a : b;
}

int main()
{
    int  v1 = 3;
    int  v2 = 6;
    int& max = get_max(v1, v2);

    std::cout << max << std::endl;
    return 0;
}
```

1. Dessinez le graphe d'ownership à la ligne 3, lorsque le `main` vient d'appeler `get_max`.
{{% hidden-solution %}}
![](/images/chapter3/ownership/07-case-1a.svg)
{{% /hidden-solution %}}

2. Dessinez maintenant le graphe d'ownership associé au retour de la fonction `get_max` dans le `main`.  
{{% hidden-solution %}}
Il faut faire pointer la variable-référence `max` sur `v2`, et non sur `b`.  
En effet, `b` n'est pas une donnée, juste un alias, on ne peut donc pas faire pointer une référence dessus.
![](/images/chapter3/ownership/07-case-1b.svg)
{{% /hidden-solution %}}

3. Redessinez le graphe correspondant au retour de la fonction `get_max`, mais en supposant que `get_max` attende ses paramètres par valeur.
Le résultat est par contre toujours retourné par référence.
{{% hidden-solution %}}
Les paramètres `a` et `b` sont maintenant des données.  
La variable-référence `max` pointera donc sur `b` et plus sur `v2`.
![](/images/chapter3/ownership/07-case-1c.svg)
{{% /hidden-solution %}}

4. Quel problème est mis en avant par ce graphe ?
{{% hidden-solution %}}
On a une référence qui pointe sur une donnée qui été désinstanciée : il s'agit d'une dangling-reference.  
Or cette référence est utilisée ligne 12, on a donc un undefined behavior... 
{{% /hidden-solution %}}

#### Cas n°2

```cpp {linenos=table}
struct Animal
{
    std::string name;
};

struct ManyAnimals
{
    ~ManyAnimals()
    {
        for (auto* a: animals)
        {
            delete a;
        }
    }

    std::vector<Animals*> animals;
};

void display_animals(ManyAnimals many_animals)
{
    for (auto* a: many_animals.animals)
    {
        std::cout << a->name << std::endl;
    }
}

int main()
{
    ManyAnimals many_animals;
    many_animals.emplace_back(new Animal { "dog" });
    many_animals.emplace_back(new Animal { "cat" });
    many_animals.emplace_back(new Animal { "mouse" });

    // display_animals(many_animals);

    return 0;
}
```

1. Établissez le graphe d'ownership du programme à la ligne 33.  
Selon-vous, les pointeurs contenus dans `ManyAnimals::animals` sont-ils ownants ou observants ? 
{{% hidden-solution %}}
Le destructeur de `ManyAnimals` se charge de libérer la mémoire associée à chacun des pointeurs contenus dans l'attribut `animals`.  
Ces pointeurs étant utilisés pour gérer le cycle de vie des données pointées, il s'agit de pointeurs-ownants.  
On représente donc les relations associées avec des flèches pleines.
![](/images/chapter3/ownership/07-case-2a.svg)
{{% /hidden-solution %}}

2. Dessinez maintenant les modifications dans ce graphe une fois arrivé à la ligne 14 (c'est-à-dire pendant la sortie du `main`, lorsque l'instance de `many_animals` est en cours de destruction).
{{% hidden-solution %}}
À la ligne 14, les instances de `Animal` ont toutes été libérées.  
![](/images/chapter3/ownership/07-case-2b.svg)
{{% /hidden-solution %}}

3. La ligne 34 est commentée, car si elle ne l'est pas, le programme se termine avec une erreur.  
Pour comprendre ce qu'il se passe, reprenez le graphe de la question 1, et ajoutez les modifications décrivant l'état du programme une fois arrivé dans la fonction `display_animals` (ligne 20).  
Quel est le problème dans ce graphe ?
{{% hidden-solution %}}
L'argument est passé par valeur, on a donc une copie de la variable `many_animals`.  
En revanche, lorsqu'un pointeur est copié, l'élément pointé ne l'est pas.
![](/images/chapter3/ownership/07-case-2c.svg)
Le problème ici, c'est qu'on a maintenant deux owners pour les données `dog`, `cat` et `mouse`.
{{% /hidden-solution %}}

4. Dessinez maintenant le graphe à la sortie de la fonction `display_animals`.  
Expliquez ce qui pose problème et qui empêche le programme de se terminer correctement.
{{% hidden-solution %}}
À la fin de `display_animals`, on désinstancie le paramètre `many_animals`, ainsi que les données qu'il own récursivement.
![](/images/chapter3/ownership/07-case-2d.svg)
Les pointeurs contenus dans `many_animals.animals` (la variable du `main`) pointent donc sur des données invalidées.  
À la destruction de `many_animals`, les instructions `delete a` vont par conséquent échouer.
{{% /hidden-solution %}}

5. Proposez une solution pour résoudre le problème et dessinez le graphe d'ownership associé.
{{% hidden-solution %}}
Il suffit de changer la signature de `display_animals` pour passer le paramètre par référence (qui peut d'ailleurs être constante).
Les références n'ayant pas d'impact sur le cycle de vie des données, lorsque l'on sort de la fonction, aucun élément ne sera désinstancié.
![](/images/chapter3/ownership/07-case-2e.svg)
{{% /hidden-solution %}}

---

### Synthèse

- L'élément responsable du cycle de vie d'une donnée est son **owner**.
- Une classe own ses champs qui ne sont pas des références.
- Une fonction own ses variables locales qui ne sont pas des références.
- Un **pointeur** est généralement **observant**, c'est-à-dire qu'il n'own pas la donnée pointée.  Dans ce cas, il a le même rôle qu'une référence, si ce n'est qu'il peut être vide (= `nullptr`) et est réassignable.  
- Un **pointeur** peut néanmoins être **ownant** dans certains cas.  Dans une classe, c'est souvent parce que le destructeur de la classe détruit explicitement les données pointées.
- Un graphe d'ownership permet de détecter différents problèmes :
  - Si une donnée est ownée par plusieurs éléments ➔ libération multiple,
  - Si on référence une donnée qui n'existe plus ➔ dangling-reference.
- Savoir qui own une donnée aide à savoir s'il est valide d'y accéder ou pas.
