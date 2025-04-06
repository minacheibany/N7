#ifndef LISTE_NOEUD_H
#define LISTE_NOEUD_H

#include "graphe.h"
#include <stdbool.h>

/**
 * Type abstrait représentant une liste de nœuds.
 */
typedef struct ListeNoeud ListeNoeud;
typedef ListeNoeud *liste_noeud_t;

/**
 * Crée une liste de nœuds, initialement vide.
 *
 * Post-conditions : `r = creer_liste()` => `r != NULL`, `est_vide_liste(r)`
 * @return liste nouvellement créée (de type liste_noeud_t)
 */
liste_noeud_t creer_liste();

/**
 * Détruit la liste passée en paramètre.
 *
 * Pré-conditions : liste_ptr != NULL
 * Post-conditions : *liste_ptr == NULL
 *
 * @param liste_ptr pointeur sur la liste à détruire
 */
void detruire_liste(liste_noeud_t *liste_ptr);

/**
 * Test si la liste passée en paramètre est vide.
 *
 * Pré-conditions : liste != NULL
 *
 * @param liste [in] liste à tester
 * @return vrai ssi la liste ne contient aucun élément
 */
bool est_vide_liste(const liste_noeud_t liste);

/**
 * Test si le nœud donné appartient à la liste donnée.
 *
 * Pré-conditions : liste != NULL
 *
 * @param liste [in] liste à parcourir
 * @param noeud nœud à rechercher
 * @return vrai ssi nœud est dans liste
 */
bool contient_noeud_liste(const liste_noeud_t liste, noeud_id_t noeud);

/**
 * Test si l'arrête donnée appartient à la liste donnée.
 * L'arrête (source, destination) appartient à la liste ssi destination appartient à liste
 * et si prec(destination) == source.
 *
 * Pré-conditions : liste != NULL
 *
 * @param liste [in] liste à parcourir
 * @param source nœud source de l'arrête
 * @param destination nœud destination de l'arrête
 * @return vrai ssi l'arrête (source,destination) est dans liste
 */
bool contient_arrete_liste(const liste_noeud_t liste, noeud_id_t source, noeud_id_t destination);

/**
 * Récupère la distance associée au nœud donné dans la liste donnée.
 * Si le nœud n'existe pas dans la liste, retourne `INFINITY`.
 *
 * Pré-conditions : liste != NULL
 * Post-conditions : `contient_noeud_liste(liste, noeud)` <=> `distance_noeud_liste(liste, noeud) != INFINITY`
 *
 * @param liste [in] liste à parcourir
 * @param noeud nœud dont on veut la distance
 * @return distance associée à nœud dans liste ou INFINITY si nœud n'est pas dans liste
 */
float distance_noeud_liste(const liste_noeud_t liste, noeud_id_t noeud);

/**
 * Récupère le nœud précédent associé au nœud donné dans la liste donnée.
 * Si le nœud n'existe pas, retourne `NO_ID`.
 *
 * Pré-conditions : liste != NULL
 * Post-conditions : `!contient_noeud_liste(liste, noeud)` => `precedent_noeud_liste(liste, noeud) = NO_ID`
 *
 * @param liste [in] liste à parcourir
 * @param noeud nœud dont on veut le précédent
 * @return précédent associé au nœud dans la liste (ou `NO_ID` si nœud n'est pas dans liste)
 */
noeud_id_t precedent_noeud_liste(const liste_noeud_t liste, noeud_id_t noeud);

/**
 * Trouve le (un) nœud de la liste dont la distance associée est la plus petite,
 * ou renvoie `NO_ID` si la liste est vide.
 *
 * Pré-conditions : liste non NULL
 * Post-conditions : `n = min_noeud_liste(liste) && n != NO_ID` =>
 *   pour tout `n'`, `contient_noeud_liste(liste, n')`, `distance_noeud_liste(liste, n) <= distance_noeud_liste(liste, n')`
 *
 * @param liste [in] liste à parcourir
 * @return nœud qui minimise la distance, ou `NO_ID` si pas de nœud
 */
noeud_id_t min_noeud_liste(const liste_noeud_t liste);

/**
 * Insère le nœud donné dans la liste.
 *
 * Pré-conditions : liste != NULL
 *
 * @param liste [in,out] liste dans laquelle insérer l'élément
 * @param noeud nœud à insérer (caractérisé par son identifiant)
 * @param precedent nœud précédent du nœud à insérer (prec(n))
 * @param distance distance du nœud à insérer (dist(n))
 */
void inserer_noeud_liste(liste_noeud_t liste, noeud_id_t noeud, noeud_id_t precedent, float distance);

/**
 * Modifie les valeurs associées au nœud donné dans la liste donnée.
 * Si le nœud n'est pas dans la liste, il est ajouté.
 *
 * Pré-conditions : liste != NULL
 * Post-conditions :
 *   - `contient_noeud_liste(liste, noeud)`
 *   - `distance_noeud_liste(liste, noeud) == distance`
 *   - `precedent_noeud_liste(liste, noeud) == precedent`
 *
 * @param liste [in,out] liste à modifier
 * @param noeud nœud à modifier
 * @param precedent nouveau nœud précédent pour nœud
 * @param distance nouvelle distance pour nœud
 */
void changer_noeud_liste(liste_noeud_t liste, noeud_id_t noeud, noeud_id_t precedent, float distance);

/**
 * Supprime le nœud donné de la liste. Si le nœud n'est pas dans la liste,
 * ne fait rien.
 *
 * Pré-conditions : liste != NULL
 * Post-conditions : après `supprimer_noeud_liste(liste, n)` : `!contient_noeud_liste(liste, n)`
 *
 * @param liste [in,out] liste à modifier
 * @param noeud nœud à supprimer de liste
 */
void supprimer_noeud_liste(liste_noeud_t liste, noeud_id_t noeud);

#endif // LISTE_NOEUD_H
