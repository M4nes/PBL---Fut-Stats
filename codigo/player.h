#ifndef PLAYER_H
#define PLAYER_H


#define MAX_NAME 50


typedef struct {
char name[MAX_NAME];
int age;
char position[20];
} Player;


void createPlayer(Player *p);
void printPlayer(Player p);


#endif