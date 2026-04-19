#include <stdio.h>
#include <string.h>  

#include "include/modify.h"

//main
int main()
{   
    Planet catalog[maxPlanet];
    int nbPlanet = 0;
    nbPlanet = loadPlanet("Res/Data/Projet_C_L1 - Planet.csv", catalog);

    Vessel fleet[maxVessel];
    int nbVessel = 0;
    nbVessel = loadVessel("Res/Data/Projet_C_L1 - Vessel.csv", fleet);

    
    int targetPlanet;
    char targetVessel[50];
    int statusFilterP;
    char statusFilterV[20];

    char choixPlanet [2];
    int choixP;
    int choixV;
    
    printf("%d planetes chargees\n", nbPlanet);
    printf("%d sondes chargees\n", nbVessel);

    //MENU
    int choixMenu;
    printf("\nBIENVENUE!!!\n");

    do 
    {
        printf("\nMENU\n");
        printf("0: Sauvegarder et sortir la programme\n");
        printf("1: CATALOGUE PLANETE\n");
        printf("2: FLOTTE\n");
        printf("Votre choix: ");

        readInt(&choixMenu);

        switch (choixMenu)
        {
            case 1: //MENU PLANETES
                do
                {
                    printf("\nMENU PLANETE\n");
                    printf("0: Retour au Menu Principal\n");
                    printf("1: Chercher/Agir sur une planete (par ID)\n");
                    printf("2: Chercher les planetes (par filtre)\n");
                    printf("3: Ajouter une nouvelle planete\n");
                    printf("4: Afficher tout le catalogue\n");
                    printf("Votre choix : ");

                    readInt(&choixP);

                    switch (choixP)
                    {
                        case 1: //ID P
                            printf("\nEntrez l'ID de la planete : ");
                            readInt(&targetPlanet);
                            Planet *p = searchP(catalog, nbPlanet, targetPlanet);

                            if (p != NULL)
                            {
                                int actionP;
                                printP(p);
                                
                                do //PLANET ACTION
                                {
                                    float g;

                                    printf("\nPLANET ACTION\n");
                                    printf("0: Retour au Menu Planete\n");
                                    printf("1: Modifier les informations\n");
                                    printf("2: Afficher la gravite\n");
                                    printf("Votre choix : ");

                                    readInt(&actionP);

                                    switch (actionP)
                                    {
                                        case 1: //modifier P
                                            editPlanet(catalog, nbPlanet, targetPlanet);
                                            break;
                                        case 2:
                                            g = calculGravity(p);
                                            if(g >= 0)
                                            {
                                                printf("La force gravitationnelle de la planete %s par rapport a la Terre est: %f\n", p->namePlanet, g);
                                            }
                                            break;
                                        default:
                                            break;
                                    }
                                } while (actionP != 0);
                            }
                            else
                            {
                                printf("\nNe trouve pas cette planete\n");
                            }
                            break;
                        case 2: //filtre P
                            do 
                            {
                                printf("\nEntrez le statut a filtrer (0: Non exploree, 1: En cours, 2: Terminee): ");
                                readInt(&statusFilterP);
                            } while ((statusFilterP != 0) && (statusFilterP != 1) && (statusFilterP != 2));

                            filterP(catalog, nbPlanet, statusFilterP);
                            break;
                        case 3: //ajouter P
                            targetPlanet = nbPlanet + 1;
                            nbPlanet = addPlanet(catalog, nbPlanet, targetPlanet);
                            break;
                        case 4: //afficher catalogue
                            printCatalog(catalog, nbPlanet);
                            break;
                        default:
                            break;
                    }
                } while (choixP != 0);
                break;
            case 2: //MENU FLOTTE
                do 
                {
                    int choixStatusV;

                    printf("\nMENU SONDE\n");
                    printf("0: Sauvegarder et Retour au Menu Principal\n");
                    printf("1: Chercher/Agir sur une sonde (par ID)\n");
                    printf("2: Chercher les sondes par filtre\n");
                    printf("3: Ajouter une nouvelle sonde\n");
                    printf("4: Afficher toute la flotte\n");
                    printf("Votre choix : ");

                    readInt(&choixV);

                    switch (choixV)
                    {
                        case 1: //ID V
                            printf("\nEntrez l'ID de la sonde : ");
                            readStr(targetVessel, 50);
                            Vessel *v = searchV(fleet, nbVessel, targetVessel);

                            if (v != NULL)
                            {
                                int actionV;
                                printV(v);

                                do 
                                {
                                    printf("\nSONDE ACTION\n");
                                    printf("0: Retour au Menu Sonde\n");
                                    printf("1: Action sur la sonde\n");
                                    printf("Votre choix : ");

                                    readInt(&actionV);

                                    if (actionV == 1) //Action sur sonde
                                    {
                                        if(strcmp(v->status, "AVAILABLE") == 0 ) //lancer
                                        {   
                                            printf("\nPreparer lancer la sonde %s\n", v->idVessel);
                                            printf("Entrez l'ID planete: ");
                                            readInt(&targetPlanet);
                                            launchVessel(catalog, nbPlanet, targetPlanet, fleet, nbVessel, targetVessel);
                                        }
                                        else if (strcmp(v->status, "NOT AVAILABLE") == 0) //maintenir
                                        {
                                            printf("\nMaintenir la sonde %s", targetVessel);
                                            maintainVessel(fleet, nbVessel, targetVessel);
                                        }
                                        else //retourner
                                        {
                                            strcpy(targetVessel, v->idVessel);
                                            printf("\nRappeller la sonde %s", targetVessel);
                                            returnVessel(catalog, nbPlanet, v->idPlanet, fleet, nbVessel, targetVessel);
                                        }
                                        
                                        actionV = 0;
                                    }
                                } while (actionV != 0);
                            }
                            else
                            {
                                printf("\nNe trouve pas cette sonde\n");
                            }
                            break;
                        case 2: //filtre V
                            do 
                            {
                                printf("\nEntrez le statut a filtrer (0: DISPONIBLE, 1: PAS DISPONIBLE, 2: EN MISSION): ");
                                readInt(&choixStatusV);
                            } while ((choixStatusV != 0) && (choixStatusV != 1) && (choixStatusV != 2));

                            //StatusV
                            if (choixStatusV == 0)
                            {
                                strcpy(statusFilterV, "AVAILABLE");
                            }
                            else if (choixStatusV == 1)
                            {
                                strcpy(statusFilterV, "NOT AVAILABLE");
                            }
                            else
                            {
                                strcpy(statusFilterV, "MISSION");
                            }
                            
                            filterV(fleet, nbVessel, statusFilterV);
                            break;
                        case 3: //ajouter V
                            printf("\nL'ID de la nouvelle sonde: ");
                            readStr(targetVessel, 50);
                            nbVessel = addVessel(fleet, nbVessel, targetVessel);
                            break;
                        case 4: //afficher flotte
                            printFleet(fleet, nbVessel);
                            break;
                        default:
                            break;

                    }
                    
                } while (choixV != 0);
                break;    
            
            case 0:
                saveFile(catalog, nbPlanet, fleet, nbVessel);
                printf("%d planetes\n", nbPlanet);
                printf("%d sondes\n", nbVessel);
                printf("\nMerci d'avoir utilise notre programme!!!\n");
                break;
            default:
                break;
        }
    } while (choixMenu != 0);
    
    return 0;
}