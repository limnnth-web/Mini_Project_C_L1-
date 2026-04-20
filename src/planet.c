#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char *field[20]; //cree 20 pointeurs 
    int nbColumn = 0;
    char *token = NULL;

    //passer la premier ligne (header)
    fgets(perLine, maxPerLine, f); //aller a fichier f, commencer a &perLine, max des donnees est maxPerLine

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
        if (nbColumn == 15) //compte nbColumn de 0 a 15, il compte le signal ","
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

    //identifiant
    printf("ID Planete: %d\n", p->idPlanet);
    printf("Nom de la Planete: %s\n", p->namePlanet);

    //des informations pour sciences
    if (p->distance == -1.0f)
    {
        printf("Distance de la planete a la Terre en annees-lumiere: Inconnue\n");
    }
    else
    {
        printf("Distance de la planete a la Terre en annees-lumiere: %f\n", p->distance);
    }

    if (p->stellarMagnitude == -999.0f)
    {
        printf("Magnitude stellaire: Inconnue\n");
    }
    else
    {
        printf("La luminosite de la planete (plus la planete est brillante, plus le nombre qui lui est attribue est faible): %f\n", p->stellarMagnitude);
    }

    printf("Type de planete: %s\n", p->planetType);

    if (p->discoveryYear == -1)
    {
        printf("Annee de la decouverte de la planete: Inconnue\n");
    }
    else
    {
        printf("Annee de la decouverte de la planete: %d\n", p->discoveryYear);
    }
    

    if (p->massMultiplier == -1.0f)
    {
        printf("Le multiplicateur de masse: Inconnue\n");
    }
    else
    {
        printf("Le multiplicateur de masse: %f\n", p->massMultiplier);
    }

    printf("L'unite de masse: %s\n", p->massWrt);

    if (p->radiusMultiplier == -1.0f)
    {
        printf("Le multiplicateur de rayon: Inconnue\n");
    }
    else
    {
        printf("Le multiplicateur de rayon: %f\n", p->radiusMultiplier);
    }

    printf("L'unite de rayon: %s\n", p->radiusWrt);

    if (p->orbitalRadius == -1.0f)
    {
        printf("Le rayon orbital: Inconnue\n");
    }
    else
    {    
        printf("Le rayon orbital: %f\n", p->orbitalRadius);
    }
    
    if (p->orbitalPeriod == -1.0f)
    {
        printf("La periode orbitale: Inconnue\n");
    }
    else
    {
        printf("La periode orbitale: %f\n", p->orbitalPeriod);

    }
    
    if (p->eccentricity == -1.0f)
    {
        printf("La excentricite: Inconnue\n");
    }
    else
    {
        printf("La excentricite: %f\n", p->eccentricity);

    }

    printf("La methode de detection: %s\n", p->detectionMethod);

    //statut et Sonde
    if (p->statusExploration == 0)
    {
        printf("Statut exploration: Non exploree\n");
    }
    else if (p->statusExploration == 1)
    {
        printf("Statut exploration: En cours d'exploration\n");
    }
    else
    {
        printf("Statut exploration: Exploration terminee\n");
    }

    printf("ID Vessel: %s\n", p->idVessel);
}

//Aficher catalogue
void printCatalog(Planet *catalog, int nbPlanet)
{
    //Verifier le nombre des Planete
    if (nbPlanet == 0)
    {
        printf("Le catalogue est vide\n");
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

    printf("Il y a %d planete(s) dans cet etat\n", count);
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

//Modifier planete 
void editPlanet(Planet *catalog, int nbPlanet, int targetPlanet)
{
    Planet *idPTarget = NULL;
    int choice = 0;
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
    printf("Distance actuelle: %f \n Voulez-vous la modifier?: ", idPTarget->distance);
    if (yesOrNo() == 1)
    {
        readFloat(&idPTarget->distance);
    }

        //stellarMagnitude
    printf("Magnitude stellaire actuelle: %f \n Voulez-vous la modifier?: ", idPTarget->stellarMagnitude);
    if (yesOrNo() == 1)
    {
        readFloat(&idPTarget->stellarMagnitude);
    }

    //planetType 
    printf("Choisissez type de la planete: \n");
    printf("Type de planete actuelle: %s \n[1] Gas Giant | [2] Neptune-like | [3] Terrestrial \n[4] Super Earth | [5] Unknown | [6] Autre type \n[autre nombre] rester inchange:\n", 
        idPTarget->planetType);
    readInt(&choice);

    switch (choice)
    {
        case 1:
            strcpy(idPTarget->planetType, "Gas Giant");
            break;
        case 2:
            strcpy(idPTarget->planetType, "Neptune-like");
            break;
        case 3:
            strcpy(idPTarget->planetType, "Terrestrial");
            break;
        case 4:
            strcpy(idPTarget->planetType, "Super Earth");
            break;
        case 5:
            strcpy(idPTarget->planetType, "Unknown");
            break;
        case 6:
            do
            {
                printf("Entrez le nom du type de la planete: \n");
                readStr(token, maxToken);
            } while (strlen(token) != 0);
            
            strcpy(idPTarget->planetType, token);
            break;
        default:
            break;
    }

    choice = 0;

        //discoveryYear
    printf("L'annee de decouverte actuelle: %d \n Voulez-vous la modifier?: ", idPTarget->discoveryYear);
    if (yesOrNo() == 1)
    {
        readInt(&idPTarget->discoveryYear);
    }

        //massMultiplier
    printf("Multiplicateur de masse actuelle: %f \n Voulez-vous le modifier?: ",idPTarget->massMultiplier);
    if (yesOrNo() == 1)
    {
        readFloat(&idPTarget->massMultiplier);
    }

        //massWrt
    printf("L'unite de masse actuelle: %s \nChoisissez l'unite de masse [1] Jupiter | [2] Earth | [3] Unknown | [autre nombre] rester inchange :\n", idPTarget->massWrt);
    readInt(&choice);

    switch (choice)
    {
        case 1:
            strcpy(idPTarget->massWrt, "Jupiter");
            break;
        case 2:
            strcpy(idPTarget->massWrt, "Earth");
            break;
        case 3:
            strcpy(idPTarget->massWrt, "");
            break;
        default:
            break;
    }

    choice = 0;

        //radiusMultiplier
    printf("Multiplicateur de rayon actuelle: %f \nVoulez-vous le modifier?: ",idPTarget->radiusMultiplier);
    if (yesOrNo() == 1)
    {
        readFloat(&idPTarget->radiusMultiplier);
    }

        //radiusWrt
    printf("Choisissez l'unite de rayon [1] Jupiter | [2] Earth | [3] Unknown | [autre nombre] rester inchange: (l'unite de rayon actuelle: %s) :\n", idPTarget->radiusWrt);
    readInt(&choice);

    switch (choice)
    {    
        case 1:
            strcpy(idPTarget->radiusWrt, "Jupiter");
            break;
        case 2:
            strcpy(idPTarget->radiusWrt, "Earth");
            break;
        case 3:
            strcpy(idPTarget->radiusWrt, "");
            break;
        default:
            break;
    }

    choice = 0;

        //orbitalRadius
    printf("Rayon orbital actuelle: %f \nVoulez-vous le modifier?: ",idPTarget->orbitalRadius);
    if (yesOrNo() == 1)
    {
        readFloat(&idPTarget->orbitalRadius);
    }

        //orbitalPeriod
    printf("Periode orbitale actuelle: %f \nVoulez-vous la modifier?: ",idPTarget->orbitalPeriod);
    if (yesOrNo() == 1)
    {
        readFloat(&idPTarget->orbitalPeriod);
    }

        //eccentricity
    printf("Excentricite actuelle: %f \nVoulez-vous le modifier?: ",idPTarget->eccentricity);
    if (yesOrNo() == 1)
    {
        readFloat(&idPTarget->eccentricity);
    }

    //detectionMethod
    printf("Methode de detection actuelle: %s \nVoulez-vous la modifier?: ", idPTarget->detectionMethod);
    if (yesOrNo() == 1)
    {
        printf("Choisissez le nom de la methode de detection: \n");
        printf("[1] Eclipse Timing Variations | [2] Astrometry | [3] Transit  \n[4] Pulsation Timing Variations | [5] Pulsar Timing | [6] Direct Imaging \n[7] Transit Timing Variations | [8] Radial Velocity | [9] Gravitational Microlensing \n[10] Disk Kinematics | [11] Orbital Brightness Modulation | [12] Other | [autre nombre] ignorer\n");
        readInt(&choice);

        switch (choice)
        {
        case 1:
            strcpy(idPTarget->detectionMethod, "Eclipse Timing Variations");
            break;
        case 2:
            strcpy(idPTarget->detectionMethod, "Astrometry");
            break;
        case 3:
            strcpy(idPTarget->detectionMethod, "Transit");
            break;
        case 4:
            strcpy(idPTarget->detectionMethod, "Pulsation Timing Variations");
            break;
        case 5:
            strcpy(idPTarget->detectionMethod, "Pulsar Timing");
            break;
        case 6:
            strcpy(idPTarget->detectionMethod, "Direct Imaging");
            break;
        case 7:
            strcpy(idPTarget->detectionMethod, "Transit Timing Variations");
            break;
        case 8:
            strcpy(idPTarget->detectionMethod, "Radial Velocity");
            break;
        case 9:
            strcpy(idPTarget->detectionMethod, "Gravitational Microlensing");
            break;
        case 10:
            strcpy(idPTarget->detectionMethod, "Disk Kinematics");
            break;
        case 11:
            strcpy(idPTarget->detectionMethod, "Orbital Brightness Modulation");
            break;
        case 12:
            readStr(token, maxToken);

            if (strlen(token) != 0)
            {
                strcpy(idPTarget->detectionMethod, token);
            }            
            break;
        default:
            break;
        }

        choice = 0;
    }
        
    //statusExploration 
    if (idPTarget->statusExploration != 1)
    {
        printf("Statut exploration actuelle: %d (0 = Non explorée, 1 = En cours d'exploration, 2 = Exploration terminée) \n", idPTarget->statusExploration);
        printf("Voulez-vous le modifier?: ");

        if (yesOrNo() == 1)        
        {
            if (idPTarget->statusExploration == 2)
            {
                idPTarget->statusExploration = 0;
            }
            else
            {
                idPTarget->statusExploration = 2;
            }
        }
    }
    
    printf("Succes mise a jour de la planete %s!\n", idPTarget->namePlanet);
    printP(idPTarget);
}

//Ajouter planete 
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
    int choice = 0;

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
    printf("Distance de la nouvelle planete \nLa connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("La distance de la planete a la Terre en annees-lumiere: \n");
        readFloat(&newP.distance);
    }
    else
    {
        newP.distance = -1.0f;
    }

    //stellarMagnitude
    printf("Magnitude stellaire de la nouvelle planete \nLa connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("La magnitude stellaire de la planete: \n");
        readFloat(&newP.stellarMagnitude);
    }
    else
    {
        newP.stellarMagnitude = -999.0f;
    }

    //planetType
    printf("Type de la nouvelle planete \nLe connaissez-vous? ");
    if (yesOrNo() == 0)
    {
        strcpy(newP.planetType, "Unknown");
    }
    else
    {
        printf("Choisissez type de la planete: \n");
        printf("[1] Gas Giant | [2] Neptune-like | [3] Terrestrial \n[4] Super Earth | [autre nombre] Autre type:\n");
        readInt(&choice);

        switch (choice)
        {
            case 1:
                strcpy(newP.planetType, "Gas Giant");
                break;
            case 2:
                strcpy(newP.planetType, "Neptune-like");
                break;
            case 3:
                strcpy(newP.planetType, "Terrestrial");
                break;
            case 4:
                strcpy(newP.planetType, "Super Earth");
                break;
            default:
                do
                {
                    printf("Entrez le nom du type de la planete: \n");
                    readStr(token, maxToken);
                } while (strlen(token) != 0);
                
                strcpy(newP.planetType, token);
                break;
        }

        choice = 0;
    }

    //discoveryYear
    printf("L'annee de decouverte la nouvelle planete \nLa connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("L'annee de decouverte de la planete: \n");
        readInt(&newP.discoveryYear);
    }
    else
    {
        newP.discoveryYear = -1;
    }

    //massMultiplier
    printf("Multiplicateur de masse de la nouvelle planete \nLe connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("Le multiplicateur de masse de la planete: \n");
        readFloat(&newP.massMultiplier);
    }
    else
    {
        newP.massMultiplier = -1.0f;
    }

    //massWrt
    printf("Choisissez l'unite de masse [1] Jupiter | [2] Earth | [autre nombre] ignorer: \n");
    readInt(&choice);

    switch (choice)
    {
        case 1:
            strcpy(newP.massWrt, "Jupiter");
            break;
        case 2:
            strcpy(newP.massWrt, "Earth");
            break;
        default:
            strcpy(newP.massWrt, "");
            break;
    }

    choice = 0;

    //radiusMultiplier
    printf("Multiplicateur de rayon de la nouvelle planete \nLe connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("Le multiplicateur de rayon de la planete: \n");
        readFloat(&newP.radiusMultiplier);
    }
    else
    {
        newP.radiusMultiplier = -1.0f;
    }

    //radiusWrt
    printf("Choisissez l'unite de masse [1] Jupiter | [2] Earth | [autre nombre] ignorer: \n");
    readInt(&choice);

    switch (choice)
    {    
        case 1:
            strcpy(newP.radiusWrt, "Jupiter");
            break;
        case 2:
            strcpy(newP.radiusWrt, "Earth");
            break;
        default:
            strcpy(newP.radiusWrt, "");
            break;
    }

    choice = 0;

    //orbitalRadius
    printf("Rayon orbital de la nouvelle planete \nLe connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("Le rayon orbital de la planete: \n");
        readFloat(&newP.orbitalRadius);
    }
    else
    {
        newP.orbitalRadius = -1.0f;
    }

    //orbitalPeriod
    printf("Periode orbital de la nouvelle planete \nLa connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("La periode orbital de la planete: \n");
        readFloat(&newP.orbitalPeriod);
    }
    else
    {
        newP.orbitalPeriod = -1.0f;
    }

    //eccentricity
    printf("Excentricite de la nouvelle planete \nLa connaissez-vous? ");
    if (yesOrNo() == 1)
    {
        printf("L'excentricite de la planete: \n");
        readFloat(&newP.eccentricity);
    }
    else
    {
        newP.eccentricity = -1.0f;
    }

    //detectionMethod
    printf("Entrez le nom de la nouvelle methode de detection (OBLIGATOIRE): \n");
    printf("Choisissez le nom de la methode de detection: \n");
        printf("[1] Eclipse Timing Variations | [2] Astrometry | [3] Transit  \n[4] Pulsation Timing Variations | [5] Pulsar Timing | [6] Direct Imaging \n[7] Transit Timing Variations | [8] Radial Velocity | [9] Gravitational Microlensing \n[10] Disk Kinematics | [11] Orbital Brightness Modulation | [autre nombre] Other \n");
        readInt(&choice);

        switch (choice)
        {
        case 1:
            strcpy(newP.detectionMethod, "Eclipse Timing Variations");
            break;
        case 2:
            strcpy(newP.detectionMethod, "Astrometry");
            break;
        case 3:
            strcpy(newP.detectionMethod, "Transit");
            break;
        case 4:
            strcpy(newP.detectionMethod, "Pulsation Timing Variations");
            break;
        case 5:
            strcpy(newP.detectionMethod, "Pulsar Timing");
            break;
        case 6:
            strcpy(newP.detectionMethod, "Direct Imaging");
            break;
        case 7:
            strcpy(newP.detectionMethod, "Transit Timing Variations");
            break;
        case 8:
            strcpy(newP.detectionMethod, "Radial Velocity");
            break;
        case 9:
            strcpy(newP.detectionMethod, "Gravitational Microlensing");
            break;
        case 10:
            strcpy(newP.detectionMethod, "Disk Kinematics");
            break;
        case 11:
            strcpy(newP.detectionMethod, "Orbital Brightness Modulation");
            break;
        default:
            do
            {
                printf("Entrez le nom de la nouvelle methode de detection (OBLIGATOIRE): \n");
                readStr(token, maxToken);

                if (strlen(token) != 0)
                {
                    strcpy(newP.detectionMethod, token);
                } 
            } while (strlen(token) == 0);
                break;
        }

        choice = 0;
    
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

