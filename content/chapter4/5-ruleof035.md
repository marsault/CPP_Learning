---
title: "Règle des 0, 3 ou 5"
pre: '<span class="presection-icon">📐</span>'
weight: 5
---


Le compilateur fournit des implémentations par défaut pour les éléments suivants.

1. Destructeur
2. Constructeur de copie
3. Opérateur d'affectation par copie
4. Constructeur de déplacement
5. Opérateur d'affectation par déplacement

{{% notice kind="warning" title="Règle des 0, 3 ou 5 (Rule of 0/3/5)" %}}
Pour une classe donnée, il faut généralement définir à la main :

- **aucun** des cinq éléments ci-dessus;
- les **trois** premiers (destructeur, constructeur de copie et opérateur d'affectation par copie);
- ou les **cinq**.
{{% /notice %}}

Pourquoi ?\
Parce que ces cinq éléments sont interdépendants. Ils définissent la façon dont la classe interagit avec la mémoire.
Pour éviter les problèmes ces interactions doivent êtres cohérentes entre elles.

{{% notice warning %}}
La règle des 0, 3 ou 5 n'est pas absolue et seul votre jugement permet de savoir ce dont vous avez besoin.\
En particulier, il suffit parfois de se poser la question: est-ce que ma modification impacte l'un des quatre autres éléments?
{{% /notice %}}

### Règle des 0

La plupart des classes suivent la règle des 0, c'est-à-dire ne modifient aucun des cinq éléments en haut de page.
En effet, le comportement généré par les implémentations par défaut correspond la gestion usuelle de la mémoire et satisfait la plupart des cas.

### Règle des 3

Au contraire, on veut que certaines classes ne suivent pas la gestion par défaut de la mémoire.  Hormis les exercices sadiques que nous vous imposons, il s'agit usuellement des classes qui définissent des structures de données.



##### Exercice

Par exemple, le fichier [RuleOfThree.cpp](../RuleOfThree.cpp) contient une classe
qui stocke un entier à travers un pointeur ownant.
Pour éviter les fuite mémoire, elle redéfinit son destructeur comme 
indiqué ci-dessous.
```cpp
class RuleOfThree {
public:
    int* int_ptr;
    RuleOfThree(int i) {
      int_ptr = new int{i};
    }
    ~RuleOfThree() { delete int_ptr; }
};

```

Que va-t-il se passer si on copie `RuleOfThree`, par exemple avec le code suivant ?
```cpp
void f(RuleOfThree s) {
  std::cout << *(s.int_ptr) << std::endl;
  // s is destroyed at the end of the function f
}

int main() {
  RuleOfThree r{42};
  
  f(r); // Calling f copies r
        // the copy is destroyed at the end of the call
  std::cout << *(r.int_ptr) << std::endl;

}
```

{{% hidden-solution %}}
Si on copie un `RuleOfThree`, le champs `int_ptr` de l'original et la copie pointerons tous les deux vers la même case mémoire.
Quand `s` est détruit à la fin de la fonction `f`, la case mémoire `s.int_ptr` est désallouée
et donc l'affichage de `*(r.int_ptr)` 

On peut s'en rendre compte en compilant le fichier et en utilisant valgrind:
``` 
    g++ RuleOfThree.cpp -o RuleOfThree
    valgrind ./RuleOfThree
```
Valgrind indique quelque chose comme "Address ... is 0 bytes inside a block of size 4 free'd", ce qui veut dire qu'on accède à de la mémoire libérée.
{{% /hidden-solution %}}


Ecrivez le code du constructeur par copie de `RuleOfThree` pour régler ce problème.

{{% hidden-solution %}}
```cpp
class RuleofThree {
    /* .. */
    RuleOfThree(const RuleOfThree& other) 
    {
      // We allocate a new int and copy the value pointed by other.int_ptr
      int_ptr = new int{*(other.int_ptr)};
    }
    /* .. */
};
{{% /hidden-solution %}}

Des problèmes vont aussi se produire en cas d'utilisation de l'opérateur d'affectation par copie. Quel problème va-t-on rencontrer avec le code suivant?
```cpp
int main() {
  RuleOfThree r{42};
  
  RuleOfThree t{9001};
  r = t;
  *(t.int_ptr) = 0;
  std::cout << *(r.int_ptr) << std::endl; // devrait afficher 9001
  std::cout << *(t.int_ptr) << std::endl; // devrait afficher 0
}
```
Décommentez la fin de la fonction `main` dans le fichier `RuleOfThree.cpp`,
et écrivez l'opérateur d'affectation par copie pour qu'il n'y ai pas de
problème mémoire.

{{% hidden-solution %}}
Après l'affectation par copie, les deux `r.int_ptr` et `t.int_ptr` pointent vers la même case mémoire.
Donc les deux dernières instructions vont afficher la même chose, à savoir 0.
De plus, la mémoire pointée par `r.int_ptr` avant la copie n'a jamais été désallouée.
Notre code produit une fuite mémoire, comme nous l'indique Valgrind dans son "LEAK SUMMARY" avec une indication comme "definitely lost: 4 bytes in 1 blocks".

{{% /hidden-solution %}}

Ecrivez le code de l'opérateur d'affectation par copie de `RuleOfThree` pour résoudre ces problèmes.

{{% hidden-solution %}}
```cpp
class RuleofThree {
    /* .. */
    RuleOfThree& operator=(const RuleOfThree& other) 
    {
      // this object existed before so int_ptr is already allocated
      // we simply copy the value pointed by other.int_ptr
      *int_ptr = *(other.int_ptr);
      return *this;
    }
    /* .. */
};
{{% /hidden-solution %}}

### Règle des 5

Les classes qui suivent la règle des 5 sont celles qui suivent déjà la règle 
des 3 et qui veulent tout de même pouvoir être déplacée efficacement.

En effet, quand on définit un des trois éléments de la règle des 3, le
compilateur ne génère pas d'implémentation par défaut ni pour le constructeur
de déplacement ni pour l'opérateur d'affectation par déplacement.
Ça veut en particulier dire que les instances de cette classe seront toujours
copiée quand elles pourraient être déplacées.

Dans le cas de la classe `RuleOfThree` plus haut, ce n'est pas très grave, car
l'objet pointé est petit.

##### Exercice

Implémenter la règle des 5 pour la classe `RuleOfFive` se trouvant dans le fichier [RuleOfFive.cpp](../RuleOfFive.cpp).

{{% hidden-solution title="toto" %}}
```cpp
class RuleOfFive {
  /* .. */

  RuleOfFive(const RuleOfFive& other)
  : vect_ptr{new std::vector<int>{*(other.vect_ptr)}}
  {}

  RuleOfFive& operator=(const RuleOfFive& other) 
  {
    (*vect_ptr) = *(other.vect_ptr);
    return *this;
  } 


  RuleOfFive(RuleOfFive&& other) 
  : vect_ptr{new std::vector<int>{std::move(*(other.vect_ptr))}}
  {}

  RuleOfFive& operator=(RuleOfFive&& other) 
  {
    (*vect_ptr) = std::move(*(other.vect_ptr));
    return *this;
  }

  /* .. */
};
```
{{% /hidden-solution %}}
