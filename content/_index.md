---
title: "Accueil"
---

## Bienvenue

Sur ce site, vous trouverez le cours de C++ destiné à l'enseignement des Master 1 de l'Université Gustave-Eiffel. Si vous ne faites pas partie des étudiants de cette section, vous êtes tout de même les bienvenus. Sachez juste que d'une part, ce cours étant un cours d'introduction, nous nous concentrerons sur les concepts de base du langage, ainsi que sur les mécanismes permettant d'écrire du code plus simplement ou de le rendre plus sûr. Et d'autre part, il est fortement recommandé pour pouvoir suivre ce cours d'avoir de bonnes bases en C et en Java.

À nos très chers étudiants et étudiantes de Master 1, merci de lire la suite de cette page attentivement.

---

### Déroulement du module

Le module sera constitué de 3 séances de cours magistraux, 12 séances de travaux pratiques et 3 séances d'évaluation.

Le planning est le suivant :
|    | Dates             | Séances | Chapitre à lire <br>(avant le TP)|
| -- | ----------------- | - | - |
|S1  | 12 - 16 janvier   | ▹ Cours 1 <br> ▹ TP 1 (Compilation, Entrée / sortie, `std::string`, `std::vector`) | [0]({{% ref chapter0 %}}) et [1]({{% ref chapter1 %}})  |
|S2  | 19 - 23 janvier   | ▹ TP 2 (Classes, Constructeurs, Membres statiques, Opérateurs) |  [2]({{% ref chapter2 %}})  |
|S3  | 26 - 30 janvier   | ▹ TP 3 (Références, Ownership) | [3]({{% ref chapter3 %}}) |
|S4  | 2 - 6 février     | ▹ TP 4 (Révisions, Framework de TP noté)  <br> ▹ TP noté 1 (sur les chapitres 0 à 3, 2h)|
|S5  | 9 - 13 février   | ▹ Cours 2 |
|S6  | 16 - 20 février   | ▹ TP 5 (Copie, Déplacement, L-value et R-value) | [4]({{% ref chapter4 %}}) |
|S7  | 23 - 27 février   | ▹ TP 6 (stdlib, conteneurs, `std::unique_ptr`) | [5]({{% ref chapter5 %}}) |
|S8  | 2 - 6 mars        | ▹ TP 7 (Polymorphisme, Héritage) | [6]({{% ref chapter6 %}}) | 
|S9  | 9 - 13 mars      | ▹ TP 8 (Révisions, Framework de TP noté) <br> ▹ TP noté 2 (sur les chapitres 0 à 6, 2h)|
|S10 | 16 - 20 mars      | ▹ Cours 3 |
|S11 | 23 - 27 mars      | ▹ TP 9 (Lambdas, Algorithmes) | [7]({{% ref chapter7 %}}) |
|S12 | 30 mars - 3 avril | ▹ TP 10 (Templates) | [8]({{% ref chapter8 %}}) |
|S13 | 6 - 10 avril      | ▹ TP 11 (Templates, Perfect forwarding, SFINAE) | [9]({{% ref chapter9 %}}) |
|S14 | 14 - 18 avril     | ▹ Vacance/Révisions (TP 12 en autonomie) |
|S15 | 21 - 24 avril     | ▹ TP noté 3 (sur tous les chapitres, 3h) |

#### Cours magistraux

Les cours magistraux sont l'occasion d'aborder les notions que vous pourrez revoir et creuser dans les chapitres du cours en ligne.  
C'est également un bon moment pour poser des questions sur le cours ou les TPs précédents.  
Les slides sont disponible [ici](slides).

#### Cours en ligne

Chaque semaine, **avant votre séance de TP**, vous devrez lire et comprendre le chapitre associé du cours en ligne.

Il faudra également réaliser les exercices proposés, afin d'assimiler rapidement ce que vous aurez lu. Pour cela, vous devrez partir du contenu de ce [dépôt git]({{% param exoducoursURL %}}).
Il est recommandé d'essayer de faire les exercices une première fois sans regarder les solutions.
Si vous êtes bloqués, recherchez d'abord de l'aide sur Internet ou en demandant à vos camarades de classe.

Une fois que vous avez quelque chose qui a l'air de fonctionner, regardez la solution pour vérifier que ce que vous avez fait est correct.
Si votre code n'est pas identique, c'est probablement parce qu'il n'y a pas qu'une seule bonne réponse.
Et si vous n'êtes vraiment pas sûr(e)s de votre solution, n'hésitez pas à m'envoyer ce que vous avez fait par mail ou Discord, ou à l'indiquer dans le formulaire de fin de chapitre afin que l'on vous donne un retour.

{{% notice tip %}}
Si vous avez une question ou une remarque (typo par exemple) sur un endroit très précis du cours, **vous pouvez sélectionner la zone concernée et cliquer sur le point d'interrogation** qui s'affiche en bas à droite de l'écran pour nous envoyer votre message.  
On pourra ainsi vous répondre et éventuellement retravailler cette partie du site pour qu'elle soit plus claire pour tout le monde ! 😄
{{% /notice %}}

#### Questionnaires

Le questionnaire de fin de chapitre sera composé comme suit :
- nom et prénom,
- adresse mail,
- des questions sur le contenu du chapitre,
- un champ pour entrer vos propres questions (nous enverrons les réponses au mail indiqué plus haut),
- un champ pour laisser des commentaires sur le format du cours et me prévenir si j'ai écrit des bêtises

N'hésitez vraiment surtout pas à poser vos questions dans le formulaire, mais aussi à nous les envoyer directement par mail ou Discord, en particulier si cela vous bloque pour avancer.

#### Séances de TP

L'énoncé pour chaque séance de TP sera disponible au format Markdown sur [dépôt git]({{% param tpURL %}}).

Certaines parties de la séance seront à réaliser en autonomie, tandis que d'autres parties devront se faire avec l'ensemble du groupe, de manière à ce que la correction puisse être comprise par tous. 

#### Questions

Si vous avez des questions sur le TP ou le cours, le meilleur moment pour les poser est pendant les séances de TP, mais n'hésitez pas à nous contacter sur Discord.

Si vous n'avez pas terminé le TP avant la fin de la séance, et que vous avez des questions pendant que vous êtes en train de le terminer chez vous, vous pouvez contacter votre chargé de TP par mail ou sur Discord. Vous pouvez également demander de l'aide à vos camarades de classe, car c'est toujours intéressant de travailler en groupe.

---

### Notation

Votre note finale sera composée des notes obtenues aux trois séances de TPs notés.
La pondération sera établie et communiquée une fois l'ensemble des rendus corrigés.

---

### Conclusion

Au final, ce cours a pour objectif les points suivants :
- que vous soyiez capables de comprendre la plupart des bouts de code auxquels vous pourrez être confrontés dans le futur,
- que vous appreniez à programmer à peu près tout ce dont vous avez envie, sans être obligé(e)s de consulter Internet en permanence,
- que vous puissiez éviter les erreurs de compilation et de programmation classiques,
- que vous acquiériez l'autonomie et les réflexes indispensables permettant de vous débloquer lorsque vous rencontrez un problème.

Bien entendu, comme n'importe quel autre cours que vous trouverez sur Internet, vous aurez à fournir un minimum d'investissement si vous souhaitez en tirer quoi que ce soit.

---

### Création et maintenance de ce site

Ce site a été créé en 2021 et maintenu par Céline Noël jusqu'en 2024. 
Depuis, il est maintenu et mis à jour par Henri Derycke et Victor Marsault.
