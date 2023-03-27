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


// Define the event to be called when the user's sign up is completed
forward TID_OnUserRegistered(playerid);

static 
            TID_g_UserPassword  [MAX_PLAYERS][BCRYPT_HASH_LENGTH],
            TID_g_UserEmail     [MAX_PLAYERS][128];

static stock 
            contentDialog[2000];

public TID_OnUserRegistered(playerid)
{
    UI_HidePlayerLoadingScreen(playerid);
    TID_SetUserStatus(playerid, E_USER_STATE_LOGGED_IN);
    SetTimerEx("TID_OnUserLogin", 2000, false, "ii", playerid, false);
    return 1;
}

/*==============================================================================

	Interface

==============================================================================*/

TID_DisplayRegisterPrompt(playerid) 
{
    Logger_Dbg("tempo-id", "[TempoID] User is registering a new account", Logger_P(playerid));

    inline const Response(response, listitem, string:inputtext[]) {
        #pragma unused listitem

        if (response) {
            if (!(ValidEmail(inputtext))) {
                TID_DisplayRegisterPrompt(playerid);
                return 0;
            }

            // TO-DO: Verify if the email is used
            // Remarks: A user can have many tempoIDs with same email
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
            if (strlen(inputtext) >=8 &&  strlen(inputtext) < 32) {
                inline const OnPasswordHashed(string:result[])
                {
                    UI_HidePlayerTempoID(playerid);
                    UI_ShowPlayerLoadingScreen(playerid);

                    StrCpy(TID_g_UserPassword[playerid], result);

                    TID_CreateTempoID(playerid);
                    return 0;
                }
                
                BCrypt_HashInline(inputtext, BCRYPT_COST, using inline OnPasswordHashed);
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
        hours, minutes, seconds,
        userNameTID[MAX_PLAYER_NAME];

    UUID(uuid);
    GetPlayerName(playerid, name);
    GetPlayerIp(playerid, ip);
    getdate(year, month, day);
    gettime(hours, minutes, seconds);
    userNameTID = TID_GetUserName(playerid);
    TID_SetUserUUID(playerid, uuid);
    
    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "INSERT INTO `tmp_accounts` (`uuid`, `username`, `password`, `email`, `registration_date`, `registration_ip`) \
                                                                VALUES ('%s', '%e', '%s', '%e', '%02d-%02d-%02d %d:%d:%d', '%s');", uuid, userNameTID, TID_g_UserPassword[playerid], TID_g_UserEmail[playerid], \
                                                                year, month, day, hours, minutes, seconds, ip);
    mysql_tquery(TID_GetMySQLHandle(), query, "TID_OnUserRegistered", "i", playerid);
}

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

// EOF
