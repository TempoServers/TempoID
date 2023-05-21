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

#include <YSI_Extra\y_inline_mysql>
#include <YSI_Coding\y_hooks>


forward TID_OnUserLogin(playerid, autolog);
forward TID_OnUserAutoLogin(playerid);
forward TID_OnLoginPasswordHashed(playerid);

public TID_OnUserLogin(playerid, autolog)
{    
    if (autolog) return 1;
    TID_AddUserAccess(playerid);
    //UI_ShowPlayerLoadingScreen(playerid, "Cargando cuenta");
    return 0;
}

public TID_OnUserAutoLogin(playerid)
{    
    TID_tFinishIntro(playerid);
    //UI_ShowPlayerLoadingScreen(playerid, "Logueado automaticamente");

    Logger_Dbg("tempo-id", "[TempoID] User automatically logged in", Logger_P(playerid));

    SetTimerEx("TID_OnUserLogin", 2000, false, "ii", playerid, true);
    return 0;
}

/*==============================================================================

	Interface

==============================================================================*/

/// <summary>Trying to auto login user</summary>
/// <param name="playerid">The ID of the player to autologin to</param>
stock TID_AutoLoginUser(playerid)
{
    new
        query[248];
        
    inline const TID_OnCheckLastAccess()
    {
        if (cache_num_rows())
        {
            new 
                serviceid, 
                currentVersion  [24],
                lastVersion     [24], 
                currentIp       [16],   
                lastIp          [16],
                lastTimestamp;
                
            GetPlayerIp(playerid, currentIp);
            GetPlayerVersion(playerid, currentVersion);

            cache_get_value_name(0, "ip", lastIp);
            cache_get_value_name(0, "version", lastVersion);
            cache_get_value_name_int(0, "serviceid", serviceid);
            cache_get_value_name_int(0, "last_timestamp", lastTimestamp);
            
            if (!(strcmp(currentIp, lastIp)) && !(strcmp(currentVersion, lastVersion)) && serviceid == TEMPO_SERVICE_ID)
            { 
                if ((gettime() - lastTimestamp) < 43200) // 12 Hours (24 Hours with VIP)
                {
                    TID_SetUserStatus(playerid, E_USER_STATE_LOGGED_IN);
                    SetTimerEx("TID_OnUserAutoLogin", 4000, false, "i", playerid);
                }                    
            }
        }
        return 0;
    }

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "SELECT *, UNIX_TIMESTAMP(timestamp) AS 'last_timestamp' FROM `tmp_access_log` WHERE uuid = '%s' ORDER BY timestamp DESC LIMIT 1", TID_GetUserUUID(playerid));
    MySQL_TQueryInline(TID_GetMySQLHandle(), using inline TID_OnCheckLastAccess, query);
    return 0;
}

/// <summary>Displays the login prompt to request the user's password</summary>
/// <param name="playerid">The ID of the player to diaplay the prompt to</param>
stock TID_DisplayLoginPrompt(playerid)
{
    inline const Response(response, listitem, string:inputtext[]) {
        #pragma unused listitem

        if (response) {
            if (8 <= strlen(inputtext) <= 32) {
                new 
                    userHash[65];
                
                cache_set_active(TID_GetUserCache(playerid));

                cache_get_value_name(0, "password", userHash);

                cache_unset_active();

                inline const OnCompared(bool:match) {
                    if (match) {
                        TID_SetUserStatus(playerid, E_USER_STATE_LOGGED_IN);
                        SetTimerEx("TID_OnUserLogin", 500, false, "i", playerid);
                    }
                    else {
                        Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_PASSWORD, "Contraseña incorrecta", "Para verificar tu identidad, ingresa tu contraseña:", "Continuar", "Cancelar");
                    }
                }
                BCrypt_CheckInline(inputtext, userHash, using inline OnCompared);
            }
        }
    }

    if (TID_IsUserRegistered(playerid)) {
        Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_PASSWORD, "Ingresa tu contraseña", "Para verificar tu identidad, ingresa tu contraseña:", "Continuar", "Cancelar");
    }
    else {
        Dialog_ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Aún no estás registrado", "Ninguna cuenta de Tempo ID está registrada con este usuario. \n\nCrea un ID y vuelve a intentarlo.", "Entiendo", "");
    }
    return 0;
}

/// <summary>Add an access record in db from user</summary>
/// <param name="playerid">The ID of the player to add an access record to</param>
stock TID_AddUserAccess(playerid)
{
    new
        query[400],
        userVersion[20],
        userIp[16],
        year, month, day;
    
    GetPlayerVersion(playerid, userVersion);
    GetPlayerIp(playerid, userIp);
    getdate(year, month, day);

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "INSERT INTO `tmp_access_log` (`accessid`, `uuid`, `serviceid`, `ip`, `date`, `timestamp`, `device`, `version`) \
                                                              VALUES (NULL, '%s', '%d', '%s', '%d-%d-%d', current_timestamp(), '%d', '%s')", TID_GetUserUUID(playerid), TEMPO_SERVICE_ID, \
                                                              userIp, year, month, day, TID_GetUserDevice(playerid), userVersion);
    mysql_tquery(TID_GetMySQLHandle(), query);
}

// EOF
