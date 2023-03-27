/*==============================================================================


	Tempo ID

		              GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

	Authors:
		- Martín Santiago (@martiagop)

	Contributors:
		-

	Special Thanks:
		-

==============================================================================*/

#include <YSI_Coding\y_hooks>


// Define the event to be called when the user's data load is completed
forward TID_OnUserDataLoaded(playerid);

enum E_USER_STATE 
{
    INVALID_USER_STATE = -1,
    E_USER_STATE_CONNECTING = 0,
    E_USER_STATE_LOGGING_IN,
    E_USER_STATE_LOGGED_IN,
    E_USER_STATE_BANNED
}

// Declare static variables and arrays that store user information
static
E_USER_STATE:   TID_g_sUserStatus           [MAX_PLAYERS],
                TID_g_sUserUUID             [MAX_PLAYERS][UUID_LEN],
                TID_g_sUserName             [MAX_PLAYERS][MAX_PLAYER_NAME],
                TID_g_sUserDevice           [MAX_PLAYERS],
Cache:          TID_g_sUserCache            [MAX_PLAYERS],
bool:           TID_g_sIsRegistered         [MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    new
        query[128],
        userNameMask[MAX_PLAYER_NAME];
    
    // Get the player's name and store it in the array TID_g_sUserName
    GetPlayerName(playerid, TID_g_sUserName[playerid]);
    
     // Temporarily change the player's name to a specific format
    format(userNameMask, sizeof userNameMask, "Conectando_U0%d", playerid);
    SetPlayerName(playerid, userNameMask);
    // Record the name change in the log
    Logger_Dbg("tempo-id", "[TempoID] Mask applied to user", Logger_S("username", TID_g_sUserName[playerid]), Logger_P(playerid));

    // Execute a database query to load cached user information
    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "SELECT * FROM `tmp_accounts` WHERE `username` LIKE '%e' LIMIT 1",  TID_g_sUserName[playerid]);
    mysql_tquery(TID_GetMySQLHandle(), query, "TID_OnUserDataLoaded", "i", playerid);
    return 0;
}

hook OnPlayerDisconnect(playerid)
{
    // Delete user's cache if available
    if (cache_is_valid(TID_g_sUserCache[playerid])) cache_delete(TID_g_sUserCache[playerid]);
    return 0;
}


public TID_OnUserDataLoaded(playerid)
{
    // Set the user status to "not registered".
    TID_g_sIsRegistered[playerid] = false;

    if (cache_num_rows()) // If there is at least one record in database with username, then...
    { 
        TID_g_sIsRegistered[playerid] = true;
        
        cache_get_value_name(0, "uuid", TID_g_sUserUUID[playerid], UUID_LEN);
        TID_g_sUserCache[playerid] = cache_save();
        
        TID_AutoLoginUser(playerid);
    }

    TID_SetUserStatus(playerid, E_USER_STATE_LOGGING_IN);
    return 0;
}



/*==============================================================================

	Interface

==============================================================================*/

/// <summary>Returns the current status of the user</summary>
/// <param name="playerid">The ID of the player to get the status from</param>
/// <seealso name="TID_SetUserStatus"/>
stock E_USER_STATE:TID_GetUserStatus(playerid)
{
    return TID_g_sUserStatus[playerid];
}

/// <summary>* * *</summary>
/// <param name="playerid">The ID of the player to set the status to</param>
/// <seealso name="TID_GetUserStatus"/>
stock TID_SetUserStatus(playerid, E_USER_STATE:status) 
{
    TID_g_sUserStatus[playerid] = status;
}

/// <summary>Returns the user's UUID</summary>
/// <param name="playerid">The ID of the player to get the UUID from</param>
/// <seealso name="TID_SetUserUUID"/>
stock TID_GetUserUUID(playerid)
{
    return TID_g_sUserUUID[playerid];
}

/// <summary>* * *</summary>
/// <param name="playerid">The ID of the player</param>
/// <seealso name="TID_GetUserUUID"/>
stock TID_SetUserUUID(playerid, const uuid[UUID_LEN])
{
    TID_g_sUserUUID[playerid] = uuid;
}

/// <summary>Return the current user device at the time of connection</summary>
/// <param name="playerid">The ID of the player to get the device from</param>
stock TID_GetUserDevice(playerid)
{
    return TID_g_sUserDevice[playerid];
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

stock TID_GetUserName(playerid)
{
    return TID_g_sUserName[playerid];
}

// EOF
