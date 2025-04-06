#include "dijkstra.h"
#include "graphe.h"
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>
/**
 * @file dijkstra.c
 * @brief Implantation du module dijkstra pour calculer le plus court chemin.
 *
 * @author Mina Cheibany
 */

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Le noeud de départ est caractérisé par un prédécesseur qui vaut `NO_ID`.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud a pour précédent `NO_ID`, on a fini (c'est le noeud de départ, le chemin de
 *     départ à départ se compose du simple noeud départ)
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
void construire_chemin_vers(liste_noeud_t *chemin, const liste_noeud_t *visites, noeud_id_t nœud)
{
    noeud_id_t precedent = precedent_noeud_liste(visites, nœud);
    if (precedent == NO_ID)
    {
        inserer_noeud_liste(chemin, nœud, NO_ID, 0.0);
    }
    else
    {
        construire_chemin_vers(chemin, visites, precedent);
        float distance = distance_noeud_liste(visites, nœud);
        inserer_noeud_liste(chemin, nœud, precedent, distance);
    }
}

float dijkstra(
    const struct graphe_t *graphe,
    noeud_id_t source, noeud_id_t destination,
    liste_noeud_t **chemin)
{
    // Initialisation
    liste_noeud_t *AVisiter = creer_liste();
    liste_noeud_t *Visites = creer_liste();
    inserer_noeud_liste(AVisiter, source, NO_ID, 0.0);

    while (!est_vide_liste(AVisiter))
    {
        noeud_id_t noeud_courant = min_noeud_liste(AVisiter);
        float distance_courant = distance_noeud_liste(AVisiter, noeud_courant);
        noeud_id_t precedent_courant = precedent_noeud_liste(AVisiter, noeud_courant);
        inserer_noeud_liste(Visites, noeud_courant, precedent_courant, distance_courant);
        supprimer_noeud_liste(AVisiter, noeud_courant);
        if (noeud_courant == destination)
        {
            if (chemin != NULL)
            {
                *chemin = creer_liste();
                construire_chemin_vers(*chemin, Visites, destination);
            }
            detruire_liste(&AVisiter);
            detruire_liste(&Visites);
            return distance_courant;
        }
        size_t nb_voisins = nombre_voisins(graphe, noeud_courant);
        noeud_id_t *voisins = malloc(nb_voisins * sizeof(noeud_id_t));
        noeuds_voisins(graphe, noeud_courant, voisins);
        for (size_t i = 0; i < nb_voisins; i++)
        {
            noeud_id_t voisin = voisins[i];
            if (!contient_noeud_liste(Visites, voisin))
            {
                float distance_voisin = distance_courant + noeud_distance(graphe, noeud_courant, voisin);
                if (distance_voisin < distance_noeud_liste(AVisiter, voisin))
                {
                    changer_noeud_liste(AVisiter, voisin, noeud_courant, distance_voisin);
                }
                else
                {
                    inserer_noeud_liste(AVisiter, voisin, noeud_courant, distance_voisin);
                }
            }
        }
        free(voisins);
    }

    // la destination n'est pas atteignable
    detruire_liste(&AVisiter);
    detruire_liste(&Visites);
    return INFINITY;
}
