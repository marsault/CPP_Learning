---
title: "Polymorphisme"
pre: '<span class="presection-icon">👥</span>'
weight: 4
---

Vous avez probablement déjà entendu le terme **polymorphisme**, vous l'avez peut-être même déjà utilisé, mais quand vous y réfléchissez, si on vous demandait
de le définir clairement, vous ne sauriez pas forcément quoi répondre. Cette page sera donc l'occasion de revenir sur sa définition.

Dans ce chapitre, nous nous sommes intéressés à deux manières de mettre-en-ouvre le polymorphisme en C++ : l'héritage statique et l'héritage dynamique.
Nous détaillerons les différences entre les deux et dans quels cas utiliser l'un ou l'autre. 

---

### Polymorphisme

En programmation, le polymorphisme est un concept consistant à fournir une interface unique pouvant accepter des objets de types différents (merci Wikipédia).

La surcharge est donc un type de polymorphisme, puisque du point de vue de l'utilisateur, si on écrit `std::cout << "aaaaaah"` ou `std::cout << 3`, on a l'impression
d'utiliser la même fonction (ou en tout cas, le même algorithme), bien qu'on ne passe pas des arguments du même type.

Le terme polymorphe peut également faire référence à un objet. Dans ce cas, cela signifie qu'il est possible de faire référence à cet objet via différents types.
Par exemple, si une classe `Dog` hérite de `Animal`, et qu'on instancie un objet `Dog dog`, alors `dog` est polymorphe, puisqu'on peut le référencer aussi bien depuis `Dog` que depuis `Animal`.

Enfin, on pourra également parler de classe polymorphe. En C++, ce terme sera employé pour désigner les classes contenant des fonctions virtuelles. On ne parlera donc pas de classes polymorphes
pour de l'héritage statique.

---

### L'héritage statique

L'héritage statique est une forme de sous-typage un peu particulière, puisqu'elle n'est pas faite pour modifier le comportement des classes dérivées.
Son seul et unique intérêt, c'est de partager du code entre plusieurs classe, par exemple pour éviter la duplication, ou encore pour employer du code déjà prêt et testé.

Il existe deux grandes manières de partager du code entre des classes :
1. L'héritage statique, comme nous venons de le voir, qui permet à une classe d'hériter de l'ensemble des champs (attributs et fonctions) d'une autre classe,
2. La **composition**, c'est-à-dire que l'on place dans sa classe un attribut du type dont on souhaite pouvoir réutiliser le code.

La composition permet une meilleure maîtrise de ce que l'on souhaite exposer de l'attribut.
En effet, il suffit de définir les fonctions-membres que l'on souhaite exposer, et d'appeler dedans la fonction-membre correspondante de l'attribut.
Vous devriez donc préférer la composition à un héritage statique, dès lors que vous ne souhaitez pas exposer l'intégralité de l'interface du type à réutiliser
(meilleure encapsulation, et donc plus simple d'enforcer les invariants de classe).

Voici un exemple permettant d'illustrer un cas d'utilisation pour un héritage statique, et un cas d'utilisation pour une composition :

```cpp
// Shared class
class SharedStuff
{
public:
    void set_stuff1(int stuff1)   { _stuff1 = stuff1; }
    void set_stuff2(float stuff2) { _stuff2 = stuff2; }

private:
    int   _stuff1 = 0;
    float _stuff2 = 0.f;
};

// Static inheritance
class OMGYouReallyGotALotOfStuff : public SharedStuff
{
public:
    void set_stuff3(char stuff3) { _stuff3 = stuff3; }

private:
    char _stuff3 = '\0';
};

// Composition
class DontBuyMoreStuffIfYouCantKeepItNeat
{
public:
    void set_stuff1(int stuff1)
    {
        if (check_room_tidy())
        {
            _the_stuff.set_stuff1(stuff1);
            _is_tidy = false;
        }
    }

    void set_stuff2(float stuff2)
    {
        if (check_room_tidy())
        {
            _the_stuff.set_stuff2(stuff2);
            _is_tidy = false;
        }
    }

    void tidy_the_room() { _is_tidy = true; }

private:
    bool check_room_tidy() const
    {
        if (!_is_tidy)
        {
            std::cerr << "Clean your room before starting to put new stuff in it!" << std::endl;
            return false;
        }

        return true;
    }

    SharedStuff _the_stuff;
    bool        _is_tidy = false;
};
```

---

### Héritage dynamique et classes polymorphes

L'intérêt de l'héritage dynamique, c'est de pouvoir définir des interfaces génériques (= polymorphisme), dans lesquelles une ou plusieurs parties de l'algorithme vont être spécialisées en fonction du type réel de l'objet passé en paramètre.
Sans ce mécanisme, le C++ ne serait plus vraiment un langage orienté-objet. Il s'agit donc de quelque chose de très important, mais qu'il faut apprendre à manipuler avec soin :
- il faut penser à rendre le destructeur de la classe de base virtuel,
- il faut penser à écrire override sur les fonctions redéfinies,
- il faut comprendre comment les virtual tables sont construites pour savoir quelle fonction sera exécutée,
- il faut faire attention à passer ses objets par références (ou par pointeurs dans les conteneurs) pour que les appels virtuels soient correctement exécutés,
- etc.

{{% notice note %}}
Il faut savoir qu'un appel virtuel est beaucoup plus coûteux à réaliser à l'exécution qu'un appel de fonction classique : il faut accéder à la VTable de l'objet, récupérer le pointeur sur la bonne fonction, jumper à la bonne adresse (potentiellement à l'autre bout de la mémoire du programme), mettre les instructions de cette fonction dans le cache du processeur, etc.\
Lorsque l'appel n'est pas virtuel, des mécanismes permettent d'optimiser beaucoup plus facilement le code, par exemple, l'inlining de fonction, ou l'anticipation de la mise en cache des instructions grâce à la prédiction.\
Du coup, n'hésitez pas à utiliser des fonctions virtuelles, mais évitez de les utiliser pour tout et n'importe quoi. Par exemple, un getter n'a pas besoin d'être virtuel si vous stocker le membre à retourner dans la classe de base.
{{% /notice %}}
