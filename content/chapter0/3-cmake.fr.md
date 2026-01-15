---
title: "CMake"
pre: '<span class="presection-icon" ><img src="/logo/cmake.svg"/></span>'
weight: 3
---

Afin de générer les artéfacts pour la compilation, nous utiliserons {{< open_in_new_tab "https://cmake.org/" "CMake" />}}.

---

### Installation

#### Windows

1. Ouvrez un terminal MSYS2 UCRT64.
2. Installez les paquets `cmake` et `make` avec l'instruction suivante :
   ```sh
   pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-make
   ```

#### Linux / MacOS

1. Ouvrez un terminal.
2. Utilisez votre gestionnaire de package afin d'installer `cmake`.

---

### Fichier de configuration

Vous aurez besoin d'un fichier `CMakeLists.txt` à la racine de votre répertoire pour configurer le projet.
Si celui-ci ne contient qu'un seul programme, vous pouvez copier et adapter dans votre `CMakeLists.txt` les instructions suivantes.
```
cmake_minimum_required(VERSION 3.16)
project(my_project)

add_executable(my_executable
    my_file1.cpp
    my_file2.cpp
    my_file3.h
)

target_compile_features(my_executable PUBLIC cxx_std_17)
```

### Configurer un projet

#### Linux / MacOS

```bash
   # se placer avec `cd` dans le répertoire racine avec le CMakelists.txt
   mkdir build
   cd build
   cmake ..
```


<!-- ### Intégration à VSCode

{{% notice style="warning" icon="hammer" title="Deprecation" %}}
Cette année nous essayons de passer à VSCodium (fork libre de VSCode) donc les sections sur VSCode concernent principalement les étudiants voulant coder depuis windows.
{{% /notice %}}


Afin de pouvoir utiliser CMake facilement depuis VSCode, il faut installer les extensions `CMake` et `CMakeTools`.

1. Démarrez VSCode.
2. Ouvrez le panneau des extensions et recherchez les extensions `CMake` et `CMakeTools`.
![](/images/chapter0/cmake-ext.png)
3. Cliquez ensuite sur le bouton `Install` pour chacune d'entre elles.
4. Redémarrez VSCode.
5. Vérifiez que vous avez accès aux commandes `CMake` depuis le panneau de commandes (`View > Command Palette ...` ou `Ctrl + Shift + P`).

Vérifiez maintenant votre installation.
1. Téléchargez et extrayez [cette archive](../hello.zip) dans un nouveau dossier.
2. Ouvrez ce dossier depuis VSCode.
![](/images/chapter0/folder-vscode.png)
3. Exécutez la commande `CMake: Configure`.
4. Sélectionnez le compilateur g++ ou clang++ le plus récent dans la liste proposée.
5.  La configuration et la génération des fichiers de build devraient avoir lieu.
![](/images/chapter0/cmake-result.png)
6.  Cliquez maintenant sur le bouton `Build` dans la barre en bas (ou F7) pour compiler le projet.
![](/images/chapter0/cmake-build.png) -->

