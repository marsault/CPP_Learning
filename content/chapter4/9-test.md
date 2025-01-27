---
title: "Questionnaire"
pre: '<span class="presection-icon">✅</span>'
weight: 100
---

{{% test chapter=4 %}}

Considérons la fonction pour les questions ci-dessous.
```cpp 
int f(int a, int& b, const int& c, int&& d, int* e) 
{ 
    return *(new int{a+b+c+d+*e});
}
```

{{% test_item lines=10 %}} Pour chacune des expressions suivantes, indiquez s'il s'agit d'une L-value ou d'une R-value: 
- `a`, 
- `b`, 
- `c`, 
- `d`, 
- `e`, 
- `*e`, 
- `a+b+c+d+*e`, 
- `new int{a+b+c+d+*e}`; 
- `*(new int{a+b+c+d+*e})`;
{{% /test_item %}}

---

Les questions ci-dessous s'appliquent à la classe `SomeClass` ci-dessous.
```cpp 
class SomeClass {
private:
    int _id;
    std::vector<int> _data;
    std::string* _ptr;
public:
    ~SomeClass() {delete _ptr;}
};
```
{{% test_item %}}
Donner le prototype du constructeur de copie de `SomeClass`.
{{% /test_item %}}

{{% test_item lines=6 %}}
Ecrire le code du constructeur de copie de `SomeClass`, tel que généré par l'implémentation par défaut du compilateur.
{{% /test_item %}}

{{% test_item lines=3 %}}
Expliquer pourquoi cette implémentation va poser des problèmes.
{{% /test_item %}}

{{% test_item %}}
Donner le prototype du constructeur de déplacement de `SomeClass`.
{{% /test_item %}}

{{% test_item lines=6 %}}
Ecrire un constructeur de déplacement correct pour `SomeClass`.
{{% /test_item %}}

{{% test_item lines=6 %}}
Ecrire le code du constructeur de déplacement de `SomeClass`, tel que généré par l'implémentation par défaut du compilateur.
{{% /test_item %}}

{{% test_item lines=3 %}}
Expliquer pourquoi cette implémentation va poser des problèmes.
{{% /test_item %}}

{{% test_item lines=6 %}}
Ecrire un constructeur de déplacement correct pour `SomeClass`.
{{% /test_item %}}

{{% test_item lines=2 %}}
Donner les prototypes de l'opérateur d'affectation par copie et de l'opérateur d'affectation par déplacement de `SomeClass`.
{{% /test_item %}}

{{% test_item lines=2 %}}
Doit-on les implémenter pour la classe `SomeClass` ? Pourquoi ?
{{% /test_item %}}


{{% test_item lines=6 %}}
Ecrire le constructeur de `SomeClass` qui prend trois arguments (un entier, un tableau dynamique d'entier et une chaine de caractère) pour initialiser les trois attributs de `SomeClass`.
{{% /test_item %}}

---

Voici deux implémentations de la fonction `main`.  On suppose que la classe `SomeOtherClass` est implémentée pour qu'il compile.
```cpp
int main() {
    SomeOtherClass a;
    SomeOtherClass b;
    b = a;
}

int main() {
    SomeOtherClass a;
    SomeOtherClass b = a;
}
```

{{% test_item lines=3 %}}
Est-ce qu'il sont équivalents? Expliquer en précisant quelles fonctions vont être appelées.
{{% /test_item %}}

{{% /test %}}
