/*==============================================================================


	Tempo Roleplay

		Copyright (C) 2022 Martin Santiago, Victor Rivera and contributors

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <YSI_Coding\y_hooks>


static
Text:       UI_sIntroFirstText = Text:INVALID_TEXT_DRAW,
Text:       UI_sIntroSecondText = Text:INVALID_TEXT_DRAW;


hook OnGameModeInit() 
{     
    Logger_ToggleDebug("ui-intro", false);

    UI_sIntroFirstText = TextDrawCreate(320.000000, 185.000000, "Tempo Open Source");
    TextDrawFont(UI_sIntroFirstText, 3);
    TextDrawLetterSize(UI_sIntroFirstText, 0.625000, 2.500000);
    TextDrawTextSize(UI_sIntroFirstText, 403.500000, 358.500000);
    TextDrawSetOutline(UI_sIntroFirstText, 1);
    TextDrawSetShadow(UI_sIntroFirstText, 0);
    TextDrawAlignment(UI_sIntroFirstText, 2);
    TextDrawColor(UI_sIntroFirstText, -1);
    TextDrawBackgroundColor(UI_sIntroFirstText, 255);
    TextDrawBoxColor(UI_sIntroFirstText, 50);
    TextDrawUseBox(UI_sIntroFirstText, false);
    TextDrawSetProportional(UI_sIntroFirstText, true);
    TextDrawSetSelectable(UI_sIntroFirstText, false);

    UI_sIntroSecondText = TextDrawCreate(320.000000, 219.000000, "Presenta");
    TextDrawFont(UI_sIntroSecondText, 2);
    TextDrawLetterSize(UI_sIntroSecondText, 0.349999, 1.399999);
    TextDrawTextSize(UI_sIntroSecondText, 400.000000, 17.000000);
    TextDrawSetOutline(UI_sIntroSecondText, 1);
    TextDrawSetShadow(UI_sIntroSecondText, 1);
    TextDrawAlignment(UI_sIntroSecondText, 2);
    TextDrawColor(UI_sIntroSecondText, -1);
    TextDrawBackgroundColor(UI_sIntroSecondText, 255);
    TextDrawBoxColor(UI_sIntroSecondText, 50);
    TextDrawUseBox(UI_sIntroSecondText, false);
    TextDrawSetProportional(UI_sIntroSecondText, true);
    TextDrawSetSelectable(UI_sIntroSecondText, false);

    Logger_Dbg("ui-intro", "[UI/Intro] First text created", Logger_I("id", _:UI_sIntroFirstText));
    Logger_Dbg("ui-intro", "[UI/Intro] Second text created", Logger_I("id", _:UI_sIntroSecondText));

    return 0;
}

hook OnPlayerConnect(playerid) 
{
    UI_ShowPlayerIntro(playerid);

    return 0;
}

/*==============================================================================

	Interface

==============================================================================*/

/// <param name="playerid">The id of the player to whom the intro will be displayed.</param>
stock UI_ShowPlayerIntro(playerid) 
{
    TextDrawShowForPlayer(playerid, UI_sIntroFirstText);
    TextDrawShowForPlayer(playerid, UI_sIntroSecondText);
}

/// <param name="playerid">The id of the player to whom the intro will be hidden.</param>
stock UI_HidePlayerIntro(playerid) 
{
    TextDrawHideForPlayer(playerid, UI_sIntroFirstText);
    TextDrawHideForPlayer(playerid, UI_sIntroSecondText);
}

// EOF
