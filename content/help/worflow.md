---
title: "Workflow"
pre: '<span class="presection-icon">🌊</span>'
---

Voici le workflow général que nous suivrons pour faire les exercices.

### Récupérer les sources

Les sources se récupèrent soit:
- par un lien direct depuis ce site (exercices du cours);
- sur [ce dépot git](https://github.com/marsault/CPP_Exercises/) pour les TPs;
- directement sur votre machine (dans `$HOME/SUJET`) pour les TPs notés.


### Configurer avec CMakeLists.

#### S'il n'est pas fourni, écrire un `CMakeLists.txt`
```CMake
cmake_minimum_required(VERSION 3.1)
project(my_project)

add_executable(my_executable  # <- Nom de l'executable
    my_file1.cpp  # \
    my_file2.cpp  #  |
    # ...            |- Sources et headers
    my_file3.h    #  |
    my_file3.h    # /
)

add_executable(my_executable2  # <- Eventuellement ajout d'un deuxième éxecutable
    # ...
)

target_compile_features(my_executable PUBLIC cxx_std_17)
    # Pour compiler avec le standard C++17   ^^^^^^^^^^

target_compile_options(hello-world PRIVATE # Ajoute des
-Wall  # Ajoute des warnings
-Wextra  # Ajoute plus de warnings
-Werror  # Transforme les warnings en erreurs
)

```
#### Lancer CMake

```bash
    # Se placer avec `cd` à la racine du répertoire (où se trouve le `CMakeLists.txt`)
    mkdir build # crée un répertoire `build` dans le répertoire courant
    cd build/   # se déplacer dans le répertoire build créé
    cmake ..    # lancer CMake sur le répertoire `..` où se trouve donc le `CMakeLists.txt`
```


### Compiler

#### Sans CMake (non recommandé)

```bash
    g++ fichier1.cpp fichier2.cpp -o nom_de_lexecutable
```

#### Avec CMake
```bash
    make  # Compile toutes les cibles
# ou
    make my_executable # Compile uniquement l'executable my_executable
```

### Exécuter



### Pour les TP notés (et les TPs de révisions)

#### Lancer les tests (TPs de révisions ou TP notés)

Le script `run_tests.sh` compile et éxécute les tests


```bash
# Se placer dans le répertoire build
    ...

# Lance la compilation et l'exécution de tous les tests unitaires
    ./run_tests.sh

# Lance la compilation et l'exécution des tests contenant le pattern donné
    ./run_tests.sh <pattern>

# Par exemple
    ./run_tests.sh ex2      # => tous les tests de l'exercice 2
    ./run_tests.sh ex2-1    # => exercice 2, tests 10 à 19
    ./run_tests.sh ex2-23   # => exercice 2, test 23 uniquement
```


#### Compiler un test sans l'éxécuter

```bash
# Se placer dans le répertoire build
    ...

# Compile le test contenu dans le répertoire ex2-01-montest,
# qui se trouve probablement dans ex2/tests/01-montest.cpp .
# Ce fichier peut appeler (avec `#include`) des fichiers 
# - fournis par nous (dans ex2/lib)
# - écris par vous (dans ex2/src)
    make ex2-01-montest 
```


