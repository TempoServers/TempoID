#if defined _INC_tid_menu
    #endinput
#endif
#define _INC_tid_menu

/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <a_samp>

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

#include <tempo-utils>

timer ClearingChat[1000](playerid) { 
    Utils_ClearChat(playerid); 
}

timer AutoDisconnect[120000](playerid) {
    Kick(playerid);
}

////////////////////////////////////////
timer tShowPlayerTempoID[4000](playerid) {
    UI_ShowPlayerTempoID(playerid);
    defer AutoDisconnect(playerid);  
}

hook OnPlayerConnect(playerid) 
{
    defer ClearingChat(playerid);
    defer tShowPlayerTempoID(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid)
{
    if (TID_GetUserStatus(playerid) == E_USER_STATE_LOGGING_IN) stop Timer:ClearingChat(playerid);
    return 1;
}