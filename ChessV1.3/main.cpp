#include <iostream>
#include <graphics.h>
#include <quadratochess.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <windows.h>

//v1.0.0.3 23:22 09/03/2016 - Terminata la funzione guarda partita. Tutto stabile e funzionante.

//aggiungere funzione che cerca il re, se non lo trova, il colore perde.

using namespace std;

int ConvertiCoordinate(char Coordinata);
int GodMode(quadrato board[][8]);
int Save(quadrato board[][8],int ColorePlayer);
void SavePartita2(string PathDaPassare);
void Importa(quadrato board[][8],int&ColorePlayer);
int Converti(string pezzo);
void SavePartita();
void LoadPartita(quadrato board[][8]);

int main()
{
    initwindow(800,800);
    char Xiapp,Yiapp,Xfapp,Yfapp;
    int Cont,Master,u,ok,varcheck_scacco,Xi,Yi,Xf,Yf,varCheckMate=0,ColorePlayer=1;
    char Scelta,Scelta1,Scelta2;
    string CoordinateIniziali;
    string CoordinateFinali;
    GameStart:
    quadrato board[8][8];
    setup(board);
    cout << "Caricare una partita? y/n" << endl;
    cin >> Scelta1;
    if (Scelta1=='y')
    {
        LoadPartita(board);
        goto GameStart;
    }
    CreateDirectory("temp",NULL);
    ofstream partita_temp ("temp\\temp.txt",ios::out|ios::trunc);
    cout << "Importare una board? y/n" << endl;
    cin >> Scelta;
    if (Scelta=='y')
    {
        int xalvolo,yalvolo;
        string Path;
        string App;
        string NomeBoardImp;
        system("cd");
        system("tree");
        system("dir /B");
        Path+="dir ";
        cout << "Inserire il nome della cartella" << endl;
        cin >> App;
        Path+=App;
        Path+=" /B";
        system(Path.c_str());
        system("PAUSE");
        Importa(board,ColorePlayer);
        for (yalvolo=0;yalvolo<8;yalvolo++)
            for (xalvolo=0;xalvolo<8;xalvolo++)
            board[xalvolo][yalvolo].cleanup_public();
        drawpezzi(board);
    }
    Master=0;
    do
    {

      /*  varcheck_onlymovere=checkre_danger2(ColorePlayer,board); //Controlla se il re va spostato. da 1 se il re è in pericolo
        if (varcheck_onlymovere==1)
        do
        {
            cin >> CoordinateIniziali;
            cin >> CoordinateFinali;
            Xiapp=CoordinateIniziali[1];
            Yiapp=CoordinateIniziali[0];
            Xfapp=CoordinateFinali[1];
            Yfapp=CoordinateFinali[0];
            Xi=ConvertiCoordinate(Xiapp);
            Yi=ConvertiCoordinate(Yiapp);
            Xf=ConvertiCoordinate(Xfapp);
            Yf=ConvertiCoordinate(Yfapp);
            CoordinateIniziali.clear;
            CoordinateIniziali.clear;


        }

        if (varcheck_onlymovere==0)                               */       //in teoria, non c'è bisogno di vedere se il re è in pericolo prima di ogni mossa, perché lo fa automaticamente la funzione sposta, prima di confermare la mossa, controlla la situazione del re, quindi è uguale se io lo so da prima di muovere o no. Serve solo per avvisare dello scacco.

        varcheck_scacco=checkre_danger2(ColorePlayer,board);
        if (varcheck_scacco==1)
        {
            cout << "Il re e' sotto scacco" << endl;
            system("PAUSE");
        }
        if (varcheck_scacco==1)
        {
            varCheckMate=CheckMate(board,ColorePlayer);
            if (varCheckMate==1)
            {
                if (ColorePlayer==1)                                  //cambio turno
                   ColorePlayer=2;
                if (ColorePlayer==0)
                   ColorePlayer=1;
                if (ColorePlayer==2)
                   ColorePlayer=0;
                cout << "CheckMate! " << ColorePlayer << " wins!" << endl;
                EndOfGame(ColorePlayer);
            }
        }

        if (varCheckMate==0)
        {
        do
        {
            Start:
            if (Master==777)
                cout << "Master Mode Attiva" << endl;
            u=0;
            cout << "------------------------------------------------------" << endl;
            cout << "Inserire le Coordinate iniziali " << endl;
            CoordinateIniziali.clear();
            CoordinateFinali.clear();
            cin >> CoordinateIniziali;              //dovrò aggiungere un controllo sulle coordinate, per evitare che vengano inserite coordinate impossibili
            if (strcmp(CoordinateIniziali.c_str(),"Save")==0)
            {
                Cont=Save(board,ColorePlayer);
                if (Cont==0)
                    return 0;
                else
                    goto Start;
            }
            Xiapp=CoordinateIniziali[0];
            Yiapp=CoordinateIniziali[1];
            Xi=ConvertiCoordinate(Xiapp);
            Yi=ConvertiCoordinate(Yiapp);
            if (Yi==777)
            {
                cout << "Entering Master Mode..." << endl;
                Master=GodMode(board);
                if (Master==1)
                    goto GameEnd;

                if ((Master==777)||(Master==0))
                    {
                        drawboard(board);
                        drawpezzi(board);
                        goto Start;
                    }
            }
            cout << "Inserire le Coordinate finali " << endl;
            cin >> CoordinateFinali;
            Xfapp=CoordinateFinali[0];
            Yfapp=CoordinateFinali[1];
            Xf=ConvertiCoordinate(Xfapp);
            Yf=ConvertiCoordinate(Yfapp);
            CoordinateIniziali.clear();
            CoordinateFinali.clear();

            cout << "Debug valori convertiti: " << endl << Xi << ", " << Yi << ". " << Xf << ", " << Yf << ". " << endl;
            cout << "------------------------------------------------------" << endl;

            ok=1;  //se ok è 1, i valori sono corretti.

            if ((Xi==666)||(Yi==666)||(Xf==666)||(Yf==666))   //se le coordinate sono invalide, ok è 0, e ricomincia il ciclo senza spostare.
                ok=0;

            if (ok==1)
                if (Master==0)
                u=sposta(Xi,Yi,Xf,Yf,board,0,ColorePlayer,0);

            if (Master==777)
            {
                MasterMode(Xi,Yi,Xf,Yf,board);
                u=1;
            }

            partita_temp << Xiapp << endl << Yiapp << endl << Xfapp << endl << Yfapp << endl;

            if (u==0)
                cout << "Non spostato. " << endl;
        }while(u==0);     //sposta ritorna 1 se ho spostato il pezzo, quindi u=sposta, se il pezzo viene spostato con successo, si esce

        if (ColorePlayer==1)                                  //cambio turno
            ColorePlayer=2;
        if (ColorePlayer==0)
            ColorePlayer=1;
        if (ColorePlayer==2)
            ColorePlayer=0;

        cout << "Cambio Player" << endl;
        system("PAUSE");
        }

    }while(varCheckMate==0);
    GameEnd:
        partita_temp.close();
        cout << "Salvare la partita?" << endl;
        cin >> Scelta2;
        if (Scelta2=='y')
        {
            SavePartita();
        }
        ofstream clear_temp ("temp\\temp.txt",ios::out|ios::trunc);
        clear_temp.close();
    return 0;
}

int ConvertiCoordinate(char Coordinata)
{
    switch(Coordinata)
    {
    case '1':
    case 'h':
    case 'H':
        return 0;
        break;
    case '2':
    case 'g':
    case 'G':
        return 1;
        break;
    case '3':
    case 'f':
    case 'F':
        return 2;
        break;
    case '4':
    case 'e':
    case 'E':
        return 3;
        break;
    case '5':
    case 'd':
    case 'D':
        return 4;
        break;
    case '6':
    case 'c':
    case 'C':
        return 5;
        break;
    case '7':
    case 'b':
    case 'B':
        return 6;
        break;
    case '8':
    case 'a':
    case 'A':
        return 7;
        break;
    case 'm':
    case 'M':
        return 777;
        break;
    default:
        return 666;
        break;
    }
    return 666;
}

int GodMode(quadrato board[][8])
{
    EndOfGame(777);
    string Commands;
    cin >> Commands;
    if(strcmp(Commands.c_str(),"WhiteWins")==0)
    {
        EndOfGame(1);
        return 1;
    }
    if(strcmp(Commands.c_str(),"BlackWins")==0)
    {
        EndOfGame(0);
        return 1;
    }
    if(strcmp(Commands.c_str(),"MasterMode")==0)
    {
        return 777;
    }
    if(strcmp(Commands.c_str(),"Disable")==0)
    {
        return 0;
    }
    if(strcmp(Commands.c_str(),"Inserisci")==0)
    {
        drawboard(board);
        drawpezzi(board);
        cout << "Inserire le Coordinate" << endl;
        string CoordinateIniziali;
        int pezz,Xiapp,Yiapp,Xi,Yi,ok;
        do
        {
            cin >> CoordinateIniziali;
            Xiapp=CoordinateIniziali[0];
            Yiapp=CoordinateIniziali[1];
            Xi=ConvertiCoordinate(Xiapp);
            Yi=ConvertiCoordinate(Yiapp);
            cout << "--------------------------------------------------------------" << endl;
            cout << "0=Vuoto; 1=PedoneB; 2=TorreB; 3=CavalloB; 4=AlfiereB; 5=ReginaB; 6=ReB; 7=PedoneN; 8=TorreN; 9=CavalloN; 10=AlfiereN; 11=ReginaN; 12=ReN" << endl;
            cout << "--------------------------------------------------------------" << endl;
            cin >> pezz;

            if ((Xi==666)||(Yi==666))
                ok=0;

            if ((pezz==0)||(pezz==1)||(pezz==2)||(pezz==3)||(pezz==4)||(pezz==5)||(pezz==6)||(pezz==7)||(pezz==8)||(pezz==9)||(pezz==10)||(pezz==11)||(pezz==12))
                ok=1;

            if(ok==1)
                InserisciPezzo(Xi,Yi,board,pezz);
        }while(ok==0);
        drawpezzi(board);
        return 777;
    }
    return 0;
}

int Save(quadrato board[][8],int ColorePlayer)
{
    int x,y,pezzo;
    char Scelta;
    string NomeBoard;
    string NomeDir;
    string Path;
    string PathDaPassare;
    cout << "Inserire il nome della Directory da creare. Non sono ammessi sottolivelli." << endl;
    cin >> NomeDir;
    CreateDirectory(NomeDir.c_str(),NULL);
    cout << "Inserire il nome del file contente la Board" << endl;
    cin >> NomeBoard;
    Path+=NomeDir;
    Path+="\\";
    Path+=NomeBoard;
    PathDaPassare=Path;
    Path+=".board";
    ofstream BoardSave (Path.c_str(),ios::out|ios::trunc);
    for (y=0;y<8;y++)
     {
         for (x=0;x<8;x++)
         {
             pezzo=board[x][y].GetPezzo();
             BoardSave << pezzo; //volendo si potrebbero salvare a matrice, basta aggiungere un endl nel for delle y
             BoardSave << endl;
         }
     }
    BoardSave << ColorePlayer;
    SavePartita2(PathDaPassare);
    cout << "Continuare la partita? y/n " << endl;
    cin >> Scelta;
    BoardSave.close();
    if (Scelta=='n')
        return 0;
        else
        return 1;
}

void Importa(quadrato board[][8],int&ColorePlayer)
{
    int x,y,pezzo_conv;
    string pezzo;
    string colore;
    string Name;
    string NameBoard;
    string NamePartita;
    string Importa;
    cout << "Inserire il nome del file da caricare. Al cambio di cartella mettere doppio '\' " << endl;
    cin >> Name;
    NameBoard=Name;
    NameBoard+=".board";
    NamePartita+=".game";
    ifstream BoardImp (NameBoard.c_str(),ios::in);
    for (y=0;y<8;y++)
        for (x=0;x<8;x++)
    {
        getline(BoardImp,pezzo);
        cout << pezzo;
        pezzo_conv=Converti(pezzo);
        board[x][y].InsertPezzo(pezzo_conv);
        pezzo.clear();
    }
    ofstream partita_temp ("temp\\temp",ios::out|ios::trunc);
    ifstream partita_imp (NamePartita.c_str(),ios::in);
    while(getline(partita_imp,Importa))
    {
        partita_temp << Importa;
        Importa.clear();
    }
    partita_temp.close();
    partita_imp.close();
    getline(BoardImp,colore);
    ColorePlayer=Converti(colore);
    return ;
}

int Converti(string pezzo)
{
    if(strcmp(pezzo.c_str(),"0")==0)
        return 0;
    if(strcmp(pezzo.c_str(),"1")==0)
        return 1;
    if(strcmp(pezzo.c_str(),"2")==0)
        return 2;
    if(strcmp(pezzo.c_str(),"3")==0)
        return 3;
    if(strcmp(pezzo.c_str(),"4")==0)
        return 4;
    if(strcmp(pezzo.c_str(),"5")==0)
        return 5;
    if(strcmp(pezzo.c_str(),"6")==0)
        return 6;
    if(strcmp(pezzo.c_str(),"7")==0)
        return 7;
    if(strcmp(pezzo.c_str(),"8")==0)
        return 8;
    if(strcmp(pezzo.c_str(),"9")==0)
        return 9;
    if(strcmp(pezzo.c_str(),"10")==0)
        return 10;
    if(strcmp(pezzo.c_str(),"11")==0)
        return 11;
    if(strcmp(pezzo.c_str(),"12")==0)
        return 12;
}

void SavePartita2(string PathDaPassare)
{
    string coordinata;
    ifstream partita_temp ("temp\\temp.txt",ios::in);
    PathDaPassare+=".game";
    ofstream PartitaSave (PathDaPassare.c_str(),ios::out|ios::trunc);
    while(getline(partita_temp,coordinata))
    {
        PartitaSave << coordinata << endl;
        coordinata.clear();
    }
    PartitaSave.close();
    partita_temp.close();
    return ;
}

void SavePartita()
{
    ifstream partita_temp ("temp\\temp.txt",ios::in);
    string coordinata;
    string NomeBoard;
    string NomeDir;
    string Path;
    cout << "Inserire il nome della Directory da creare. Non sono ammessi sottolivelli." << endl;
    cin >> NomeDir;
    CreateDirectory(NomeDir.c_str(),NULL);
    cout << "Inserire il nome del file contente la Partita" << endl;
    cin >> NomeBoard;
    Path+=NomeDir;
    Path+="\\";
    Path+=NomeBoard;
    Path+=".game";
    ofstream PartitaSave (Path.c_str(),ios::out|ios::trunc);
    while(getline(partita_temp,coordinata))
    {
        PartitaSave << coordinata;
        coordinata.clear();
    }
    PartitaSave.close();
    partita_temp.close();
    return ;
}

void LoadPartita(quadrato board[][8])
{
    string Xiapp;
    string Yiapp;
    string Xfapp;
    string Yfapp;
    int Xi,Yi,Xf,Yf;
    string PathGame;
    string Path1;
    string App1;
    string NomePartitaImp;
    system("cd");
    system("tree");
    system("dir /B");
    Path1+="dir ";
    cout << "Inserire il nome della cartella" << endl;
    cin >> App1;
    Path1+=App1;
    Path1+=" /B";
    system(Path1.c_str());
    system("PAUSE");
    cout << "Inserire il nome del file da importare. Usare il doppio '\' per le cartelle " << endl;
    cin >> PathGame;
    PathGame+=".game";
    ifstream ImportedGame (PathGame.c_str(),ios::in);
    cout << "Partita Caricata" << endl;
    cout << "--------------------------------------" << endl;
    while(getline(ImportedGame,Xiapp))
    {
        getline(ImportedGame,Yiapp);
        getline(ImportedGame,Xfapp);
        getline(ImportedGame,Yfapp);
        Xi=ConvertiCoordinate(Xiapp[0]);
        Yi=ConvertiCoordinate(Yiapp[0]);
        Xf=ConvertiCoordinate(Xfapp[0]);
        Yf=ConvertiCoordinate(Yfapp[0]);
        MasterMode(Xi,Yi,Xf,Yf,board);
        Xiapp.clear();
        Yiapp.clear();
        Xfapp.clear();
        Yfapp.clear();
        system("PAUSE");
    }
    return;
}
