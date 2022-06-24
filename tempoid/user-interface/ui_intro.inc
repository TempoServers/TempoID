#if defined _UI_tid_intro
    #endinput
#endif
#define _UI_tid_intro

/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <a_samp>
#include <textdraw-streamer>

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Extra\y_inline_timers>


static
Text:   blackScreen,
Text:   introFirstText,
Text:   introSecondText;


hook OnGameModeInit() {  
    blackScreen = TextDrawCreate(340.000000, -15.000000, "_");
    TextDrawFont(blackScreen, 1);
    TextDrawLetterSize(blackScreen, 0.500000, 55.000000);
    TextDrawTextSize(blackScreen, 0.000000, 720.000000);
    TextDrawSetOutline(blackScreen, 1);
    TextDrawSetShadow(blackScreen, 0);
    TextDrawAlignment(blackScreen, 2);
    TextDrawColor(blackScreen, -1);
    TextDrawBackgroundColor(blackScreen, 255);
    TextDrawBoxColor(blackScreen, 255);
    TextDrawUseBox(blackScreen, true);
    TextDrawSetProportional(blackScreen, true);
    TextDrawSetSelectable(blackScreen, false);

    introFirstText = TextDrawCreate(320.000000, 185.000000, "Tempo Services");
    TextDrawFont(introFirstText, 3);
    TextDrawLetterSize(introFirstText, 0.625000, 2.500000);
    TextDrawTextSize(introFirstText, 403.500000, 358.500000);
    TextDrawSetOutline(introFirstText, 1);
    TextDrawSetShadow(introFirstText, 1);
    TextDrawAlignment(introFirstText, 2);
    TextDrawColor(introFirstText, -1);
    TextDrawBackgroundColor(introFirstText, 255);
    TextDrawBoxColor(introFirstText, 50);
    TextDrawUseBox(introFirstText, false);
    TextDrawSetProportional(introFirstText, true);
    TextDrawSetSelectable(introFirstText, false);

    introSecondText = TextDrawCreate(320.000000, 219.000000, "Presenta");
    TextDrawFont(introSecondText, 2);
    TextDrawLetterSize(introSecondText, 0.349999, 1.399999);
    TextDrawTextSize(introSecondText, 400.000000, 17.000000);
    TextDrawSetOutline(introSecondText, 1);
    TextDrawSetShadow(introSecondText, 0);
    TextDrawAlignment(introSecondText, 2);
    TextDrawColor(introSecondText, -1);
    TextDrawBackgroundColor(introSecondText, 255);
    TextDrawBoxColor(introSecondText, 50);
    TextDrawUseBox(introSecondText, false);
    TextDrawSetProportional(introSecondText, true);
    TextDrawSetSelectable(introSecondText, false);
    return 1;
}

hook OnPlayerConnect(playerid) 
{
    UI_ShowPlayerIntroScreen(playerid);

    inline const tFinishIntro()
    {
        UI_HidePlayerIntroScreen(playerid);
    }

    Timer_CreateCallback(using inline tFinishIntro, 4000, 1);
    return 1;
}

/*==============================================================================

	Interface

==============================================================================*/

stock UI_ShowPlayerIntroScreen(playerid) 
{
    TextDrawShowForPlayer(playerid, blackScreen);
    TextDrawShowForPlayer(playerid, introFirstText);
    TextDrawShowForPlayer(playerid, introSecondText);
}

stock UI_HidePlayerIntroScreen(playerid) 
{
    TextDrawHideForPlayer(playerid, blackScreen);
    TextDrawHideForPlayer(playerid, introFirstText);
    TextDrawHideForPlayer(playerid, introSecondText);
}
