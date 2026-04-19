#ifndef PLANET_H
#define PLANET_H

#define maxPlanet 6000
#define maxPerLine 1000 //pour lire les donnees sur une ligne csv

typedef struct {
    //identifiant
    int idPlanet;
    char namePlanet[50];

    //des informations pour sciences
    float distance;
    float stellarMagnitude;
    char planetType[20];
    int discoveryYear;

        //pour calcul
    float massMultiplier;
    char massWrt[20];
    float radiusMultiplier;
    char radiusWrt[20];

    float orbitalRadius;
    float orbitalPeriod;
    float eccentricity;
    char detectionMethod[50];

    //statut et Sonde
    int statusExploration;
    char idVessel[50];
} Planet;

//Charger planete
int loadPlanet (const char *planetcsv, Planet *catalog);

//Aficher une planete
void printP(const Planet *p);

//Aficher catalogue
void printCatalog(Planet *catalog, int nbPlanet);

//Chercher idP
Planet* searchP(Planet *catalog, int nbPlanet, int targetPlanet);

//Planete filtre
void filterP(const Planet *catalog, int nbPlanet, int statusFilter);

//Ajouter planete
int addPlanet(Planet *catalog, int nbPlanet, int targetPlanet);

//Calculer la gravite
float calculGravity (const Planet *p);

#endif