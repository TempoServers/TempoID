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

#include <utils>
#include <logger>
#include <uuid>
#include <samp_bcrypt>

// YSI Libraries
#include <YSI_Visual\y_dialog>

#include <YSI_Server\y_colors>

#include <YSI_Coding\y_timers>

#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_bcrypt>
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Extra\y_inline_timers>

#include <YSI_Coding\y_hooks>

/*==============================================================================

	Modules

==============================================================================*/

#include <tempoid\core\tid_mysql>
#include <tempoid\core\tid_menu>
#include <tempoid\core\tid_account>
#include <tempoid\core\tid_signup>
#include <tempoid\core\tid_login>

#include <tempoid\user-interface\ui_intro>
#include <tempoid\user-interface\ui_menu>

#include <tempoid\cutscenes\cs_background>
