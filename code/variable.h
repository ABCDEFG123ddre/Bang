#include <stdbool.h>
#include <time.h>
typedef struct
{
    int alive;
    int health;
    int character;
    int cards [15];
	int weapon;
    int role;
	int distance;
	bool HasMustang;
    int hide;

}player;


void playGame();
void shuffle(int *arr, int n);
void showSheriff(int sheriffNum);
void computerTurn(player p[], player *player, int n, int deck[], int* pointDeck);
void playerTurn(player p[], player *player, int deck[], int* pointDeck);
void setPlayer(player* player, int n, int arr[],int arrChar[]);
void showPlayerStruct(player* player, int n);
int checkWin (player p[], int sheriffNum, int sheriffNum7);
int checkCard(player *player,int start, int end);
void showAllCard(int hand[10]);
void cardName(int id, char str[]);
void showCharacter(int num, char str[]);
void showrole(player p[], int idx);
void showINFO(player p[]);
void PrintInfo(player p[]);
void help(void);

void DrawCard(int deck[], int* pointDeck , int playerCards[], int num);

// source is where that card from
// sourceCardIndex is the index of the cards in source[]
void Discard(int deck[], int source[], int sourceCardIndex, int bound); 


//int NumberOfPlayer(player p[]); get the total number of player(temporary)
//void doAfterDeath(player* p, int deck[]); do the thing when someone died.
void Bang(player p[], int current, int target, int deck[], int* pointDeck);
int Beer(player p[], int deck[], int current);
void Sallon(player p[], int deck[], int current);
void WellsFargo(player p[], int current, int deck[], int* pointDeck);
void Diligenza(player p[], int current, int deck[], int* pointDeck);
void Panic(player p[], int current, int target, int deck[], int* pointDeck);
void Gatling(player p[], int current, int deck[], int* pointDeck);
void CatBalou(player p[], int current, int target, int deck[]);
bool HasBarrel(player p, int target, int* pointDeck, int deck[], int character);
int HasMiss(player p, int target, int hasPlayed, int character);

int getDistance(player players[], int nowTurn, int targets[]);

void help(void);
