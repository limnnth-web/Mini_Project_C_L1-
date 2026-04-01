#ifndef VESSEL_H
#define VESSEL_H

#define maxVessel 40
#define maxPerLineV 50



typedef struct {
    char idVessel[50];
    int idPlanet;
    char status[20];
} Vessel;

//Charger sonde
int loadVessel(const char *vesselcsv, Vessel *fleet);

//Aficher une planete
void printV(const Vessel *v);

//Aficher catalogue
void printFleet(Vessel *fleet, int nbVessel);

//Chercher idV
Vessel* searchV(Vessel *fleet, int nbVessel, char targetVessel[50]);

//Sonde filtre
void filterV(const Vessel *fleet, int nbVessel, char statusFilter[20]);

#endif