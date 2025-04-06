/**
 * @file liste_noeud.c
 * @brief Implantation du module liste_noeud pour gérer des listes chaînées de nœuds.
 *
 * @author Mina Cheibany
 */

#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

typedef struct ListeNoeud ListeNoeud;

typedef struct _cellule
{
    noeud_id_t noeud;
    float distance;
    noeud_id_t precedent;
    struct _cellule *suivant;
} Cellule;

struct ListeNoeud
{
    Cellule *tete;
    Cellule *queue;
};

liste_noeud_t creer_liste()
{
    ListeNoeud *liste = (ListeNoeud *)malloc(sizeof(ListeNoeud));
    if (liste == NULL)
        return NULL; // gérer les cas où l'allocation de mémoire pour la liste échoue
    liste->tete = NULL;
    liste->queue = NULL;
    return liste;
}

void detruire_liste(liste_noeud_t *liste_ptr)
{
    if (liste_ptr == NULL || *liste_ptr == NULL)
        return;
    Cellule *courant = (*liste_ptr)->tete;
    while (courant != NULL)
    {
        Cellule *aSupprimer = courant;
        courant = courant->suivant;
        free(aSupprimer);
    }
    free(*liste_ptr);
    *liste_ptr = NULL;
}

bool est_vide_liste(const liste_noeud_t liste)
{
    return liste->tete == NULL;
}

bool contient_noeud_liste(const liste_noeud_t liste, noeud_id_t noeud)
{
    Cellule *courant = (liste)->tete;
    while (courant != NULL)
    {
        if (courant->noeud == noeud)
            return true;
        courant = courant->suivant;
    }
    return false;
}

bool contient_arrete_liste(const liste_noeud_t liste, noeud_id_t source, noeud_id_t destination)
{
    Cellule *courant = liste->tete;
    while (courant != NULL)
    {
        if (courant->noeud == destination && courant->precedent == source)
            return true;
        courant = courant->suivant;
    }
    return false;
}

float distance_noeud_liste(ListeNoeud *liste, noeud_id_t noeud)
{
    Cellule *courant = liste->tete;
    while (courant != NULL)
    {
        if (courant->noeud == noeud)
            return courant->distance;
        courant = courant->suivant;
    }
    return INFINITY;
}

noeud_id_t precedent_noeud_liste(ListeNoeud *liste, noeud_id_t noeud)
{
    Cellule *courant = liste->tete;
    while (courant != NULL)
    {
        if (courant->noeud == noeud)
            return courant->precedent;
        courant = courant->suivant;
    }
    return NO_ID;
}

noeud_id_t min_noeud_liste(ListeNoeud *liste)
{
    if (liste->tete == NULL)
        return NO_ID;

    Cellule *courant = liste->tete;
    Cellule *minCellule = liste->tete;

    while (courant != NULL)
    {
        if (courant->distance < minCellule->distance)
        {
            minCellule = courant;
        }
        courant = courant->suivant;
    }
    return minCellule->noeud;
}

void inserer_noeud_liste(ListeNoeud *liste, noeud_id_t noeud, noeud_id_t precedent, float distance)
{
    Cellule *nouvelleCellule = (Cellule *)malloc(sizeof(Cellule));
    nouvelleCellule->noeud = noeud;
    nouvelleCellule->precedent = precedent;
    nouvelleCellule->distance = distance;
    nouvelleCellule->suivant = NULL;

    if (liste->queue == NULL)
    {
        liste->tete = nouvelleCellule;
    }
    else
    {
        liste->queue->suivant = nouvelleCellule;
    }
    liste->queue = nouvelleCellule;
}

void changer_noeud_liste(ListeNoeud *liste, noeud_id_t noeud, noeud_id_t nv_precedent, float nv_distance)
{
    Cellule *courant = liste->tete;
    while (courant != NULL)
    {
        if (courant->noeud == noeud)
        {
            courant->precedent = nv_precedent;
            courant->distance = nv_distance;
            return;
        }
        courant = courant->suivant;
    }
    inserer_noeud_liste(liste, noeud, nv_precedent, nv_distance);
}

void supprimer_noeud_liste(ListeNoeud *liste, noeud_id_t noeud)
{
    if (liste->tete == NULL)
        return;

    if (liste->tete->noeud == noeud)
    {
        Cellule *aSupprimer = liste->tete;
        liste->tete = liste->tete->suivant;
        if (liste->tete == NULL)
            liste->queue = NULL;
        free(aSupprimer);
        return;
    }

    Cellule *courant = liste->tete;
    while (courant->suivant != NULL && courant->suivant->noeud != noeud)
    {
        courant = courant->suivant;
    }

    if (courant->suivant != NULL)
    {
        Cellule *aSupprimer = courant->suivant;
        courant->suivant = courant->suivant->suivant;
        if (courant->suivant == NULL)
            liste->queue = courant;
        free(aSupprimer);
    }
}
