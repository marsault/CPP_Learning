---
title: "Introduction"
pre: '<span class="presection-icon">🐣</span>'
weight: 1
---

---

### Qu'est-ce qu'un template ?

Les **templates** sont un mécanisme du C++ permettant de faire de la programmation générique.

Le terme "template" se traduit littéralement par "patron" en français (au sens patron de vêtement, pas patron d'entreprise).
Les templates vont donc permettre de construire un modèle de classe (ou de fonction) à partir duquel le compilateur pourra générer de véritables classes (ou fonctions).

Notez donc bien que malgré le terme, une classe-template n'est pas une classe.
C'est un modèle de classe.
Par exemple, `std::vector` n'est pas une classe, mais `std::vector<int>` est bien une classe.
La différence est importante à noter, car cela signifie que `vector` n'est pas un type.
Il est donc incorrect de dire qu'on instancie un objet de type `vector`; il faut plutôt dire qu'on instancie un objet de type `vector<int>`.

---

### Génération à partir d'un template

Jusqu'à présent, vous avez eu l'occasion d'utiliser tout un tas de templates proposés par la STL.

{{% notice note %}}
D'ailleurs, STL signifie "Standard Template Library", soit bibliothèque standard templatée.
Celle-ci regroupe les bibliothèques "Conteneurs", "Algorithmes", "Itérateurs" et "Chaînes de caractères" de la librairie standard.
J'en profite d'ailleurs pour indiquer que `std::string` est une classe générée à partir d'un template, au même titre que `std::vector<int>` ou `std::vector<float>`.
En effet, si vous allez voir la documentation, vous pourrez constater que `std::string` est en fait un alias pour la classe `std::basic_string<char>`.
{{% /notice %}}

Lorsque vous utilisez un `vector<int>`, un `array<float, 8>` ou encore un `std::back_insert_iterator<vector<int>>`, le compilateur fait trois choses :
- générer le code de la classe à partir de la classe-template et des paramètres de template fournis : template `vector` + paramètre `int` = classe `vector<int>`,
- compiler cette nouvelle classe,
- définir une variable de ce type.

De même, lorsque vous essayez d'appeler une fonction-template, comme `max`, le compilateur a besoin de réaliser des étapes supplémentaires par rapport à un appel classique :
- si besoin, déduire les paramètres de template à partir des arguments fournis lors de l'appel : `std::max(3, 4)` -> le paramètre de template est `int`, car 3 et 4 sont des `int`, 
- générer le code de la fonction correspondant à la fonction-template et aux paramètres de templates : template `max` + paramètre `int` = fonction `max<int>`,
- compiler cette nouvelle fonction,
- générer les instructions pour l'appel.

Nous reviendrons plus en détail sur ces étapes de génération de code et de déduction de paramètres de templates dans le prochain chapitre.
Ce qu'il faut néanmoins retenir ici, c'est qu'au moment où vous faites appel à un type ou une fonction templatée, le compilateur aura besoin du template pour générer le code dont il a besoin.
La conséquence de cela, c'est que dans 90% des cas, **vous devrez définir l'ensemble du contenu de vos templates dans les headers**, afin que le compilateur puisse y avoir accès.

---

### Conclusion

Un template est un modèle utilisé par le compilateur pour générer des classes ou des fonctions.\
Pour utiliser une classe ou une fonction générée à partir d'un template, il faut que le compilateur puisse avoir accès au code de ce template.\
Cela implique donc généralement que l'ensemble du code de ce template se trouve dans un fichier header, qu'il faut inclure dans les fichiers où il y en a besoin.
