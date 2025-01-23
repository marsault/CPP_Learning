---
title: "Résolution d'appel virtuel"
pre: '<span class="presection-icon">👪</span>'
weight: 3
---

Nous allons maintenant rentrer dans les détails de ce qu'il se passe sous le manteau, lorsque le programme effectue un **appel virtuel**.

---

### Virtual table 

Lorsqu'une classe `Parent` contenant des fonctions virtuelles est compilée, le compilateur va générer pour l'ensemble des classes qui en dérivent une **virtual table**.
Il s'agit d'une tableau qui contient, pour chaque fonction virtuelle de la classe, un pointeur sur la fonction qui sera vraiment appelée.

Analysons la hiérarchie suivante :

```cpp
struct GrandFather
{
    virtual ~GrandFather() {}

    virtual void fcn_a(bool);
            void fcn_b();
    virtual void fcn_c() const;
};

struct Father : GrandFather
{
    void fcn_a(bool);
    void fcn_b();
    virtual void fcn_d();
};

struct Son : Father
{
    void fcn_a(bool);
    void fcn_c();
};

struct GrandSon : Son
{
    void fcn_a(char, int);
    void fcn_c() const;
    void fcn_d();
};
```

{{% notice info %}}
Nous avons volontairement omis les `override`, car le but est d'analyser le comportement du programme pendant un appel de fonction.
Bien entendu, dans un vrai programme, vous devez toujours placer `override` sur une fonction redéfinie.
{{% /notice %}}

Nous allons commencer par déterminer le contenu de la virtual table de `Father`.
Listons d'abord l'ensemble des fonctions virtuelles de son parent `GrandFather` :\
\- `void fcn_a(bool)`\
\- `void fcn_c() const`

Pour chacune de ces fonctions, on regarde dans la classe courante si on trouve une déclaration avec la même signature. C'est le cas pour `fcn_a`, mais pas pour `fcn_c`.
La virtual table de `Father` sera donc la suivante :\
\- `void fcn_a(bool)    -> void Father::fcn_a(bool)`\
\- `void fcn_c() const  -> void GrandFather::fcn_c() const`.

Réalisons maintenant le même travail pour `Son` et `GrandSon`.

Fonctions virtuelles dans la classe `Father`, parent de `Son` :\
\- `void fcn_a(bool)`\
\- `void fcn_c() const`\
\- `void fcn_d();`

{{% notice tip %}}
Pour avoir toutes les fonctions virtuelles de `Father`, on prend toutes les fonctions virtuelles de son propre parent `GrandFather` et on ajoute les fonctions marquées virtuelles dans `Father`.
{{% /notice %}}

Virtual table de `Son` :\
\- `void fcn_a(bool)    -> void Son::fcn_a(bool)`\
\- `void fcn_c() const  -> void GrandFather::fcn_c() const` (car `Son::fcn_c` n'est pas const)\
\- `void fcn_d()        -> void Father::fcn_d()`

Fonctions virtuelles dans la classe `Son`, parent de `GrandSon` :\
\- `void fcn_a(bool)`\
\- `void fcn_c() const`\
\- `void fcn_d();`

Virtual table de `GrandSon` :\
\- `void fcn_a(bool)    -> void Son::fcn_a(bool)` (car `GrandSon::fcn_a` n'a pas le bon nombre de paramètres)\
\- `void fcn_c() const  -> void GrandSon::fcn_c() const`\
\- `void fcn_d()        -> void GrandSon::fcn_d()`

---

### Résolution d'appel

Maintenant que l'on connaît les virtual table, nous allons pouvoir déterminer la fonction appelée sur un objet en fonction de son **type statique** (= type de la variable ou de l'expression) et de son **type dynamique** (= type avec lequel l'objet est construit).

```cpp
Son          real_son;
GrandSon     real_grand_son;
Father       real_father;
GrandFather  real_grand_father;

Father&      son_as_father          = real_son;
Father&      grand_son_as_father    = real_grand_son;
GrandFather& son_as_grand_father    = real_son;
GrandFather& father_as_grand_father = real_father;
```

Considérons l'objet `real_father`.\
Le type statique est `Father`, puisque la variable est de type `Father`.\
Le type dynamique est `Father`, puisqu'il a été construit en tant que `Father`.

Considérons maintenant `son_as_father`.\
Le type statique est toujours `Father`, puisque la variable est de type `Father&`.\
En revanche, le type dynamique est `Son`, puisque l'objet référencé par `son_as_father` est `real_son`, qui a été construit en tant que `Son`.

La résolution d'un appel de fonction se fait en 3 étapes :
1. Le compilateur recherche la fonction appelée dans le type statique de l'objet. S'il ne trouve pas la fonction, il remonte dans la classe du parent, et ainsi de suite.
2. Une fois cette fonction trouvée, il regarde si elle est virtuelle ou non.
3. Si oui, alors la résolution de l'appel est finalisée à l'exécution, en utilisant la virtual table du type dynamique de l'objet.\
Si non, alors la résolution de l'appel s'achève pendant la compilation.

Essayons de prédire ce qu'il va se produire à l'exécution sur quelques exemples.

---

```cpp
son_as_grand_father.fcn_b();
```

1. Le type statique de `son_as_grand_father` est `GrandFather`. Dans la classe `GrandFather`, on trouve la fonction `fcn_b()`.
2. Celle-ci n'est pas virtuelle.
3. Le compilateur décide que l'instruction appelera `GrandFather::fcn_b()`.

---

```cpp
son_as_father.fcn_b();
```

1. Le type statique de `son_as_grand_father` est `Father`. Dans la classe `Father`, on trouve la fonction `fcn_b()`.
2. Celle-ci n'est pas virtuelle, puisqu'elle n'est pas référencée dans la virtual table de `Father`.
3. Le compilateur décide que l'instruction appelera `Father::fcn_b()`.

---

```cpp
son_as_grand_father.fcn_d();
```

1. Le type statique de `son_as_grand_father` est `GrandFather`. Dans la classe `GrandFather`, on ne trouve pas de fonction fonction `fcn_d()`.\
=> L'instruction ne compile pas.

---

```cpp
son_as_father.fcn_d();
```

1. Le type statique de `son_as_father` est `Father`. Dans la classe `Father`, on trouve la fonction `fcn_d()`.
2. Celle-ci est virtuelle.
3. Au moment de l'exécution, le type dynamique de `son_as_father` est `Son`. Dans sa virtual table, `fcn_d()` pointe sur `Father::fcn_d()`, c'est donc cette fonction là qui sera appelée.

---

```cpp
grand_son_as_father.fcn_d();
```

1. Le type statique de `grand_son_as_father` est `Father`. Dans la classe `Father`, on trouve la fonction `fcn_d()`.
2. Celle-ci est virtuelle.
3. Au moment de l'exécution, le type dynamique de `grand_son_as_father` est `GrandSon`. Dans sa virtual table, `fcn_d()` pointe sur `GrandSon::fcn_d()`, c'est donc cette fonction là qui sera appelée.

---

### A vous de jouer

Essayez maintenant de déterminer par vous-mêmes les fonctions qui seront appelées par les instructions ci-dessous.
```cpp
Father& grand_son_as_father = grand_son;
grand_son_as_father.fcn_a('a', 8)   // (1)

GrandSon grand_son;
grand_son.fcn_a(false);             // (2)

grand_son_as_father.fcn_c();        // (3)

Son        son;
const Son& son_cref = son;
son_cref.fcn_c();                   // (4)

GrandFather& son_as_grand_father = son;
son_as_grand_father.fcn_c();        // (5)

Father grand_son_copy_as_father = grand_son;
grand_son_copy_as_father.fcn_d();   // (6)
```

Attention, il y a des vilains pièges, donc vérifiez bien la solution à la fin !

{{% expand "Solution" %}}
1/ Ca ne compile pas.\
La résolution statique n'identifie aucun candidat pour `fcn_a(char, int)` ni dans `Father`, ni dans son parent `GrandFather`.

2/ Ca ne compile pas non plus.\
Lorsqu'on que dans une classe dérivée, on définit une fonction ayant le même nom, mais pas la même signature qu'une fonction de la classe parent, alors cette dernière se retrouve masquée. On parle de **shadowing**. Ici, du coup, on ne peut pas accéder à `fcn_a(bool)` depuis `grand_son`, car `GrandSon` la masque avec `fcn_a(char, int)`.

3/ `GrandSon::fcn_c() const`\
La résolution statique identifie `fcn_c() const` dans `Father` (héritée de `GrandFather`), et celle-ci étant virtuelle, la VTable de `GrandSon` nous renvoie à `GrandSon::fcn_c() const`.

4/ Ca ne compile pas.\
Comme `son_cref` est une référence constante, on ne peut pas appeler `Son::fcn_c()`, et cette dernière masque `GrandFather::fcn_c() const`.

5/ `GrandFather::fcn_c() const`\
La résolution statique identifie `fcn_c() const` dans `GrandFather`, et celle-ci étant virtuelle, la VTable de `Son` nous renvoie à `GrandFather::fcn_c() const`.

6/ `Father::fcn_d()`\
La résolution statique identifie `fcn_d()` dans `Father`.
Comme `grand_son_copy_as_father` n'est pas une référence, il n'y a pas besoin de résolution dynamique : le compilateur peut déduire immédiatement qu'il faut appeler `Father::fcn_d()`.
{{% /expand %}}
