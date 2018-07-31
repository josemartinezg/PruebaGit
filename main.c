#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define LEN 60
#define CANT  5

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
MATERIA getInfoCurso(MATERIA);
MATERIA getInfoEval(MATERIA);
MATERIA getInfoEstud(MATERIA);
MATERIA getCalificaciones(MATERIA);
void imprimirResultados(MATERIA);

int main()
{
    textbackground(BLUE);
    textcolor(YELLOW);
    MATERIA Materia;
    FILE *ofp;
    char tecla;
    int i, j, ind;
    char opciones[CANT][LEN] = {"1. Registrar Curso                       ",
                                "2. Registrar Evaluacion(es)              ",
                                "3. Registrar Estudiante(s)               ",
                                "4. Visualizar Calificacion(es) del curso ",
                                "5. Salir                                 "};
    for ( ind = 0; ind < CANT; ind ++ )
    {
        printf("%s\n", opciones[ind]);
    }
    printf("Escoja una opcion...");
    tecla = getch();
    if (tecla == '1'){
         Materia = getInfoCurso(Materia);
    }if (tecla == '2'){
        Materia = getInfoEval(Materia);
    }if (tecla == '3'){
        Materia = getInfoEstud(Materia);
    }if (tecla == '4'){
        Materia = getCalificaciones(Materia);
    }if (tecla == '5'){
        imprimirResultados(Materia);
    }

   /*int opc;

   opc = menu(opciones,CANT,10,5);
*/

    return 0;
}
/*
    Función "getInfoCurso".
    Recibe: un dato de tipo MATERIA.
    Devuelve: un dato de tipo MATERIA.
    Obtiene toda la información, del usuario, concerniente a un curso.
*/
MATERIA getInfoCurso(MATERIA Materia){
    clrscr();

    FILE *ofp;
    do{
        printf("Digite el nombre de la materia: ");
        gets(Materia.nombMateria);
        fflush(stdin);
    if (strlen(Materia.nombMateria) == 0)
        printf("\n\nERROR NO PUEDE DEJAR EL NOMBRE DEL ESTUDIANTE EN BLANCO.\n  ");
    }while(strlen(Materia.nombMateria) == 0);

    do{
        printf("Digite la cantidad de estudiantes (Max: 40): ");
        fflush(stdin);
        scanf("%d",&Materia.cantEst);
    if (Materia.cantEst <= 0 || Materia.cantEst > 40)
        printf("\n\nERROR, REVISE EL NUMERO DE ESTUDIANTES DIGITADOS.\n");
    }while (Materia.cantEst <= 0 || Materia.cantEst > 40);
    fflush(stdin);
    do{
        printf("Digite la cantidad de evaluaciones (Max: 10) : ");
        scanf("%d",&Materia.cantEval);
    if (Materia.cantEval <= 0 || Materia.cantEval > 10)
        printf("\n\nERROR, REVISE EL NUMERO DE MATERIAS DIGITADOS.\n");
    }while (Materia.cantEval <= 0 || Materia.cantEval > 10);
    fflush(stdin);
    char *filename = concat(Materia.nombMateria,".txt");
    ofp = fopen( filename, "w");
    free(filename);

    /* Recibir evaluaciones del grupo Descripcion + Valor conceptual */
    return Materia;
    clrscr();
}
/*
    Función "getInfoEval".
    Recibe: un dato de tipo MATERIA.
    Devuelve: un dato de tipo MATERIA.
    Obtiene toda la información, del usuario, concerniente a una evaluación de un curso.
*/
MATERIA getInfoEval(MATERIA Materia){
    int i;
    float porcientoTotal = 0;
    for(i = 0; i < Materia.cantEval ; i++)
    {
        clrscr();

        printf("\n\n*** Descripcion Evaluacion # %d/%d ***\n\n",i+1,Materia.cantEval);
        do{
            printf("Digite la descripcion: ");
            gets(Materia.evaluaciones[i]);
            fflush(stdin);
            if (strlen(Materia.evaluaciones[i]) == 0)
                printf("\n\nERROR NO PUEDE DEJAR LA DESCRIPCION EN BLANCO.\n  ");
        }while(strlen(Materia.evaluaciones[i]) == 0);
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
        printf("\n\nERROR LA SUMA DEL VALOR PORCENTUAL NO PUEDE EXCEDER NI ESTAR POR DEBAJO DE 100%");
        exit(1);
    }

    /* Recibir nombre y matricula del estudiante */
    return Materia;
    clrscr();

}
/*
    Función "getInfoEstud".
    Recibe: un dato de tipo MATERIA.
    Devuelve: un dato de tipo MATERIA.
    Obtiene toda la información, del usuario, concerniente a los estudiantes de la materia.
*/
MATERIA getInfoEstud(MATERIA Materia)
{
    int i;
    for(i = 0; i < Materia.cantEst ; i++)
    {
        printf("\n\n*** Nombre y matricula del estudiante # %d/%d ***\n\n",i+1,Materia.cantEst);
        do{
            printf("Digite el nombre completo del estudiante:");
            fflush(stdin);
            gets(Materia.Estudiantes[i].nombre);
            if (strlen(Materia.Estudiantes[i].nombre) == 0)
                printf("\n\nERROR NO PUEDE DEJAR EL NOMBRE DEL ESTUDIANTE EN BLANCO.\n");
        }while(strlen(Materia.Estudiantes[i].nombre) == 0);

        do{
            printf("Digite matricula del estudiante:");
            fflush(stdin);
            gets(Materia.Estudiantes[i].matricula);
            if (strlen(Materia.Estudiantes[i].matricula) == 0 || matriculaTypo(Materia.Estudiantes[i].matricula) == 1)
                printf("\n\nERROR FORMATO INVALIDO DE LA MATRICULA.\n");
        }while(strlen(Materia.Estudiantes[i].matricula) == 0 || matriculaTypo(Materia.Estudiantes[i].matricula) == 1);

        Materia.Estudiantes[i].calif = 0; //inicializacion de variable acumuladora de puntos totales en 0
    }

    /* Recibir calificaciones del estudiante */
    return Materia;
    clrscr();
}
/*
    Función "getCalificaciones".
    Recibe: un dato de tipo MATERIA.
    Devuelve: un dato de tipo MATERIA.
    Obtiene toda la información, del usuario, concerniente a las calificaciones obtenidas por los estudiantes de una materia.
*/
MATERIA getCalificaciones(MATERIA Materia)
{
    int i, j;
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
    return Materia;
    clrscr();
}
/*
    Función "imprimirResultados".
    Recibe: un dato de tipo MATERIA.
    Devuelve: nada.
    Muestra en orden toda la información obtenida y cálculada a solicitud de la especificación del programa.
*/
void imprimirResultados(MATERIA Materia)
{
    int i, j, may = 0,men = 0;;
    FILE *ofp;
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

}
/*
    Función "letter".
    Recibe: float.
    Devuelve: char.
    Calcula la letra correspondiente en base a los rangos de promedio.
*/
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

/*
    Función "concat".
    Recibe: char *. char *.
    Devuelve: char*.
    Recibe dos punteros de caracteres (dos cadenas o strings) y los concatena.
*/
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
/*
    Función "matriculaTypo".
    Recibe: char[].
    Devuelve: int.
    Recibe un arreglo de caracteres (una cadenas o string) y verifica caracter a caracter si cumple
    con el formato requerido de una matricula.
*/
int matriculaTypo (char mat[])
{
    int len = strlen(mat), lenCod = strlen(&mat[5]);
    int i;

    if (lenCod < 4 || lenCod > 4) return 1;

    for (i = 0; i < len; i++) {
        if (i < 4)
        {
            if (mat[i] < '0' || mat[i] > '9')
                return 1;
        }

        if (mat[4] != '-')
            return 1;

        if (i > 4)
        {
            if (mat[i] < '0' || mat[i] > '9')
                return 1;
        }
    }
    return 0;
}

