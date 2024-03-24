#include <stdio.h>
#include "variable.h"


extern int NumberOfPlayer;
extern int alivePlayer;

void showAllCard(int hand[15]){
	char str[50]={0};
	printf("\n-----hand cards list-----\n");
    for (int i=0; i< 15; i++){
		if(hand[i]!=0){
			cardName(hand[i],str);
			printf(" - %2d %s",hand[i],str);
		}
    }
}

void showSheriff(int sheriffNum){
    printf("Player %d is the sheriff!\n",sheriffNum);
}

void showPlayerStruct(player* player, int n){
    if(player->hide == 0 ) {
        printf("Show Player\n");
        printf("Player %d\n",n);
        printf("Is player alive = %d\n",player->alive);
        printf("Player role = ");
		
		if(NumberOfPlayer==4 || NumberOfPlayer==5){
			if(player->role == 0) printf("Sheriff\n");
			else if(player->role == 1) printf("Renegade\n");
			else if(player->role==2 || player->role==3) printf("Outlaw\n");
			else if(player->role == 4) printf("Deputy Sheriff\n");
		}
		else if(NumberOfPlayer==6 || NumberOfPlayer==7){
			if(player->role == 0) printf("Sheriff\n");
			else if(player->role == 1) printf("Renegade\n");
			else if(player->role==2 || player->role==3 || player->role==4) printf("Outlaw\n");
			else if(player->role == 5) printf("Deputy Sheriff\n");
			else if(player->role == 6) printf("Sheriff\n");
		}
		
		char str[50]={0};
		showCharacter(player->character,str);
        printf("Player character = %s\n",str);

        printf("Player health = %d\n\n",player->health);
    }
}

void showrole(player p[], int idx){
	if(p[idx].role==0 || p[idx].role==6)
		printf("player %d is Sheriff.\n",idx);
	else if(p[idx].role==1)
		printf("player %d is Renegade.\n",idx);
	else if(p[idx].role==2 || p[idx].role==3)
		printf("player %d is Outlaw.\n",idx);
	else if(NumberOfPlayer==5 && p[idx].role==4)
		printf("player %d is Deputy Sheriff.\n",idx);
	else if(NumberOfPlayer>=6 && p[idx].role==4)
		printf("player %d is Outlaw.\n",idx);
	else if(NumberOfPlayer>=6 && p[idx].role==5)
		printf("player %d is Deputy Sheriff.\n",idx);
}

void cardName(int id, char str[]){
	if(id==0)
		sprintf(str,"\n");
	else if(id>=1 && id<3)
		sprintf(str,"(Barrel)\n");
	else if(id>=3 && id<5)
		sprintf(str,"(Mustang)\n");
	else if(id==5)
		sprintf(str,"(Scope)\n");
	else if(id>=6 && id<9)
		sprintf(str,"(Schofield)\n");
	else if(id==9)
		sprintf(str,"(Remington)\n");
	else if(id==10)
		sprintf(str,"(Rev Carabine)\n");
	else if(id==11)
		sprintf(str,"(Winchester)\n");
	else if(id>=12 && id<14)
		sprintf(str,"(Volcanic)\n");
	else if(id>=14 && id<39)
		sprintf(str,"(Bang)\n");
	else if(id>=39 && id<45)
		sprintf(str,"(Beer)\n");
	else if(id>=45 && id<49)
		sprintf(str,"(Cat Balou)\n");
	else if(id==49)
		sprintf(str,"(Gatling)\n");
	else if(id>=50 && id<62)
		sprintf(str,"(Missed)\n");
	else if(id>=62 && id<66)
		sprintf(str,"(Panic)\n");
	else if(id==66)
		sprintf(str,"(Saloon)\n");
	else if(id>=67 && id<69)
		sprintf(str,"(Diligenza)\n");
	else if(id=69)
		sprintf(str,"(Wells Fargo)\n");
	
}

void showCharacter(int num, char str[]){
	switch(num){

        case 0:
            sprintf(str,"Bart Cassidy");
            break;
        case 1:
            sprintf(str,"Black Jack");
            break;
        case 2:
            sprintf(str,"Calamity Janetk");
            break;
        case 3:
            sprintf(str,"El Gringo");
            break;
        case 4:
            sprintf(str,"Jesse Jones");
            break;
        case 5:
            sprintf(str,"Jourdonnais");
            break;
        case 6:
            sprintf(str,"Kit Carlson");
            break;
        case 7:
            sprintf(str,"Lucky Duke");
            break;
        case 8:
            sprintf(str,"Paul Regret");
            break;
        case 9:
            sprintf(str,"Pedro Ramirez");
            break;
        case 10:
            sprintf(str,"Rose Doolan");
            break;
        case 11:
            sprintf(str,"Sid Ketchum");
            break;
        case 12:
            sprintf(str,"Slab the Killer");
            break;
        case 13:
            sprintf(str,"Suzy Lafayette");
            break;
        case 14:
            sprintf(str,"Vulture Sam");
            break;
        case 15:
            sprintf(str,"Willy the Kid");
            break;
        }
}

void showINFO(player p[]){
	char str[50]={0};
    for (int i=0; i < NumberOfPlayer; i++){
    	printf("\nPlayer %d health = %d\n",i,p[i].health);
      showCharacter(p[i].character,str);
		printf("Player %d character = %s",i,str);
		cardName(p[i].weapon,str);
		printf("\nPlayer %d weapon = %d %s",i, p[i].weapon,str);
		if(p[i].role == 0 || p[i].role==6){
			printf("\nPlayer %d is Sheriff\n",i);
		}
   	 }
}

void help(){
	printf("\nHow to play this game: \n\n");
	printf(" 1. It is my turn, what should I do:\n\n");
	printf("   If it is your turn, you will see four option: (1)Show all data (2)Play Card (3)Discard card + end (4)Help\n");
	printf("   Enter 1 to see the information.\n   Enter 2 to play cards.\n   Enter 3 to finish your round.\n   Enter 4 to see help\n\n");
	printf(" 2. How to play cards: \n\n");
	printf("   If you choose the play card option, you will see the list of your hand cards.\n");
	printf("   eg: - 39(Beer)\n       -  2(barrel)\n       - 63(Panic)\n           .\n           .\n           . \n");
	printf("    Enter the card number to play the card (eg: - 39 (Beer), enter 39 to play the (Beer) card).\n\n");
	printf("   If your can't play that card at that moment, you will see the warning massage on the screen.\n    eg: Can't play Bang.\n\n");
	printf(" 3.If I want to play Bang, who can I Bang:\n\n");
	printf("   The system will list all the players you can attck based on the distance between you and others and your equipments.\n   To choose the target, you need to enter the target player number.\n");
	printf("   eg: Choose one target from following list:\n       player 2\n       player 4\n");
	printf("     Enter 4 if you want to attck player 4.\n\n");
	printf(" 4. How to finish your round:\n\n");
	printf("   Enter 3 to finish your round. If the number your hand cards is more than the number of your lives(bullets), the system will list your hand cards and let you discard. Otherwise, your turn is finished.\n\n");
	printf(" 5. How to discard:\n\n");
	printf("   The way to discard is similar to play card. \n   Enter the card number to choose the card you want to discard, and the system will remove that card from your hand cards. \n   The system will not leave the discard mode until the number of your hand cards is less than the number of your lives(bullets).\n\n");
	printf(" Hope you enjoy the game!!\n\n");

}
