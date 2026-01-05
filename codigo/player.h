#ifndef PLAYER_H
#define PLAYER_H

#define MAX_PLAYERS 200
#define MAX_NAME 50
#define MAX_NATIONALITY 50
#define MAX_POSITION 30
#define MAX_CLUB 50

typedef struct {
    char name[MAX_NAME];
    int shirtNumber;              //
    char position[MAX_POSITION];
    char nationality[MAX_NATIONALITY];
    int age;
    char lastClub[MAX_CLUB];      
    char currentClub[MAX_CLUB];
    int careerGoals;              
} Player;

// Funções
void menuJogadores(void);
void addPlayer(void);
void listPlayers(void);
int findPlayerIndex(const char *name);
Player* getPlayer(int index);
int getPlayerCount(void);
void editPlayer(void);

extern Player players[MAX_PLAYERS];
extern int playerCount;

#endif