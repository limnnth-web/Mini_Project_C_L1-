#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "modify.h"

//Charger sonde
int loadVessel (const char *vesselcsv, Vessel *fleet)
{
    FILE *f = NULL;
    f = fopen(vesselcsv, "r");

    if (!f) //si le programme trouve pas le fichier, il s'arrete
    {
        printf("Erreur d'ouverture de fichier vesselcsv\n");
        return 0;
    }

    char perLine[maxPerLine];
    int nbVessel = 0;
    int nbLine = 1;
    char *field[10]; //si l'utilisateur ajoute quelque "," incorrect
    int nbColumn = 0;
    char *token = NULL;

    //passer la premier ligne (header)
    fgets(perLine, maxPerLineV, f); //aller a fichier f, commencer a &surLigne, max des donnees est maxSurLigne

    //Charger sonde
    while (fgets(perLine, maxPerLineV, f) && (nbVessel < maxVessel))
    {
        cleanStr(perLine); //pour couper \n et \r

        nbColumn = 0;

        //couper le chaine par ","
        token = strtok(perLine, ",");
        while ((token) && (nbColumn < 10))
        {
            field[nbColumn ++] = token;
            token = strtok(NULL, ","); //continue couper de la derniere ","
        }

        //condition pour mettre les donnees dans le structure
        if (nbColumn == 3)
        {
            Vessel *v = &fleet[nbVessel];

            strcpy(v -> idVessel, field[0]); // v -> IdVessel = fleet[nbVessel].idVessel
            v -> idPlanet = atoi(field[1]);
            strcpy(v -> status, field[2]);
            
            nbVessel ++;
        }
        else
        {
            printf("La ligne %d corrompue\n", nbLine);
        }
        nbLine ++;
    }
    fclose(f);
    return nbVessel;
};

//Aficher une sonde
void printV(const Vessel *v)
{
    //Verifier
    if (v == NULL)
    {
        return;
    }

    printf("ID sonde: %s\n", v->idVessel);
    printf("ID Planete: %d\n", v->idPlanet);
    printf("Statut: %s\n", v->status);
}

//Aficher flotte
void printFleet(Vessel *fleet, int nbVessel)
{
    //Verifier le nombre des sondes
    if (nbVessel == 0)
    {
        printf("La flotte est vide.\n");
    }
    else
    {
        for (int i = 0; i < nbVessel; i++)
        {
            printV(&fleet[i]);
            printf("\n");
        }
    }
}

//Sonde filtre
void filterV(const Vessel *fleet, int nbVessel, char statusFilter[20])
{
    int count = 0; 
    
    for (int i = 0; i < nbVessel; i++)
    {
        if (strcmp(fleet[i].status, statusFilter) == 0)
        {
            printV(&fleet[i]);
            printf("\n"); 
            count++;
        }
    }

    printf("Il y a %d sonde(s) dans cet etat.\n", count);
}

//Chercher idV
Vessel* searchV(Vessel *fleet, int nbVessel, char targetVessel[50])
{
    Vessel *idVTarget = NULL;
    
    for (int i = 0; i < nbVessel; i++)
    {
        if (strcmp(fleet[i].idVessel, targetVessel) == 0)
        {
            idVTarget = &fleet[i];
            break;
        }
    }
    return idVTarget;
}

