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

#include <YSI_Server\y_colors>
#include <YSI_Coding\y_hooks>


// MS = Membership

static const
    MAX_VIP_DURATION = 2629743; // 30.44 DAYS in Seconds

// Comprobar si el jugador tiene VIP y modificar su variable al conectarse
forward e_USER_VIP_TYPE:TID_GetUserVIP(playerid);

enum e_USER_VIP_TYPE
{
    INVALID_USER_VIP = -1,
    USER_VIP_TYPE_NONE = 0,
    USER_VIP_TYPE_BASIC,
    USER_VIP_TYPE_PLUS
}

static
    e_USER_VIP_TYPE:    g_sUserVIP          [MAX_PLAYERS],
    Text3D:             l_sVipBadge         [MAX_PLAYERS];



hook TID_OnUserLogin(playerid)
{
    TID_LoadUserMembership(playerid);
    return 1;
}

/*==============================================================================

	Interface

==============================================================================*/

/// <summary>User VIP status</summary>
/// <param name="playerid">The ID of the player to get the VIP from</param>
/// <seealso name="TID_SetUserStatus"/>
public e_USER_VIP_TYPE:TID_GetUserVIP(playerid)
{
    return g_sUserVIP[playerid];
}

stock e_USER_VIP_TYPE:GetUserVIP(playerid)
{
    return TID_GetUserVIP(playerid);
}

/// <summary>* * *</summary>
/// <param name="playerid">The ID of the player to get the status from</param>
/// <seealso name="TID_GetUserStatus"/>
stock TID_SetUserVIP(playerid, e_USER_VIP_TYPE:type) 
{
    g_sUserVIP[playerid] = type;
}

stock bool:TID_ValidateMembership(playerid, currentTimestamp)
{
    return ((TID_GetUserVIP(playerid) != INVALID_USER_VIP) && ((gettime() - currentTimestamp) < MAX_VIP_DURATION));
}

stock TID_LoadUserMembership(playerid)
{
    new
        query[220];
    
    inline const OnMembershipLoaded()
    {
        if (cache_num_rows()) // If user has any membership
        {
            new
                timestamp;
            cache_get_value_name_int(0, "timestamp", timestamp);

            if (TID_ValidateMembership(playerid, timestamp))
                cache_get_value_name_int(0, "vip", g_sUserVIP[playerid]);
            else
                g_sUserVIP[playerid] = USER_VIP_TYPE_NONE;

            switch (g_sUserVIP[playerid])
            {
                case USER_VIP_TYPE_BASIC:
                {
                    l_sVipBadge[playerid] = Create3DTextLabel("{0058ff}>>-VIP-<<\n{FFFFFF}", -1, 30.0,40.0,5.0,40.0, 0, false);
                    Attach3DTextLabelToPlayer(l_sVipBadge[playerid], playerid, 0.0, 0.0, 0.40);
                    SetPlayerColor(playerid, Y_MEDIUM_PURPLE_3);
                }
                case USER_VIP_TYPE_PLUS:
                {
                    l_sVipBadge[playerid] = Create3DTextLabel("{0058ff}>>-VIP+-<<\n{FFFFFF}", -1, 30.0,40.0,5.0,40.0, 0, false);
                    Attach3DTextLabelToPlayer(l_sVipBadge[playerid], playerid, 0.0, 0.0, 0.40);
                    SetPlayerColor(playerid, Y_MAGENTA_2);
                }
            }
        }
        else
            g_sUserVIP[playerid] = USER_VIP_TYPE_NONE;
    }

    mysql_format(TID_GetMySQLHandle(), query, sizeof(query), "SELECT vip, UNIX_TIMESTAMP(timestamp) AS 'timestamp' FROM `tmp_membership_log` WHERE uuid = '%s' ORDER BY timestamp DESC LIMIT 1;", TID_GetUserUUID(playerid));
    MySQL_TQueryInline(TID_GetMySQLHandle(), using inline OnMembershipLoaded, query);
}

hook OnPlayerDisconnect(playerid)
{
    Delete3DTextLabel(l_sVipBadge[playerid]);
    return 1;
}

// EOF
