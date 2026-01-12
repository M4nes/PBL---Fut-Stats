#ifndef PLAYER_H
#define PLAYER_H

#define MAX_PLAYERS 500
#define MAX_NAME 50
#define MAX_NATIONALITY 50
#define MAX_POSITION 30
#define MAX_CLUB 50

typedef struct {
    char name[MAX_NAME];
    int shirtNumber;
    int age;
    char nationality[MAX_NATIONALITY];
    char position[MAX_POSITION];
    char lastClub[MAX_CLUB];
    char currentClub[MAX_CLUB];
    int careerGoals;
} Player;

int findPlayerIndex(const char *name);
Player* getPlayer(int index);
int getPlayerCount(void);

extern Player players[MAX_PLAYERS];
extern int playerCount;

#endif