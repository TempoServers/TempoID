/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <a_samp>

stock Cutscene_StartBackground(playerid) 
{   
    PlayAudioStreamForPlayer(playerid, "https://alewaa.host/assets/audio/connectionSoundtrack.mp3");
    
    TogglePlayerSpectating(playerid, true);

    InterpolateCameraPos(playerid, 1472.706054, -2192.959472, 58.557556, 2441.482666, -2141.939941, 58.557556, 120000);
    InterpolateCameraLookAt(playerid, 1472.699462, -2187.968505, 58.856517, 2441.181396, -2136.957031, 58.840141, 120000);
}

stock Cutscene_StopBackground(playerid) 
{
    StopAudioStreamForPlayer(playerid);
    TogglePlayerSpectating(playerid, false);
}