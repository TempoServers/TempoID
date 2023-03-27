#if defined _tempoid_included
    #endinput
#endif
#define _tempoid_included

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

#if !defined TEMPO_SERVICE_ID
    #error Define TEMPO_SERVICE_ID before using Tempo ID
#endif

#include <Logger>
#include <a_samp>


#include <uuid>
#include <samp_bcrypt>

// YSI Libraries
#define YSI_NO_HEAP_MALLOC

#include <YSI_Visual\y_dialog>
#include <YSI_Server\y_colors>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_bcrypt>
#include <YSI_Extra\y_inline_timers>

/*==============================================================================

	Modules

==============================================================================*/


#include <TempoID\constants>
#include <TempoID\tid_mysql>
#include <TempoID\tid_account>
#include <TempoID\tid_menu>
#include <TempoID\tid_signup>
#include <TempoID\tid_login>
#include <TempoID\tid_vip>

#include <tempoid\user-interface\ui_intro>
#include <tempoid\user-interface\ui_menu>

#include <tempoid\cutscenes\cs_background>

/*==============================================================================

	Init

==============================================================================*/

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() 
{
    Logger_Log("[Tempo ID] Trying to load Tempo ID services in this server.");
    // TO-DO: Setting up closest coords to the cutscene
    AddPlayerClass(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // Allow spawn of the player
    return 0;
}

hook OnIncomingConnection(playerid, ip_address[], port)
{
    TID_SetUserStatus(playerid, E_USER_STATE_CONNECTING);
    return 0;    
}

// EOF
