#ifndef MODIFY_H
#define MODIFY_H

#include "planet.h"
#include "vessel.h"

void cleanStr(char *str);

void saveFile(const Planet *catalog, int nbPlanet, const Vessel *fleet, int nbVessel);

void readFloat(float *token);

void readInt(int *token);

void readStr(char *token, int maxToken);

int yesOrNo();

//Modifier planete
void editPlanet(Planet *catalog, int nbPlanet, int targetPlanet);

//gestion des sondes
void launchVessel(Planet *catalog, int nbPlanet, int targetPlanet, Vessel *fleet, int nbVessel, char targetVessel[50]);

void returnVessel(Planet *catalog, int nbPlanet, int targetPlanet, Vessel *fleet, int nbVessel, char targetVessel[50]);

void maintainVessel(Vessel *fleet, int nbVessel, char targetVessel[50]);

int addVessel(Vessel *fleet, int nbVessel, char targetVessel[50]);

#endif