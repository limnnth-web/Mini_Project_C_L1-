#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "planet.h"
#include "modify.h"


//Charger planete
int loadPlanet(const char *planetcsv, Planet *catalog)
{
    FILE *f = NULL;
    f = fopen(planetcsv, "r");
    
    if (!f) //si le programme trouve pas le fichier, il s'arrete
    {
        printf("Erreur d'ouverture de fichier planetcsv\n");
        return 0;
    }

    char perLine[maxPerLine];
    int nbPlanet = 0;
    int nbLine = 1;
    char *field[20]; //si l'utilisateur ajoute quelque "," incorrect
    int nbColumn = 0;
    char *token = NULL;

    //passer la premier ligne (header)
    fgets(perLine, maxPerLine, f); //aller a fichier f, commencer a &surLigne, max des donnees est maxSurLigne

    //Charger planete
    while (fgets(perLine, maxPerLine, f) && (nbPlanet < maxPlanet))
    {
        cleanStr(perLine); //pour couper \n et \r

        nbColumn = 0;
        token = perLine; //Debut du mot
        char *pointer = perLine;


        //couper le chaine par ',' ( ',' -> '\0')
        while ((*pointer != '\0') && (nbColumn < 20))
        {
            if (*pointer == ',')
            {
                *pointer = '\0';
                field[nbColumn ++] = token; //field[nbColumn] = token; nbColumn++;
                token = pointer + 1; //Debut de la prochaine mot
            }
            pointer++; //p bouge jusqu'a la prochaine ','
        }

        //pour la derniere column
        if (nbColumn < 20)
        {
            field[nbColumn] = token;
        }

        //condition pour mettre les donnees dans le structure
        if (nbColumn == 15) //compte nbColumn de 0 a 15
        {
            Planet *p = &catalog[nbPlanet];

            p -> idPlanet = atoi(field[0]); // p -> idPlanet = catalog[nbPlanet].idPlanet
            strcpy(p -> namePlanet, field[1]);

            p -> distance = atof(field[2]);
            p -> stellarMagnitude = atof(field[3]);
            strcpy(p -> planetType, field[4]);
            p -> discoveryYear = atoi(field[5]);

            p -> massMultiplier = atof(field[6]);
            strcpy(p -> massWrt, field[7]);
            p -> radiusMultiplier = atof(field[8]);
            strcpy(p -> radiusWrt, field[9]);

            p -> orbitalRadius = atof(field[10]);
            p -> orbitalPeriod = atof(field[11]);
            p -> eccentricity = atof(field[12]);
            strcpy(p -> detectionMethod, field[13]);

            p -> statusExploration = atoi(field[14]);
            strcpy(p -> idVessel, field[15]);
            
            nbPlanet ++;
        }
        else
        {
            printf("La ligne %d corrompue\n", nbLine);
        }
        nbLine ++;
    }
    fclose(f);
    return nbPlanet;
};

//Aficher planete
void printP(const Planet *p)
{
    //Verifier
    if (p == NULL)
    {
        return;
    }

    printf("ID Planete: %d\n", p->idPlanet);
    printf("Nom de la Planete: %s\n", p->namePlanet);
    printf("Distance de la planete a la Terre en annees-lumiere: %f\n", p->distance);
    printf("La luminosite de la planete (plus la planete est brillante, plus le nombre qui lui est attribue est faible): %f\n", p->stellarMagnitude);
    printf("Type de planete: %s\n", p->planetType);
    printf("Annee de la decouverte de la planete: %d\n", p->discoveryYear);
    printf("Le multiplicateur de masse: %f\n", p->massMultiplier);
    printf("L'unite de masse: %s\n", p->massWrt);
    printf("Le multiplicateur de rayon: %f\n", p->radiusMultiplier);
    printf("L'unite de rayon: %s\n", p->radiusWrt);
    printf("Le rayon orbital: %f\n", p->orbitalRadius);
    printf("La periode orbitale: %f\n", p->orbitalPeriod);
    printf("La excentricite: %f\n", p->eccentricity);
    printf("La methode de detection: %s\n", p->detectionMethod);
    printf("Le status exploration: %d\n", p->statusExploration);
    printf("ID Vessel: %s\n", p->idVessel);
}

//Aficher catalogue
void printCatalog(Planet *catalog, int nbPlanet)
{
    //Verifier le nombre des Planete
    if (nbPlanet == 0)
    {
        printf("Le catalogue est vide.\n");
    }
    else
    {
        for (int i = 0; i < nbPlanet; i++)
        {
            printP(&catalog[i]);
            printf("\n");
        }
    }
}

// Planete filtre
void filterP(const Planet *catalog, int nbPlanet, int statusFilter)
{
    int count = 0; 
    
    for (int i = 0; i < nbPlanet; i++)
    {
        if (catalog[i].statusExploration == statusFilter)
        {
            printP(&catalog[i]);
            printf("\n"); 
            count++;
        }
    }

    printf("Il y a %d planete(s) dans cet etat.\n", count);
}

//Chercher idP
Planet* searchP(Planet *catalog, int nbPlanet, int targetPlanet)
{
    Planet *idPTarget = NULL;

    for (int i = 0; i < nbPlanet; i++)
    {
        if (catalog[i].idPlanet == targetPlanet)
        {
            idPTarget = &catalog[i];
            break;
        }
    }
    return idPTarget;
}

//Modifier planete [chưa xong]
void editPlanet(Planet *catalog, int nbPlanet, int targetPlanet)
{
    Planet *idPTarget = NULL;
    int wrt = 0;
    int maxToken = 50;
    char token [maxToken];

    //Chercher la planete
    idPTarget = searchP(catalog, nbPlanet, targetPlanet);

    if (idPTarget == NULL)
    {
        printf("Ne trouve pas cette planete\n");
        return;
    }

    //Modifier la planete
    printf("Modifier la planete %s (id: %d)\n", idPTarget->namePlanet, idPTarget->idPlanet);

        //Distance
    printf("Nouvelle distance (distance actuelle: %f): \n", idPTarget->distance);
    readFloat(&idPTarget->distance);

        //stellarMagnitude
    printf("Nouvelle magnitude stellaire (magnitude stellaire actuelle: %f): \n", idPTarget->stellarMagnitude);
    readFloat(&idPTarget->stellarMagnitude);

 //XEM LẠIIII       //planetType (Xem lại!!!!)
    printf("Choisissez type de planete [1] Gas Giant | [2] Neptune-like | [autre nombre] rester inchange (type de planete actuelle: %s):\n", idPTarget->planetType);
    readInt(&wrt);
    if (wrt == 1)
    {
        strcpy(idPTarget->planetType, "Gas Giant");
    }
    else if (wrt == 2)
    {
        strcpy(idPTarget->planetType, "Neptune-like");
    }
    wrt = 0;

        //discoveryYear
    printf("L'annee de decouverte (L'annee de decouverte actuelle: %d): \n", idPTarget->discoveryYear);
    readInt(&idPTarget->discoveryYear);

        //massMultiplier
    printf("Nouveau multiplicateur de masse (multiplicateur de masse actuelle: %f): \n",idPTarget->massMultiplier);
    readFloat(&idPTarget->massMultiplier);

        //massWrt
    printf("Choisissez l'unite de masse [1] Jupiter | [2] Earth | [autre nombre] rester inchange (l'unite de masse actuelle: %s) :\n", idPTarget->massWrt);
    readInt(&wrt);
    if (wrt == 1)
    {
        strcpy(idPTarget->massWrt, "Jupiter");
    }
    else if (wrt == 2)
    {
        strcpy(idPTarget->massWrt, "Earth");
    }
    wrt = 0;

        //radiusMultiplier
    printf("Nouveau multiplicateur de rayon (multiplicateur de rayon actuelle: %f): \n",idPTarget->radiusMultiplier);
    readFloat(&idPTarget->radiusMultiplier);

        //radiusWrt
    printf("Choisissez l'unite de rayon [1] Jupiter | [2] Earth | [autre nombre] rester inchange: (l'unite de rayon actuelle: %s) :\n", idPTarget->radiusWrt);
    readInt(&wrt);
    if (wrt == 1)
    {
        strcpy(idPTarget->radiusWrt, "Jupiter");
    }
    else if (wrt == 2)
    {
        strcpy(idPTarget->radiusWrt, "Earth");
    }
    wrt = 0;

        //orbitalRadius
    printf("Nouveau rayon orbital (rayon orbital actuelle: %f): \n",idPTarget->orbitalRadius);
    readFloat(&idPTarget->orbitalRadius);


        //orbitalPeriod
    printf("Nouvelle periode orbitale (periode orbitale actuelle: %f): \n",idPTarget->orbitalPeriod);
    readFloat(&idPTarget->orbitalPeriod);

        //eccentricity
    printf("Nouvelle excentricite (excentricite actuelle: %f): \n",idPTarget->eccentricity);
    readFloat(&idPTarget->eccentricity);

 //LƯU Ý!!!       //detectionMethod
    do
    {
        printf("Entrez le nom de la nouvelle methode de détection (OBLIGATOIRE): \n");
        fgets(token, maxToken, stdin); //stdin: standard input, apporter les donnees de la clavier
        cleanStr(token);

        if (strlen(token) == 0)
        {
            printf("Le nom pour la nouvelle methode de détection est obligatoire.\n");
        }
        
    } while (strlen(token) == 0);
    strcpy(idPTarget->detectionMethod, token);
    

    //statusExploration !!!!
    if (idPTarget->statusExploration != 1)
    {
        printf("Choisissez nouvel statut exploration [0 ou entree] Non exploree | [2] Exploration | [autre nombre] rester inchange (statut exploration actuelle: %d (0 = Non explorée, 1 = En cours d'exploration, 2 = Exploration terminée)): \n", idPTarget->statusExploration);
        readInt(&wrt);
        if (wrt == 0)
        {
            idPTarget->statusExploration = 0;
        }
        else if (wrt == 2)
        {
            idPTarget->statusExploration = 2;
        }
        wrt = 0;
    }
    else
    {
        printf("Il n'est pas possible de modifier le statut d'exploration d'une planete en cours d'exploration\n");
    }


    printf("Succes mise à jour de la planète %s!\n", idPTarget->namePlanet);
    printP(idPTarget);

}

//Ajouter planete [chưa xong]
int addPlanet(Planet *catalog, int nbPlanet, int targetPlanet)
{
    //Verifier
    if (nbPlanet >= maxPlanet)
    {
        printf("La memoire est pleine, impossible d'ajouter une nouvelle planete!\n");
        return nbPlanet;
    }
    
    //Id planete
    Planet newP = {0};
    newP.idPlanet = targetPlanet;


    int maxToken = 50;
    char token [maxToken]; 
    int wrt = 0;

    //Nom planete
    do
    {
        printf("Entrez le nom de la nouvelle planete (OBLIGATOIRE): \n");
        fgets(token, maxToken, stdin); //stdin: standard input, apporter les donnees de la clavier
        cleanStr(token);

        if (strlen(token) == 0)
        {
            printf("Le nom pour la nouvelle planete est obligatoire.\n");
        }
        
    } while (strlen(token) == 0);
    strcpy(newP.namePlanet, token);

    //Distance
    printf("Distance de la nouvelle planete (entree pour ignorer): \n");
    readFloat(&newP.distance);

    //stellarMagnitude
    printf("Magnitude stellaire de la nouvelle planete (entree pour ignorer): \n");
    readFloat(&newP.stellarMagnitude);

    //planetType
    printf("Type de la nouvelle planete (entree pour ignorer): \n");
    printf("Choisissez type de planete [1] Gas Giant | [2] Neptune-like | [autre nombre] ignorer: \n");
    readInt(&wrt);

    if (wrt == 1)
    {
        strcpy(newP.planetType, "Gas Giant");
    }
    else if (wrt == 2)
    {
        strcpy(newP.planetType, "Neptune-like");
    }
    else
    {
        strcpy(newP.planetType, "");
    }
    wrt = 0;
    
    //discoveryYear
    printf("L'annee de decouverte la nouvelle planete (entree pour ignorer): \n");
    readInt(&newP.discoveryYear);

    //massMultiplier
    printf("Multiplicateur de masse de la nouvelle planete (entree pour ignorer): \n");
    readFloat(&newP.massMultiplier);

    //massWrt
    printf("Choisissez l'unite de masse [1] Jupiter | [2] Earth | [autre nombre] ignorer: \n");
    readInt(&wrt);

    if (wrt == 1)
    {
        strcpy(newP.massWrt, "Jupiter");
    }
    else if (wrt == 2)
    {
        strcpy(newP.massWrt, "Earth");
    }
    else
    {
        strcpy(newP.massWrt, "");
    }
    wrt = 0;

    //radiusMultiplier
    printf("Multiplicateur de rayon de la nouvelle planete (entree pour ignorer): \n");
    readFloat(&newP.radiusMultiplier);
    
    //radiusWrt
    printf("Choisissez l'unite de masse [1] Jupiter | [2] Earth | [autre nombre] ignorer: \n");
    readInt(&wrt);

    if (wrt == 1)
    {
        strcpy(newP.radiusWrt, "Jupiter");
    }
    else if (wrt == 2)
    {
        strcpy(newP.radiusWrt, "Earth");
    }
    else
    {
        strcpy(newP.radiusWrt, "");
    }
    wrt = 0;

    //orbitalRadius
    printf("Rayon orbital de la nouvelle planete (entree pour ignorer): \n");
    readFloat(&newP.orbitalRadius);

    //orbitalPeriod
    printf("Periode orbital de la nouvelle planete (entree pour ignorer): \n");
    readFloat(&newP.orbitalPeriod);

    //eccentricity
    printf("Excentricite de la nouvelle planete (entree pour ignorer): \n");
    readFloat(&newP.eccentricity);

    //detectionMethod
    do
    {
        printf("Entrez le nom de la nouvelle methode de détection (OBLIGATOIRE): \n");
        fgets(token, maxToken, stdin); //stdin: standard input, apporter les donnees de la clavier
        cleanStr(token);

        if (strlen(token) == 0)
        {
            printf("Le nom pour la nouvelle methode de détection est obligatoire.\n");
        }
        
    } while (strlen(token) == 0);
    strcpy(newP.detectionMethod, token);


    //statusExploration
    newP.statusExploration = 0;

    //idVessel
    strcpy(newP.idVessel, "0");

    catalog[nbPlanet] = newP;
    printf("Vous avez ajoute une planete\n");
    printP(&newP);

    nbPlanet++;
    return nbPlanet;
}


