#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct
{
    char matricula[10];
    char nombre[15];
    float calif;
    char letra;
    float notaEval[10];//10 de cantidad de evaluaciones

} ESTUD;

typedef struct
{
    ESTUD Estudiantes[40];
    char nombMateria[10];
    int cantEst;
    int cantEval;
    float valorPorcentual[10];//10 de cantidad de evaluaciones
    char evaluaciones[10][15];//10 de cantidad de evaluaciones y 20 para espacio del nombre

} MATERIA;

char letter(float );
char* concat(const char *, const char *);

int main()
{
    textbackground(BLUE);
    textcolor(YELLOW);
    FILE *ofp;
    int i, j,may = 0,men = 0;
    float porcientoTotal = 0;
    MATERIA Materia;
    clrscr();
    printf("Digite el nombre de la materia: ");
    gets(Materia.nombMateria);
    fflush(stdin);
    printf("Digite la cantidad de estudiantes (Max: 40): ");
    scanf("%d",&Materia.cantEst);
    fflush(stdin);
    printf("Digite la cantidad de evaluaciones (Max: 10) : ");
    scanf("%d",&Materia.cantEval);
    fflush(stdin);
    char *filename = concat(Materia.nombMateria,".txt");
    ofp = fopen( filename, "w");
    free(filename);

    /* Recibir evaluaciones del grupo Descripcion + Valor conceptual */

    clrscr();
    for(i = 0; i < Materia.cantEval ; i++)
    {
        clrscr();
        printf("\n\n*** Descripcion Evaluacion # %d/%d ***\n\n",i+1,Materia.cantEval);
        printf("Digite la descripcion: ");
        gets(Materia.evaluaciones[i]);
        fflush(stdin);
        printf("Digite valor porcentual (en base a 100): ");
        scanf("%f",&Materia.valorPorcentual[i]);
        fflush(stdin);
        Materia.valorPorcentual[i] = Materia.valorPorcentual[i]/100;
        if(porcientoTotal < 0)
        {
            clrscr();
            printf("\n\nERROR EL VALOR PORCENTUAL NO PUEDE ESTAR POR DEBAJO DE 0");
            exit(1);
        }
        porcientoTotal += Materia.valorPorcentual[i];
    }

    if(porcientoTotal != 1)
    {
        clrscr();
        printf("\n\nERROR LA SUMA DEL VALOR PORCENTUAL NO PUEDE EXCEDER DE 100%");
        exit(1);
    }

    /* Recibir nombre y matricula del estudiante */

    clrscr();
    for(i = 0; i < Materia.cantEst ; i++)
    {
        printf("\n\n*** Nombre y matricula del estudiante # %d/%d ***\n\n",i+1,Materia.cantEst);
        printf("Digite el nombre completo del estudiante:");
        fflush(stdin);
        gets(Materia.Estudiantes[i].nombre);
        printf("Digite matricula del estudiante:");
        fflush(stdin);
        gets(Materia.Estudiantes[i].matricula);
        Materia.Estudiantes[i].calif = 0; //inicializacion de variable acumuladora de puntos totales en 0
    }

    /* Recibir calificaciones del estudiante */

    clrscr();
    for(i = 0; i < Materia.cantEval ; i++)
    {
        clrscr();
        printf("\n\n***%s (%.2f) %d/%d***\n\n",Materia.evaluaciones[i], Materia.valorPorcentual[i], i+1, Materia.cantEval);
        for(j = 0; j < Materia.cantEst ; j++)
        {
            printf("Calificacion de el estudiante: %s, matricula :%9s\nCalificacion (##/100):",Materia.Estudiantes[j].nombre, Materia.Estudiantes[j].matricula);
            scanf("%f",&Materia.Estudiantes[j].notaEval[i]);
            fflush(stdin);
            Materia.Estudiantes[j].calif += (Materia.Estudiantes[j].notaEval[i] * Materia.valorPorcentual[i]);//sacar de inmediato puntos totales
            Materia.Estudiantes[j].letra = letter(Materia.Estudiantes[j].calif);
        }
    }

    /* Imprimir calificaciones del grupo */

    fflush(stdin);
    clrscr();
    printf("\n\n*** Reporte de calificaciones grupo: %s ***\n\n",Materia.nombMateria);
    printf("  Matricula  |      Nombre               |");
    for(i = 0 ; i < Materia.cantEval ; i++)
    {
        printf("%10s (%.2f)|", Materia.evaluaciones[i], Materia.valorPorcentual[i]);
    }
    printf("Puntos Totales   |  Calif. Final");


    for(j = 0; j < Materia.cantEst ; j++)
    {
        printf("\n  %9s  |%27s|   ", Materia.Estudiantes[j].matricula, Materia.Estudiantes[j].nombre);
        for(i = 0 ; i < Materia.cantEval ; i++)
        {
            printf("     %3.2f     |  ",Materia.Estudiantes[j].notaEval[i]);
        }
        printf("%15.2f   |      %c",Materia.Estudiantes[j].calif, Materia.Estudiantes[j].letra);
    }

    float mayor = Materia.Estudiantes[0].calif;
    float menor = Materia.Estudiantes[0].calif;

    for (i = 0; i < Materia.cantEst; i++)
    {
        if (Materia.Estudiantes[i].calif> mayor)
        {
            mayor=Materia.Estudiantes[i].calif;
            may = i;
        }
    }


    for (i = 0; i < Materia.cantEst; i++)
    {
        if (Materia.Estudiantes[i].calif < menor)
        {
            menor=Materia.Estudiantes[i].calif;
            men = i;
        }
    }

    printf("\n\nEl estudiante de mayor nota es %s %s con una calif. de %.2f equivalente a %c\n",Materia.Estudiantes[may].nombre, Materia.Estudiantes[may].matricula, Materia.Estudiantes[may].calif, Materia.Estudiantes[may].letra);
    printf("\nEl estudiante de menor nota es %s %s con una calif. de %.2f equivalente a %c\n",Materia.Estudiantes[men].nombre, Materia.Estudiantes[men].matricula, Materia.Estudiantes[men].calif, Materia.Estudiantes[men].letra);

    /* Imprimir calificaciones del grupo en archivo txt*/

    fprintf(ofp, "\n\n*** Reporte de calificaciones grupo: %s ***\n\n",Materia.nombMateria);
    fprintf(ofp,"  Matricula  |      Nombre               |");
    for(i = 0 ; i < Materia.cantEval ; i++)
    {
        fprintf(ofp,"%10s (%.2f)|", Materia.evaluaciones[i], Materia.valorPorcentual[i]);
    }
    fprintf(ofp,"Puntos Totales   |  Calif. Final");


    for(j = 0; j < Materia.cantEst ; j++)
    {
        fprintf(ofp,"\n  %9s  |%27s|   ", Materia.Estudiantes[j].matricula, Materia.Estudiantes[j].nombre);
        for(i = 0 ; i < Materia.cantEval ; i++)
        {
            fprintf(ofp,"     %3.2f     |  ",Materia.Estudiantes[j].notaEval[i]);
        }
        fprintf(ofp,"%15.2f   |      %c",Materia.Estudiantes[j].calif, Materia.Estudiantes[j].letra);
    }

    fprintf(ofp,"\n\nEl estudiante de mayor nota es %15s %9s con una calif. de %.2f equivalente a %c",
            Materia.Estudiantes[may].nombre, Materia.Estudiantes[may].matricula, Materia.Estudiantes[may].calif, Materia.Estudiantes[may].letra);

    fprintf(ofp,"\n\nEl estudiante de menor nota es %15s %9s con una calif. de %.2f equivalente a %c",
            Materia.Estudiantes[men].nombre, Materia.Estudiantes[men].matricula, Materia.Estudiantes[men].calif, Materia.Estudiantes[men].letra);

    free(ofp);

    return 0;
}

//Es para hallar la nota en letra
char letter(float promedio)
{
    if(promedio < 60)
        return 'F';
    else if(promedio >= 60 && promedio < 70)
        return 'D';
    else if(promedio >= 70 && promedio < 80)
        return 'C';
    else if(promedio >= 80 && promedio < 90)
        return 'B';
    else if(promedio >= 90)
        return 'A';
}

//funcion para conectar 2 strings
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

