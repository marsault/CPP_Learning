---
title: "Minimiser les copies"
pre: '<span class="presection-icon">🔥</span>'
weight: 6
---

Dans le [chapitre 3](chapter3), nous avons vu comment choisir le type des paramètres d'une fonction.  Maintenant qu'on sait comment déplacer les objets, on peut faire mieux !

---

### Un puzzle à résoudre

Nous allons considérer la classe `BoxedString` en dessous.
Notre but est d'implémenter un constructeur qui prend un argument une chaîne de caractères pour initialiser l'attribut `_str`, et ce en minimisant le nombre de copies.

```cpp
class BoxedString 
{
    std::string _str;
};
```

Pour commencer, évaluons notre objectif: combien de copies peut-on espérer faire au minimum dans les cas typiques.
Les variables `b1`, `b2`, `b3` et `b4` (en dessous) montrent les quatre façons dont on va usuellement construire une `BoxedString` à partir d'une `std::string`.

```cpp
int main() {
    std::string some_str{"Hello world!"};
    BoxedString b1{some_str};
    BoxedString b2{std::move(some_str)};
    BoxedString b3{std::string{"Hello Universe!"}};
    BoxedString b4{"Hello Universe!"};
}
```


Pour chacun de ces quatre cas, combien de copies de la `std::string` passée en argument peut-on espérer au minimum?

{{% hidden-solution %}}
- Pour `b1`, on ne peut pas espérer faire moins qu'une copie.
- Pour `b2`, on peut espérer faire zéro copie car on déplace `some_str` dans l'attribut `_str`  du `BoxedString` construit.
- Pour `b3`, on peut espérer faire zéro copie car on peut espérer que l'objet temporaire passé en argument soit déplacé dans `_str`  du `BoxedString` construit (ou construit directement à cet emplacement mémoire si le compilateur y arrive).
- Le cas `b4` est en fait équivalent à `b3`.
Dans la suite, on considère les cas `b1` et `b2`.  Les cas `b3` et `b4` seront toujours équivalent à `b2`.
{{% /hidden-solution %}}


#### Passage par valeur

On peut naïvement passer la `std::string` par valeur.
```cpp
class BoxedString 
{
    std::string _str;
public:
    BoxedString(std::string str) :  _str{str} {}
};
```

Pour chacun des cas `b1` et `b2` (voir le `main` en haut de la page), combien de copies vont avoir lieu?
{{% hidden-solution %}}
- La construction de `b1` provoque 2 copies consécutives. 😭
- La construction de `b2` provoque 1 copie (de `str` vers `_str`). 😭
{{% /hidden-solution %}}


#### Passage par référence constante

Imaginons qu'on décide de passer la `std::string` par const-ref.

```cpp
class BoxedString 
{
    std::string _str;
public:
    BoxedString(const std::string& str) :  _str{str} {}
};
```

Notez que le `main` donné plus haut compile, car les `R-value` peuvent être transtypées en références constantes (on ne fait que perdre des droits sur elles).

Pour chacun des cas `b1` et `b2` (voir le `main` en haut de la page), combien de copies vont avoir lieu?
{{% hidden-solution %}}
- La construction de `b1` provoque 1 copie. 😀
- La construction de `b2` provoque 1 copie (de `str` vers `_str`). 😭
{{% /hidden-solution %}}


#### Utiliser deux constructeurs

On peut aussi faire deux constructeurs différents.

```cpp
class BoxedString 
{
    std::string _str;
public:
    BoxedString(const std::string& str) : _str{str} {}
    BoxedString(std::string&& str) : _str{std::move(str)} {}
};
```
Pour chacun des cas `b1` et `b2` (voir le `main` en haut de la page), combien de copies vont avoir lieu?
{{% hidden-solution %}}
- La construction de `b1` provoque 1 copie car on utilise le premier constructeur. 😀
- La construction de `b2` provoque 0 copie: on utilise le second constructeur et donc `_some_str` est déplacé vers `str`, puis celle-ci est déplacée vers `_str`. 😀

Super, on a atteint notre objectif de copie! 🥳
{{% /hidden-solution %}}



Cette implémentation crée un autre problème 😱.\
Voyez-vous lequel?

{{% hidden-solution title="un indice" %}}
Que se passe-t-il si on a deux attributs `std::string _str1` et `std::string _str2` dans la classe?
{{% /hidden-solution %}}

<br> 

{{% hidden-solution%}}
Si on a plusieurs attributs, on va devoir démultiplier les constructeurs. Par exemple, avec deux chaines, il nous faut 4 constructeurs.
```cpp
class TwoBoxedStrings 
{
    std::string _str1;
    std::string _str2;
public:
    TwoBoxedStrings (const std::string& str1, const std::string& str2) 
    :  _str1{str1}, _str2{str2}
    {}
    TwoBoxedStrings (std::string&& str1, const std::string& str2) 
    :  _str1{std::move(str1)}, _str2{str2}
    {}
    TwoBoxedStrings (const std::string& str1, std::string&& str2) 
    :  _str1{str1}, _str2{std::move(str2)}
    {}
    TwoBoxedStrings (std::string&& str1, std::string&& str2) 
    :  _str1{std::move(str1)}, _str2{std::move(str2)}
    {}
};
```
C'est parfaitement illisible hein?\
Et notez bien qu'avec 3 attributs, il nous faut 8 constructeurs; avec 4 attributs, 16 constructeurs; etc.
{{% /hidden-solution %}}

#### Passage par valeur puis déplacement

Comment faire alors?  Voici une autre implémentation possible.
```cpp
class BoxedString 
{
    std::string _str;
public:
    BoxedString(std::string str) : _str{std::move(str)} {}
};
```

Pour chacun des cas `b1` et `b2` (voir le `main` en haut de la page), combien de copies vont avoir lieu?
{{% hidden-solution %}}
- La construction de `b1` provoque 1 copie. 😀
- La construction de `b2` provoque 0 copie: `_some_str` est déplacé vers `str`, puis celle-ci est déplacée vers `_str`. 😀
{{% /hidden-solution %}}



### Synthèse: choix du type d'un paramètre v2

Notez que le problème illustré sur cette page peut se poser pour une fonction qui n'est pas un constructeur.
On peut donc mettre à jour notre petit schéma pour choisir comment on passe un argument.

{{< mermaid >}}
%%{init: {"flowchart": {"htmlLabels": false}} }%%
flowchart TD;
    Q1(Est-ce que la fonction est censée avoir un effet de bord sur le paramètre ?)
    Ref[Passage par référence non-constante]
    Q2("Est-ce que la copie du paramètre est couteuse?<br/>(allocation dynamique, appels-système, calculs complexes, ...)")
    Q3("Est-ce la fonction va avoir besoin de sa propre copie du paramètre ?<br/>(attributs,...)")
    Move[Passage par valeur, puis déplacement dans la fonction]
    CRef[Passage par reference constante]
    Value[Passage par valeur]
    Q1 -->|Oui| Ref
    Q1 -->|Non| Q2
    Q2 -->|Oui| Q3 
    Q3 -->|Oui| Move
    Q3 -->|Non| CRef
    Q2 -->|Non| Value
{{< /mermaid >}}

