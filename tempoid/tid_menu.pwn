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

#include <tempo_utils>
#include <YSI_Coding\y_hooks>

timer ClearingChat[400](playerid) { 
    Utils_ClearPlayerChat(playerid); 
}

/*timer AutoDisconnect[120000](playerid) {
    Kick(playerid);
}*/

////////////////////////////////////////
timer TID_tFinishIntro[5000](playerid) {
    UI_HidePlayerIntro(playerid);
    
    if (TID_GetUserStatus(playerid) != E_USER_STATE_LOGGED_IN) {    
        UI_HidePlayerBlackScreen(playerid);

        UI_ShowPlayerTempoID(playerid);
    } 
}

hook OnPlayerConnect(playerid) 
{
    defer ClearingChat(playerid);
    defer TID_tFinishIntro(playerid);
    return 0;
}

hook OnPlayerDisconnect(playerid)
{
    if (TID_GetUserStatus(playerid) == E_USER_STATE_LOGGING_IN) stop Timer:ClearingChat(playerid);
    return 0;
}

// EOF
