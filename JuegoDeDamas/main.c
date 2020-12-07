#include <stdio.h>
#include <stdlib.h>

#define NomSize 20

#define Punto 46
#define Aster 42

#define PiezaJug1 80
#define PiezaJug2 112
#define ReinaJug1 81
#define ReinaJug2 113

typedef struct{
    char PrimerNom[NomSize];
    char SegundoNom[NomSize];
} JUGADOR;

void ImpTablero(int *Tablero[9][9]);
int LetrasToNum(char Letra);
int MoverPiezaJug1(int **Tablero[9][9], int Jugador);
int MoverPiezaJug2(int **Tablero[9][9], int Jugador);
int CheckQUEEN_P(int **Tablero[9][9]);
int CheckQUEEN_p(int **Tablero[9][9]);
int CharToInt(char Letra);
int TurnoJug1(int **Tablero[9][9], int **Jugador);
int TurnoJug2(int **Tablero[9][9], int **Jugador);
void GuardarFILE(int *Tablero[9][9], JUGADOR Jug1, JUGADOR Jug2, char *JuegoACTUAL);
FILE* abrir_archivo(char *nombre, char *modo);
void cerrar_archivo(FILE *archivo);
void Leer_Juego_Guardado(int **Tablero[9][9], JUGADOR **Jug1, JUGADOR **Jug2, char *JuegoACTUAL);
void Pedir_tablas(int *Tablero[9][9], int FichasActJug1, int FichasActJug2);

int main()
{
    int JugardorACT = 1, Turno = 1, i, j, FichasActJug1 = 0, FichasActJug2 = 0, RespJueGuar = 0;
    char OpcionSel;
    JUGADOR Jug1, Jug2;
    char JuegoACTUAL[] = "Juego_G.txt";
    FILE *GuardarJuego;
    int Tablero[9][9] = {
        {49},
        {111, PiezaJug1, Punto, PiezaJug1, Punto, PiezaJug1, Punto, PiezaJug1, Punto},
        {111, Punto, PiezaJug1, Punto, PiezaJug1, Punto, PiezaJug1, Punto, PiezaJug1},
        {111, PiezaJug1, Punto, PiezaJug1, Punto, PiezaJug1, Punto, PiezaJug1, Punto},
        {111, Punto, Aster, Punto, Aster, Punto, Aster, Punto, Aster},
        {111, Aster, Punto, Aster, Punto, Aster, Punto, Aster, Punto},
        {111, Punto, PiezaJug2, Punto, PiezaJug2, Punto, PiezaJug2, Punto, PiezaJug2},
        {111, PiezaJug2, Punto, PiezaJug2, Punto, PiezaJug2, Punto, PiezaJug2, Punto},
        {111, Punto, PiezaJug2, Punto, PiezaJug2, Punto, PiezaJug2, Punto, PiezaJug2}
    }; //FILA y COLUMNA

    int Prueba[9][9] = {
        {111},
        {111, PiezaJug2, Punto, Aster, Punto, ReinaJug1, Punto, Aster, Punto},
        {111, Punto, PiezaJug2, Punto, PiezaJug2, Punto, Aster, Punto, Aster},
        {111, Aster, Punto, Aster, Punto, Aster, Punto, Aster, Punto},
        {111, Punto, PiezaJug2, Punto, PiezaJug2, Punto, Aster, Punto, Aster},
        {111, PiezaJug2, Punto, Aster, Punto, PiezaJug2, Punto, Aster, Punto},
        {111, Punto, Aster, Punto, Aster, Punto, Aster, Punto, Aster},
        {111, Aster, Punto, Aster, Punto, Aster, Punto, Aster, Punto},
        {111, Punto, Aster, Punto, Aster, Punto, Aster, Punto, Aster}
    }; //FILA y COLUMNA

    printf("Hay un juego guardado? (1 = si)\n");
    scanf("%d", &RespJueGuar);
    if(RespJueGuar == 1){
        Leer_Juego_Guardado(&Tablero, &Jug1, &Jug2, JuegoACTUAL);
        Turno = Tablero[0][0] - 48;
        JugardorACT = Tablero [0][1] - 48;
    }
    else{
        printf("Nombre del Jugador No. 1\n");
        scanf("%s %s", &Jug1.PrimerNom, &Jug1.SegundoNom);
        printf("%s %s\n", Jug1.PrimerNom, Jug1.SegundoNom);
        printf("Nombre del Jugador No. 2\n");
        scanf("%s %s", &Jug2.PrimerNom, &Jug2.SegundoNom);
        printf("%s %s\n", Jug2.PrimerNom, Jug2.SegundoNom);
    }

    /*
    while(OpcionSel != '3'){
        CheckQUEEN_p(&Prueba); //FUNCIONA
        CheckQUEEN_P(&Prueba); //FUNICONA
        ImpTablero(Prueba); // test
        MoverPiezaJug1(&Prueba, 1); //test
        printf("\ntermino el turno\n");
        scanf("%c", &OpcionSel);
    }*/

    while(OpcionSel != '4'){
        if(JugardorACT == 1){
            ImpTablero(Tablero);
            printf("\nTurno numero: %d\n", Turno);
            printf("Jugador Actual: %d\n", JugardorACT);
            printf("Juega: %s %s \n", Jug1.PrimerNom, Jug1.SegundoNom);
            printf("Opciones:\n [1]: Jugar\n [2]: Pedir tablas\n [3]: Guardar\n [4]: salir\n");
            scanf("%s", &OpcionSel); //getchar imprime todo dos veces
            switch(OpcionSel){
                case '1':
                    JugardorACT = MoverPiezaJug1(&Tablero, 1);
                    Tablero[0][1] = JugardorACT + 48;
                    break;
                case '2':
                    Pedir_tablas(Tablero, FichasActJug1, FichasActJug2);
                    break;
                case '3':
                    GuardarFILE(Tablero, Jug1, Jug2, JuegoACTUAL);
                    break;
            }
        }
        else{
            if(JugardorACT == 2){
                ImpTablero(Tablero);
                printf("\nTurno numero: %d\n", Turno);
                printf("Jugador Actual: %d\n", JugardorACT);
                printf("Juega: %s %s \n", Jug2.PrimerNom, Jug2.SegundoNom);
                printf("Opciones:\n [1]: Jugar\n [2]: Pedir tablas\n [3]: Guardar\n [4]: salir\n");
                scanf("%s", &OpcionSel); //getchar imprime todo dos veces
                switch(OpcionSel){
                    case '1':
                        JugardorACT = MoverPiezaJug2(&Tablero, 2);
                        Tablero[0][1] = JugardorACT + 48;
                        break;
                    case '2':
                        Pedir_tablas(Tablero, FichasActJug1, FichasActJug2);
                        break;
                    case '3':
                        GuardarFILE(Tablero, Jug1, Jug2, JuegoACTUAL);
                        break;
                }
                if( JugardorACT == 1){
                    Turno+=1;
                    Tablero[0][0] = Turno + 48;
                }
            }
        }
        FichasActJug1 = 0;
        FichasActJug2 = 0;
        for(i=0;i<=9;i++){
            for(j=0;j<=9;j++){
                if(Tablero[i][j] == PiezaJug1 || Tablero[i][j] == ReinaJug1){
                    FichasActJug1+=1;
                }
                if(Tablero[i][j] == PiezaJug2 || Tablero[i][j] == PiezaJug2){
                    FichasActJug2+=1;
                }
            }
        }
        if(FichasActJug1 == 0){
            printf("\n\nEL GANADOR ES EL JUGADOR 2\n\n");
            printf("%s %s", Jug2.PrimerNom, Jug2.SegundoNom);
            return;
        }
        if(FichasActJug2 == 0){
            printf("\n\nEL GANADOR ES EL JUGADOR 1\n");
            printf("%s %s\n", Jug1.PrimerNom, Jug1.SegundoNom);
            return;
        }
    }
}

void ImpTablero(int *Tablero[9][9]){
    if (Tablero == NULL){
        return NULL;
    }
    int FIL;
    printf("   a  b  c  d  e  f  g  h\n\n");
    for(FIL = 8;FIL>0;FIL--){
        printf("%d  %c  %c  %c  %c  %c  %c  %c  %c  %d\n",FIL, Tablero[FIL][1], Tablero[FIL][2], Tablero[FIL][3],
               Tablero[FIL][4], Tablero[FIL][5], Tablero[FIL][6], Tablero[FIL][7], Tablero[FIL][8], FIL);
    }
    printf("\n   a  b  c  d  e  f  g  h\n");
}

int LetrasToNum(char Letra){
    switch(Letra){
        case 'a':
        case 'A':
            return 1;
        case 'b':
        case 'B':
            return 2;
        case 'c':
        case 'C':
            return 3;
        case 'd':
        case 'D':
            return 4;
        case 'e':
        case 'E':
            return 5;
        case 'f':
        case 'F':
            return 6;
        case 'g':
        case 'G':
            return 7;
        case 'h':
        case 'H':
            return 8;
    }
    printf("ESTA LETRA NO ES VALIDA");
    return 0;
}

int CheckQUEEN_P(int **Tablero[9][9]){
    if(Tablero[8][1] == PiezaJug1){
        Tablero[8][1] = ReinaJug1;
        return 1;
    }
    if(Tablero[8][2] == PiezaJug1){
        Tablero[8][2] = ReinaJug1;
        return 1;
    }
    if(Tablero[8][3] == PiezaJug1){
        Tablero[8][3] = ReinaJug1;
        return 1;
    }
    if(Tablero[8][4] == PiezaJug1){
        Tablero[8][4] = ReinaJug1;
        return 1;
    }
    if(Tablero[8][5] == PiezaJug1){
        Tablero[8][5] = ReinaJug1;
        return 1;
    }
    if(Tablero[8][6] == PiezaJug1){
        Tablero[8][6] = ReinaJug1;
        return 1;
    }
    if(Tablero[8][7] == PiezaJug1){
        Tablero[8][7] = ReinaJug1;
        return 1;
    }
    if(Tablero[8][8] == PiezaJug1){
        Tablero[8][8] = ReinaJug1;
        return 1;
    }
    return 0;
}

int CheckQUEEN_p(int **Tablero[9][9]){
    if(Tablero[1][1] == PiezaJug2){
        Tablero[1][1] = ReinaJug2;
        return 1;
    }
    if(Tablero[1][2] == PiezaJug2){
        Tablero[1][2] = ReinaJug2;
        return 1;
    }
    if(Tablero[1][3] == PiezaJug2){
        Tablero[1][3] = ReinaJug2;
        return 1;
    }
    if(Tablero[1][4] == PiezaJug2){
        Tablero[1][4] = ReinaJug2;
        return 1;
    }
    if(Tablero[1][5] == PiezaJug2){
        Tablero[1][5] = ReinaJug2;
        return 1;
    }
    if(Tablero[1][6] == PiezaJug2){
        Tablero[1][6] = ReinaJug2;
        return 1;
    }
    if(Tablero[1][7] == PiezaJug2){
        Tablero[1][7] = ReinaJug2;
        return 1;
    }
    if(Tablero[1][8] == PiezaJug2){
        Tablero[1][8] = ReinaJug2;
        return 1;
    }
    return 0;
}

int MoverPiezaJug1(int **Tablero[9][9], int Jugador){
    char PosOri[5], PosNue[5];
    printf("Escribir Movimientos (<Pieza><PoscicionORI> <PoscicionNUEVA>)\n");
    scanf("%s %s", &PosOri, &PosNue);
    printf("%s %s\n", PosOri, PosNue);
    //printf("%c %c %c %c %c", PosOri[0], PosOri[1], PosOri[2], PosNue[0], PosNue[1]); //ver si todo esta bien [FUNCIONA]
    if(Jugador == 1){ //movimientos para el Jugador 1
        if(PosOri[0] == PiezaJug1){
            PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
            PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
            int PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
            //printf("\n%d %d\n", PosOri[1], PosNue[0]); //Imprimir posicion para ver si esta correcto [FUNCIONA BIEN]
            //printf("\n Posicion Nueva fila: %d\n Posicion Nueva columna: %d\n Posicion original columna: %d\n Posicion original fila :%d\n", PosNueFIL, PosNueCOL, PosOriCOL, PosOriFIL);
            //printf("\n\n%d\n\n%d\n\n%d\n\n", Tablero[PosOriCOL+1][PosOriFIL+1], Tablero[PosNueCOL][PosNueFIL], Tablero[PosOriCOL+1][PosOriFIL+1]);
            //printf("\n\n%d  %d\n\n", Tablero[PosOriCOL+1][PosOriFIL+1], Tablero[PosOriCOL+1][PosOriFIL-1]);
            if(Tablero[PosOriCOL+1][PosOriFIL+1] != Aster && Tablero[PosOriCOL+1][PosOriFIL-1] != Aster
               && Tablero[PosOriCOL+2][PosOriFIL+2] != Aster && Tablero[PosOriCOL+2][PosOriFIL-2] != Aster){
                printf("ESTA PIEZA NO SE PUEDE MOVER\n");
                return 1;
            }
            if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2
               || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2){
                   if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                        printf("\Movimiento permitido\n");
                   }
                   else{
                       printf("SIEMPRE SE DEBE DE COMER\n");
                       return 1;
                   }
            }
            else{
                if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && PosNueCOL != PosOriCOL+1
                   || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && PosNueCOL != PosOriCOL+1){
                       if(Tablero[PosOriCOL+2][PosOriFIL+2] != Aster){
                            printf("\Movimiento permitido\n");
                       }
                       else{
                            printf("SIEMPRE SE DEBE DE COMER\n");
                       return 1;
                       }
                }
                else{
                   if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && PosNueFIL != PosOriFIL+1
                      || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && PosNueFIL != PosOriFIL+1){
                          if(Tablero[PosOriCOL+2][PosOriFIL+2] != Aster){
                              printf("\Movimiento permitido\n");
                          }
                          else{
                              printf("SIEMPRE SE DEBE DE COMER\n");
                          return 1;
                          }
                   }
                    else{
                        if(Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2 && PosNueCOL != PosOriCOL+1
                            || Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2 && PosNueCOL != PosOriCOL+1){
                                if(Tablero[PosOriCOL+2][PosOriFIL-2] != Aster){
                                    printf("\Movimiento permitido\n");
                                }
                                else{
                                    printf("SIEMPRE SE DEBE DE COMER\n");
                                    return 1;
                                }
                        }
                        else{
                            if(Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2 && PosNueFIL != PosOriFIL-1
                                || Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2 && PosNueFIL != PosOriFIL-1){
                                    if(Tablero[PosOriCOL+2][PosOriFIL-2] != Aster){
                                        printf("\Movimiento permitido\n");
                                    }
                                    else{
                                        printf("SIEMPRE SE DEBE DE COMER\n");
                                        return 1;
                                    }
                            }
                        }
                    }
                }
            }
            //printf("\n\n%d == %d\n\n%d == %d\n\n", PosNueCOL, PosOriCOL+1, PosNueFIL, PosOriFIL+1);
            if(PosNueCOL > PosOriCOL && PosNueCOL < PosOriCOL+2 && Tablero[PosNueCOL][PosNueFIL] == Aster){
                Tablero[PosNueCOL][PosNueFIL] = PiezaJug1;
                Tablero[PosOriCOL][PosOriFIL] = Aster; //FUNACIONA (SE MUEVE)
                CheckQUEEN_P(&Tablero); //ver si hay QUEEN
            }
            else{
                if(PosNueCOL > PosOriCOL && PosNueCOL < PosOriCOL+2 && Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 //cambiar
                   || PosNueCOL > PosOriCOL && PosNueCOL < PosOriCOL+2 && Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                    int PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                    if(PosNueFIL < PosOriFIL){
                        PosNueFIL-=2; //cambiar
                    }
                    if(PosNueCOL < PosOriCOL){
                        PosNueCOL-=2; //cambiar
                    }
                    if(Tablero[PosNueCOL+1][PosNueFIL+1] != Aster){ //cambiar
                        printf("Jugada Ilegal\n");
                        return 1;
                    }
                    Tablero[PosNueCOL+1][PosNueFIL+1] = PiezaJug1;//FIL ESTA AL REVES //cambiar
                    Tablero[PosOriCOL][PosOriFIL] = Aster;
                    Tablero[PosNueCOLOri][PosNueFILOri] = Aster; //poner asterisoco en la posicion del enemigo comido
                    int PosActCOL = PosNueCOL+1, PosActFIL = PosNueFIL+1, RESP = 1;
                    while(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug2 || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug2 //ver si se puede comer otra ves
                          || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug2 || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug2
                          || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug2 || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug2
                          || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug2 || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug2
                          && RESP == 1 && CheckQUEEN_P(Tablero) != 1){
                            int MOVimpedido = 0;
                            ImpTablero(Tablero);
                            printf("\n pos act: %d, %d", PosActFIL, PosActCOL);
                            printf("\nPuede moverse otra ves (1 = si)\n");
                            scanf("%d", &RESP);
                            if(RESP != 1){
                                break;
                            }
                            if(Tablero[PosActCOL+2][PosActFIL+2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(Tablero[PosActCOL-2][PosActFIL+2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(Tablero[PosActCOL+2][PosActFIL-2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(Tablero[PosActCOL-2][PosActFIL-2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(MOVimpedido >= 3){
                                printf("NO SE PUEDE MOVER MAS\n");
                                break;
                            }
                            if(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug2 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug2 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug2 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug2 && Tablero[PosActCOL-2][PosActFIL-2] == Aster
                               || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug2 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug2 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug2 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug2 && Tablero[PosActCOL-2][PosActFIL-2] == Aster){
                                printf("\nContinue\n");
                            }
                            else{
                                break;
                            }
                            printf("\n<Pieza><PoscicionORI> <PoscicionNUEVA>\n");
                            scanf("%s %s", &PosOri, &PosNue);
                            printf("%s %s\n", PosOri, PosNue);
                            PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
                            PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
                            PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
                            //printf("\n\n%d %d\n\n", Tablero[PosNueCOL][PosNueFIL], ReinaJug2);
                            if(Tablero[PosNueCOL][PosNueFIL] != PiezaJug2 && Tablero[PosNueCOL][PosNueFIL] != ReinaJug2){
                                printf("\nSIEMPRE SE DEBE DE COMER\n");
                            }
                            else{
                                if(PosActCOL != PosOriCOL && PosActFIL != PosOriFIL){
                                    printf("esta no es su pieza\n");
                                }
                                else{
                                    PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                                    if(PosNueFIL < PosOriFIL){
                                        PosNueFIL-=2;
                                    }
                                    if(PosNueCOL < PosOriCOL){
                                        PosNueCOL-=2;
                                    }
                                    if(Tablero[PosNueCOL+1][PosNueFIL+1] != Aster){
                                        printf("Jugada Ilegal\n");
                                    }
                                    else{
                                        Tablero[PosNueCOL+1][PosNueFIL+1] = PiezaJug1; //mover pieza
                                        Tablero[PosActCOL][PosActFIL] = Aster; //poner asterisco en posicion anterior
                                        Tablero[PosNueCOLOri][PosNueFILOri] = Aster; //poner asterisoco en la posicion del enemigo comido
                                        PosActCOL = PosNueCOL+1, PosActFIL = PosNueFIL+1;
                                    }
                                }
                            }
                    }
                    CheckQUEEN_P(&Tablero); //ver si hay QUEEN de JUG 1
                }
                else{
                    printf("Poscicion nueva no permitida\n");
                    return 1;
                }
            }
        }
        else{
            if(PosOri[0] == ReinaJug1){
                PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
                PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
                int PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
                int PosNueFILuso = PosNueFIL, PosNueCOLuso = PosNueCOL;
                //printf("\n\n%d %d = %d\n\n%d %d = %d\n\n", PosNueCOL, PosOriCOL, abs(PosNueCOL - PosOriCOL), PosNueFIL, PosOriFIL, abs(PosNueFIL - PosOriFIL));
                if(abs(PosNueCOL - PosOriCOL) != abs(PosNueFIL - PosOriFIL)){
                    printf("ESTE MOVIMIENTO NO ES PERMITIDO\n");
                    return 1;
                }
                if(PosNueFIL < PosOriFIL){
                    PosNueFILuso-=2;
                }
                if(PosNueCOL < PosOriCOL){
                    PosNueCOLuso-=2;
                }
                int PosActCOL = PosNueCOLuso+1, PosActFIL = PosNueFILuso+1, MOVimpedido = 0;
                if(Tablero[PosActCOL+2][PosActFIL+2] != Aster){
                    MOVimpedido+=1;
                }
                if(Tablero[PosActCOL-2][PosActFIL+2] != Aster){
                    MOVimpedido+=1;
                }
                if(Tablero[PosActCOL+2][PosActFIL-2] != Aster){
                    MOVimpedido+=1;
                }
                if(Tablero[PosActCOL-2][PosActFIL-2] != Aster){
                    MOVimpedido+=1;
                }
                if(MOVimpedido >= 3){
                    printf("Este movimiento es permitido");
                }
                else{
                    if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2
                       && Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug2 && Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug2
                       || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2
                       && Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug2 && Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug2){
                           if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                                printf("\nJugada permitida\n");
                           }
                           else{
                               printf("SIEMPRE SE DEBE DE COMER\n");
                               return 1;
                           }
                       }
                       else{
                           if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2
                              || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2){
                                  if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                                     printf("\nJugada permitida\n");
                                  }
                                  else{
                                     printf("SIEMPRE SE DEBE DE COMER\n");
                                     return 1;
                                  }
                            }
                            else{
                               if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug2
                                  || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug2){
                                      if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                                          printf("\nJugada permitida\n");
                                      }
                                      else{
                                          printf("SIEMPRE SE DEBE DE COMER\n");
                                          return 1;
                                      }
                               }
                               else{
                                  if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug2 && Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug2
                                     || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug2 && Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug2){
                                       if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                                          printf("\nJugada permitida\n");
                                       }
                                       else{
                                           printf("SIEMPRE SE DEBE DE COMER\n");
                                           return 1;
                                       }
                                   }
                                   else{
                                      if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2
                                         || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug2 && Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2){
                                            if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                                                printf("\nJugada permitida\n");
                                            }
                                            else{
                                                printf("SIEMPRE SE DEBE DE COMER\n");
                                                return 1;
                                            }
                                       }
                                       else{
                                           if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && PosNueCOL != PosOriCOL+1
                                              || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && PosNueCOL != PosOriCOL+1){
                                                  printf("SIEMPRE SE DEBE DE COMER\n");
                                                  return 1;
                                           }
                                           else{
                                                if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug2 && PosNueFIL != PosOriFIL+1
                                                   || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug2 && PosNueFIL != PosOriFIL+1){
                                                       printf("SIEMPRE SE DEBE DE COMER\n");
                                                       return 1;
                                                }
                                                else{
                                                    if(Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2 && PosNueCOL != PosOriCOL+1
                                                       || Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2 && PosNueCOL != PosOriCOL+1){
                                                        printf("SIEMPRE SE DEBE DE COMER\n");
                                                        return 1;
                                                    }
                                                    else{
                                                        if(Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug2 && PosNueFIL != PosOriFIL-1
                                                           || Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug2 && PosNueFIL != PosOriFIL-1){
                                                              printf("SIEMPRE SE DEBE DE COMER\n");
                                                              return 1;
                                                        }
                                                        else{
                                                            if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug2 && PosNueCOL != PosOriCOL-1
                                                               || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug2 && PosNueCOL != PosOriCOL-1){
                                                                  printf("SIEMPRE SE DEBE DE COMER\n");
                                                                  return 1;
                                                            }
                                                            else{
                                                                if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug2 && PosNueFIL != PosOriFIL+1
                                                                   || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug2 && PosNueFIL != PosOriFIL+1){
                                                                     printf("SIEMPRE SE DEBE DE COMER\n");
                                                                     return 1;
                                                                }
                                                                else{
                                                                    if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug2 && PosNueCOL != PosOriCOL-1
                                                                       || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug2 && PosNueCOL != PosOriCOL-1){
                                                                         printf("SIEMPRE SE DEBE DE COMER\n");
                                                                         return 1;
                                                                    }
                                                                    else{
                                                                        if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug2 && PosNueFIL != PosOriFIL-1
                                                                           || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug2 && PosNueFIL != PosOriFIL-1){
                                                                              printf("SIEMPRE SE DEBE DE COMER\n");
                                                                              return 1;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                   }
                               }
                           }
                      }
                 }
                //movimientos posibles de la QUEEN
                if(Tablero[PosNueCOL][PosNueFIL] == Aster){
                    Tablero[PosNueCOL][PosNueFIL] = ReinaJug1;
                    Tablero[PosOriCOL][PosOriFIL] = Aster;
                }
                else{
                    if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug2 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug2){
                        int PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                        if(PosNueFIL < PosOriFIL){
                            PosNueFIL-=2;
                        }
                        if(PosNueCOL < PosOriCOL){
                            PosNueCOL-=2;
                        }
                        if(Tablero[PosNueCOL+1][PosNueFIL+1] != Aster){
                            printf("Jugada Ilegal\n");
                            return 1;
                        }
                        Tablero[PosNueCOLOri][PosNueFILOri] = Aster;
                        Tablero[PosNueCOL+1][PosNueFIL+1] = ReinaJug1;//FIL ESTA MAL
                        Tablero[PosOriCOL][PosOriFIL] = Aster;
                        PosActCOL = PosNueCOL+1, PosActFIL = PosNueFIL+1;
                        int RESP = 1;
                        while(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug2 || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug2 //ver si se puede comer otra ves
                              || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug2 || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug2
                              || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug2 || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug2
                              || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug2 || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug2
                              && RESP == 1 && CheckQUEEN_p(Tablero) != 1){
                                  MOVimpedido = 0;
                                  ImpTablero(Tablero);
                                  printf("\n pos act: %d, %d", PosActFIL, PosActCOL);
                                  printf("\nPuede moverse otra ves (1 = si)\n");
                                  scanf("%d", &RESP);
                                  if(RESP != 1){
                                    break;
                                  }
                                  if(Tablero[PosActCOL+2][PosActFIL+2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(Tablero[PosActCOL-2][PosActFIL+2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(Tablero[PosActCOL+2][PosActFIL-2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(Tablero[PosActCOL-2][PosActFIL-2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(MOVimpedido >= 3){
                                    printf("NO SE PUEDE MOVER MAS\n");
                                    break;
                                  }
                                  if(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug2 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug2 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug2 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug2 && Tablero[PosActCOL-2][PosActFIL-2] == Aster
                                     || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug2 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug2 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug2 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug2 && Tablero[PosActCOL-2][PosActFIL-2] == Aster){
                                        printf("\nContinue\n");
                                  }
                                  else{
                                      break;
                                  }
                                  printf("\n<Pieza><PoscicionORI> <PoscicionNUEVA>\n");
                                  scanf("%s %s", &PosOri, &PosNue);
                                  printf("%s %s\n", PosOri, PosNue);
                                  PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
                                  PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
                                  PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
                                  if(Tablero[PosNueCOL][PosNueFIL] != PiezaJug2 && Tablero[PosNueCOL][PosNueFIL] != ReinaJug2){
                                    printf("SIEMPRE SE DEVE COMER\n");
                                  }
                                  else{
                                      if(PosActCOL != PosOriCOL && PosActFIL != PosOriFIL){
                                        printf("esta no es su pieza\n");
                                      }
                                      else{
                                          PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                                          if(PosNueFIL < PosOriFIL){
                                              PosNueFIL-=2;
                                          }
                                          if(PosNueCOL < PosOriCOL){
                                              PosNueCOL-=2;
                                          }
                                          if(Tablero[PosNueCOL+1][PosNueFIL+1] != Aster){
                                              printf("Jugada Ilegal\n");
                                          }
                                          else{
                                              Tablero[PosNueCOL+1][PosNueFIL+1] = PiezaJug1; //mover pieza
                                              Tablero[PosActCOL][PosActFIL] = Aster; //poner asterisco en posicion anterior
                                              Tablero[PosNueCOLOri][PosNueFILOri] = Aster; //poner asterisoco en la posicion del enemigo comido
                                              PosActCOL = PosNueCOL+1, PosActFIL = PosNueFIL+1;
                                          }
                                      }
                                  }
                        }
                        printf("\nNo se puede mover mas\n");
                    }
                    else{
                        printf("Poscicion nueva no permitida\n");
                        return 1;
                    }
                }
            }
            else{
                printf("Pieza incorrecta\n");
                return 1;
            }
        }
        return 2;
    }
    else{
        printf("Jugador Equivocado\n");
        return 0;
    }
}

int MoverPiezaJug2(int **Tablero[9][9], int Jugador){
    char PosOri[5], PosNue[5];
    printf("Escribir Movimientos (<Pieza><PoscicionORI> <PoscicionNUEVA>)\n");
    scanf("%s %s", &PosOri, &PosNue);
    printf("%s %s\n", PosOri, PosNue);
    //printf("%c %c %c %c %c", PosOri[0], PosOri[1], PosOri[2], PosNue[0], PosNue[1]); //ver si todo esta bien [FUNCIONA]
    if(Jugador == 2){ //movimientos para el jugador 2
        if(PosOri[0] == PiezaJug2){ //pieza (p)
            PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
            PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
            int PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
            //printf("\n%d %d\n", PosOri[1], PosNue[0]); //Imprimir posicion para ver si esta correcto [FUNCIONA BIEN]
            //printf("\n Posicion Nueva fila: %d\n Posicion Nueva columna: %d\n Posicion original columna: %d\n Posicion original fila :%d\n", PosNueFIL, PosNueCOL, PosOriCOL, PosOriFIL);
            //printf("\n\n%d\n\n%d\n\n%d\n\n", Tablero[PosOriCOL+1][PosOriFIL+1], Tablero[PosNueCOL][PosNueFIL], Tablero[PosOriCOL+1][PosOriFIL+1]);
            if(Tablero[PosOriCOL-1][PosOriFIL+1] != Aster && Tablero[PosOriCOL-1][PosOriFIL-1] != Aster
               && Tablero[PosOriCOL-2][PosOriFIL+2] != Aster && Tablero[PosOriCOL-2][PosOriFIL-2] != Aster){
                printf("ESTA PIEZA NO SE PUEDE MOVER MAS\n");
                return 2;
            }
            if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1 && Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1
               || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1 && Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1){
                   if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug1 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                       printf("\njugada permitida\n");
                   }
                   else{
                       printf("SIEMPRE SE COME\n");
                       return 2;
                   }
            }
            else{
                if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1 && PosNueCOL != PosOriCOL-1
                   || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1 && PosNueCOL != PosOriCOL-1){
                       if(Tablero[PosOriCOL-2][PosOriFIL+2] != Aster){
                            printf("\Movimiento permitido\n");
                       }
                       else{
                            printf("SIEMPRE SE DEBE DE COMER\n");
                       return 2;
                       }
                }
                else{
                    if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1 && PosNueFIL != PosOriFIL+1
                       || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1 && PosNueFIL != PosOriFIL+1){
                           if(Tablero[PosOriCOL-2][PosOriFIL+2] != Aster){
                                printf("\Movimiento permitido\n");
                           }
                           else{
                                printf("SIEMPRE SE DEBE DE COMER\n");
                                return 2;
                           }
                    }
                    else{
                        if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1 && PosNueCOL != PosOriCOL-1
                           || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1 && PosNueCOL != PosOriCOL-1){
                               if(Tablero[PosOriCOL-2][PosOriFIL-2] != Aster){
                                    printf("\Movimiento permitido\n");
                               }
                               else{
                                    printf("SIEMPRE SE DEBE DE COMER\n");
                               return 2;
                               }
                        }
                        else{
                            if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1 && PosNueFIL != PosOriFIL-1
                               || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1 && PosNueFIL != PosOriFIL-1){
                                   if(Tablero[PosOriCOL-2][PosOriFIL-2] != Aster){
                                        printf("\Movimiento permitido\n");
                                   }
                                   else{
                                       printf("SIEMPRE SE DEBE DE COMER\n");
                                       return 2;
                                   }
                            }
                        }
                    }
                }
            }
            //printf("\n\n%d == %d\n\n%d == %d\n\n", PosNueCOL, PosOriCOL+1, PosNueFIL, PosOriFIL+1);
            if(PosNueCOL < PosOriCOL && PosNueCOL > PosOriCOL-2 && Tablero[PosNueCOL][PosNueFIL] == Aster){
                Tablero[PosNueCOL][PosNueFIL] = PiezaJug2;
                Tablero[PosOriCOL][PosOriFIL] = Aster; //FUNACIONA (SE MUEVE)
                CheckQUEEN_p(&Tablero); //ver si hay QUEEN
            }
            else{
                if(PosNueCOL < PosOriCOL && PosNueCOL > PosOriCOL-2 && Tablero[PosNueCOL][PosNueFIL] == PiezaJug1
                   || PosNueCOL < PosOriCOL && PosNueCOL > PosOriCOL-2 && Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                    int PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                    if(PosNueFIL > PosOriFIL){
                        PosNueFIL+=2;
                    }
                    if(PosNueCOL > PosOriCOL){
                        PosNueCOL+=2;
                    }
                    if(Tablero[PosNueCOL-1][PosNueFIL-1] != Aster){
                        printf("Jugada Ilegal\n");
                        return 2;
                    }
                    Tablero[PosNueCOL-1][PosNueFIL-1] = PiezaJug2;//FIL ESTA AL REVES
                    Tablero[PosOriCOL][PosOriFIL] = Aster;
                    Tablero[PosNueCOLOri][PosNueFILOri] = Aster; //poner asterisoco en la posicion del enemigo comido
                    int PosActCOL = PosNueCOL-1, PosActFIL = PosNueFIL-1, RESP = 1;
                    while(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug1 || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug1 //ver si se puede comer otra ves
                          || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug1 || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug1
                          || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug1 || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug1
                          || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug1 || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug1
                          && RESP == 1){
                            int MOVimpedido = 0;
                            ImpTablero(Tablero);
                            printf("\n pos act: %d, %d", PosActFIL, PosActCOL);
                            printf("\nPuede moverse otra ves (1 = si)\n");
                            scanf("%d", &RESP);
                            if(RESP != 1){
                                break;
                            }
                            if(Tablero[PosActCOL+2][PosActFIL+2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(Tablero[PosActCOL-2][PosActFIL+2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(Tablero[PosActCOL+2][PosActFIL-2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(Tablero[PosActCOL-2][PosActFIL-2] != Aster){
                                MOVimpedido+=1;
                            }
                            if(MOVimpedido >= 3){
                                printf("NO SE PUEDE MOVER MAS\n");
                                break;
                            }
                            if(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug1 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug1 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug1 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug1 && Tablero[PosActCOL-2][PosActFIL-2] == Aster
                               || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug1 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug1 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                               || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug1 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                               || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug1 && Tablero[PosActCOL-2][PosActFIL-2] == Aster){
                                printf("\nContinue\n");
                            }
                            else{
                                break;
                            }
                            printf("\n<Pieza><PoscicionORI> <PoscicionNUEVA>\n");
                            scanf("%s %s", &PosOri, &PosNue);
                            printf("%s %s\n", PosOri, PosNue);
                            PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
                            PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
                            PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
                            if(Tablero[PosNueCOL][PosNueFIL] != PiezaJug2 && Tablero[PosNueCOL][PosNueFIL] != ReinaJug2){
                                printf("SIEMPRE HAY QUE COMER\n");
                            }
                            else{
                                if(PosActCOL != PosOriCOL && PosActFIL != PosOriFIL){
                                    printf("esta no es su pieza\n");
                                }
                                else{
                                    PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                                    if(PosNueFIL > PosOriFIL){
                                        PosNueFIL+=2;
                                    }
                                    if(PosNueCOL > PosOriCOL){
                                        PosNueCOL+=2;
                                    }
                                    if(Tablero[PosNueCOL-1][PosNueFIL-1] != Aster){
                                        printf("Jugada Ilegal\n");
                                    }
                                    else{
                                        Tablero[PosNueCOL-1][PosNueFIL-1] = PiezaJug2; //mover pieza
                                        Tablero[PosNueCOLOri][PosNueFILOri] = Aster; //poner asterisoco en la posicion del enemigo comido
                                        PosActCOL = PosNueCOL-1, PosActFIL = PosNueFIL-1;
                                        Tablero[PosActCOL][PosActFIL] = Aster; //poner asterisco en posicion anterior
                                    }
                                }
                            }
                    }
                    CheckQUEEN_p(&Tablero); //ver si hay QUEEN de JUG 2
                }
                else{
                    printf("Poscicion nueva no permitida\n");
                    return 2;
                }
            }
        }
        else{
            if(PosOri[0] == ReinaJug2){ //AQUI ESTOY
                PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
                PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
                int PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
                int PosNueFILuso = PosNueFIL, PosNueCOLuso = PosNueCOL;
                if(abs(PosNueCOL - PosOriCOL) != abs(PosNueFIL - PosOriFIL)){
                    printf("ESTE MOVIMIENTO NO ES PERMITIDO\n");
                    return 2;
                }
                if(PosNueFIL < PosOriFIL){
                    PosNueFILuso-=2;
                }
                if(PosNueCOL < PosOriCOL){
                    PosNueCOLuso-=2;
                }
                int PosActCOL = PosNueCOLuso+1, PosActFIL = PosNueFILuso+1, MOVimpedido = 0;
                if(Tablero[PosActCOL+2][PosActFIL+2] != Aster){
                    MOVimpedido+=1;
                }
                if(Tablero[PosActCOL-2][PosActFIL+2] != Aster){
                    MOVimpedido+=1;
                }
                if(Tablero[PosActCOL+2][PosActFIL-2] != Aster){
                    MOVimpedido+=1;
                }
                if(Tablero[PosActCOL-2][PosActFIL-2] != Aster){
                    MOVimpedido+=1;
                }
                if(MOVimpedido >= 3){
                    printf("Este movimiento es permitido");
                }
                else{
                    if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug1 && Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug1
                       && Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1 && Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1
                       || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug1 && Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug1
                       && Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1 && Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1){
                           if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug1 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                               printf("\nJugada permitida\n");
                            }
                            else{
                                printf("SIEMPRE SE DEBE DE COMER\n");
                                return 2;
                            }
                    }
                    else{
                        if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug1 && Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug1
                           || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug1 && Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug1){
                               if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug1 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                                   printf("\nJugada permitida\n");
                               }
                               else{
                                   printf("SIEMPRE SE DEBE DE COMER\n");
                                   return 2;
                               }
                        }
                        else{
                           if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug1 && Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1
                              || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug1 && Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1){
                                  if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug1 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                                      printf("\nJugada permitida\n");
                                  }
                                  else{
                                      printf("SIEMPRE SE DEBE DE COMER\n");
                                      return 2;
                                  }
                           }
                           else{
                               if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1 && Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1
                                  || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1 && Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1){
                                        if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug1 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                                            printf("\nJugada permitida\n");
                                        }
                                        else{
                                            printf("SIEMPRE SE DEBE DE COMER\n");
                                            return 2;
                                        }
                               }
                               else{
                                    if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1 && Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug1
                                       || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1 && Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug1){
                                           if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug1 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                                              printf("\nJugada permitida\n");
                                           }
                                           else{
                                              printf("SIEMPRE SE DEBE DE COMER\n");
                                              return 2;
                                           }
                                    }
                                    else{
                                         if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug1 && PosNueCOL != PosOriCOL+1
                                            || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug1 && PosNueCOL != PosOriCOL+1){
                                                printf("SIEMPRE SE DEBE DE COMER\n");
                                                return 2;
                                         }
                                         else{
                                             if(Tablero[PosOriCOL+1][PosOriFIL+1] == PiezaJug1 && PosNueFIL != PosOriFIL+1
                                                || Tablero[PosOriCOL+1][PosOriFIL+1] == ReinaJug1 && PosNueFIL != PosOriFIL+1){
                                                    printf("SIEMPRE SE DEBE DE COMER\n");
                                                    return 2;
                                             }
                                             else{
                                                 if(Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug1 && PosNueCOL != PosOriCOL+1
                                                    || Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug1 && PosNueCOL != PosOriCOL+1){
                                                     printf("SIEMPRE SE DEBE DE COMER\n");
                                                     return 2;
                                                 }
                                                 else{
                                                     if(Tablero[PosOriCOL+1][PosOriFIL-1] == PiezaJug1 && PosNueFIL != PosOriFIL-1
                                                         || Tablero[PosOriCOL+1][PosOriFIL-1] == ReinaJug1 && PosNueFIL != PosOriFIL-1){
                                                             printf("SIEMPRE SE DEBE DE COMER\n");
                                                             return 2;
                                                     }
                                                     else{
                                                         if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1 && PosNueCOL != PosOriCOL-1
                                                            || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1 && PosNueCOL != PosOriCOL-1){
                                                             printf("SIEMPRE SE DEBE DE COMER\n");
                                                             return 2;
                                                         }
                                                         else{
                                                             if(Tablero[PosOriCOL-1][PosOriFIL+1] == PiezaJug1 && PosNueFIL != PosOriFIL+1
                                                                || Tablero[PosOriCOL-1][PosOriFIL+1] == ReinaJug1 && PosNueFIL != PosOriFIL+1){
                                                                 printf("SIEMPRE SE DEBE DE COMER\n");
                                                                 return 2;
                                                             }
                                                             else{
                                                                 if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1 && PosNueCOL != PosOriCOL-1
                                                                    || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1 && PosNueCOL != PosOriCOL-1){
                                                                     printf("SIEMPRE SE DEBE DE COMER\n");
                                                                     return 2;
                                                                 }
                                                                 else{
                                                                     if(Tablero[PosOriCOL-1][PosOriFIL-1] == PiezaJug1 && PosNueFIL != PosOriFIL-1
                                                                         || Tablero[PosOriCOL-1][PosOriFIL-1] == ReinaJug1 && PosNueFIL != PosOriFIL-1){
                                                                             printf("SIEMPRE SE DEBE DE COMER\n");
                                                                             return 2;
                                                                     }
                                                                 }
                                                             }
                                                         }
                                                     }
                                                 }
                                             }
                                         }
                                    }
                                }
                            }
                        }
                    }
                 }
                //movimientos posibles de la QUEEN
                if(Tablero[PosNueCOL][PosNueFIL] == Aster){
                    Tablero[PosNueCOL][PosNueFIL] = ReinaJug2;
                    Tablero[PosOriCOL][PosOriFIL] = Aster;
                }
                else{
                    if(Tablero[PosNueCOL][PosNueFIL] == PiezaJug1 || Tablero[PosNueCOL][PosNueFIL] == ReinaJug1){
                        int PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                        if(PosNueFIL > PosOriFIL){
                            PosNueFIL+=2;
                        }
                        if(PosNueCOL > PosOriCOL){
                            PosNueCOL+=2;
                        }
                        if(Tablero[PosNueCOL-1][PosNueFIL-1] != Aster){
                            printf("Jugada Ilegal\n");
                            return 2;
                        }
                        Tablero[PosNueCOLOri][PosNueFILOri] = Aster;
                        Tablero[PosNueCOL-1][PosNueFIL-1] = ReinaJug2;//FIL ESTA MAL
                        Tablero[PosOriCOL][PosOriFIL] = Aster;
                        int PosActCOL = PosNueCOL+1, PosActFIL = PosNueFIL+1, RESP = 1;
                        while(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug1 || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug1 //ver si se puede comer otra ves
                              || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug1 || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug1
                              || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug1 || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug1
                              || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug1 || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug1
                              && RESP == 1){
                                  int MOVimpedido = 0;
                                  ImpTablero(Tablero);
                                  printf("\n pos act: %d, %d", PosActFIL, PosActCOL);
                                  printf("\nPuede moverse otra ves (1 = si)\n");
                                  scanf("%d", &RESP);
                                  if(RESP != 1){
                                    break;
                                  }
                                  if(Tablero[PosActCOL+2][PosActFIL+2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(Tablero[PosActCOL-2][PosActFIL+2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(Tablero[PosActCOL+2][PosActFIL-2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(Tablero[PosActCOL-2][PosActFIL-2] != Aster){
                                    MOVimpedido+=1;
                                  }
                                  if(MOVimpedido >= 3){
                                    printf("NO SE PUEDE MOVER MAS\n");
                                    break;
                                  }
                                  if(Tablero[PosActCOL+1][PosActFIL+1] == PiezaJug1 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL+1] == PiezaJug1 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL+1][PosActFIL-1] == PiezaJug1 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL-1] == PiezaJug1 && Tablero[PosActCOL-2][PosActFIL-2] == Aster
                                     || Tablero[PosActCOL+1][PosActFIL+1] == ReinaJug1 && Tablero[PosActCOL+2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL+1] == ReinaJug1 && Tablero[PosActCOL-2][PosActFIL+2] == Aster
                                     || Tablero[PosActCOL+1][PosActFIL-1] == ReinaJug1 && Tablero[PosActCOL+2][PosActFIL-2] == Aster
                                     || Tablero[PosActCOL-1][PosActFIL-1] == ReinaJug1 && Tablero[PosActCOL-2][PosActFIL-2] == Aster){
                                        printf("\nContinue\n");
                                  }
                                  else{
                                      break;
                                  }
                                  printf("\n<Pieza><PoscicionORI> <PoscicionNUEVA>\n");
                                  scanf("%s %s", &PosOri, &PosNue);
                                  printf("%s %s\n", PosOri, PosNue);
                                  PosOri[1] = LetrasToNum(PosOri[1]); //posisicon original letras a numeros
                                  PosNue[0] = LetrasToNum(PosNue[0]); //posisicon nueva letras a numeros
                                  PosNueFIL = PosNue[0], PosNueCOL = CharToInt(PosNue[1]), PosOriFIL = PosOri[1], PosOriCOL = CharToInt(PosOri[2]);
                                  if(Tablero[PosNueCOL][PosNueFIL] != PiezaJug2 && Tablero[PosNueCOL][PosNueFIL] != ReinaJug2){
                                      printf("SIEMPRE HAY QUE COMER\n");
                                  }
                                  else{
                                     if(PosActCOL != PosOriCOL && PosActFIL != PosOriFIL){
                                         printf("esta no es su pieza\n");
                                     }
                                     else{
                                         PosNueFILOri = PosNueFIL, PosNueCOLOri = PosNueCOL;
                                         if(PosNueFIL > PosOriFIL){
                                            PosNueFIL+=2;
                                         }
                                         if(PosNueCOL > PosOriCOL){
                                            PosNueCOL+=2;
                                         }
                                         if(Tablero[PosNueCOL-1][PosNueFIL-1] != Aster){
                                            printf("Jugada Ilegal\n");
                                         }
                                         else{
                                            Tablero[PosNueCOL-1][PosNueFIL-1] = ReinaJug2; //mover pieza
                                            Tablero[PosActCOL][PosActFIL] = Aster; //poner asterisco en posicion anterior
                                            PosActCOL = PosNueCOL-1, PosActFIL = PosNueFIL-1;
                                            Tablero[PosNueCOLOri][PosNueFILOri] = Aster; //poner asterisoco en la posicion del enemigo comido
                                         }
                                     }
                                  }
                        }
                        printf("\nNo se puede mover mas\n");
                    }
                    else{
                        printf("Poscicion nueva no permitida\n");
                        return 2;
                    }
                }
            }
            else{
                printf("Pieza incorrecta\n");
                return 2;
            }
        }
        return 1;
    }
    else{
        printf("Jugador Equivocado\n");
        return 0;
    }
}

int CharToInt(char Letra){
    int Num = 0;
    Num = Letra - '0';
    return Num;
}

void GuardarFILE(int *Tablero[9][9], JUGADOR Jug1, JUGADOR Jug2, char *JuegoACTUAL){
                     FILE *GuardarJuego = abrir_archivo(JuegoACTUAL, "w+");
                     int i,j;
                     for(i=0;i<9;i++){
                        for(j=0;j<10;j++){
                            if(j > 8){
                                fputs("\n", GuardarJuego);
                            }
                            else{
                                printf("1");
                                fputc(Tablero[i][j], GuardarJuego);
                            }
                        }
                     }
                     fwrite(&Jug1, sizeof(JUGADOR), 1, GuardarJuego);
                     fwrite(&Jug2, sizeof(JUGADOR), 1, GuardarJuego);
                     cerrar_archivo(GuardarJuego);
}

void Leer_Juego_Guardado(int **Tablero[9][9], JUGADOR **Jug1, JUGADOR **Jug2, char *JuegoACTUAL){
                             FILE *Leer_Juego = abrir_archivo(JuegoACTUAL, "r");
                             int c, Cprev, Linea = 0, posicion = 0, fileend = 0;
                             while(1) {
                                    if ((c = fgetc(Leer_Juego)) != EOF) {
                                        if (Cprev == '\n') {
                                            Linea++;
                                            posicion = 0;
                                        }
                                        Cprev = c;
                                        Tablero[Linea][posicion] = c;
                                        posicion++;
                                    }
                                    else{
                                        fileend = 1;
                                    }
                                    if (fileend == 1) {
                                        break;
                                    }
                            }
                            fread(&Jug1, sizeof(JUGADOR), 1, Leer_Juego);
                            fread(&Jug2, sizeof(JUGADOR), 1, Leer_Juego);
                            cerrar_archivo(Leer_Juego);
}


FILE* abrir_archivo(char *nombre, char *modo){
    FILE *archivo = fopen(nombre, modo);
    if(archivo == NULL){
        fputs("Archivo no abierto, verificar...", stderr);
        exit(-1);
    }
    printf("Archivo abierto\n");
    return archivo;
}

void cerrar_archivo(FILE *archivo){
    int cerrado = fclose(archivo);
    cerrado == 0 ? printf("Archivo Cerrado\n") : printf("Error Archivo No Cerrado\n");
}

void Pedir_tablas(int *Tablero[9][9], int FichasActJug1, int FichasActJug2){
    int FichasConMovimientos_JUG1 = FichasActJug1, FichasConMovimientos_JUG2 = FichasActJug2;
    int  i, j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(Tablero[i][j] == PiezaJug1){
                if(Tablero[i+1][j+1] != Aster && Tablero[i+1][j-1] != Aster
                   && Tablero[i+2][j+2] != Aster && Tablero[i+2][j-2] != Aster){
                       FichasConMovimientos_JUG1-=1;
                }
            }
            if(Tablero[i][j] == PiezaJug2){
                if(Tablero[i-1][j+1] != Aster && Tablero[i-1][j-1] != Aster
                   && Tablero[i-2][j+2] != Aster && Tablero[i-2][j-2] != Aster){
                       FichasConMovimientos_JUG2-=1;
                }
            }
            if(Tablero[i][j] == ReinaJug1){
                if(Tablero[i+1][j+1] != Aster && Tablero[i+1][j-1] != Aster
                   && Tablero[i+2][j+2] != Aster && Tablero[i+2][j-2] != Aster
                   && Tablero[i-1][j+1] != Aster && Tablero[i-1][j-1] != Aster
                   && Tablero[i-2][j+2] != Aster && Tablero[i-2][j-2] != Aster){
                       FichasConMovimientos_JUG1-=1;
                }
            }
            if(Tablero[i][j] == ReinaJug2){
                if(Tablero[i+1][j+1] != Aster && Tablero[i+1][j-1] != Aster
                   && Tablero[i+2][j+2] != Aster && Tablero[i+2][j-2] != Aster
                   && Tablero[i-1][j+1] != Aster && Tablero[i-1][j-1] != Aster
                   && Tablero[i-2][j+2] != Aster && Tablero[i-2][j-2] != Aster){
                       FichasConMovimientos_JUG2-=1;
                }
            }
        }
    }
    if(FichasConMovimientos_JUG1 == 0 && FichasConMovimientos_JUG2 == 0){
        printf("\n\n EL JUEGO NO SE PUEDE COMPLETAR\n\n");
        exit(-1);
    }
    else{
        if(FichasConMovimientos_JUG1 == 0){
            printf("\n\nEL GANADOR ES EL JUGADOR 2\n\n");
            exit(-1);
        }
        else{
            if(FichasConMovimientos_JUG2 == 0){
                printf("\n\nEL GANADOR ES EL JUGADOR 1\n\n");
                exit(-1);
            }
            else{
                printf("El juego continua\n");
            }
        }
    }
}
