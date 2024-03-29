#include "Bdef.h"

void BI_BlacsWarn(int ConTxt, int line, char *file, char *form, ...)
{
   extern int BI_Iam;
   extern BLACSCONTEXT **BI_MyContxts;
   int myrow, mycol;
   va_list argptr;
   char cline[100];

   va_start(argptr, form);
   //WCC vsprintf(cline, form, argptr);
   snprintf(cline, 100, form, argptr);
   va_end(argptr);

   if (ConTxt > -1)
   {
      myrow = BI_MyContxts[ConTxt]->cscp.Iam;
      mycol = BI_MyContxts[ConTxt]->rscp.Iam;
   }
   else myrow = mycol = -1;

//WCC   fprintf(stderr,
//WCC:add
   REprintf(
"BLACS WARNING '%s'\nfrom {%d,%d}, pnum=%d, Contxt=%d, on line %d of file '%s'.\n\n",
           cline, myrow, mycol, BI_Iam, ConTxt, line, file);
}
