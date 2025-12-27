#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[50];
    int age;
    char nationality[50];
    char position[20];

    int birthDay;
    int birthMonth;
    int birthYear;

    char lastClub[50];
    char currentClub[50];
    int careerGoals;
} Player;

void addPlayer();
void listPlayers();
int findPlayerIndex(char name[]);
Player getPlayer(int index);
int getPlayerCount();

#endif
