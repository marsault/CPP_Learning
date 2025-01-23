---
title: "Copie"
pre: '<span class="presection-icon">🧬</span>'
weight: 3
---

Dans cette section vous verrez comment implémenter un constructeur de copie et un opérateur d'assignation.
On compilera le fichier [Person.cpp](../Person.cpp).


### Constructeur de copie

Dans la fonction `main`, instanciez à la suite du code existant une nouvelle instance de `Person` et initialisée là à partir de la variable `batman`. Cela se fait exactement de la même manière que si vous souhaitiez créer une copie d'une variable de type `int`.\
Affichez ensuite le contenu de cet objet grâce à l'opérateur `<<`.

{{% hidden-solution %}}
```cpp
Person copy = batman; // ou   Person copy{batman};   ou   auto copy = Person{batman};
std::cout << copy << std::endl;
```
{{% /hidden-solution %}}

---

Vous devriez obtenir le même affichage en sortie pour Batman et sa copie.

Nous aimerions maintenant avoir un clône plutôt qu'une copie. C'est-à-dire qu'au moment de l'instanciation du clône, ce serait bien qu'il vienne de naître, plutôt qu'il ait déjà 23 ans.

Pour ce faire, vous allez devoir redéfinir votre propre constructeur de copie. Je dis "redéfinir", car le compilateur (qui est gentil des fois) en a déjà défini un pour vous. Sans ça, l'instruction `Person copy = batman;` n'aurait pas pu compiler.

{{% notice note %}}
Le compilateur génère un constructeur de copie uniquement si vous n'en définissez pas un vous-même, et que chacun des attributs de votre classe est **copiable** (= disposant d'un constructeur de copie).\
Dans ce cas, l'**implémentation par défaut du constructeur de copie** appelera pour chacun des attributs de la classe son propre constructeur de copie.
{{% /notice %}}

Voici la syntaxe permettant de définir un constructeur de copie :
```cpp
class ClassName
{
public:
    ClassName(const ClassName& other)
        : _attribute_1 { /* probably other._attribute_1 */ }
        , _attribute_2 { /* probably other._attribute_2 */ }
        , ...
    {
        // some optional code
    }

private:
    type _attribute_1;
    type _attribute_2;
    ...
};
```

Au final, il s'agit simplement d'un constructeur à 1 paramètre, ce paramètre étant une const-ref sur la classe courante.

Essayez de définir un constructeur de copie pour la classe `Person`, qui effectue la copie de l'ensemble des attributs de la classe.\
Vérifiez que vous obtenez le même résultat que précédemment.

{{% hidden-solution %}}
```cpp
Person(const Person& other)
    : _name { other._name }
    , _surname { other._surname }
    , _age { other._age }
{}
```
{{% /hidden-solution %}}

---

Supprimez l'initialisation de l'attribut `_age` de la liste d'initialisation. De cette manière, le compilateur réalisera l'initialisation de `_age` à partir de son class-initializer (c'est-à-dire le `= 0u`).\
Testez le programme pour vous assurer que le clône a bien 0 an après son instanciation.

{{% hidden-solution %}}
```cpp
class Person
{
public:
    ...

    Person(const Person& other)
        : _name { other._name }
        , _surname { other._surname }
    {}

    ...

private:
    ...
    unsigned int _age = 0u;
}
```
{{% /hidden-solution %}}

---

Vous devriez avoir remarqué que l'age de batman ne s'affiche maintenant plus correctement.  Relisez bien votre code pour comprendre pourquoi.

{{% hidden-solution %}}
La signature de l'opérateur `<<` est incorrecte: `p` est passé par valeur.
```cpp
//                                               ici
//                                               vvvvvv
friend std::ostream& operator<<(std::ostream& o, Person p) {
    std::cout << "A person named \"" << p._name << " " << p._surname
            << "\" with age " << p._age << ".";
    return o;
}
```
En conséquence de quoi, une copie de batman est effectuée lors de l'appel à l'opérateur `<<` pour construire `p`.
Notre constructeur de copie réinitialise l'age à 0, donc `p` a un age de 0, et c'est cet age qui s'affiche.
{{% /hidden-solution %}}

---

Corrigez le code pour que l'age de Batman soit correctement affiché. Faire attention à ce que l'age de sa copie soit toujours 0.

{{% hidden-solution %}}
Il faut passer `p` par const-ref:
```cpp
//                                               vvvvv        v
friend std::ostream& operator<<(std::ostream& o, const Person & p) {
    /* pas de modification */
}
```

{{% /hidden-solution %}}



### Quand le constructeur de copie est appelé?

Pour faire court: quand le compilateur doit construire un nouvel objet
à partir d'une L-value.

```cpp
MyClass my_obj1 = /* .. */
MyClass my_obj2{my_obj1};
```

Dans le code au dessus, le compilateur doit construire `my_obj2` à partir de l'expression `my_obj1` qui est une L-value.

---

C'est pareil dans le code en dessous. L'argument `arg` est passé par valeur à `my_func` donc le compilateur doit construire un nouveau `MyClass` sur la pile à partir de `my_obj1`, qui est toujours une L-value.
```cpp
void my_func(MyClass arg) { /* .. */}

int main() 
{
    MyClass my_obj1 = /* .. */
    my_func(my_obj1);
}
```