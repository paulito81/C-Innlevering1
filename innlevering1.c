#include <string.h>
#include <stdio.h>
#include "fileList.h"
#include <math.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

// READ FROM FILE
int readFromFile(char path [] );
void readFileMenu(char printOut[], char filename[], int menuChoice, int menuChoice2, char inputFileName[], long unsigned int numbersOfFile[]);

// PRINT OUT
void printOut(int index, int numbersOfFile[], int numChoice, int totalSum, char filename[]);
void printQuit();

// SEARCH MENU
void runSearchMenu(int numbersOfFile[], int index, char filename[], int totalSum, int menuChoose);
void resetValues(int totalSum, char filename[], int index, int numbersOfFile[] );


// SORT ALGORITHM
void bubbleSort(int countOfNumbers[], int sum  );
void quicksort( int countOfNumbers[], int firstElement, int lastElement );

// SEARCH ALGORITHM
int binarySearch( int numberArray[], int searchKey, int firstElement, int middle, int lastElement, int index, char filename[]);
int linearSearch( int numberArray[], int searchKey, int index, int tempNum , char filename[] );


int main(int argc, char *argv[] ){

        char printOut[45] = "------------------------------------------";
    
        char filename[1000] = "";
        int menuChoice =0, menuChoice2 =0;
        char inputFileName[100];
        long unsigned int numbersOfFile[5000];

        readFileMenu(printOut, filename, menuChoice, menuChoice2, inputFileName, numbersOfFile);

        return 0;
}
void readFileMenu(char printOut[], char filename[], int menuChoice, int menuChoice2, char inputFileName[], long unsigned int numbersOfFile[]){
                
                do{    //MENU CHOICE
                
                    printf("\n%s\n'Velkommen til Innlevering 1.0'\n%s\nVelg et av valgene under fra menyen:\n(Tast inn et tall mellom 1-4 + Trykk 'Enter')\n\n%s\n", printOut, printOut, printOut);
                    printf("[Tast 1]\tLes inn en fil fra keyboard.\n");
                    printf("[Tast 2]\tVelg en fil fra en ferdig liste.\n");
                    printf("\n([Tast 3] for å 'avslutt programmet')\n:");
                    scanf("%d", &menuChoice);
                    
                    switch( menuChoice){

                            case 1:
                                    //READ FILE FROM KEYBOARD INPUT    
                                    printf("\nSkriv inn filen du ønsker å åpne.\n(F.eks tast:  /home/ubuntu/Documents/Innlevering1/1.txt + 'Trykk Enter'  )\n:");
                                    scanf(" %s", inputFileName);
                                    strcat(filename, inputFileName);
                                    readFromFile(filename);

                                    break;

                            case 2:
                                    do{
                                        // READ FILE FROM LIST
                                        printf("\n%s\nVelg en av filene fra listen: \n(Tast inn et tall mellom 1-4 + Trykk 'Enter')\n%s\n", printOut, printOut);
                                        printf("[Tast 1]: %s\n", FILENAME1 );
                                        printf("[Tast 2]: %s\n", FILENAME2 );
                                        printf("[Tast 3]: %s\n", FILENAME3 );
                                        printf("[Tast 4]: %s\t\t(nb! tar lang tid ved bruk av bubbleSort (+4min)\n%s\n", FILENAME4, printOut );
                                        
                                        printf("\n([Tast 5]: For å avslutt og gå tilbake til hovedmeny)\n\n:" );
                                        scanf(" %d", &menuChoice2);
                            
                                        switch( menuChoice2 ){

                                                case 1:
                                                        strcat(filename, FILENAME1);
                                                        readFromFile(filename);
                                                        break;
                                                case 2:
                                                        strcat(filename, FILENAME2);
                                                        readFromFile(filename);
                                                        break;
                                                    
                                                case 3:
                                                        strcat(filename, FILENAME3);
                                                        readFromFile(filename);
                                                        break;

                                                case 4:
                                                        strcat(filename, FILENAME4);
                                                        readFromFile(filename);
                                                        break;

                                                case 5:
                                                        printf("  >>Programmet går tilbake til hovedmeny>>\n");    
                                                        break;    

                                                default:        
                                                        printf("En ugyldig inputverdi har blitt registret.\t\t --> Velg en verdi mellom [1..2] <--\n\n");
                                                    
                                        }
                            
                                    }while( menuChoice2 !=5 && menuChoice2 != 0 && !isdigit(menuChoice2) );
                                                break;
                            case 3:

                                    printf("\nProgrammet avsluttes!\n\t\tØnsker deg en fin dag videre!\n\n");
                                    printQuit();                        
                                    break;
                            
                            default:
                                printf("En ugyldig inputverdi har blitt registret.\t\t --> Velg en verdi mellom [1..3] <--\n\n");                            
                    }

                }while( menuChoice !=3 && menuChoice !=0 && !isdigit(menuChoice)  );
            
}// END OF READFILE MENU           


// FILE OPTIONS MENU
int readFromFile(char filename[]){
    int menuChoose;
   
    int numbersOfFile[2000000];
    int totalSum;

   
    FILE* f = fopen(filename, "r");

    int scanNumber = 0;
    fscanf ( f, "%d", &scanNumber);
    int index = 0;

    //SORT FILE MENU
    printf("\nVelkommen til sortering:\nVelg type sortering\n1: Bubblesort\n2: QuickSort\n");
    scanf("%d", &menuChoose);

    if( menuChoose == 1){
        
        while (!feof (f)){
            
            fscanf (f, "%d", &scanNumber);
            
            numbersOfFile[index] = scanNumber;
            totalSum += scanNumber;
            index++;
        }

        // BUBBLE SORT
        bubbleSort(numbersOfFile, index);        
        printOut( index, numbersOfFile, 1, totalSum, filename);
        totalSum =0;

    }else if( menuChoose == 2){

        while (!feof (f)){
            
            fscanf (f, "%d", &scanNumber);
            
            numbersOfFile[index] = scanNumber;
            totalSum += scanNumber;
            index++;
        }

        //QUICK SORT
        quicksort(numbersOfFile, 0, index-1);
        printOut( index, numbersOfFile, 2, totalSum, filename);
        totalSum =0;

    }
    fclose (f);
    menuChoose = '\0';
        
    runSearchMenu(numbersOfFile, index, filename, totalSum, menuChoose);
    return 0;
}
// SEARCH MENU OPTIONS
void runSearchMenu(int numbersOfFile[], int index, char filename[], int totalSum, int menuChoose){
    int searchKey;
    char print[25] = "------------------------";
    printf("\n%s\nVelkommen til filsøk:\n%s\nVelg type søk\n[Tast 1]: BinarySearch\n[Tast 2]: LinearSearch\n\n([Tast 3]: for å avslutte programmet)\n", print, print);
    scanf("%d", &menuChoose);

    
        switch(menuChoose) {

            case 1:
                        printf("\n(BinarySearch):\n");
                        printf("Hvilket tall vil du søke etter, skriv inn et søketall:\n(F. eks [Tast: 8021] )\n" );
                        scanf("%d", &searchKey);
                        binarySearch( numbersOfFile,  searchKey , 0, 0, index-1,  index, filename);

                        break;
            case 2:
                        printf("\n(linearSearch):\n");
                        printf("Hvilket tall vil du søke etter, skriv inn et søketall:\n(F. eks [Tast: 8021] )\n" );
                        scanf("%d", &searchKey);
                        linearSearch(numbersOfFile, searchKey, index,  0 , filename);    

                        break;
            case 3:        
                        printf("\nDu har valgt å avslutte! programmet\n" );
                        printQuit();
                        exit(0);
                        break;            

            default:
                        printf("En ugyldig inputverdi har blitt registret.\t\t --> Velg en verdi mellom [1..3] <--\n\n");                            
                        break;

        }
        //RESET VALUES
        resetValues(totalSum, filename, index, numbersOfFile);
}
void resetValues(int totalSum, char filename[], int index, int numbersOfFile[] ){
        totalSum = 0;
        filename[0] = 0;
        index = 0;
        numbersOfFile =0;
}

// PRINT OUT RESULT
void printOut(int index, int numbersOfFile[], int numSum, int totalSum, char filename[] ){

        for( int j = 0; j < index; j++ ) {
                printf("%d\n", numbersOfFile[ j ]);
        }
        
        printf("\n(%s) er gjennomsøkt ok!\n--------------------------\n1) Summen av alle tallene:  %d\n", filename, totalSum );
        printf("2) Antall tall i filen:\t\t%d\n", index);

        switch(numSum){

            case 1:
                    printf("3) Filen er ferdig sortert ved hjelp av 'Bubblesort'\n");
                    break;
                    
            case 2:
                    printf("3) Filen er ferdig sortert ved hjelp av 'QuickSort'\n");
                    break;
                    
            default:
                    printf("En feil verdi er registret %d", numSum);        
                    break;
        }
}

//BUBBLE SORT ALGORITHM
void bubbleSort( int array[], int size ) {

    int xNum, yNum, k, temp;
 
    printf("\nUsortert liste:");
    for (k = 0; k < size; k++) {
         printf("%d ", array[ k ]);
    }
    
    for ( xNum = 1; xNum < size; xNum++ )
    {
        for ( yNum = 0; yNum < size - 1; yNum++ )
        {
            if ( array[ yNum ] > array[ yNum + 1] )
            {
                temp = array[ yNum ];
                array[ yNum ] = array[ yNum + 1 ];
                array[ yNum + 1] = temp;
            }
        }
    }

    for (k = 0; k < size; k++) {
                printf("%d", array[ k ]);
    }

}

//QUICKSORT ALGORITHM
void quicksort( int array[], int firstElement, int lastElement ){

     int iFirst, temp, xNum, yNum;

     if( firstElement < lastElement ){

         iFirst = firstElement;
         xNum = firstElement;
         yNum = lastElement;

         while( xNum < yNum ){
             
             while( array[ xNum ] <= array[ iFirst ] && xNum < lastElement )
                 xNum++;
             
             while( array[ yNum ] > array[ iFirst ] )
                 yNum--;

             if( xNum < yNum ){
                 temp = array[ xNum ];
                 array[ xNum ] = array[ yNum ];
                 array[ yNum ] = temp;
             }
         }

         temp = array[ iFirst ];
         array[ iFirst ] = array[ yNum ];
         array[ yNum ] = temp;
         
         quicksort( array, firstElement, yNum - 1);
         quicksort( array, yNum + 1, lastElement);

    }
}

int binarySearch( int numberArray[], int searchKey, int firstElement, int middle, int lastElement, int index, char filename[] ){

        firstElement = 0;
        lastElement = index - 1;
        middle = ( firstElement + lastElement ) / 2;

        while( firstElement <= lastElement){

            if( numberArray[ middle ] < searchKey ){
                firstElement = middle + 1;
            }
            else if ( numberArray[ middle ] == searchKey){
                printf("\n4) 'BinarySearch' har gjennomsøkt ferdig --> \nTallet ditt:  '%d' , finnes på index-nr:[%d] i filen: %s!\n",  searchKey, middle + 1, filename );
                return 1;
            }
            else
                lastElement = middle - 1;
                middle = ( firstElement + lastElement ) / 2;
        }
        if( firstElement > lastElement )
            printf("\n4) 'BinarySearch' har gjennomsøkt ferdig --> \nTallet ditt: '%d' , 'finnes dessverre ikke i filen: '%s'\n", searchKey, filename);

        return 0 ;
}

int linearSearch( int numberArray[], int searchKey, int index, int tempNum , char filename[]){

    for( tempNum = 0; tempNum < index; tempNum++ ) {

        if( searchKey == numberArray[tempNum] ){

            printf("\n4) 'LinearSearch' har gjennomsøkt ferdig --> \nTallet ditt: '%d' , finnes på index-nr:[%d] i filen: '%s'\n", searchKey, tempNum +1,filename);
            return 1;
        }
    }
    if( tempNum == index){
        printf("\n4) 'LinearSearch' har gjennomsøkt ferdig --> \nTallet ditt: '%d' , 'finnes dessverre ikke i filen: '%s'\n", searchKey, filename);
        return 0;
    }        

    return 0;
}

                                                                                              
                                                                                                    
void printQuit(){   


unsigned int sleep();
sleep(1);
printf("                                      ..    . ..                              \n");
printf("                                ....  .  .,.  .  . .  .                  \n");                                    
printf("                        .... ........   .. . ... .                        \n");                                  
printf("                      .....,IDMMMMMM8=,..~MNODO=                             \n");                                 
printf("                    .   ,,7M?..  .    ,+MM= . ~,=I..... ..,=+~.....,...... \n");                 
printf("               ....... ,M~... M~  ..=M .. . .. .,::M..... =, .,:M..~O::,...  \n");                
printf("              .....+M+++M:  $. . . ..$ . ........:,M,...,M., .:O..,:=..M..    \n");              
printf("           ...:M7MN .. ., I8 ...... ..M.      ....:.8...+O?==+~I,..,Z..,?...   \n");             
printf("           . .$  O,,, , .:,M....+M .:.M:      ....,:,$. $MI:.,:8+..:8..,O...    \n");            
printf("           ,.M ,,~ .~M? .,:Z . ..,  ,.D ,     ....,:~7,I. ..   :?N:,+.:.Z...    \n");            
printf("           .=M ..I .,....:.MD .. ,.,,M  ... .......,,,DN..,,::::M7O~$8OM....     \n");           
printf("          ..~M. .?8.  ..$8~. ?Z+,,=O?,. ..I.  ......,:+~,..::::M:..,,:~,=...     \n");           
printf("          . ,M...  N?MM7... .. .~:..., .  :~. .......:,IM,....,D.....,::=...     \n");           
printf(" .  . ....+8DNZI:. ..  .....    .......... $........:::M.O...........,:?..       \n");           
sleep(1);
printf(" . , ,M~   ...   ...  .                  . M=.....,::.O,.7...........::M..       \n");           
printf(" . +?... .. .. . . .                      .,M,:,,:=8D,.,.M.     .....:,M.        \n");           
printf(" ,O...  .  . ..    ..                       ,,=::,.M,.. ?8.     .....:,M.        \n");           
printf(" =: . ..  7MMMMM?. ....                   .,  ,::::O7.. O?.     .....::D.        \n");           
printf(".I..  .~MMNDDNMMMMM~ .                        ...:,.M...M..     .....,:O....     \n");           
printf("N.. ..ZNNDDNMMMMMMMMZ,                        ...::,~:. Z..     .....::Z....     \n");           
printf("8+... IMDNDNMMMMMMMMMMZ,                       ...,::.N.:~       .....::$....    \n");           
printf("M. ..=MNDNNMMMMMMMMMMMMZ. ...                   . ,::,8.+, .     .....::7....    \n");            
printf("I.. .MMNDNNMMMMMMMMMMMNM..                     .. .:::~,$ .      .....::7....    \n");            
printf("+.   MNDDNMMMMMMMMMMMMMM?. ..                    ...::.$M. .     .....::7....    \n");           
printf("?   .MNDDMMMMMMMMMMMMMMMZ..                       ..::,D8..      ....:::I....    \n");           
printf("Z ...MNNNMMMMMMMMMMMMMMMZ,  .                     ..:::ZI  .     ....:::I....    \n");           
printf("M: . MNNNMMMMMMMMMMMMMMM7,                        ..,::=, .      ....:::I....    \n");           
printf("IZ ..OMMNMMMMMMMMMMMMMMM~.. .                 .... ..,:7.        ....,::7....    \n");           
printf("8 .  ZMNNMMMMMMMMMMMMMM:....                 .... ...:N ...     ....:::Z....     \n");           
printf(":~ ...MMNMMMMMMMMMMMMN?, ..                  ....  ..:N.. .     ....,::O....     \n");          
printf("M ..,,MMMMMMMMMMMMNM::              .       ....  ..:$...      ....:::M.         \n");          
printf(".7 .  .DMMMMMMMMMMZ~:               ...     .... ...:~...      ....::,M.         \n");          
printf(". ~, . ...~OMMMMO~::  .              ............ ...8....      ....::.Z.        \n");          
printf("   ?:.. ... ...,.  .     ..  ..... ~MMMN...........+MN....      ...,,::=.        \n");           
printf("   .8Z... ..    ...    ........ ,=MNMMMM,.........?OZM....      ...,:,=,.        \n");            
printf(".. . N..  ....... ... . .,=8MMMMMMMMMMM........:N7ZZO....      ...::,Z..        \n");            
printf("   .,. NM=... .:=+8M8$~ :MMMMMMMMMMMMMM......Z$?ZZZO?.         ...::~M..        \n");            
printf("    ..  .  .. ..  . =... .IMMMMMMMMMMIO...:MMIZOOOZNZ,.         ..,::8+..        \n");            
printf("    . ..... . .  . .:,.,..~MMMMMMMMM~M.~$M$7ZOZZOZM,I..         ..,:,M,..        \n");            
printf("                  ..Z+?$MMNNMMMMMMMD..MZZZZZZZOZNI.....        ...:::= ..        \n");            
printf("                  ..ZZZNNNMMNOI+....,NOZZ$ZOZOM:,......        ..,:,8  .         \n");            
printf("              .   ..$ZO,.........,,=NOZZZZ8MZ,....   ..     .  .,::.Z  ..        \n");            
printf("                ....ZDM8,,,,.,,:,=MDOOZOND~,,...... ...        .:::~:.           \n");            
printf("              ..  .M... .=7MNDNO$Z$$+~:,.............        ..:::,M. ...         \n");           
printf("                . $....... .....~,........    .....       ....::,,.I..              \n");         
printf("               . I$  . ... .,.:NI=IZ+....                 ...,::::.7...               \n");       
printf("               ...M,. ~N... ..:7~???7I=..                  ..,::::::Z....               \n");     
sleep(1);
printf("               ...O...$$    ..?=+?I?I?I...                 ...,,:,::,?.  .               \n");     
printf("              .  $ ..D=    .,.D+??77Z:...                 ....:::,::7.. .               \n");     
printf("               .7.. D:    ...,:NDNO,....                 .....:::::.M,                 \n");    
printf("           .... :~. .D:         .....                      .  .,::::,:M....             \n");     
printf("           ...  7 . .D,         .....                      . . ,::::::+,....            \n");     
printf("           ...,:~..  D:                                      . .,:::::.M.....           \n");     
printf("      .  .  . 8,  ...N=                                         .,:::,,~:..             \n");     
printf("      ..... +M=      .OI                                         ..:::::,N ..           \n");     
printf("       . ,M:,  ..,  .7O                                         ..:::::,I. .            \n");    
printf("  . ....M: +..........~M. ...                                    ...:::::,Z..            \n");   
printf("  . ..Z,I:...........::Z..                                       ...,::::,87..            \n");   
printf(" .. O.+M  .7:....,,::::~ .                                      ....::::,~M .            \n");   
printf(" . ,Z..+,,.:M,~$:,~~::,O .                                      ....:::::.Z .            \n");   
printf(" .  ?D::7M..ZO::~:~,::.D . ,                                    ....:::::.=,             \n");   
printf("  .. . I.,7M+?,,::,:.NZ.O. .                                    ....:::::.~~.            \n");   
printf("     ..D,,:O=.,7~.+M,.. =,                                      ....,::::,~,.....        \n");   
printf("     ...,Z...,~M?.... .  8I                                     ....,::::.I.... .        \n");   
printf("     . ..=:.,+7.... . .   Z                                     ....,::::,OD$~=~ .       \n");   
printf("       .. .. .....     ...O .                                  ....::::,+D,,.?,         \n");  
printf("        .. .  ..       .. ..8,.,                                ...,::::,M~.$=..         \n");   
printf("                            D  .         ..........             ...::::,~Z7..            \n");   
printf("                            D. .          . .......             ..,:::::M ..              \n");  
printf("                            8.           .,IN8=..,.             .,::,,,$....              \n");  
printf("                            $ .            ::::,O..        .....:,:::,?,.                 \n");  
printf("                            I.           ..  ::,O..         ......,:::M..                 \n");  
printf("                            I.            .  :::8..           ....,:,,N..                 \n");  
printf("                            7. .          ...:::8..             ..,::,7..                 \n");  
sleep(1);
printf("                            Z..           . .::,O..             ...:,:~:.                 \n");  
printf("                            D .          ..  ,::$..             ...:::,I.                 \n");  
printf("                       . .  N...           . ,::+,.             ...,,:,M....               \n");  
printf("                        .  .D ..           . ,~,::.             ...,,::N....               \n");
printf("                       ....:Z .            . ,~,~?.             ....::,=,...               \n");
printf("           ............. ..~7.. ... ..........,:IO,...            . .:::.I.                \n");  
printf("          ...............M~,. .  . .........,::O,....             ...:::N  ..              \n");    
printf("         ..........,,,:~=....~: .. .......,:,M .   ...           ...:::Z.........         \n");
printf("      .  ...,:~~~=======$,...?:  ..7,......::8..  . ,. . ,.        ..::~~?=:~,,...  .      \n");
printf("       .::~============~Z....M.  .IO......,::7, ..~~ .  .O       ....:::,Z=~====~:. .       \n");
printf("     . .:~=~~=~~~======~~M~..8....ZI....,:::,?.   M ...,?O.     ....::::8:===~~==~,         \n");
printf("     .  ,,:~~=~~======~==~IM=Z....Z$,,,:~+ZMM8. . M.  . +D ... ,...,~,:M~======~:.....     \n");
 printf("     . .....,,:::~~~~~~=~~~~=+?I?+==~~~====~M . Z ... ,M. .. ,=+OM$~:~~::,,........  \n");     
 printf("      .. ...............,.,.,,,,:,::~::::~~~~~~:~~OMO$I7$8MMN7?: ..,....,........... \n");         
 printf("                    ...........................    .    .............  \n");                      
 printf("                        ......................        ......      \n\n");

printf(" \t\t\t\tGOOD BYE! \n\n");


 }