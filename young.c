#include "young.h"
#include <limits.h>
#include <stdlib.h>

struct YOUNG_Matrice
{
   int m, n;
   int **A;
};

static void YOUNG_Echanger(int *p, int *q)
{
   int tmp = *p;
   
   *p = *q;
   *q = tmp;
}

static void YOUNG_Initialiser(YOUNG_Tableau p)
{
   int i, j;
   
   for (i = 1; i <= p->m; i++)
   {
      for (j = 1; j <= p->n; j++)
      {
         p->A[i][j] = INT_MAX;
      }
   }
}

static void YOUNG_Entasser(YOUNG_Tableau p, int i, int j)
{
   int maxi = i;
   int maxj = j;
   
   if (i < p->m && p->A[i + 1][j] < p->A[maxi][maxj])
   {
      maxi = i + 1;
      maxj = j;
   }
   
   if (j < p->n && p->A[i][j + 1] < p->A[maxi][maxj])
   {
      maxi = i;
      maxj = j + 1;
   }
   
   if (maxi != i || maxj != j)
   {
      p->A[i][j] = p->A[maxi][maxj];
      p->A[maxi][maxj] = INT_MAX;
      YOUNG_Entasser(p, maxi, maxj);
   }
}

YOUNG_Tableau YOUNG_Creer(int m, int n)
{
   YOUNG_Tableau p = malloc(sizeof *p);
   int i;   
   
   if (p == NULL)
   {
      goto erreur;
   }
   
   p->A = malloc((m + 1) * sizeof *p->A);
   
   if (p->A == NULL)
   {
      goto erreur;
   }
   
   for (i = 1; i <= m; i++)
   {   
      p->A[i] = malloc((n + 1) * sizeof *p->A[i]);
         
      if (p->A[i] == NULL)
      {
         goto erreur;
      }
   }   
   
   p->n = n;
   p->m = m;
   YOUNG_Initialiser(p);   
   return p;
   
erreur:
   if (p != NULL)
   {
      if (p->A != NULL)
      {
         int j;
      
         for (j = 1; j < i; j++)
         {
            free(p->A[i]);
         }
            
         free(p->A);
      }
      
      free(p);
   }
   
   return YOUNG_NIL;
}

int YOUNG_ExtraireMin(YOUNG_Tableau p)
{
   int min;
   
   if (p == YOUNG_NIL)
   {
      return INT_MAX;
   }
   
   min = p->A[1][1];
   
   p->A[1][1] = INT_MAX;
   YOUNG_Entasser(p, 1, 1);
   return min;
}

int YOUNG_Inserer(YOUNG_Tableau p, int k)
{   
   int i, j, stable;

   if (p == YOUNG_NIL || p->A[p->m][p->n] < INT_MAX || k == INT_MAX)
   {
      return -1;
   }
     
   p->A[p->m][p->n] = k;
   i = p->m;
   j = p->n;
   stable = 0;
   
   do
   {
      int maxi = i;
      int maxj = j;
   
      if (i > 1 && p->A[i - 1][j] > p->A[maxi][maxj])
      {
         maxi = i - 1;
         maxj = j;
      }
      
      if (j > 1 && p->A[i][j - 1] > p->A[maxi][maxj])
      {
         maxi = i;
         maxj = j - 1;
      }

      if (maxi != i || maxj != j)
      {
         YOUNG_Echanger(&p->A[maxi][maxj], &p->A[i][j]);
         i = maxi;
         j = maxj;
      }
      else
      {
         stable = 1;
      }
   } while (stable == 0);
   
   return 0;
}

int YOUNG_Rechercher(YOUNG_Tableau p, int k)
{
   int i = 1;
   int j = 1;

   if (p == YOUNG_NIL)
      return 0;
   
   while (i < p->m || j < p->n)
   {
      int maxi = i;
      int maxj = j;
      
      if (i < p->m && p->A[i + 1][j] > p->A[maxi][maxj] && p->A[i + 1][j] <= k)
      {
         maxi = i + 1;
         maxj = j;
      }
      
      if (j < p->n && p->A[i][j + 1] > p->A[maxi][maxj] && p->A[i][j + 1] <= k)
      {
         maxi = i;
         maxj = j + 1;
      }
      
      if (p->A[maxi][maxj] == k)
      {
         return 1;
      }
      else if (i == maxi && j == maxj)
      {
         return 0;
      }
         
      i = maxi;
      j = maxj;
   }
   
   return 0;
}

int YOUNG_Trier(int *T, int n)
{
   YOUNG_Tableau p;
   int i;

   if (T == NULL || n == 0)
   {
      goto erreur;
   }

   p = YOUNG_Creer(n, n);
   
   if (p == YOUNG_NIL)
   {
      goto erreur;
   }
   
   for (i = 0; i < n * n; i++)
   {
      if (YOUNG_Inserer(p, T[i]) == -1)
      {
         goto erreur;   
      }
   }
   
   for (i = 0; i < n * n; i++)
   {
      T[i] = YOUNG_ExtraireMin(p);
      
      if (T[i] == INT_MAX)
      {
         goto erreur;
      }
   }

   YOUNG_Liberer(p);
   return 0;   
   
erreur:
   YOUNG_Liberer(p);
   return -1;
}

void YOUNG_Liberer(YOUNG_Tableau p)
{
   if (p != YOUNG_NIL)
   {
      int i;
      
      for (i = 1; i <= p->m; i++)
      {
         free(p->A[i]);
      }
      
      free(p->A);
      free(p);
   }
}
