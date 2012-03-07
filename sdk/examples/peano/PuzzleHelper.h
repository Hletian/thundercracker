#pragma once

#include "TokenGroup.h"
#include "Puzzle.h"
#include "Game.h"

namespace TotalsGame {

class Token;

class PuzzleHelper {
public:
    //-------------------------------------------------------------------------
    // ADVANCEMENT
    //-------------------------------------------------------------------------


    static TokenGroup *ConnectRandomly(IExpression *grp1, IExpression *grp2, bool secondTime = false);

    static Puzzle *SelectRandomTokens(Difficulty difficulty, int nTokens);

    static void ComputeDifficulties(Puzzle *p);
    static void ComputeDifficulties(Token *t);

};

}
