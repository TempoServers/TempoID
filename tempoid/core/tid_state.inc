/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <YSI_Coding\y_hooks>


forward TID_OnUserStateChange(playerid, E_USER_STATE:newstate, E_USER_STATE:oldstate);

enum E_USER_STATE 
{
    INVALID_USER_STATE = -1,
    E_USER_STATE_NONE = 0,
    E_USER_STATE_CONNECTING,
    E_USER_STATE_LOGGING_IN,
    E_USER_STATE_LOGGED_IN,
    E_USER_STATE_DISC,
    E_USER_STATE_BANNED
}

static
E_USER_STATE:   TID_g_sUserState           [MAX_PLAYERS];


hook OnIncomingConnection(playerid, ip_address[], port)
{
    #pragma unused ip_address, port
    TID_SetUserStatus(playerid, E_USER_STATE_CONNECTING);
    return 1;    
}

hook OnPlayerConnect(playerid)
{
    SetPlayerColor(playerid, Y_WHITESMOKE);
    SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    
    Cutscene_StartBackground(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid)
{
    switch (TID_g_sUserState[playerid])
    {
        case  E_USER_STATE_LOGGING_IN:
            TID_g_sUserState[playerid] = E_USER_STATE_DISC;
        default:
            TID_g_sUserState[playerid] = E_USER_STATE_NONE;
    }
}

public TID_OnUserStateChange(playerid, E_USER_STATE:newstate, E_USER_STATE:oldstate)
{
    return 0;
}

// Conocer en qué momento el jugador está

// Conocer en qué submomento

/*==============================================================================

	Interface

==============================================================================*/

/// <summary>Returns the current status of the user</summary>
/// <param name="playerid">The ID of the player to get the status from</param>
/// <seealso name="TID_SetUserStatus"/>
stock E_USER_STATE:TID_GetUserStatus(playerid)
{
    return TID_g_sUserState[playerid];
}

/// <summary>* * *</summary>
/// <param name="playerid">The ID of the player to get the status from</param>
/// <seealso name="TID_GetUserStatus"/>
stock TID_SetUserStatus(playerid, E_USER_STATE:newstate) 
{
    new 
        E_USER_STATE:oldstate = TID_g_sUserState[playerid];
    
    TID_g_sUserState[playerid] = newstate;
    
    return TID_OnUserStateChange(playerid, newstate, oldstate);
}