---
title: "Questionnaire"
pre: '<span class="presection-icon">✅</span>'
weight: 100
---

Le premier objectif de ce chapitre était de vous présenter quelques classes de la STL, leurs rôles, leurs différences, dans quelles situations les utiliser et comment.\
Il avait également un deuxième objectif, qui était en quelque sorte de vous apprendre à vous débrouiller tout seul : vous devriez désormais être capable de rechercher par vous-même des informations dans la documentation, et vous devriez aussi appréhender un peu mieux qu'avant les messages du compilateur.

J'espère donc que ce chapitre a rempli ses objectifs et que vous vous sentez maintenant plus à l'aise pour programmer !​ 😀​

---

{{% test chapter=5 %}}

{{% test_item %}}
Citez 3 informations que vous pouvez retrouver dans l'en-tête de la documentation d'une classe.
{{% /test_item %}}

{{% test_item %}}
Comment savoir s'il est nécessaire ou non de fournir un paramètre de template à une classe ?
{{% /test_item %}}

{{% test_item %}}
Citez 3 fonctions de `vector` qu'il ne faut pas appeler à l'intérieur d'une boucle foreach.
{{% /test_item %}}

{{% test_item %}}
Dans quel cas l'instanciation d'une classe via `(p1, p2, p3)` n'a pas le même comportement que l'instanciation via `{ p1, p2, p3 }` ?
{{% /test_item %}}

{{% test_item %}}
Quel section de la documentation faut-il regarder pour savoir rapidement comment utiliser une fonction ?
{{% /test_item %}}

---

{{% test_item %}}
Quelle est la fonction définie par `vector` qui permet d'accéder à un élément avec l'expression `values[idx]` ?
{{% /test_item %}}

{{% test_item %}}
Quelles fonctions faut-il définir dans un conteneur pour pouvoir le parcourir au moyen d'une boucle foreach ?
{{% /test_item %}}

{{% test_item %}}
Pour pouvoir utiliser un `std::set<Key>`, quelle contrainte la classe `Key` doit-elle respecter ?
{{% /test_item %}}

{{% test_item %}}
Afin de respecter cette contrainte, quelle est la signature de la fonction à définir ?
{{% /test_item %}}


---

{{% test_item %}}
Quelle fonction permet de connaître le nombre d'éléments d'un conteneur ?
{{% /test_item %}}

{{% test_item %}}
Quelle fonction permet de savoir si un conteneur est vide ?
{{% /test_item %}}

{{% test_item %}}
Quelle fonction permet de récupérer le premier élément d'un conteneur séquentiel ?
{{% /test_item %}}

{{% test_item %}}
Citez deux fonctions permettant d'ajouter des éléments dans un dictionnaire.
{{% /test_item %}}

{{% test_item %}}
Quelle fonction permet de supprimer des éléments d'un conteneur séquentiel ?
{{% /test_item %}}

{{% test_item %}}
Quelle fonction permet de vider entièrement un conteneur ?
{{% /test_item %}}

---

{{% test_item %}}
Quelle classe permet de définir un tableau de taille fixe ?
{{% /test_item %}}

{{% test_item %}}
Définissez une variable de ce type, contenant les valeurs `'a'`, `'b'` et `'c'`.
{{% /test_item %}}

{{% test_item %}}
Quelles classes faut-il utiliser pour représenter une collections dans laquelle chaque valeur ne peut pas apparaître plus d'une fois ? Indiquez la complexité en temps des opérations d'insertions pour chacune d'entre elles.
{{% /test_item %}}

{{% test_item %}}
Quelle classe permet de retourner plusieurs valeurs d'une fonction facilement ?
{{% /test_item %}}

---

{{% test_item %}}
Quel type doit-on utiliser pour un pointeur ownant? un pointeur observant? (le type pointé est `A`).
{{% /test_item %}}

{{% test_item %}}
Une fonction `my_func` a pour prototype `void my_func(std::unique_ptr<std::string>& arg)`; notez la `&`.
Est-ce que la chaine de caractère `*arg` sera désinstanciée à la fin de la fonction `my_func`?
{{% /test_item %}}

---

{{% test_item %}}
Comment récupérer l'itérateur de début d'un conteneur dans une variable `it` ?
{{% /test_item %}}

{{% test_item %}}
Comment incrémenter de 5 positions cet itérateur ?
{{% /test_item %}}

{{% test_item %}}
Comment récupérer la valeur pointé par cette itérateur dans une variable `value` ?
{{% /test_item %}}

{{% /test %}}
