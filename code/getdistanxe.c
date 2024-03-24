#include <stdio.h>
#include "variable.h"

extern int NumberOfPlayer;
extern int alivePlayer;
int getDistance(player players[], int nowTurn, int targets[]){
	int arr[7]={0};
	int idx=nowTurn;
	int t=1;
	int count=0;
	int distance=players[nowTurn].distance;

	if(players[nowTurn].weapon==6)
		distance=2;
	else if(players[nowTurn].weapon==9)
		distance=3;
	else if(players[nowTurn].weapon==10)
		distance=4;
	else if(players[nowTurn].weapon==11)
		distance=5;
	
	idx++;
	if(idx>=NumberOfPlayer)
		idx=0;
	while(idx!=nowTurn){
		if(players[idx].alive==1)
			arr[idx]=t++;
		idx++;
		if(idx>=NumberOfPlayer)
			idx=0;
	}
	
	idx=nowTurn-1;
	t=1;
	if(idx<0)
		idx=NumberOfPlayer-1;
	while(idx!=nowTurn){
		if(players[idx].alive==1){
			arr[idx]= t<arr[idx]? t:arr[idx];
			t++;
		}
		idx--;
		if(idx<0)
			idx=NumberOfPlayer-1;
	}
	
	for(int i=0;i<NumberOfPlayer;i++){
		if(arr[i]<=distance && arr[i]!=0 && players[i].HasMustang==0){
			if(nowTurn!=0){
				if(NumberOfPlayer==5 && players[nowTurn].role==4 && players[i].role==0)
					continue;
				else if(NumberOfPlayer>5 && players[nowTurn].role==5 && (players[i].role==0 || players[i].role==6))
					continue;
				else if((players[nowTurn].role==0 && players[i].role==6) || (players[nowTurn].role==6 && players[i].role==0))
					continue;
				targets[count++]=i;
			}
			else
				targets[count++]=i;
		}
		else if( players[i].HasMustang==1 && arr[i]!=0 && (distance-arr[i])>0){
			if(nowTurn!=0){
				if(NumberOfPlayer==5 && players[nowTurn].role==4 && players[i].role==0)
					continue;
				else if(NumberOfPlayer>5 && players[nowTurn].role==5 && players[i].role==0)
					continue;
				else if((players[nowTurn].role==0 && players[i].role==6) || (players[nowTurn].role==6 && players[i].role==0))
					continue;
				targets[count++]=i;
			}
			else
				targets[count++]=i;
		}
	}
	/*for(int i=0;i<4;i++)
		printf("%d ",targets[i]);*/
	return count;
}
