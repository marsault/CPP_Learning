---
title: "Projets VSCode"
weight: 1
hidden: true
---

Lorsque vous avez un projet un peu plus conséquent, il est plus pratique de passer par VSCode pour configurer, compiler et tester vos programmes.

---



Pour configurer le projet, utilisez la commande `CMake: Configure`.

---

### Configuration du fichier launch.json

Afin de pouvoir exécuter votre ou vos programme rapidemment, il vous faudra créer et configurer le fichier `launch.json`.

1. Créez un dossier `.vscode` à la racine du répertoire (si celui-ci n'existe pas déjà) et ajoutez dedans un fichier que vous nommerez `launch.json`.
![](/images/chapter0/new-launch.png)
2. Une fois ce fichier créé, ouvrez-le et cliquez sur le bouton `Add Configuration`.
![](/images/chapter0/add-conf.png)
3. Sélectionnez ensuite la configuration `C/C++: (XXX) Launch` adéquate.\
Windows et Linux devraient vous proposez GDB et MacOS devrait vous fournir LLVM.
![](/images/chapter0/launch-conf.png)
4. Remplacez la variable `cwd` par la valeur ci-dessous :
```json
"cwd": "${workspaceFolder}",
```
5. Si vous avez compilé votre programme "à la main", remplacez `program` par le chemin de votre exécutable.  
Si vous avez utilisé CMake, vous pouvez indiquer `${command:cmake.launchTargetPath}`.
```json
"program": "${workspaceFolder}/chap-02/1-first_class",
"program": "${command:cmake.launchTargetPath}",
```
6. Si vous êtes sous Windows, supprimez la ligne contenant `"miDebuggerPath"`.

---

### Lancer un programme

Une fois que votre `launch.json` existe, vous pouvez lancer votre programme avec la commande `Debug: Start Debugging` ou en appuyant sur F5.

Si votre projet contient plusieurs exécutables, vous pouvez changer l'exécutable à lancer avec la commande `CMake: Set Debug Target`.
![](/images/chapter0/set-debug-target.png)

Si vous souhaitez lancer le programme en utilisant des arguments, vous pouvez renseigner ces derniers en modifiant la variable `args` dans le fichier `launch.json`.
![](/images/chapter0/args.png)
