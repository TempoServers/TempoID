/*==============================================================================


	Tempo Roleplay

		Copyright (C) 2022 Martin Santiago, Victor Rivera and contributors

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <YSI_Coding\y_hooks>


static 
PlayerText: UI_sPlayerBrightness[MAX_PLAYERS] = { PlayerText:INVALID_PLAYER_TEXT_DRAW, ... };

static
Text:       UI_sBlackScreen = Text:INVALID_TEXT_DRAW;

hook OnGameModeInit() 
{
    Logger_ToggleDebug("ui-brightness", false);

    UI_sBlackScreen = TextDrawCreate(340.000000, -15.000000, "_");
    TextDrawFont(UI_sBlackScreen, 1);
    TextDrawLetterSize(UI_sBlackScreen, 0.500000, 55.000000);
    TextDrawTextSize(UI_sBlackScreen, 0.000000, 720.000000);
    TextDrawSetOutline(UI_sBlackScreen, 1);
    TextDrawSetShadow(UI_sBlackScreen, 0);
    TextDrawAlignment(UI_sBlackScreen, 2);
    TextDrawColor(UI_sBlackScreen, -1);
    TextDrawBackgroundColor(UI_sBlackScreen, 255);
    TextDrawBoxColor(UI_sBlackScreen, 255);
    TextDrawUseBox(UI_sBlackScreen, true);
    TextDrawSetProportional(UI_sBlackScreen, true);
    TextDrawSetSelectable(UI_sBlackScreen, true);

    Logger_Dbg("ui-brightness", "[UI/Brightness] Black Screen TD created", Logger_I("id", _:UI_sBlackScreen));

    return 0;
}

hook OnPlayerConnect(playerid) 
{
    UI_sPlayerBrightness[playerid] = CreatePlayerTextDraw(playerid, 340.000000, -15.000000, "_");
    PlayerTextDrawFont(playerid, UI_sPlayerBrightness[playerid], 1);
    PlayerTextDrawLetterSize(playerid, UI_sPlayerBrightness[playerid], 0.500000, 55.000000);
    PlayerTextDrawTextSize(playerid, UI_sPlayerBrightness[playerid], 0.000000, 720.000000);
    PlayerTextDrawSetOutline(playerid, UI_sPlayerBrightness[playerid], 1);
    PlayerTextDrawSetShadow(playerid, UI_sPlayerBrightness[playerid], 0);
    PlayerTextDrawAlignment(playerid, UI_sPlayerBrightness[playerid], 2);
    PlayerTextDrawColor(playerid, UI_sPlayerBrightness[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, UI_sPlayerBrightness[playerid], 255);
    PlayerTextDrawBoxColor(playerid, UI_sPlayerBrightness[playerid], 75);
    PlayerTextDrawUseBox(playerid, UI_sPlayerBrightness[playerid], true);
    PlayerTextDrawSetProportional(playerid, UI_sPlayerBrightness[playerid], true);
    PlayerTextDrawSetSelectable(playerid, UI_sPlayerBrightness[playerid], false);

    Logger_Dbg("ui-brightness", "[UI/Brightness] Brightness textdraw created", Logger_P(playerid), Logger_I("id", _:UI_sPlayerBrightness[playerid]));

    UI_ShowPlayerBlackScreen(playerid);

    return 0;
}

/*==============================================================================

	Interface

==============================================================================*/

/// <param name="playerid">The id of the player whose brightness will be modified.</param>
/// <param name="brightness">A value between 0 - 100.</param>
/// <remarks>Function still not tested in game with many users. Unexpected behaviour is possible.</remarks>
stock UI_SetPlayerBrightness(playerid, brightness)
{
    new
        alpha;

    if (brightness > 100 || brightness < 0)
    {
        brightness = 100;
    }

    alpha = floatround(2.55 * brightness);
    Logger_Dbg("ui-brightness", "[UI/Brightness] Brightness set to player", Logger_P(playerid), Logger_I("alpha", alpha));

    PlayerTextDrawBoxColor(playerid, UI_sPlayerBrightness[playerid], alpha);
    PlayerTextDrawShow(playerid, UI_sPlayerBrightness[playerid]);
}

/// <param name="playerid">The id of the player to whom the black screen will be displayed.</param>
stock UI_ShowPlayerBlackScreen(playerid) 
{
    TextDrawShowForPlayer(playerid, UI_sBlackScreen);
}

/// <param name="playerid">The id of the player to whom the black screen will be hidden.</param>
stock UI_HidePlayerBlackScreen(playerid) 
{
    TextDrawHideForPlayer(playerid, UI_sBlackScreen);
}

// EOF
