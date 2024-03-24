#include <stdio.h>
#include "variable.h"

int pileidx=0;
void DrawCard(int deck[], int* pointDeck ,int playerCards[], int num) {
	int cardPoint=0;
	int draw_times = num; 
	while(draw_times>0){ 
		if( playerCards[cardPoint] == 0){
			while(deck[*pointDeck]==0){
				(*pointDeck)++;
				if(*pointDeck>68)
					*pointDeck=0;
			}
			playerCards[cardPoint] = deck[*pointDeck];
			//printf("draw %d: %d\n",*pointDeck, playerCards[cardPoint]);
			deck[*pointDeck]=0;
			(*pointDeck)++;
			draw_times--;
		}
		cardPoint++;
		if(cardPoint>=15)
			break;
		if(*pointDeck>68)
			*pointDeck=0;
	}
}

void Discard(int deck[], int source[], int sourceCardIndex, int bound){

	if(sourceCardIndex!=-1){ //discard a card
		deck[pileidx]=source[sourceCardIndex];
		//printf("discard %d: %d\n",pileidx, source[sourceCardIndex]);
		//printf("%d\n",deck[pileidx]);
		/*for(int i=sourceCardIndex;i<bound-1;i++){
			source[i]=source[i+1];
		}*/
		source[sourceCardIndex]=0;
		// the card go back to discardPile
		//source[bound-1]=0;
		pileidx++; //point to the position where the next card should go
		if(pileidx>68)
			pileidx=0;
	}
}