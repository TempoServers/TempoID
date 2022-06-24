/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Martin Santiago

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

#include <a_mysql>

#include <YSI_Coding\y_hooks>


#define TID_MYSQL_FILE              "tempoid_mysql.ini"

forward MySQL:TID_GetMySQLHandle();

static
MySQL:      TID_g_sMySQL; /// Connection handle with database


hook OnGameModeInit() 
{
    mysql_log(ALL); // Controls what information will be logged
    Logger_Log("[TempoID/MySQL] Connecting to the database...");

    TID_g_sMySQL = mysql_connect_file(TID_MYSQL_FILE);

    if (mysql_errno(TID_GetMySQLHandle()) != 0) // If there was an error trying to connect to database
        Logger_Err("[TempoID/MySQL] There was an error trying to connect to database.", Logger_I("errcode", mysql_errno()));
    else
        Logger_Log("[TempoID/MySQL] Successfully connected with database.");     
    return 1;
}

hook OnGameModeExit() 
{
    mysql_close(TID_GetMySQLHandle());    
    return 1;   
}

hook OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
    if (handle == TID_GetMySQLHandle()) {
        switch (errorid)
        {
            case CR_SERVER_LOST:
            {
                Logger_Log("[TempoID/MySQL] There was an error trying to perfom a query.", Logger_I("errorid", errorid), Logger_S("error", error));
                // TO-DO Show an error message on screen
            }
        }
    }
    return 1;
}


/*==============================================================================

	Interface

==============================================================================*/

/// <summary>Returns the actual MySQL handle of the connection with database</summary>
public MySQL:TID_GetMySQLHandle()
{
    return TID_g_sMySQL;
}