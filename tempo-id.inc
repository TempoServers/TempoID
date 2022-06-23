#if defined _INC_TempoID
    #endinput
#endif
#define _INC_TempoID

/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

// Third-party dependencies 
#include <a_samp>

// YSI Libraries
#include <YSI_Visual\y_dialog>
#include <YSI_Server\y_colours>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_bcrypt>
#include <YSI_Extra\y_inline_mysql>

#include <YSI_Coding\y_hooks>

/*==============================================================================

	Modules

==============================================================================*/

#if !defined _INC_tid_mysql
    #tryinclude <tid_mysql>
#endif
#if !defined _INC_tid_menu
    #tryinclude <tid_menu>
#endif
#if !defined _INC_tid_account
    #tryinclude <tid_account>
#endif
#if !defined _INC_tid_signup
    #tryinclude <tid_signup>
#endif
#if !defined _INC_tid_login
    #tryinclude <tid_login>
#endif

//
#include <user-interface\ui_intro>

hook OnGameModeInit() 
{
    print("\n====================================");
    print("\tTempo ID v0.1 loaded");
    print("\t(c) Martin Santiago");
    print("====================================\n");
    return 1;
}

hook OnIncomingConnection(playerid, ip_address[], port)
{
    printf("Incoming connection for player ID %i [IP/port: %s:%i]", playerid, ip_address, port);
    return 1;    
}

hook OnPlayerConnect(playerid) 
{
    SetPlayerColor(playerid, Y_WHITESMOKE);
    
    SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    
    Cutscene_StartLogin(playerid);
    return 1;
}