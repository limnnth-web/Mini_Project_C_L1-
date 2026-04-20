# Objectif du Projet
Développer une application Console en langage C pour gérer une base de données de planètes et une flotte de sondes spatiales. 
Le programme permet à l'utilisateur de manipuler, rechercher des informations et simuler le déploiement de vaisseaux, avec une persistance des données assurée par des fichiers CSV.

## Structures de Données Principales:
**Planète (Struct Planet) :**
- Identification : ID, Nom.
- Données scientifiques : Distance, Magnitude stellaire, Type de planète, Année de découverte, Méthode de détection.
- Données physiques (pour calcul) : Multiplicateur et Unité de masse/rayon (Jupiter/Earth), Rayon orbital, Période orbitale, Excentricité.
- Statut : Statut d'exploration (0: Non explorée, 1: En cours, 2: Terminée), ID de la sonde affectée.
  
**Sonde (Struct Vessel) :**
- Informations : ID de la Sonde, ID de la Planète cible.
- Statut : AVAILABLE (Disponible), MISSION (En mission), NOT AVAILABLE (En maintenance).

## Structure du projet:
Mon projet est organisé de manière modulaire pour séparer la logique, les données et les différentes fonctionnalités. 
Voici la structure détaillée de mon dossier Projet/ (qui contient le fichier principal main.c et tout le reste du projet) :
- **build/** : Contient les versions compilées et exécutables du programme (les fichiers `.exe`).
- **include/** : Contient les fichiers d'en-tête (.h) pour définir les structures et les fonctions : modify.h, planet.h, vessel.h.
- **Res/Data/** : Contient les bases de données au format CSV (Planet.csv et Vessel.csv).
- **src/** : Contient les fichiers sources (.c) divisés par fonctionnalités spécifiques :
  - `cleanstr.c` : Contient la fonction `cleanStr()` pour nettoyer les fins de ligne.
  - `gravity.c` : Contient la fonction `calculGravity()` pour calculer la gravité des planètes.
  - `manage.c` : Contient les fonctions pour gérer les missions des sondes (`launchVessel()`, `returnVessel()`, `maintainVessel()`, `addVessel()`).
  - `planet.c` : Contient les fonctions pour gérer le catalogue des planètes (`loadPlanet()`, `printP()`, `printCatalog()`, `filterP()`, `searchP()`, `editPlanet()`, `addPlanet()`).
  - `saveFile.c` : Contient les fonctions pour la saisie sécurisée des utilisateurs et la sauvegarde des données (`saveFile()`, `readFloat()`, `readInt()`, `readStr()`, `yesOrNo()`).
  - `vessel.c` : Contient les fonctions de base pour les sondes (`loadVessel()`, `printV()`, `printFleet()`, `filterV()`, `searchV()`).

# Configuration requise
Pour exécuter ce programme, votre ordinateur doit disposer des éléments suivants :
- Compilateur C (GCC / MinGW).
- git.
- Code Editor.

## Instructions d'installation et d'exécution (Comment exécuter)
**Étape 1:** Téléchargez le code sur votre ordinateur: 
```
git clone https://github.com/limnnth-web/Mini_Project_C_L1-.git
```
**Étape 2:** Accédez au dossier contenant le code:
```
cd Mini_Project_C_L1-
```
**Étape 3:** Compilez tous les fichiers de code C:
```
 gcc main.c src/*.c -Iinclude -o build/version4.exe
```
**Étape 4:** Exécutez le programme:
```
./build/version4.exe
```
