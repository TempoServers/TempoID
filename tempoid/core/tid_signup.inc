/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <YSI_Coding\y_hooks>


forward TID_OnUserRegister(playerid);

enum e_USER_REGISTRATION_STATE
{
    e_USER_REGISTRATION_STATE_NONE, // Just connected, not started registering yet
    e_USER_REGISTRATION_STATE_E1,   // Typed the email
    e_USER_REGISTRATION_STATE_E2,   // Verified the email
    e_USER_REGISTRATION_STATE_P1,   // Typed the password
    e_USER_REGISTRATION_STATE_P2,   // Verified the password
    e_USER_REGISTRATION_STATE_WAIT, // Awaiting verification
    e_USER_REGISTRATION_STATE_DONE, // Registered
    e_USER_REGISTRATION_STATE_DISC, // Disconnected, but waiting for a callback to complete

}

static stock
                            TID_g_UserPassword          [MAX_PLAYERS][BCRYPT_HASH_LENGTH],
                            TID_g_UserEmail             [MAX_PLAYERS][128],
e_USER_REGISTRATION_STATE:  TID_g_sRegistrationState    [MAX_PLAYERS];


stock TID_DisplayRegisterPrompt(playerid) 
{
    TID_g_sRegistrationState[playerid] = e_USER_REGISTRATION_STATE_E1;

    inline const Response(response, listitem, string:inputtext[]) {
        #pragma unused listitem

        if (response) {
            if (TID_g_sRegistrationState[playerid] == e_USER_REGISTRATION_STATE_E1) {
                if (!(Utils_ValidEmail(inputtext))) {
                    TID_DisplayRegisterPrompt(playerid);
                    return 0;
                }

                // TO-DO: Verify if the email is used
                TID_g_sRegistrationState[playerid] = e_USER_REGISTRATION_STATE_E2;

                format(TID_g_UserEmail[playerid], 128, "%s", inputtext);
                TID_RequestPassword(playerid);
            }     
        }        
        return 1;
    }

    if (!TID_IsUserRegistered(playerid) && TID_g_sRegistrationState[playerid] == e_USER_REGISTRATION_STATE_E1) {
        new contentDialog[300];
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
    if (TID_g_sRegistrationState[playerid] != e_USER_REGISTRATION_STATE_E2) {
        // Some error? Reset user data and   trying again
    }
    else if (TID_g_sRegistrationState[playerid] == e_USER_REGISTRATION_STATE_E2)  {
        TID_g_sRegistrationState[playerid] = e_USER_REGISTRATION_STATE_P1;
    }
    else {
        // Some error?
    }

    inline const Response(response, listitem, string:inputtext[]) {
        #pragma unused listitem

        if (response) {
            if (8 <= strlen(inputtext) < 32) {
                inline const OnPasswordHashed(string:result[])
                {
                    StrCpy(TID_g_UserPassword[playerid], result);
                    TID_g_sRegistrationState[playerid] = e_USER_REGISTRATION_STATE_P2;

                    TID_CreateTempoID(playerid);
                    return 0;
                }
                
                BCrypt_HashInline(inputtext, BCRYPT_COST, OnPasswordHashed);
            }
        }
        else {
            if (TID_g_sRegistrationState[playerid] == e_USER_REGISTRATION_STATE_P1)
                TID_g_sRegistrationState[playerid] = e_USER_REGISTRATION_STATE_NONE;
        }
    }

    new contentDialog[300];
    format(contentDialog, sizeof(contentDialog), "Debe tener entre 8 - 32 caracteres.\n\nNo compartas tu contraseña con nadie ni uses una \nque ya hayas usado en otro servidor. \
                                                  \n\nNosotros nunca te pediremos tu contraseña.");
    Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_PASSWORD, "Ingresa una contraseña segura", contentDialog, "Continuar", "Cancelar");

    return 1;
}

stock TID_CreateTempoID(playerid) 
{
    new query   [3000],
        uuid    [UUID_LEN],
        name    [MAX_PLAYER_NAME],
        ip      [16],
        year, month, day,
        hours, minutes, seconds;

    UUID(uuid);
    GetPlayerName(playerid, name);
    GetPlayerIp(playerid, ip);
    getdate(year, month, day);
    gettime(hours, minutes, seconds);

    //TO-DO handle this Query using external files
    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "INSERT INTO `tmp_accounts` (`uuid`, `username`, `password`, `email`, `registration_date`, `registration_ip`) \
                                                                VALUES ('%s', '%e', '%s', '%e', '%02d-%02d-%02d %d:%d:%d', '%s');", uuid, name, TID_g_UserPassword[playerid], TID_g_UserEmail[playerid], \
                                                                year, month, day, hours, minutes, seconds, ip);
    mysql_tquery(TID_GetMySQLHandle(), query, "OnUserRegister", "i", playerid);
    return 0;
}

// TO-DO 
/*
stock TID_CreateTag(&usertag[])
{
    for (new i = 0; i < len; ++i) {
        usertag[i] = random(94) + 33;
    }
    Logger_Log("", Logger_S("usertag", usertag));
}*/

// TO-DO when Query is fetched is too late... idea: waiting message? cache all mails registered previously?
stock TID_IsEmailUsed(const string:email[])
{
    new 
        query[128];

    inline const CheckEmail()
    {
        if (cache_num_rows()) return true;
    }

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "SELECT `uuid` FROM `tmp_accounts` WHERE `email`='%e' LIMIT 1", email);
    MySQL_TQueryInline(TID_GetMySQLHandle(), CheckEmail, query);

    return false;
}