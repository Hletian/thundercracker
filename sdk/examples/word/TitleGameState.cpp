#include "TitleGameState.h"
#include "ScoredGameState.h"
#include "EventID.h"
#include "EventData.h"
#include "Dictionary.h"
#include "GameStateMachine.h"
#include <string.h>
#include "WordGame.h"
#include "assets.gen.h"

unsigned TitleGameState::update(float dt, float stateTime)
{
    return GameStateIndex_Title;
}

unsigned TitleGameState::onEvent(unsigned eventID, const EventData& data)
{
    switch (eventID)
    {
    case EventID_EnterState:
        WordGame::playAudio(flap_laugh_fireball, AudioChannelIndex_Time);
        WordGame::playAudio(wordplay_music_sohcahtoa, AudioChannelIndex_Music, LoopRepeat);
        break;

    case EventID_Input:
        WordGame::playAudio(shake, AudioChannelIndex_Shake);
        return GameStateIndex_StartOfRoundScored;

    default:
        break;
    }
    return GameStateIndex_Title;
}
