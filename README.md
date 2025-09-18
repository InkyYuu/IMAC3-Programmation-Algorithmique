# TDs de Programmation et Algorithmique – IMAC E3

Ce dépôt contient les Travaux Dirigés (TDs) réalisés dans le cadre du cours de Programmation et Algorithmique en IMAC E3 (Cours fait par Enguerrand DE SMET). Les TDs sont ajoutés progressivement au fil de l'année.

## Organisation

- **Langages utilisés** : C/C++
- **Outils** : GCC/G++, CMake
- **Environnement** : Windows

## Lien vers les énoncés

Vous pouvez retrouver les sujets des TDs ici :  
[https://dsmte.github.io/Learn--cpp_programming/TDs](https://dsmte.github.io/Learn--cpp_programming/TDs)

## Particularités Windows

Pour garantir un affichage correct des caractères spéciaux (notamment l’UTF-8) dans la console Windows, vous verrez souvent ces lignes dans les fichiers sources :

En début de fichier :
```cpp
#include <windows.h>
```
Dans le `main` :
```cpp
SetConsoleOutputCP(CP_UTF8);
SetConsoleCP(CP_UTF8);
```

**Explications :**
- `#include <windows.h>` : Permet d’accéder aux fonctions spécifiques à Windows, comme la gestion de l’encodage de la console.
- `SetConsoleOutputCP(CP_UTF8);` : Configure la console pour afficher les caractères UTF-8.
- `SetConsoleCP(CP_UTF8);` : Configure la console pour lire les entrées en UTF-8.

Cela permet d’éviter les problèmes d’affichage lors de l’utilisation de caractères accentués ou spéciaux.

---

Bon code à vous !