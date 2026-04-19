#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modify.h"

//Sauvegarder Donnees
void saveFile(const Planet *catalog, int nbPlanet, const Vessel *fleet, int nbVessel)
{
    //fichier planete
    FILE *fplanet = NULL;
    fplanet = fopen("Res/Data/Projet_C_L1 - Planet.csv","w");

    if (!fplanet) //si le programme trouve pas le folder inclus le fichier ou il ne peut pas ouvrir le fichier, il s'arrete
    {
        printf("Erreur d'ouverture et sauvegarder des donnees de fichier planetcsv\n");
        return;
    }

    //Ecrire la premiere ligne
    fprintf(fplanet, "Id_planet,Name,Distance,Stellar_magnitude,Planet_type,Discovery_year,Mass_multiplier,Mass_wrt,Radius_multiplier,Radius_wrt,Orbital_radius,Orbital_period,Eccentricity,Detection_method,Status_Exploration,ID_Vessel\n");

    //Ecrire les nouveaux donnees
    for (int i = 0; i < nbPlanet; i++)
    {
        const Planet *p = &catalog[i];
        
        fprintf(fplanet, "%d,%s,%f,%f,%s,%d,%f,%s,%f,%s,%f,%f,%f,%s,%d,%s\n",
                    p -> idPlanet, p -> namePlanet, 
                    p -> distance, p -> stellarMagnitude, p -> planetType, p -> discoveryYear,
                    p -> massMultiplier, p -> massWrt, p -> radiusMultiplier, p -> radiusWrt,
                    p -> orbitalRadius, p -> orbitalPeriod, p -> eccentricity, p -> detectionMethod,
                    p -> statusExploration, p -> idVessel);
    }
    fclose(fplanet);
    printf("\nSauvegarde des planetes reussie!\n");

    //fichier sonde
    FILE *fvessel = NULL;
    fvessel = fopen("Res/Data/Projet_C_L1 - Vessel.csv","w");

    if (!fvessel) //si le programme trouve pas le folder inclus le fichier ou il ne peut pas ouvrir le fichier, il s'arrete
    {
        printf("Erreur d'ouverture et sauvegarder des donnees de fichier vesselcsv\n");
        return;
    }

    //Ecrire la premiere ligne
    fprintf(fvessel, "Id_Vessel,Planet,Status\n");

    //Ecrire les nouveaux donnees
    for (int i = 0; i < nbVessel; i++)
    {
        const Vessel *v = &fleet[i];

        fprintf(fvessel, "%s,%d,%s\n",
            v -> idVessel, v -> idPlanet, v -> status);
    }
    fclose(fvessel);
    printf("Sauvegarde des sondes reussie!\n");
};

void readFloat(float *token)
{
    char temp [50];

    fgets(temp, sizeof(temp), stdin);
    cleanStr(temp);

    if (strlen(temp) == 0)
    {
        *token = 0.0f;
    }
    else
    {
        *token = atof(temp);
    }
}

void readInt(int *token)
{
    char temp [50];

    fgets(temp, sizeof(temp), stdin);
    cleanStr(temp);

    if (strlen(temp) == 0)
    {
        *token = 0;
    }
    else
    {
        *token = atoi(temp);
    }
}

void readStr(char *token, int maxToken)
{
    fgets(token, maxToken, stdin); //stdin: standard input, apporter les donnees de la clavier
    cleanStr(token); //fgets() collecte aussi \n 

    //si l'utilisateur ajouter ','
    for (int i = 0; i < strlen(token); i++)
    {
        if (token[i] == ',')
        {
            token[i] = '_';
        }
    }
}

int yesOrNo()
{
    int choice;
    printf("[0 ou entree] Non | [autre nombre]: Oui\n"); 
    readInt(&choice);
    if (choice != 0)
    {
        return 1;
    }
    return 0;
}

