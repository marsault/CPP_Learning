---
title: "Cycle de vie"
type: "chapter"
pre: "<span class=\"chapnum\">3.</span>&ensp;"
weight: 3
---

En C++, lorsque vous allouez une donnée, celle-ci ne reste pas miraculeusement accessible durant toute l'exécution de votre programme.  
Contrairement à des langages comme Java ou C#, qui disposent d'un garbage-collector pour libérer automatiquement la mémoire lorsque celle-ci n'est plus nécessaire, c'est ici au développeur de faire ce travail.

Il doit penser à libérer la mémoire lorsqu'il ne compte plus s'en servir, mais surtout, il doit faire attention à ne pas tenter d'accéder à des données si celles-ci n'existent déjà plus 😬

Dans ce chapitre, nous nous intéresserons au cycle de vie des données.  
Nous reviendrons sur les notions d'instanciation et de désinstanciation des données, et nous détaillerons à quel moment ces deux événements se produisent.  
Nous ferons un rappel de comment sont stockées les données en mémoire.  
Enfin, nous reparlerons des références et verrons comment faire pour comprendre si une donnée à laquelle le développeur souhaite accéder est toujours valide ou non.
