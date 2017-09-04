#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ERROR 6
void welcome();
void init(char*, char*);
char leave();
void game(char *, char*, char*);
void hangman(int i);
void mysteryWord( char*);
void alphabet(char *);
int guess(char *ansWord, char *mystWord, char* abc);
void winner(char *);
void gameOver(char*);

//these are my global variables
int gameloop = 1;//this is my true for the game loop


int main(int argc, char *argv[]){
    char ansWord[] = "need a better word";//This will be the mystery word
    char mystWord[sizeof(ansWord)];
    while(gameloop){//this is to restart the game or play again
        char abc[] = {'a','b','c','d','e','f','g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o' , 'p' ,'q','r','s','t','u','v','w',
                      'x','y','z'};
        welcome();
        init(ansWord, mystWord);//this will set up the initial state of the game
        game(ansWord, mystWord,abc);
        if(((int)leave()) == 'n')//this is to see if you want to play again
            gameloop = 0;
    }
}


void welcome(){//this is just the welcome message
    printf("Welcome to Hangman in c\n");
    printf("hope you enjoy\n");
}



void init(char* ansWord, char* mystWord){
    FILE *file;//this creates a var of type FILE
    file = fopen("/media/randy/Storage/programming/more c/words.txt", "r");//opens the file with read permission
    if(file == NULL)//this checks for bad files
    {
        perror("fopen()");//if cannot open file throw error and exit
        exit(1);//  while ((ch = getchar()) != '\n' && ch != EOF);
    } else{
        time_t sec;
        sec = time (NULL);
        int rand = (sec*random())%10;
        int i = 0;
        while(fscanf(file, "%s",ansWord)!= EOF && i++ != rand);
    }
    fclose(file);//closed the file
    int size = sizeof(ansWord);
    memcpy(mystWord, ansWord, size);//copies ansWord to mystWord
    int i = 0;
    while(ansWord[i] !='\0'){//initializes the mystery word to blanks
        mystWord[i++] = '_';
    }
    mystWord[i] = '\0';
    printf("\n");
}


char leave(){
    printf("play again? \ny/n ");
    char ans,ch;
    fscanf(stdin,"%c", &ans);//get the user input
    while ((ch = getchar()) != '\n' && ch != EOF);
    while(ans != 'n' && ans != 'y'){//loop to check the validity of input
        printf("Please use only a \"y\" or a \"n\"\n");
        fscanf(stdin,"%c", &ans);
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("\n");
    }
    return ans;
}


void winner(char *mystWord) {//just a short function to say good job
    printf("\n\n\nYep the word was: %s\ncongratulations you won\n\n",mystWord);
}


void gameOver(char* ansWord){
    printf("\n\nLook what you have done.\nThe word was: %s\n", ansWord);
}


void game(char *ansWord, char* mystWord, char* abc){
    int error = 0;
    while(error<MAX_ERROR){//the game loop
        hangman(error);//draws the hangman
        alphabet(abc);//displays the remaining letters
        mysteryWord(mystWord);//prints the mystery word
        error = error + guess(ansWord, mystWord, abc);//this controls the users guess
        if(!strcmp(ansWord, mystWord) ){
            winner(mystWord);
            break;
        }
    }
    if(error == MAX_ERROR){
        hangman(6);
        gameOver(ansWord);
    }

}
void mysteryWord(char* mystWord){//this will printout the "_" and the letters of the word as the guesses go
    int i = 0;
    while(mystWord[i] != '\0'){
        printf("%c ",mystWord[i++]);//%c not %s
    }
    printf("\n\n");

}
void alphabet(char *abc){
    int i;
    for(i=0 ; i<26; i++){
        printf("%c ", abc[i]);
    }
    printf("\n");
}
int guess(char *ansWord, char *mystWord, char* abc){
    char ans,ch;//this is where we are going to save our user input
    do {
        if(abc[ans-97] == '_'){
            printf("\nPlease pick a new letter a - z\n");
        }
        printf("What is your next guess: ");
        fscanf(stdin,"%c",&ans);
        while ((ch = getchar()) != '\n' && ch != EOF);
        if(ans > 40 && ans < 91){
            ans = ans + 32;//makes the answer lower case
        }
    }while((ans < 97 || ans >122) && abc[ans-97] != '_');//this makes sure the answer is a character in the alphabet and hasn't already been chosen
    int i;//iterator to go through the word to find if the letter appears
    abc[ans-97] = '_';//this removes the letter from the alphabet
    int wrong = 1;
    for(i = 0; i< sizeof(ansWord); i++){
        if(ans == ansWord[i]){
            wrong = 0;
            mystWord[i] = ans;
        }
    }
    return wrong;
}
void hangman(int i) {
    switch (i){
        case (0):
            printf("  ______\n  |    |\n  |    \n  |   \n  |    \n  |\n|-----------|\n");
            break;
        case(1):
            printf("  ______\n  |    |\n  |    O\n  |   \n  |    \n  |\n|-----------|\n");
            break;
        case(2):
            printf("  ______\n  |    |\n  |    O\n  |    |\n  |    \n  |\n|-----------|\n");
            break;
        case(3):
            printf("  ______\n  |    |\n  |    O\n  |   /|\n  |    \n  |\n|-----------|\n");
            break;
        case(4):
            printf("  ______\n  |    |\n  |    O\n  |   /|\\\n  |    \n  |\n|-----------|\n");
            break;
        case(5):
            printf("  ______\n  |    |\n  |    O\n  |   /|\\\n  |   / \n  |\n|-----------|\n");
            break;
        default:
            printf("  ______\n  |    |\n  |    O\n  |   /|\\\n  |   / \\\n  |\n|-----------|\n");
            break;
    }
}
/*
printf("
  ______\n
  |    |\n
  |    \n
  |   \n
  |    \n
  |\n
  |-----------|\n");

*/