#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Function to generate secret code
char* generateCode(){
  char* codeToUse = malloc(4  * sizeof(char));
  srand(time(0));

  //Declaring colors
  char* colors[9] = {"red", "pink", "bleu", "green", "grey", "yellow", "white", "black", "orange"};

//Generating secret code
for(int i=0; i < 4; i++){
  codeToUse[i] = *colors[rand() % 9];
  }
  return codeToUse;
}

struct mastermind_args{char* code; int attemp;};
struct mastermind_args parse_args(int argc, char **argv){
  struct mastermind_args arg;
  arg.code = generateCode();
  arg.attemp = 10;
  for(int i=1; i < argc; i++){
    if (strcmp(argv[i], "-c") == 0){
      arg.code = argv[i+1];
    }
    else if(strcmp(argv[i], "-t") == 0){
      arg.attemp = *argv[i+1];
    }
  }
  return arg;
}

//Fuction to check if player guessed right
int checkGuess(char secretCode[4], char playerGuess[5]){
  int wellPlacedPieces = 0;
  int missPlacedPieces = 0;

  for(int i=0; i < 4; i++){
    if(secretCode[i] == playerGuess[i]){
      wellPlacedPieces++;
    }
    else{
        for(int j=0; j <= 4; j++){
            if(secretCode[j] == playerGuess[i]){
                missPlacedPieces++;
                break;
            }

        }
    }
  }
  
if(wellPlacedPieces == 4){
  return 1;
  }
else{
  return 0;
  }
  printf("Well placed pieces: %d\nMissplaced pieces: %d\n", wellPlacedPieces, missPlacedPieces);
}

//Function to execute the game
void mastermind(struct mastermind_args *args){
  printf("Will you find the secret code?\n");
  printf("Please enter a valid guess\n");
  
  //Declaring and initializing attempt variable
int attempts = args->attemp;
int round = 0;

while(attempts > 0){
  printf("---\nRound %d\n", round);
  //Declaring player guess
  char playerGuess[5];
  ssize_t eof = read(STDIN_FILENO, playerGuess, sizeof(playerGuess));
  if(eof == 0){
      return;
  }

//Checking if player guessed right
  if(checkGuess(args->code,playerGuess)){
      printf("Congratz! You did it!\n");
      break;
  }

  //Decrementing attempts
  attempts--;
  round++;
    
  }
  if(attempts == 0){
    printf("You failed to guess the secret code\n");
 }
}

int main(int argc, char **argv){
  struct mastermind_args args = parse_args(argc, argv);
  
 //Calling mastermind
mastermind(&args);

    return 0;
}
