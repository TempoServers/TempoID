/*==============================================================================


	Tempo Roleplay

		Copyright (C) 2022 Martin Santiago & Victor Rivera

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <a_samp>
#include <uuid>
#include <samp_bcrypt>

#include <YSI_Coding\y_hooks>


forward TID_OnUserLogin(playerid);
forward TID_OnUserAutoLogin(playerid);
forward TID_OnLoginPasswordHashed(playerid);

/* 
public TID_OnUserLogin(playerid)
{
    Logger_Log("[OnUserLogin] This callback was called", Logger_P(playerid));
    
    UI_HidePlayerTempoID(playerid);
    UI_ShowPlayerLoadingScreen(playerid, "Cargando cuenta");
    return 0;
} */

public TID_OnUserAutoLogin(playerid)
{
    Logger_Log("[OnUserAutoLogin] This callback was called", Logger_P(playerid));
    UI_ShowPlayerLoadingScreen(playerid, "Logueado automaticamente");
    return 0;
}

TID_AutoLoginUser(playerid)
{
    Logger_Log("trying to autologin user...", Logger_P(playerid));

    new
        query[248];
        
    inline const TID_OnCheckLastAccess()
    {
        Logger_Log("data retrieved from database");
        if (cache_num_rows()) {
            new 
                serviceid, 
                currentVersion  [24],   lastVersion [24], 
                currentIp       [16],   lastIp      [16],
                lastTimestamp;
                
            GetPlayerIp(playerid, currentIp);
            GetPlayerVersion(playerid, currentVersion);

            cache_get_value_name(0, "ip", lastIp);
            cache_get_value_name(0, "version", lastVersion);
            cache_get_value_name_int(0, "serviceid", serviceid);
            cache_get_value_name_int(0, "last_timestamp", lastTimestamp);
            
            if (!(strcmp(currentIp, lastIp)) && !(strcmp(currentVersion, lastVersion)) && serviceid == TEMPO_SERVICE_ID) { 
                if ((gettime() - lastTimestamp) < 86400) {
                    Logger_Log("user was connected previously in less than 24 hours");
                    TID_SetUserStatus(playerid, E_USER_STATE_LOGGED_IN);
                    return TID_OnUserAutoLogin(playerid); // Success
                }                    
            }
        }
        return 0;
    }

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "SELECT *, UNIX_TIMESTAMP(timestamp) AS 'last_timestamp' FROM `tmp_access_log` WHERE uuid = '%s' ORDER BY timestamp DESC LIMIT 1", TID_GetUserUUID(playerid));
    MySQL_TQueryInline(TID_GetMySQLHandle(), using inline TID_OnCheckLastAccess, query);
    return 0;
}

public TID_OnLoginPasswordHashed(playerid)
{
    new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	printf("hash : %s", dest);
}

/*==============================================================================

	Interface

==============================================================================*/

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
                        return TID_OnUserLogin(playerid);
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