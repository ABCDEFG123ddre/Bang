#include <stdio.h>
#include <stdlib.h>
#include "variable.h"


extern int NumberOfPlayer;
extern int alivePlayer;
int heart[13]={3, 4, 14, 15, 39, 40, 45, 49, 62, 63, 64, 66, 69};

void setPlayer(player* player, int n, int arr[],int arrChar[]){
    printf("Set player %d\n",n);
    player->alive = true;
    player->role = arr[n];
	player->weapon = 0;
    player->character = arrChar[n];
	player->HasMustang = 0;
	if(player->character==8)
		player->HasMustang = 1;
	
    ///Show every player's info
    if(n == 0) player->hide = 0;//no hide
    else player->hide = 1;


    switch(player->character){
        case 3:
        case 8:
            player->health = 3;
            break;
        default:
            player->health = 4;
            break;
    }
	if(player->role==0 || player->role==6)
		player->health++;
	
	if(player->character==10)
		player->distance=2;
	else
		player->distance=1;
	
	for(int i=0;i<15;i++)
		player->cards[i]=0;
	
}

void shuffle(int *arr, int n){
    srand(time(0));
    for (int i=0; i < rand()+20; i++){
        int a = rand()%n;
        int b = rand()%n;
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

}

int checkCard(player *player,int start, int end){

	for (int i=0; i < 15; i++){
		if (player->cards[i]>= start && player->cards[i] <= end){
			return i;
		}
	}

	return 100;

}

int checkWin (player p[], int sheriffNum, int sheriffNum7){

	int renegadeNum=0;
	int DeputySheriff=-1;
	int outlawNum[3]={0};

	for(int i=0; i < NumberOfPlayer; i++){
		if(p[i].role == 1)renegadeNum = i;
		else if(p[i].role == 2)outlawNum[0]=i;
		else if(p[i].role == 3)outlawNum[1]=i;
		else if(p[i].role == 4 && NumberOfPlayer>=6) outlawNum[2]=i;
		else if(p[i].role == 4 && NumberOfPlayer==5) DeputySheriff=i;
		else if(p[i].role == 5 && NumberOfPlayer>=6) DeputySheriff=i;
	}


	if(NumberOfPlayer<7 && p[sheriffNum].alive == 0){
		printf("\nThe game is done\n");
		if(NumberOfPlayer==4 && p[renegadeNum].alive == 1 && p[outlawNum[0]].alive == 0 && p[outlawNum[1]].alive == 0){
			printf("\033[1m\nRenegade win!\n\033[0m");
		}
		else if(NumberOfPlayer==5 && p[renegadeNum].alive == 1 && p[outlawNum[0]].alive == 0 && p[outlawNum[1]].alive == 0 && p[DeputySheriff].alive==0){
			printf("\033[1m\nRenegade win!\n\033[0m");
		}
		else if(NumberOfPlayer==6 && p[renegadeNum].alive == 1 && p[outlawNum[0]].alive == 0 && p[outlawNum[1]].alive == 0 && p[outlawNum[2]].alive==0 && p[DeputySheriff].alive==0 ){
			printf("\033[1m\nRenegade win!\n\033[0m");
		}
		else{
			printf("\033[1m\nOutlaws win!\n\033[0m");
		}
		return 100;
	}
	else if(NumberOfPlayer==7 && p[sheriffNum].alive == 0 && p[sheriffNum7].alive==0){
		printf("\nThe game is done\n");
		if(p[renegadeNum].alive == 1 && p[outlawNum[0]].alive == 0 && p[outlawNum[1]].alive == 0 && p[DeputySheriff].alive==0 && p[outlawNum[2]].alive==0){
			printf("\033[1m\nRenegade win!\n\033[0m");
		}
		else{
			printf("\033[1m\nOutlaws win!\n\033[0m");
		}
		return 100;
	}
	else if(NumberOfPlayer<6 && p[sheriffNum].alive == 1 && p[renegadeNum].alive == 0 && p[outlawNum[0]].alive == 0 && p[outlawNum[1]].alive == 0){
		printf("\nThe game is done\n");
		printf("\033[1m\nSheriff win!\n\033[0m");
		return 100;
	}
	else if(NumberOfPlayer==6 && p[sheriffNum].alive == 1 && p[renegadeNum].alive == 0 && p[outlawNum[0]].alive == 0 && p[outlawNum[1]].alive == 0 && p[outlawNum[2]].alive == 0){
		printf("\nThe game is done\n");
		printf("\033[1m\nSheriff win!\n\033[0m");
		return 100;
	}
	else if(NumberOfPlayer==7 && (p[sheriffNum].alive == 1 || p[sheriffNum7].alive==1 )&& p[renegadeNum].alive == 0 && p[outlawNum[0]].alive == 0 && p[outlawNum[1]].alive == 0 && p[outlawNum[2]].alive == 0){
		printf("\nThe game is done\n");
		printf("\033[1m\nSheriff win!\n\033[0m");
		return 100;
	}
	return 0;
}

bool HasBarrel(player p, int target, int* pointDeck, int deck[], int character){
	for(int i=0;i<15;i++){ //check is the target has barrel
		if(p.cards[i]==1 || p.cards[i]==2 || p.character==5){
			printf("player %d has Barrel!\n",target);
			for(int j=0;j<13;j++){
				if(deck[*pointDeck]==heart[j]){
					Discard(deck,deck,*pointDeck,69);
					if(character!=12)
						printf("player %d draws a heart card. Missed!\n",target);
					else
						printf("player %d draws a heart card.\n",target);
					return 1;
				}
				else if(p.character==7 && deck[(*pointDeck)+1]==heart[j]){
					Discard(deck,deck,*(pointDeck+1),69);
					if(character!=12)
						printf("player %d draws a heart card. Missed!\n",target);
					else
						printf("player %d draws a heart card.\n",target);
					return 1;
				}
			}
			printf("player %d doesn't draws a heart card.\n",target);
			break;
		}
	}
	return 0;
}

int HasMiss(player p, int target, int hasPlayed, int character){
	for(int i=0;i<15;i++){ // 15: player cards[15], checked if target has Missed
		if(i==hasPlayed)
			continue;
		if(p.cards[i]>=50 && p.cards[i]<62){
			if(character!=12)
				printf("player %d plays Missed!\n",target);
			return i;
		}
	}
	if(p.character==2){
		for(int i=0;i<15;i++){
			if(i==hasPlayed)
				continue;
			if(p.cards[i]>=14 && p.cards[i]<39){
				if(character!=12)
					printf("player %d (Calamity Janet) plays Bang as Missed!\n",target);
				return i;
			}
		}
	}
	return -1;
}
