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

#include <a_mysql>

#include <YSI_Coding\y_hooks>

// MySQL credential files, it must be on the root of your server folder
#define TID_MYSQL_FILE "tempoid_mysql.ini"

// Forward declaration of the public function to get the MySQL handle
forward MySQL:TID_GetMySQLHandle();

static
MySQL:      TID_g_sMySQL; /// Connection handle with database in Tempo ID module


hook OnGameModeInit() 
{
    mysql_log(ALL);
    Logger_Log("[TempoID/MySQL] Connecting to the database...");

    TID_g_sMySQL = mysql_connect_file(TID_MYSQL_FILE);

    if (mysql_errno(TID_GetMySQLHandle()) != 0) { // If there was an error trying to connect to database
        Logger_Log("[TempoID/MySQL] There was an error trying to connect to database.", Logger_I("errcode", mysql_errno()));
        // TO-DO: Callback promise when an error occurs connecting
    }
    else {
        Logger_Log("[TempoID/MySQL] Successfully connected with database.");
    }
             
    return 0;
}

hook OnGameModeExit() 
{
    mysql_close(TID_GetMySQLHandle());    
    return 0;   
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

// EOF
