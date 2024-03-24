#include <stdio.h>
#include <stdlib.h>
#include "variable.h"


extern int NumberOfPlayer;
extern int alivePlayer;


void doAfterDeath(player p[], int dead, int deck[], int killer, int* pointDeck){
	p[dead].alive=0;
	alivePlayer--;
	int hasVulture=0;
	showrole(p,dead);
	if(p[dead].role==2 || p[dead].role==3 || (NumberOfPlayer>=6 && p[dead].role==4)){
		DrawCard(deck, pointDeck, p[killer].cards, 3);
		printf("player %d kills Outlaw. Draw 3 cards as reward.\n",killer);
	}
	for(int i=0;i<NumberOfPlayer;i++){
		if(p[i].character==14 && p[i].alive==1){
			printf("player %d (Vulture Sam) takes all the cards player %d had\n",i, dead);
			hasVulture=1;
			int idx=0;
			while(p[i].cards[idx]!=0)
				idx++;
			for(int j=0;j<15;j++){
				if(p[dead].cards[j]!=0)
					p[i].cards[idx]=p[dead].cards[j];
				while(p[i].cards[idx]!=0)
					idx++;
			}
			break;
		}
	}
	if(((NumberOfPlayer==5 && p[dead].role==4) || (NumberOfPlayer>=6 && p[dead].role==5)) && (p[killer].role==0 || p[killer].role==6)){
		printf("Sheriff kills the Deputy. Discard all the cards he has in hand and in play!\n");
		int i=0;
		while(i<15){
			if(p[killer].cards[i]!=0)
				Discard(deck, p[killer].cards, i, 15);
			else
				i++;
		}
		p[killer].weapon=0;
		if(p[killer].character!=8)
			p[killer].HasMustang=0;
		p[killer].distance--;
	}
	if(hasVulture==0){
		for(int i=0;i<15;i++){
			if(p[dead].cards[i]!=0)
				Discard(deck, p[dead].cards, i, 15);
		}
	}
	p[dead].weapon=0;
}

void Bang(player p[], int current, int target, int deck[], int* pointDeck){
	int targetHasMiss=0;
	int MissNum=0, discard1, discard2;
	if(p[current].alive==0)
		return;
	
	if(HasBarrel(p[target],target, pointDeck, deck, p[current].character)){
		if(p[current].character!=12)
			targetHasMiss=1;
		else
			MissNum++;
	}
	//printf("%d\n",targetHasMiss);
	if(targetHasMiss==0){
		if((discard1=HasMiss(p[target], target, -1, p[current].character))!=-1){
			MissNum++;
			if(p[current].character!=12){
				targetHasMiss=1;
				Discard(deck, p[target].cards, discard1, 15);
			}
			else if(p[current].character==12 && MissNum==2){
				targetHasMiss=1;
				Discard(deck, p[target].cards, discard1, 15);
				printf("player %d plays two Missed to avoid player %d (Slab the Killer)'s Bang.\n",target, current);
			}
			else if(p[current].character==12 && MissNum==1){
				if((discard2=HasMiss(p[target], target, discard1, p[current].character))!=-1){
					targetHasMiss=1;
					Discard(deck, p[target].cards, discard1, 15);
					Discard(deck, p[target].cards, discard2, 15);
					printf("player %d plays two Missed to avoid player %d (Slab the Killer)'s Bang.\n",target, current);
				}
			}
		}
	}
	//printf("*%d\n",targetHasMiss);
	if(targetHasMiss==0){
		p[target].health--;
		system("aplay bang.wav >>/dev/null 2>>/dev/null");
		printf("\033[33mplayer %d lose one life!\033[0m\n",target);
		if(p[target].health==0){
			system("aplay warning.wav >>/dev/null 2>>/dev/null");
			printf("\033[31mplayer %d is death!\033[0m\n",target);
			doAfterDeath(p, target, deck, current, pointDeck);
		}
		else if(p[target].character==0){
			DrawCard(deck, pointDeck, p[target].cards, 1);
			printf("player %d (Bart Cassidy) draws a card.\n",target);
		}
		else if(p[target].character==3){
			int idx=9, t=0;
			while(p[current].cards[idx]==0)
				idx--;
			while(p[target].cards[t]!=0)
				t++;
			p[target].cards[t]=p[current].cards[idx];
			p[current].cards[idx]=0;
			printf("player %d (El Gringo) takes a card from player %d.\n", target, current);
		}
		//system("aplay play1.wav");
	}
}

int Beer(player p[], int deck[], int current){
	if(p[current].alive==0)
		return 0;
	else if(p[current].health>=4){
		printf("Can't play Beer.\n");
		return 0;
	}
	else if(p[current].health>=3 && (p[current].character==3 || p[current].character==8)){
		printf("Can't play Beer.\n");
		return 0;
	}
	else if(alivePlayer==2){ //+ variable: NumberOfPlayer
		printf("Can't play Beer.\n");
		return 0;
	}
	system("aplay beer.wav >>/dev/null 2>>/dev/null");
	printf("Player %d plays a BEER card!\n",current);
	printf("\033[36mplayer %d gain one live.\033[0m\n",current);
	p[current].health++;
	//system("aplay play1.wav");
	return 1;
}

void Sallon(player p[], int deck[], int current){

	if(p[current].alive==0)
		return;
	system("aplay beer.wav >>/dev/null 2>>/dev/null");
	for(int i=0;i<NumberOfPlayer;i++){
		if(p[i].character!=3 && p[i].character!=8){
			if(p[i].health<4 && p[i].alive==1){
				p[i].health++;
				printf("\033[36mplayer %d gain one live.\033[0m\n",i);
			}
		}
		else{
			if(p[i].health<3 && p[i].alive==1){
				p[i].health++;
				printf("\033[36mplayer %d gain one live.\033[0m\n",i);
			}
		}
	}
	//system("aplay play1.wav");
}

void WellsFargo(player p[], int current, int deck[], int* pointDeck){
	if(p[current].alive==0)
		return;
	DrawCard(deck, pointDeck, p[current].cards,3);//(draw 3 cards)

}

void Diligenza(player p[], int current, int deck[], int* pointDeck){
	if(p[current].alive==0)
		return;
	DrawCard(deck, pointDeck ,p[current].cards, 2);//call the draw card function(draw 2 cards)

}

void Panic(player p[], int current, int target, int deck[], int* pointDeck){
	if(p[current].alive==0)
		return;
	
	int idx=0,t=0;
	
	while(p[current].cards[idx]!=0 && idx<15)
		idx++;
	if(idx==15){
		printf("player %d doesn't have any card in hand.\n",target);
		return;
	}
	while(p[target].cards[t]==0 && t<15)
		t++;
	//printf("panic %d %d\n",idx,t);
	p[current].cards[idx]=p[target].cards[t];
	p[target].cards[t]=0;
	
	printf("player %d get a card from player %d.\n",current, target);
}

void CatBalou(player p[], int current, int target, int deck[]){
	if(p[current].alive==0)
		return;
	
	int i=0;
	while(p[target].cards[i]==0 && i<15)
		i++;
	if(i==15){
		printf("player %d doesn't have any card in hand.\n",target);
		return;
	}
	Discard(deck, p[target].cards, i, 15); // + a discard card funtion
	printf("player %d discard a card\n",target);

}

void Gatling(player p[], int current, int deck[], int* pointDeck){
	
	if(p[current].alive==0)
		return;
	
	for(int i=0;i<NumberOfPlayer;i++){
		int targetHasMiss=0, MissNum=0;
		int discard1, discard2;
		
		if(i==current) // current player
			continue;
		else if(p[i].alive==0)
			continue;
		
		if(HasBarrel(p[i],i, pointDeck, deck, p[current].character)==1){
			if(p[current].character!=12)
				targetHasMiss=1;
			else
				MissNum++;
		}
		
		if(targetHasMiss==0){
			if((discard1=HasMiss(p[i], i, -1, p[current].character))!=-1){
				MissNum++;
				if(p[current].character!=12){
					targetHasMiss=1;
					Discard(deck, p[i].cards, discard1, 15);
				}
				else if(p[current].character==12 && MissNum==2){
					targetHasMiss=1;
					Discard(deck, p[i].cards, discard1, 15);
					printf("player %d plays two Missed to avoid player %d (Slab the Killer)'s Bang.\n",i, current);
				}
				else if(p[current].character==12 && MissNum==1){
					if((discard2=HasMiss(p[i], i, discard1, p[current].character))!=-1){
						targetHasMiss=1;
						Discard(deck, p[i].cards, discard1, 15);
						Discard(deck, p[i].cards, discard2, 15);
						printf("player %d plays two Missed to avoid player %d (Slab the Killer)'s Bang.\n",i, current);
					}
				}
			}
		}
		if(targetHasMiss==0){
			p[i].health--;
			system("aplay bang.wav >>/dev/null 2>>/dev/null");
			printf("\033[33mplayer %d lose one life!\033[0m\n",i);
			if(p[i].health==0){
				system("aplay warning.wav >>/dev/null 2>>/dev/null");
				printf("\033[31mplayer %d is death!\033[0m\n",i);
				doAfterDeath(p, i, deck, current, pointDeck);
			}
			else if(p[i].character==0){
				DrawCard(deck, pointDeck, p[i].cards, 1);
				printf("player %d (Bart Cassidy) draws a card.\n",i);
			}
			else if(p[i].character==3){
				int idx=9, t=0;
				while(p[current].cards[idx]==0)
					idx--;
				while(p[i].cards[t]!=0)
					t++;
				p[i].cards[t]=p[current].cards[idx];
				p[current].cards[idx]=0;
				printf("player %d (El Gringo) takes a card from player %d.\n", i, current);
			}	
		}
	}
	//system("aplay play1.wav");
}
