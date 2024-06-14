// Rock Paper Scissors Game //

// Programmed by ThatCodedDude //

// First program with data saving! //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#define MAX 100

#define SUCCESS 1
#define FAILURE 0

#define INVALID 10
#define WIN 1
#define LOSS 0
#define TIE 2

const char* SaveFileName = "RPSSave.txt";

typedef struct GameInfo{

  int Wins;
  int Losses;

}GameInfo;

typedef enum Choices{

  ROCK = 2,
  PAPER = 0,
  SCISSORS = 1,

}Choices;

const char PlayArray[3] = {'R', 'P', 'S'};

GameInfo NewGame;

void wait(float);

void ClearScrn();

void TitleScreen();
void SaveData();
int LoadData();

Choices PlayerInput(char*, char*, char**);
Choices ComputerInput(char*, char**);

int MainGame();

int main(){

  int Data = LoadData();

  if(Data == FAILURE){

    SaveData(); // Creates Save File

  }

  atexit(SaveData); // Saves Data

  while(1){

    ClearScrn();

    TitleScreen();

    int Result = MainGame();

    if(Result == WIN){

      NewGame.Wins++;
      continue;

    }else if(Result == LOSS){

      NewGame.Losses++;
      continue;

    }else if(Result == INVALID){

      continue;

    }



  }

}

void TitleScreen(){

  char* Programmer = "ThatCodedDude";

  char* MainTitle = " _____            _      _____                         _____      _\n"
                    "|  __ \\          | |    |  __ \\                     / ____|    (_)                       \n"
                    "| |__) | ___   ___| | __ | |__) |_ _ _ __   ___ _ __  | (___   ___ _ ___ ___  ___  _ __ ___ \n"
                    "|  _  / / _ \\/ __| |/ / |  ___/ _` | '_ \\ / _ \\'__|\___ \\ / __| / __/ __|/ _ \\| '__/ __|\n"
                    "| | \\ \\(_) | (__|   <  | |  | (_| | |_) |  __/ |    ____) | (__| \\__ \\__ \\ (_)| |  \\__ \\\n"
                    "|_| \\_\\___/ \\___|_|\\_\\ |_|  \\__,_| .__/ \\___|_|    |_____/\\___|_|___/___/\\___/|_|  |___/\n"
                    "                                   | |                                                     \n"
                    "                                   |_|                                                     \n";

  printf("%s\n\n", MainTitle);

  printf("(Game Title ASCII Messed up...)\n\n");

  printf("Programmed By: %s\n\n", Programmer);
  printf("Press A to Play!\n\n");

  printf("Wins: %d Losses: %d \n\n", NewGame.Wins, NewGame.Losses);

  bool Waiting = true;

  while(Waiting){

    char Input = getch();

   if(tolower(Input) == tolower('A')){

      Waiting = false;

   }else{

     continue;

   }

  }


}

int MainGame(){

   char Input[MAX];

   char* Result;

   ClearScrn();

   int MainResult = INVALID;

   printf("Type In either Rock, Paper, or Scissors (Not Case-Sensitive)\n\n");

   printf("Player's Input: ");

   fgets(Input, MAX, stdin);

   char PlrChar; char* Chosen;

   Choices PlrChoice = PlayerInput(Input, &PlrChar, &Chosen);

   if(PlrChoice == INVALID){

     return INVALID;

   }

   char CPUInput; char* CPUChose;

   Choices ComputerChoice = ComputerInput(&CPUInput, &CPUChose);

   printf("\n");

   printf("Player's Choice: %s\n", Chosen);
   printf("Computer's Choice: %s\n\n", CPUChose);

   if(PlayArray[PlrChoice] == CPUInput){

     MainResult = WIN;

     printf("You Win!");

   }else if(PlayArray[ComputerChoice] == PlrChar){

     MainResult = LOSS;

     printf("You Lose!!");

   }else if(PlrChar == CPUInput){

     MainResult = TIE;

     printf("Tie Game!");

   }

   printf("\n\nPlay Again: A\n");
   printf("Title Screen: B\n");

   bool Waiting = true;

  while(Waiting){

    char Input = getch();

   if(tolower(Input) == tolower('A')){

      if(MainResult == WIN){

        NewGame.Wins++;

      }else if(MainResult == LOSS){

        NewGame.Losses++;

      }

      MainGame();
      break;

   }else if(tolower(Input) == tolower('B')){

     return MainResult;

   }

  }

  //return MainResult;
}

Choices PlayerInput(char* Input, char* CharAddress, char** Chose){

  Choices ReturnInput;

  // Finds and Destroys New-Line Character //

  char PlaceHolder[MAX];

  strcpy(PlaceHolder, Input);

  PlaceHolder[strcspn(Input, "\n")] = 0;

  Input = PlaceHolder;

  // Lowercases Input //

  for(int i  = 0; i < (sizeof(Input) / sizeof(char)); i++){
    PlaceHolder[i] = tolower(PlaceHolder[i]);
  }

  // Checks Input //

  if(strcmp(PlaceHolder, "rock") == 0){

    *Chose = "Rock";

    ReturnInput = ROCK;
    *CharAddress = PlayArray[0];

  }else if(strcmp(PlaceHolder, "paper") == 0){

     *Chose = "Paper";

     ReturnInput = PAPER;
     *CharAddress = PlayArray[1];

  }else if(strcmp(PlaceHolder, "scissors") == 0){

    *Chose = "Scissors";

    ReturnInput = SCISSORS;
    *CharAddress = PlayArray[2];

  }else{

    ReturnInput = INVALID;

    printf("\nInvalid Input...");

    wait(3);

  }

  return ReturnInput;

}

Choices ComputerInput(char* CharAddress, char** CpuChose){

  Choices CPUInput;

  srand(time(NULL));

  int Rand = rand() % 3; // Gets Random Choice

  *CharAddress = PlayArray[Rand];

  if(*CharAddress == PlayArray[0]){

    CPUInput = ROCK;
    *CpuChose = "Rock";

  }else if(*CharAddress == PlayArray[1]){

    CPUInput = PAPER;
    *CpuChose = "Paper";

  }else if(*CharAddress == PlayArray[2]){

    CPUInput = SCISSORS;
    *CpuChose = "Scissors";

  }

  return CPUInput;

}

void SaveData(){

  FILE* SaveFile;

  SaveFile = fopen(SaveFileName, "w");

  fprintf(SaveFile, "Wins: %d Losses: %d", NewGame.Wins, NewGame.Losses);

  fclose(SaveFile);

}

int LoadData(){

   int LoadingSave = SUCCESS;

  if(fopen(SaveFileName, "r")){ // Checks if File Exists

    FILE* File = fopen(SaveFileName, "r");

    fseek(File, 0, SEEK_END);

    int Size = ftell(File);

    if(Size != 0){ // Checks if the save file is empty

      int Wins, Losses;

      rewind(File);

      fscanf(File, "Wins: %d Losses: %d", &NewGame.Wins, &NewGame.Losses); // Gets Saved Data

      printf("Wins: %d Losses: %d", NewGame.Wins, NewGame.Losses);

      fclose(File);

    }else{

      printf("[-] The File is empty...\n");
      fclose(File);

      wait(2);

      exit(EXIT_SUCCESS); // Exits Program

      LoadingSave = FAILURE;

    }

  }else{

     LoadingSave = FAILURE;

  }

  return LoadingSave;

}


void wait(float Seconds){ // Sleep Function Wrapper

  Sleep(1000 * Seconds);

}

void ClearScrn(){ // Clear Screen Wrapper

  system("cls");

}
