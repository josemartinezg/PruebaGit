#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.c>
//Definición de colores a utilizar.
#define COLORFONDO LIGHTGRAY
#define COLORTEXTO BLUE

#define CSELFONDO  YELLOW
#define CSELTEXTO  BLUE

#define CTDEF       LIGHTGRAY
#define CFDEF       BLACK
//Definición de MACROS para las teclas.
#define ARRIBA    72
#define ABAJO     80
#define DERECHA   77
#define IZQUIERDA 75

#define ESC     27
#define ENTER   13

#define CANT 4
#define LEN 20

#define MAX   100
#define MAXEVA 10
#define MAXDES 40

typedef struct
{
    char matricula[10];
    char nombre[30];
    float puntosTotales;
    char calificacion;

}ESTUD;
typedef struct
{
    char descripcion[MAXDES];
    float puntosPorEvaluacion;
    float porcentaje;

}EVAL;


int main()
{
       char opciones[CANT][LEN] = {" Opc 1 ",
                               " Opc 2 ",
                               " Opc 3 ",
                               " Salir "};
   int opc;

   opc = menu(opciones,CANT,10,5);

   if ( opc != -1 )
      printf("Opci%cn seleccionada ==> [%s]",162,opciones[opc]);


    int i,j, cantEval, cantEstud;
    EVAL evaluacion[MAXEVA];
    char descripcion[20][MAXDES];
    float puntosPorEvaluacion[20];
    ESTUD estudiantes[MAX];
    printf("Introduzca la cantidad de evaluaciones del curso: \n");
    scanf("%d", &cantEval);
    for (i = 1; i<=cantEval; i++)
    {
        printf("Decsriba en dos palabras la evaluacion no. %d\n", i);
        fflush(stdin);
        gets(descripcion[i]);
        fflush(stdin);
        puts(descripcion[i]);
        fflush(stdin);
    }

    printf("Introduzca la cantidad de eestudiantes a tomar el curso: \n");
    scanf("%d", &cantEstud);

    for (i = 0; i<cantEstud; i++)
    {
        fflush(stdin);
        printf("%d. Matricula en formato (2018-0000): \n", i+1);
        gets(estudiantes[i].matricula);
        fflush(stdin);
        puts(estudiantes[i].matricula);
        fflush(stdin);
        printf("%d. Nombre: \n", i+1);
        gets(estudiantes[i].nombre);
        puts(estudiantes[i].nombre);
        fflush(stdin);
        for (j = 1; j<=cantEval; j++)
        {
            do {
            fflush(stdin);
            puts(descripcion[j]);
            fflush(stdin);
            scanf("%f", &puntosPorEvaluacion[j]);
            fflush(stdin);
            printf("%.2f\n", puntosPorEvaluacion[j]);
            if (puntosPorEvaluacion[j]< 0 || puntosPorEvaluacion[j] > 100) {
                printf("DIGITE UNA CALIFICACION VALIDA\n");
            }
            }while (puntosPorEvaluacion[j] < 0 || puntosPorEvaluacion[j] > 100);
        }
    }
    return 0;
}


void desplegar(char opc[CANT][LEN],int n, int px, int py, int sel )
{
   int ind;

   for ( ind = 0; ind < n; ind ++ )
   {
      setcolor(COLORTEXTO,COLORFONDO);
      if ( ind == sel )
         setcolor(CSELTEXTO,CSELFONDO);
      gotoxy(px,py+ind);
      printf(" %s \n",opc[ind]);
   }

   colordefault();
   return;
}

void setcolor(int text,int fond)
{
   textcolor(text);
   textbackground(fond);
}

void colordefault()
{
   setcolor(CTDEF,CFDEF);
}


int menu(char opc[CANT][LEN], int n,int px,int py)
{
   int select = 0;
   char tecla;

   _setcursortype(0);
   do{
      desplegar(opc,n,px,py,select);
      tecla = getch();

      if ( tecla == ARRIBA )
      {
         select --;

         if ( select < 0 )
            select = n - 1;
      }

      if ( tecla == ABAJO )
      {
         select ++;

         if ( select == n )
            select = 0;
      }
   }while ( tecla != ESC && tecla != ENTER );

   if ( tecla == ESC )
      select = -1;
   else
   {
      if ( select != n-1 )
         menu(opc,n,px+10,py+select);
   }

   return select;
}

int random(int a, int b)
{
   return rand() % (b-a+1) + a;
}
