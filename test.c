/*
 * Copyright (C) 2013 Lucas Pesenti
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
 * MA  02110-1301, USA.
 */

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
