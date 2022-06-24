
/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <YSI_Coding\y_hooks>


forward TID_OnUserDataLoaded(playerid);

static
                TID_g_sUserUUID             [MAX_PLAYERS][UUID_LEN],
Cache:          TID_g_sUserCache            [MAX_PLAYERS],
bool:           TID_g_sIsRegistered         [MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    new
        query[128],  
        username[MAX_PLAYER_NAME];
    
    GetPlayerName(playerid, username);

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "SELECT * FROM `tmp_accounts` WHERE `username` LIKE '%e' LIMIT 1",  username);
    mysql_tquery(TID_GetMySQLHandle(), query, "TID_OnUserDataLoaded", "i", playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid)
{
    if (cache_is_valid(TID_g_sUserCache[playerid])) cache_delete(TID_g_sUserCache[playerid]);
    return 1;
}

public TID_OnUserDataLoaded(playerid)
{
    TID_g_sIsRegistered[playerid] = false;
    if (cache_num_rows()) { 
        TID_g_sIsRegistered[playerid] = true;
        
        cache_get_value_name(0, "uuid", TID_g_sUserUUID[playerid], UUID_LEN);
        TID_g_sUserCache[playerid] = cache_save();
    }

    TID_SetUserStatus(playerid, E_USER_STATE_LOGGING_IN);
    return 0;
}

/*==============================================================================

	Interface

==============================================================================*/

/// <summary>Returns the user's UUID</summary>
/// <param name="playerid">The ID of the player to get the UUID from</param>
stock TID_GetUserUUID(playerid, &uuid[])
{
    return TID_g_sUserUUID[playerid];
}

/// <summary>Return the current cache id of the user at the time of connection</summary>
/// <param name="playerid">The ID of the player to get the cache from</param>
stock Cache:TID_GetUserCache(playerid)
{
    if (cache_is_valid(TID_g_sUserCache[playerid])) return TID_g_sUserCache[playerid];
    else return MYSQL_INVALID_CACHE;
}

/// <summary>Returns true if the user is registered, false otherwise</summary>
/// <param name="playerid">The ID of the player</param>
stock bool:TID_IsUserRegistered(playerid) 
{
    return TID_g_sIsRegistered[playerid];
}