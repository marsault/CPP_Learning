---
title: "Questionnaire"
pre: '<span class="presection-icon">✅</span>'
weight: 100
---

{{% test chapter=2 %}}

{{% test_item %}}
Quel est le terme C++ permettant de désigner les "méthodes" d'une classe ?
{{% /test_item %}}

{{% test_item %}}
Citez une règle permettant de respecter le principe d'encapsulation en C++.
{{% /test_item %}}

---

{{% test_item %}}
Quel nom donne-t-on au constructeur d'une classe acceptant 0 paramètre ?
{{% /test_item %}}

{{% test_item %}}
Dans un constructeur, comment s'appelle la zone dans laquelle on initialise les attributs de la classe ?
{{% /test_item %}}

{{% test_item %}}
A quoi fait-on référence lorsque l'on parle d'implémentation par défaut ?
{{% /test_item %}}

---

{{% test_item %}}
Supposons une fonction-membre `bool hello() const` définie dans une classe `Greetings`.  
Que faut-il écrire pour l'implémenter dans un .cpp séparé ?
{{% /test_item %}}

{{% test_item %}}
Soit un attribut déclaré par `static float _attr` dans une classe `UneClasse`.  
Comment faut-il faire pour le définir ?
{{% /test_item %}}

{{% test_item %}}
La ligne `static int Toto::fcn_static() { return 1; }` placée dans un fichier `Toto.cpp` ne compile pas.
Pourtant, `fcn_static` a été déclarée comme il faut dans la classe `Toto` et l'include a été fait.  
Quel est le problème ?
{{% /test_item %}}

---

{{% test_item %}}
Donnez la signature de l'opérateur `<<` que l'on doit définir pour afficher notre classe `Cat` grâce à un flux de sortie.
{{% /test_item %}}

{{% test_item %}}
Quelle instruction permet de définir un alias `SmallerName` sur le type suivant : `std::unique_ptr<std::array<std::string, 3>>` 
{{% /test_item %}}

---

Les deux prochaines questions font référence à cette classe :
```cpp
class Toto
{
public:
    Toto() : Toto(3), _value2(5)
    {}

    Toto(int v1) : _value1(v1)
    {}

private:
    int _value1;
    int _value2;
}
```

{{% test_item %}}
Ce code ne compile pas pour deux raisons. Quelles sont-elles ?
{{% /test_item %}}

{{% test_item %}}
Identifiez un autre problème lié au constructeur à 1 paramètre.  
Il ne s'agit pas d'un problème de compilation.
{{% /test_item %}}

---

On considère une classe `Dog` dont le *header* est donné ci-dessous.   On suppose toutes les fonctions implémentées dans un cpp non-donné.
```cpp
class Dog
{
public:
    Dog();
    Dog(int v1, int v2);

    void set(int v);
    int get() const;

    static void call(const Dog& d);

private:
    void move();
    static void speak();
    int _age = 0;
};
```
Est-ce que chacune des `main` ci-dessous compile et pourquoi?



{{% test_item %}}`int main(){ Dog d { -1, 3 }; }`
{{% /test_item %}}

{{% test_item %}}`int main(){ const Dog d; d.set(8); }`
{{% /test_item %}}

{{% test_item %}}`int main(){ const Dog d; auto v = d.get(); }`
{{% /test_item %}}

{{% test_item %}}`int main(){ auto a = Dog::get(); }`
{{% /test_item %}}

{{% test_item %}}`int main(){ Dog d; d.call(d); }`
{{% /test_item %}}

{{% test_item %}}`int main(){ Dog d; d.move(); }`
{{% /test_item %}}

{{% test_item %}}`int main(){ Dog::speak(); }`
{{% /test_item %}}

{{% test_item %}}`int main(){ const Dog d; int age = d._age; }`
{{% /test_item %}}



{{% /test %}}



