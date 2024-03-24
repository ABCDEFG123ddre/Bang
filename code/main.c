#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "variable.h"

int NumberOfPlayer=4;
int alivePlayer=4;

int main(){
	int menuInput=0;
	/*pid_t pid = fork();

	if (pid == 0) {
	   system("canebrake-gtk-play -f play.wav");
	   exit(0);
	}*/
	while(1){
		//system("aplay play.wav");
		printf("_____________Welcome to the game Bang!_____________\n(1)Play 4 players\n(2)Play 5 players\n(3)Play 6 players\n(4)Play 7 players\n(5)Help\n(6)Exit\nInput: ");
		scanf("%d",&menuInput);

		switch(menuInput){
		case (1):
			NumberOfPlayer=alivePlayer=4;
			playGame(4);
			break;
		case (2):
			NumberOfPlayer=alivePlayer=5;
			playGame(5);
			break;
		case (3):
			NumberOfPlayer=alivePlayer=6;
			playGame(6);
			break;
		case (4):
			NumberOfPlayer=alivePlayer=7;
			playGame(7);
			break;
		case (5):
			help();
			break;
		case (6):
			printf("Okay! See you next time!\n");
			return 0;
		default:
			printf("Menu input error!\n");
			break;
		}
	}

	return 0;

}

void playGame(int playerNumber){

	int sheriffNum = 0;
	int playerNum = 0;
	int pointDeck=0, deck[69]={0};
	int gameRunning = 0, nowTurn = 0;
	int everyOneHealth[playerNumber];		

	printf("The game is starting!\n");

	printf("\nShuffling the deck...\n");
	for (int i=1; i < 70; i++){
		deck[i-1]=i;
	}
	///Shuffle deck///
	shuffle(deck, 69-pointDeck);

	for(int i=0; i < 69; i++){
		if(deck[i] > 70) deck[i]=1;
	}
	///Shuffle deck///

	printf("\nSetting each players....\n");

	player p[playerNumber];

	////////////////Example////////////////
	/*printf("Old Health = %d\n",p[0].health);

	setPlayer(&p[0]);

	printf("New Health = %d\n",p[0].health);*/

	////////////////Example////////////////

	///Role randomizer///
	int arrRole[playerNumber];
	for(int i=0; i < playerNumber; i++){
		arrRole[i]=i;  
	}

	shuffle(arrRole,playerNumber);

	for(int i=0; i < playerNumber; i++){
		if(arrRole[i] > playerNumber) arrRole[i]=1;
		//printf("\n%d ROLE ROLE %d\n",i,arrRole[i]);
	}

	///Role randomizer///

	///Character randomize///
	int arrChar[16];
	for(int i=0; i < 16; i++){
		arrChar[i]=i;
	}

	shuffle(arrChar,16);

	for(int i=0; i < 16; i++){
		if(arrChar[i] > 16) arrChar[i]=1;
		//printf("\n%d CHAR %d\n",i,arrChar[i]);
	}
	///Character randomize///

	for (int i=0; i < playerNumber; i++){
		setPlayer(&p[i], i,arrRole,arrChar);
	}

	printf("\nShowing your info...\n");
	for (int i=0; i < playerNumber; i++){
		showPlayerStruct(&p[i],i);
	}
	
	int sheriffNum7;
	for(int i=0; i < playerNumber; i++){
		if (arrRole[i]==0) sheriffNum = i;
		else if(arrRole[i]==6) sheriffNum7=i;
	}
	printf("\nShowing sheriff positions....\n");
	showSheriff(sheriffNum);
	if(NumberOfPlayer==7)
		showSheriff(sheriffNum7);

	printf("\nShowing everybody's health...\n");
	for (int i=0; i < playerNumber; i++){
		printf("Player %d health = %d\n",i,p[i].health);
		everyOneHealth[i]=p[i].health;
	}


	printf("\nEach players first draw cards...\n");
	for (int i=0; i < playerNumber; i++){
		for (int j=0; j < p[i].health; j++){
			p[i].cards[j] = deck[pointDeck];
			deck[pointDeck]=0;
			pointDeck++;
		}
	}


	/*for (int j=0; j < playerNumber; j++){
			printf("\nP%d card is:\n",j);
		for (int i=0; i<p[j].health;i++){
			printf("Player's card= %d\n", p[j].cards[i]);
		}
	}*/
	int option;
	printf("If you are ready to start, please press 1. Otherwise, press 0 to go back to the menu.\n");
	scanf("%d", &option);
	if(option==0)
		return ;
	printf("\nGame starting....\n\n");
	printf("\n==========================================START GAME==========================================\n\n");

	///*////////////////////////////////////////////////                     ///*////////////////////////////////////////////////
	///*////////////////////////////////////////////////  Game is starting   ///*////////////////////////////////////////////////
	///*////////////////////////////////////////////////                     ///*////////////////////////////////////////////////

	gameRunning = 1;
	/// Sheriff Turn
	nowTurn = sheriffNum;
	int hasWarned=0;
	char buf;
	while(gameRunning == 1){// 1 == true
		
		PrintInfo(p);
		
		if (nowTurn == sheriffNum){
			printf("\n--------NEW ROUND--------\n\n");
		}
		if(p[0].health==1 && hasWarned==0){
			system("zenity --warning --text=\"You only have one life left!\"");
			hasWarned=1;
		}
		if (nowTurn == 0){
			if(p[0].alive==1)
				playerTurn(p,&p[0],deck, &pointDeck);
		}
		else{
			if(p[nowTurn].alive==1){
				computerTurn(p,&p[nowTurn],nowTurn,deck, &pointDeck);
				sleep(2);
			}
		}
		if(hasWarned==1 && p[0].health==2)
			hasWarned=0;
		if( checkWin(p,sheriffNum, sheriffNum7) == 100){
			gameRunning = 0;
			system("aplay exit_cue_y.wav >>/dev/null 2>>/dev/null");
		}
		nowTurn++;
		nowTurn %= NumberOfPlayer;
	}

	printf("\nGame finish~ Thank you for playing :) Back to the menu\n\n");

}

/////////////////////////////////////////////////////////////////////FUNCTION LIST/////////////////////////////////////////////////////////////////////


void computerTurn(player p[], player *player, int n, int deck[], int* pointDeck){
    srand(time(0));
    int randNum = rand()%10;
    //printf("\nRandom Number = %d\n",randNum);
	/// DRAW -> PLAY CARDS -> DISCARD
	DrawCard(deck, pointDeck , p[n].cards, 2);
	char str[100]={0};
	showCharacter(p[n].character,str);
	printf("\033[32m\nplayer %d (%s) turn\033[0m\n",n,str);
	/*for(int i=0;i<15;i++)
		printf("%d ",p[n].cards[i]);
	printf("\n");*/
	int cardIdx, target;
		if ((cardIdx=checkCard(player,14,38)) != 100){//BANG Card
			int targets[8]={0}, targetNum;
			targetNum=getDistance(p, n, targets);
			if(targetNum!=0){
				target=rand()%targetNum;
				printf("Player %d plays a BANG card!\n",n); ////////////////////////////BANG CARD
				Bang(p, n, targets[target], deck, pointDeck);
				Discard(deck, p[n].cards, cardIdx, 15);
			}
		}
		if(player->health <= 2 && (cardIdx=checkCard(player,39,44)) != 100){//BEER HEALTH
			int PlayBeer;
			PlayBeer=Beer(p, deck, n);
			if(PlayBeer==1)
				Discard(deck, player->cards, cardIdx, 15);
		}
		else if(player->health <= 2 && (cardIdx=checkCard(player,66,66)) != 100){//SALOON HEALTH
			printf("Player %d plays a SALOON card!\n",n);
			Sallon(p, deck, n);
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		if (randNum <=7 && (cardIdx=checkCard(player,67,68)) != 100){//STAGE COACH
			printf("Player %d plays a Diligenza card!\n",n);
			Diligenza(p, n, deck, pointDeck);
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		if (randNum <=5 && (cardIdx=checkCard(player,69,69)) != 100){//WELLS FARGO
			printf("Player %d plays a Wells Fargo card!\n",n);
			WellsFargo(p, n, deck, pointDeck);
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		if((cardIdx=checkCard(player,49,49)) != 100){//GATLING CARD
			printf("Player %d plays a GATLING card!\n",n);
			Gatling(p, n, deck, pointDeck);
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		if (randNum <=6 && (cardIdx=checkCard(player,45,48)) != 100){//CAT BALOU
			int targets[8]={0}, targetNum;
			targetNum=getDistance(p, n, targets);
			if(targetNum>0){
				printf("Player %d plays a CAT BALOU card!\n",n);
				CatBalou(p, n, targets[rand()%targetNum], deck);
				Discard(deck, p[n].cards, cardIdx, 15);
			}
		}
		if (randNum <=5 && (cardIdx=checkCard(player,62,65)) != 100){//PANIC
			int targets[8]={0}, targetNum;
			targetNum=getDistance(p, n, targets);
			if(targetNum>0){
				printf("Player %d plays a PANIC card!\n",n);
				Panic(p, n, targets[rand()%targetNum], deck, pointDeck);
				Discard(deck, p[n].cards, cardIdx, 15);
			}
		}
		if((player->weapon < 11 || player->weapon==12) &&(cardIdx=checkCard(player,11,11)) != 100){
			printf("Player %d change weapon to Winchester\n",n);
			p[n].weapon = 11;
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		else if((player->weapon < 10 || player->weapon==12) &&(cardIdx=checkCard(player,10,10)) != 100){
			printf("Player %d change weapon to Rev. Carabine\n",n);
			p[n].weapon = 10;
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		else if((player->weapon < 9 || player->weapon==12) &&(cardIdx=checkCard(player,9,9)) != 100){
			printf("Player %d change weapon to Remington\n",n);
			p[n].weapon = 9;
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		else if((player->weapon < 6 || player->weapon==12) &&(cardIdx=checkCard(player,6,8)) != 100){
			printf("Player %d change weapon to Schofield\n",n);
			p[n].weapon = 6;
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		else if((cardIdx=checkCard(player,12,13)) != 100){
			printf("Player %d change weapon to Volcanic\n",n);
			p[n].weapon = 12;
			Discard(deck, p[n].cards, cardIdx, 15);
		}
		if((cardIdx=checkCard(player,3,4)) != 100){
			printf("Player %d has Mustang\n",n);
			p[n].HasMustang = 1;
			p[n].cards[cardIdx]=0;
		}
		if((cardIdx=checkCard(player,5,5)) != 100){
			printf("Player %d has Scope\n",n);
			p[n].distance = (p[n].character==10 ? 3:2);
			p[n].cards[cardIdx]=0;
		}
	
	int count=0;
	int idx=0;
	for (int i =0; i < 15; i++){
        if (player->cards[i] != 0 )count++;
    }
	
	if(p[n].character==11 && (count-p[n].health)>=2){
		while (count > player->health){
			if(p[n].cards[idx]!=0){
				Discard(deck, p[n].cards, idx, 15);
				count--;
			}
			idx++;
		}
		if(p[n].health<4){
			printf("\033[36mplayer %d (Sid Ketchum) discard 2 cards to gain one live.\033[0m\n",n);
			p[n].health++;
		}
	}
	else if(p[n].character==11 && count>=2 && p[n].health<2){
		int c=0;
		for(int i=0;i<15;i++){
			if(p[n].cards[i]!=0){
				Discard(deck, p[n].cards, i, 15);
				c++;
			}
			if(c==2)
				break;
		}
		printf("\033[36mplayer %d (Sid Ketchum) discard 2 cards to gain one live.\033[0m\n",n);
		p[n].health++;
	}
	else{
		while (count > player->health){
			if(p[n].cards[idx]!=0){
				Discard(deck, p[n].cards, idx, 15);
				count--;
			}
			idx++;
		}
	}
	//printf("%d\n",count);
}

void playerTurn(player p[], player *player, int deck[], int* pointDeck){
	int cardIdx, index;
    int playerInput = 0;
    int count = 0 ;
    int playerDiscardNum = 0, playerCardNum = 0;
    int target = 0;
	int n = 0;
	int alreadyBang=0;
	
    printf("\n\033[92mIts the player turn!\033[0m\n");
    ///////////////////First Draw card
	DrawCard(deck, pointDeck , p[0].cards, 2);
    while (playerInput != 3){
        printf("\n(1)Show all data\n(2)Play Card\n(3)Discard card + end\n(4)Help\n");
        printf("Waiting for input: ");
        scanf("%d",&playerInput);

        if(playerInput == 1)
			showINFO(p);
        else if(playerInput == 4)
			help();
		
        else if (playerInput == 2){
            showAllCard(player->cards);
			printf(" - -1 Cancel");
            printf("\nCard number to play: ");
            scanf("%d",&playerCardNum);
			   index = checkCard(player,playerCardNum,playerCardNum);
			
			if(playerCardNum == -1)
				continue;
				
			if (playerCardNum >= 14 && playerCardNum <= 38 && (cardIdx=checkCard(player,14,38)) != 100 && alreadyBang==0){//BANG Card
				printf("Player %d plays a BANG card!\n",n); ////////////////////////////BANG CARD
				printf("Choose one target from following list: \n");
				int targets[8]={0}, targetNum;
				targetNum=getDistance(p, 0, targets);
				if(targetNum==0)
					printf("No one in your Bang distance.\n");
				else{
					for(int i=0;i<targetNum;i++)
						printf("player %d\n",targets[i]);
					scanf("%d",&target);
					Bang(p, n, target, deck, pointDeck);
					Discard(deck, p[0].cards, index, 15);
					if(p[0].character!=15 && p[0].weapon!=12)
						alreadyBang=1;
				}
			}
			else if(playerCardNum >= 14 && playerCardNum <= 38 && (cardIdx=checkCard(player,14,38)) != 100 && alreadyBang==1)
				printf("Can't play Bang.\n");
			else if(playerCardNum >= 39 && playerCardNum <= 44 && (cardIdx=checkCard(player,39,44)) != 100){//BEER HEALTH
				int PlayBeer;
				PlayBeer=Beer(p, deck, n);
				if(PlayBeer==1)
					Discard(deck, p[0].cards, index, 15);
			}
			else if(playerCardNum == 66 && (cardIdx=checkCard(player,66,66)) != 100){//SALOON HEALTH
				printf("Player %d plays a SALOON card!\n",n);
				Sallon(p, deck, n);
				Discard(deck, p[0].cards, index, 15);
			}
			else if(playerCardNum == 49 && (cardIdx=checkCard(player,49,49)) != 100){//GATLING CARD
				printf("Player %d plays a GATLING card!\n",n);
				Gatling(p, n, deck, pointDeck);
				Discard(deck, p[0].cards, index, 15);
			}
			else if (playerCardNum >= 45 && playerCardNum <= 48 && (cardIdx=checkCard(player,45,48)) != 100){//CAT BALOU
				printf("Player %d plays a CAT BALOU card!\n",n);
				printf("Choose one target from following list: \n");
				int targets[8]={0}, targetNum;
				targetNum=getDistance(p, 0, targets);
				if(targetNum==0)
					printf("No one in your Bang distance.\n");
				else{
					for(int i=0;i<targetNum;i++)
						printf("player %d\n",targets[i]);
					scanf("%d",&target);
				}
				CatBalou(p, n, target, deck);
				Discard(deck, p[0].cards, index, 15);
			}
			else if (playerCardNum >= 62 && playerCardNum <= 65 &&(cardIdx=checkCard(player,62,65)) != 100){//PANIC
				printf("Player %d plays a PANIC card!\n",n);
				printf("Choose one target from following list: \n");
				int targets[8]={0}, targetNum;
				targetNum=getDistance(p, 0, targets);
				if(targetNum==0)
					printf("No one in your Bang distance.\nCan't play Bang.\n");
				else{
					for(int i=0;i<targetNum;i++)
						printf("player %d\n",targets[i]);
					scanf("%d",&target);
					Panic(p, n, target, deck, pointDeck);
					Discard(deck, p[0].cards, index, 15);
				}
			}
			else if (playerCardNum >= 67 && playerCardNum <= 68 &&(cardIdx=checkCard(player,67,68)) != 100){//STAGE COACH
				printf("Player %d plays a Diligenza card!\n",n);
				Diligenza(p, n, deck, pointDeck);
				Discard(deck, p[0].cards, index, 15);
			}
			else if (playerCardNum == 69 && (cardIdx=checkCard(player,69,69)) != 100){//WELLS FARGO
				printf("Player %d plays a Wells Fargo card!\n",n);
				WellsFargo(p, n, deck, pointDeck);
				Discard(deck, p[0].cards, index, 15);
			}
			else if(playerCardNum >= 6 && playerCardNum <= 8 &&(cardIdx=checkCard(player,6,8)) != 100){
				printf("Player %d change weapon to Schofield\n",n);
				p[0].weapon = 6;
				Discard(deck, p[0].cards, index, 15);
			}
			else if(playerCardNum == 9 &&(cardIdx=checkCard(player,9,9)) != 100){
				printf("Player %d change weapon to Remington\n",n);
				p[0].weapon = 9;
				Discard(deck, p[0].cards, index, 15);
			}
			else if(playerCardNum == 10 &&(cardIdx=checkCard(player,10,10)) != 100){
				printf("Player %d change weapon to Rev. Carabine\n",n);
				p[0].weapon = 10;
				Discard(deck, p[0].cards, index, 15);
			}
			else if(playerCardNum == 11  &&(cardIdx=checkCard(player,11,11)) != 100){
				printf("Player %d change weapon to Winchester\n",n);
				p[0].weapon = 11;
				Discard(deck, p[0].cards, index, 15);
			}
			else if(playerCardNum >= 12 && playerCardNum <= 13 &&(cardIdx=checkCard(player,12,13)) != 100){
				printf("Player %d change weapon to Volcanic\n",n);
				p[0].weapon = 12;
				Discard(deck, p[0].cards, index, 15);
			}
			if(playerCardNum>=3 && playerCardNum<=4 && (cardIdx=checkCard(player,3,4)) != 100){
				printf("Player %d has Mustang\n",n);
				p[n].HasMustang = 1;
				p[n].cards[index]=0;
			}
			if(playerCardNum==5 && (cardIdx=checkCard(player,5,5)) != 100){
				printf("Player %d has Scope\n",n);
				p[n].distance = (p[n].character==10 ? 3:2);
				p[n].cards[index]=0;
			}
		}
        
    }
    for (int i =0; i < 15; i++){
        if (player->cards[i] != 0 )count++;
    }
	int c=count;
    while (count > player->health){
		int idx;
        showAllCard(player->cards);
        printf("\nCard number to discard: ");
        scanf("%d",&playerDiscardNum);
		idx=checkCard(player, playerDiscardNum, playerDiscardNum);
		Discard(deck, p[0].cards, idx, 15);
		count--;
    }
	if(p[n].character==11 && (c-p[n].health)>=2){
		if(p[0].health<4){
			printf("\033[36mplayer %d (Sid Ketchum) discard 2 cards to gain one live.\033[0m\n",n);
			p[n].health++;
		}
	}
}
