#include <stdio.h>
#include <stdlib.h>
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
