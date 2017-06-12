//
// Created by mbataglia on 12/06/17.
//

#ifndef Z_INFOGAMESELECTION_H
#define Z_INFOGAMESELECTION_H


class InfoGameSelection {
public:
    int idCreator;
    int maxPlayers;
    int joinedPlayers;
    int typeGame;
    int numTeams;
public:
    InfoGameSelection(int idCreator,
                      int maxPlayers,
                      int joinedPlayers,
                      int typeGame,
                      int numTeams);
};


#endif //Z_INFOGAMESELECTION_H
