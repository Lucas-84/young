#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "young.h"

int main(void)
{
   int t[9] = { 10, 3, 12, 5, 6, 14, 10, 2, 15 };
   YOUNG_Tableau p = YOUNG_Creer(2, 2);

   printf("Testing phase... ");
   assert(p != YOUNG_NIL);
   assert(YOUNG_Inserer(p, 24) != -1);
   assert(YOUNG_Inserer(p, 42) != -1);
   assert(YOUNG_Inserer(p, 12) != -1);
   assert(YOUNG_Inserer(p, 13) != -1);
   assert(YOUNG_Inserer(YOUNG_NIL, 22) == -1);
   assert(YOUNG_Inserer(p, INT_MAX) == -1);
   assert(YOUNG_Inserer(p, 78) == -1);
   assert(YOUNG_Rechercher(p, 12) == 1);
   assert(YOUNG_ExtraireMin(YOUNG_NIL) == INT_MAX);
   assert(YOUNG_Rechercher(p, 24) == 1);
   assert(YOUNG_Rechercher(p, 42) == 1);
   assert(YOUNG_Rechercher(YOUNG_NIL, 42) == 0);
   assert(YOUNG_Rechercher(p, 14) == 0);   
   assert(YOUNG_Rechercher(p, 43) == 0);
   assert(YOUNG_Rechercher(p, 2) == 0);   
   assert(YOUNG_ExtraireMin(p) == 12);
   assert(YOUNG_Rechercher(p, 12) == 0);
   assert(YOUNG_ExtraireMin(p) == 13);
   assert(YOUNG_Rechercher(p, 12) == 0);
   assert(YOUNG_ExtraireMin(p) == 24);
   assert(YOUNG_ExtraireMin(p) == 42);
   YOUNG_Trier(t, 3);
   assert(t[0] == 2);
   assert(t[1] == 3);
   assert(t[2] == 5);
   assert(t[3] == 6);
   assert(t[4] == 10);
   assert(t[5] == 10);
   assert(t[6] == 12);
   assert(t[7] == 14);
   assert(t[8] == 15);
   YOUNG_Liberer(p);
   puts("OK");
   return 0;
}
