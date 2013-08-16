#ifndef H_LP_YOUNG_20130816113657
#define H_LP_YOUNG_20130816113657

#define YOUNG_NIL NULL

typedef struct YOUNG_Matrice *YOUNG_Tableau;

/*
 * Crée un tableau de Young de dimensions m x n. Retourne un handle de type
 * YOUNG_Tableau qui égale la valeur spéciale YOUNG_NIL en cas d'échec.
 * Temps d'exécution : O(mn).
 */
YOUNG_Tableau YOUNG_Creer(int m, int n);

/*
 * Retourne et supprime le minimum du tableau de Young p. En cas d'erreur, la
 * valeur spéciale INT_MAX est retournée.
 * Temps d'exécution : O(m+n).
 */
int YOUNG_ExtraireMin(YOUNG_Tableau p);

/*
 * Insère la clé k de type entier dans le tableau de Young p. Attention : la
 * clé doit être dans l'intervalle semi-ouvert [-INT_MAX; INT_MAX[.
 * Temps d'exécution : O(m+n).
 */
int YOUNG_Inserer(YOUNG_Tableau p, int k);

/*
 * Recherche l'élément k dans le tableau de Young p. Retourne 1 si il est
 * présent, 0 sinon.
 * Temps d'exécution : O(m+n).
 */
int YOUNG_Rechercher(YOUNG_Tableau p, int k);

/*
 * Trie un tableau T de taille n x n grâce à un tableau de Young. Retourne -1
 * en cas d'erreur, 0 sinon.
 * Temps d'exécution : O(n^3).
 */
int YOUNG_Trier(int *T, int n);

/*
 * Libère la mémoire allouée au tableau de Young p. Le contenu du handle p est
 * indéfini après un appel à cette fonction.
 * Temps d'exécution : O(1).
 */
void YOUNG_Liberer(YOUNG_Tableau p);

#endif
