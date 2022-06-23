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


static 
            TID_g_UserPassword  [MAX_PLAYERS][BCRYPT_HASH_LENGTH],
            TID_g_UserEmail     [MAX_PLAYERS][128];

stock 
            contentDialog[2000];


forward TID_OnUserRegister(playerid);

stock TID_DisplayRegisterPrompt(playerid) 
{
    Logger_Log("player is registering...", Logger_P(playerid));

    inline const Response(response, listitem, string:inputtext[]) {
        #pragma unused listitem

        if (response) {
            if (!(ValidEmail(inputtext))) {
                TID_DisplayRegisterPrompt(playerid);
                return 0;
            }

            // TO-DO: Verify if the email is used
            /*if (TID_IsEmailUsed(inputtext)) {
                Logger_Log("email alredy used", Logger_S("email", inputtext));
                Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT, "Ya hay una cuenta registrada con ese correo", "Escribe un correo electrónico diferente", "Continuar", "Cancelar");
                return 0;
            }*/

            format(TID_g_UserEmail[playerid], 128, "%s", inputtext);
            TID_RequestPassword(playerid);
        }        

        return 1;
    }

    if (!TID_IsUserRegistered(playerid)) {
        format(contentDialog, sizeof(contentDialog), "Si olvidas tu contraseña, puedes recuperarla usando tu correo.\n\nSolo usaremos tu correo \
                                                        con fines de verificar tu identidad.\nNo te enviaremos spam ni venderemos tus datos a terceros.");
        Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_INPUT, "Ingresa un correo electrónico válido", contentDialog, "Continuar", "Cancelar");
    }
    else {
        Dialog_ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Ya hay una cuenta registrada", "Si esta cuenta te pertenece, inicia sesión en su lugar.\nDe lo contrario, intenta con otro nombre.", "Entiendo", "");
    }

    return 1;
}

TID_RequestPassword(playerid)
{
    inline const Response(response, listitem, string:inputtext[]) {
        #pragma unused listitem

        if (response) {
            if (8 <= strlen(inputtext) < 32) {
                inline const OnPasswordHashed(string:result[])
                {
                    UI_HidePlayerTempoID(playerid);
                    UI_ShowPlayerLoadingScreen(playerid);

                    Logger_Log("on user hash", Logger_S("hash", result));
                    StrCpy(TID_g_UserPassword[playerid], result);

                    TID_CreateTempoID(playerid);
                    return 0;
                }
                
                BCrypt_HashInline(inputtext, BCRYPT_COST, OnPasswordHashed);
            }
        }
    }

    format(contentDialog, sizeof(contentDialog), "Debe tener entre 8 - 32 caracteres.\n\nNo compartas tu contraseña con nadie ni uses una \nque ya hayas usado en otro servidor. \
                                                  \n\nNosotros nunca te pediremos tu contraseña.");
    Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_PASSWORD, "Ingresa una contraseña segura", contentDialog, "Continuar", "Cancelar");

    return 1;
}

stock TID_CreateTempoID(playerid) 
{
    Logger_Log("creating Tempo ID account", Logger_P(playerid));

    new query       [3000],
        uuid        [UUID_LEN],
        name        [MAX_PLAYER_NAME],
        ip          [16],
        year, month, day,
        hours, minutes, seconds;
    
    inline const UserRegistered() {
        Logger_Log("user registered");
        UI_HidePlayerLoadingScreen(playerid);
    }

    UUID(uuid);
    GetPlayerName(playerid, name);
    GetPlayerIp(playerid, ip);
    getdate(year, month, day);
    gettime(hours, minutes, seconds);
    
    Logger_Log("creating user", Logger_S("uuid", uuid), Logger_S("name", name), Logger_S("ip", ip), Logger_S("email", TID_g_UserEmail[playerid]));

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "INSERT INTO `tmp_accounts` (`uuid`, `username`, `password`, `email`, `registration_date`, `registration_ip`) \
                                                                VALUES ('%s', '%e', '%s', '%e', '%02d-%02d-%02d %d:%d:%d', '%s');", uuid, name, TID_g_UserPassword[playerid], TID_g_UserEmail[playerid], \
                                                                year, month, day, hours, minutes, seconds, ip);
    MySQL_TQueryInline(TID_GetMySQLHandle(), UserRegistered, query);
}

/*
stock TID_CreateTag(&usertag[])
{
    for (new i = 0; i < len; ++i) {
        usertag[i] = random(94) + 33;
    }
    Logger_Log("", Logger_S("usertag", usertag));
}*/

stock TID_IsEmailUsed(const string:email[])
{
    new 
        query[128];

    inline const CheckEmail()
    {
        if (cache_num_rows()) return true;
        Logger_I("email registered", cache_num_rows());
    }

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "SELECT `uuid` FROM `tmp_accounts` WHERE `email`='%e' LIMIT 1", email);
    MySQL_TQueryInline(TID_GetMySQLHandle(), CheckEmail, query);

    return false;
}