/*==============================================================================


	Tempo ID

		Copyright (C) 2022 Tempo Enterprise and contributors

		This Source Code Form is subject to the terms of the Mozilla Public
		License, v. 2.0. If a copy of the MPL was not distributed with this
		file, You can obtain one at http://mozilla.org/MPL/2.0/.



==============================================================================*/

// Class TIDUserInterface

#include <YSI_Coding\y_hooks>

// TO-DO: Rename variables to better convention
// TIDUI_sBackgroundXXX[]
// TIDUI_sButtonYYY[]
// TIDUI_sIndicatorZZZ[]


static
    Text:TIDUI_sBackgroundBannerUp,
    Text:bgBannerDown,
    Text:bgMain,
    Text:bgButtonOne,
    Text:logoTempoIDA,
    Text:loginText,
    Text:logoTempoIDB,
    Text:descText,
    Text:bgButtonTwo,
    Text:signupText,
    Text:faqButton,
    Text:forgotButton,
    Text:bgNews,
    Text:newsTitle,
    Text:newHeader_one,
    Text:aestheticDesign1,
    Text:newBanner_one,
    Text:newTime_one,
    Text:newCategory_one,
    Text:aestheticDesing2,
    Text:newBanner_two,
    Text:newCategory_two,
    Text:newTime_two,
    Text:newHeader_two;

hook OnGameModeInit() 
{
    TIDUI_sBackgroundBannerUp = TextDrawCreate(420.000000, 215.000000, "loadsc14:loadsc14");
    TextDrawFont(TIDUI_sBackgroundBannerUp, 4);
    TextDrawLetterSize(TIDUI_sBackgroundBannerUp, 0.600000, 2.000000);
    TextDrawTextSize(TIDUI_sBackgroundBannerUp, 158.500000, 143.000000);
    TextDrawSetOutline(TIDUI_sBackgroundBannerUp, 1);
    TextDrawSetShadow(TIDUI_sBackgroundBannerUp, 0);
    TextDrawAlignment(TIDUI_sBackgroundBannerUp, 1);
    TextDrawColor(TIDUI_sBackgroundBannerUp, -1);
    TextDrawBackgroundColor(TIDUI_sBackgroundBannerUp, 255);
    TextDrawBoxColor(TIDUI_sBackgroundBannerUp, 50);
    TextDrawUseBox(TIDUI_sBackgroundBannerUp, true);
    TextDrawSetProportional(TIDUI_sBackgroundBannerUp, true);
    TextDrawSetSelectable(TIDUI_sBackgroundBannerUp, false);

    bgBannerDown = TextDrawCreate(420.000000, 72.000000, "loadsc5:loadsc5");
    TextDrawFont(bgBannerDown, 4);
    TextDrawLetterSize(bgBannerDown, 0.600000, 2.000000);
    TextDrawTextSize(bgBannerDown, 158.500000, 143.000000);
    TextDrawSetOutline(bgBannerDown, 1);
    TextDrawSetShadow(bgBannerDown, 0);
    TextDrawAlignment(bgBannerDown, 1);
    TextDrawColor(bgBannerDown, -1);
    TextDrawBackgroundColor(bgBannerDown, 255);
    TextDrawBoxColor(bgBannerDown, 50);
    TextDrawUseBox(bgBannerDown, true);
    TextDrawSetProportional(bgBannerDown, true);
    TextDrawSetSelectable(bgBannerDown, false);

    bgMain = TextDrawCreate(343.000000, 75.000000, "_");
    TextDrawFont(bgMain, 1);
    TextDrawLetterSize(bgMain, 0.600000, 31.200023);
    TextDrawTextSize(bgMain, 0.000000, 265.000000);
    TextDrawSetOutline(bgMain, 1);
    TextDrawSetShadow(bgMain, 0);
    TextDrawAlignment(bgMain, 2);
    TextDrawColor(bgMain, -1);
    TextDrawBackgroundColor(bgMain, -168430166);
    TextDrawBoxColor(bgMain, -151587073);
    TextDrawUseBox(bgMain, true);
    TextDrawSetProportional(bgMain, true);
    TextDrawSetSelectable(bgMain, false);

    bgButtonOne = TextDrawCreate(345.000000, 187.000000, "_");
    TextDrawFont(bgButtonOne, 1);
    TextDrawLetterSize(bgButtonOne, 0.600000, 3.800003);
    TextDrawTextSize(bgButtonOne, 298.500000, 148.000000);
    TextDrawSetOutline(bgButtonOne, 1);
    TextDrawSetShadow(bgButtonOne, 0);
    TextDrawAlignment(bgButtonOne, 2);
    TextDrawColor(bgButtonOne, -1);
    TextDrawBackgroundColor(bgButtonOne, 255);
    TextDrawBoxColor(bgButtonOne, 9145343);
    TextDrawUseBox(bgButtonOne, true);
    TextDrawSetProportional(bgButtonOne, true);
    TextDrawSetSelectable(bgButtonOne, false);

    logoTempoIDA = TextDrawCreate(328.000000, 90.000000, "Tempo");
    TextDrawFont(logoTempoIDA, 3);
    TextDrawLetterSize(logoTempoIDA, 0.500000, 2.000000);
    TextDrawTextSize(logoTempoIDA, 400.000000, 17.000000);
    TextDrawSetOutline(logoTempoIDA, 0);
    TextDrawSetShadow(logoTempoIDA, 0);
    TextDrawAlignment(logoTempoIDA, 2);
    TextDrawColor(logoTempoIDA, 255);
    TextDrawBackgroundColor(logoTempoIDA, 255);
    TextDrawBoxColor(logoTempoIDA, 50);
    TextDrawUseBox(logoTempoIDA, false);
    TextDrawSetProportional(logoTempoIDA, true);
    TextDrawSetSelectable(logoTempoIDA, false);

    loginText = TextDrawCreate(345.000000, 199.000000, "iniciar_sesi¦n");
    TextDrawFont(loginText, 2);
    TextDrawLetterSize(loginText, 0.300000, 1.200000);
    TextDrawTextSize(loginText, 20.000000, 147.500000);
    TextDrawSetOutline(loginText, 0);
    TextDrawSetShadow(loginText, 0);
    TextDrawAlignment(loginText, 2);
    TextDrawColor(loginText, -1);
    TextDrawBackgroundColor(loginText, 255);
    TextDrawBoxColor(loginText, 65480);
    TextDrawUseBox(loginText, false);
    TextDrawSetProportional(loginText, true);
    TextDrawSetSelectable(loginText, true);

    logoTempoIDB = TextDrawCreate(373.000000, 89.000000, "ID");
    TextDrawFont(logoTempoIDB, 2);
    TextDrawLetterSize(logoTempoIDB, 0.500000, 2.000000);
    TextDrawTextSize(logoTempoIDB, 20.000000, 18.00000);
    TextDrawSetOutline(logoTempoIDB, 0);
    TextDrawSetShadow(logoTempoIDB, 0);
    TextDrawAlignment(logoTempoIDB, 2);
    TextDrawColor(logoTempoIDB, -168430081);
    TextDrawBackgroundColor(logoTempoIDB, 255);
    TextDrawBoxColor(logoTempoIDB, 286331391);
    TextDrawUseBox(logoTempoIDB, true);
    TextDrawSetProportional(logoTempoIDB, true);
    TextDrawSetSelectable(logoTempoIDB, false);

    descText = TextDrawCreate(345.000000, 123.000000, "Protege tu cuenta y juega en mªltiples servidores.");
    TextDrawFont(descText, 1);
    TextDrawLetterSize(descText, 0.300000, 1.200000);
    TextDrawTextSize(descText, 400.000000, 180.000000);
    TextDrawSetOutline(descText, 0);
    TextDrawSetShadow(descText, 0);
    TextDrawAlignment(descText, 2);
    TextDrawColor(descText, 255);
    TextDrawBackgroundColor(descText, 255);
    TextDrawBoxColor(descText, 50);
    TextDrawUseBox(descText, false);
    TextDrawSetProportional(descText, true);
    TextDrawSetSelectable(descText, false);

    bgButtonTwo = TextDrawCreate(345.000000, 240.000000, "_");
    TextDrawFont(bgButtonTwo, 1);
    TextDrawLetterSize(bgButtonTwo, 0.600000, 3.800003);
    TextDrawTextSize(bgButtonTwo, 298.500000, 148.000000);
    TextDrawSetOutline(bgButtonTwo, 3);
    TextDrawSetShadow(bgButtonTwo, 0);
    TextDrawAlignment(bgButtonTwo, 2);
    TextDrawColor(bgButtonTwo, -1);
    TextDrawBackgroundColor(bgButtonTwo, 255);
    TextDrawBoxColor(bgButtonTwo, -741092353);
    TextDrawUseBox(bgButtonTwo, true);
    TextDrawSetProportional(bgButtonTwo, true);
    TextDrawSetSelectable(bgButtonTwo, false);

    signupText = TextDrawCreate(345.000000, 251.000000, "CREAR ID");
    TextDrawFont(signupText, 2);
    TextDrawLetterSize(signupText, 0.300000, 1.200000);
    TextDrawTextSize(signupText, 20.000000, 138.500000);
    TextDrawSetOutline(signupText, 0);
    TextDrawSetShadow(signupText, 0);
    TextDrawAlignment(signupText, 2);
    TextDrawColor(signupText, 1296911871);
    TextDrawBackgroundColor(signupText, 255);
    TextDrawBoxColor(signupText, -741092408);
    TextDrawUseBox(signupText, false);
    TextDrawSetProportional(signupText, true);
    TextDrawSetSelectable(signupText, true);

    faqButton = TextDrawCreate(345.000000, 316.000000, "¯Qu es Tempo ID?");
    TextDrawFont(faqButton, 1);
    TextDrawLetterSize(faqButton, 0.250000, 1.000000);
    TextDrawTextSize(faqButton, 10.000000, 80.000000);
    TextDrawSetOutline(faqButton, 0);
    TextDrawSetShadow(faqButton, 0);
    TextDrawAlignment(faqButton, 2);
    TextDrawColor(faqButton, 9145343);
    TextDrawBackgroundColor(faqButton, 255);
    TextDrawBoxColor(faqButton, 50);
    TextDrawUseBox(faqButton, false);
    TextDrawSetProportional(faqButton, true);
    TextDrawSetSelectable(faqButton, true);

    forgotButton = TextDrawCreate(345.000000, 333.000000, "He olvidado mi contrase®a");
    TextDrawFont(forgotButton, 1);
    TextDrawLetterSize(forgotButton, 0.250000, 1.000000);
    TextDrawTextSize(forgotButton, 10.000000, 110.000000);
    TextDrawSetOutline(forgotButton, 0);
    TextDrawSetShadow(forgotButton, 0);
    TextDrawAlignment(forgotButton, 2);
    TextDrawColor(forgotButton, 9145343);
    TextDrawBackgroundColor(forgotButton, 255);
    TextDrawBoxColor(forgotButton, 50);
    TextDrawUseBox(forgotButton, false);
    TextDrawSetProportional(forgotButton, true);
    TextDrawSetSelectable(forgotButton, true);

    bgNews = TextDrawCreate(129.000000, 75.000000, "_");
    TextDrawFont(bgNews, 1);
    TextDrawLetterSize(bgNews, 0.600000, 31.200023);
    TextDrawTextSize(bgNews, 0.000000, 128.500000);
    TextDrawSetOutline(bgNews, 1);
    TextDrawSetShadow(bgNews, 0);
    TextDrawAlignment(bgNews, 2);
    TextDrawColor(bgNews, -1);
    TextDrawBackgroundColor(bgNews, 255);
    TextDrawBoxColor(bgNews, -168430081);
    TextDrawUseBox(bgNews, true);
    TextDrawSetProportional(bgNews, true);
    TextDrawSetSelectable(bgNews, false);

    newsTitle = TextDrawCreate(129.000000, 90.000000, "Noticias");
    TextDrawFont(newsTitle, 3);
    TextDrawLetterSize(newsTitle, 0.500000, 2.000000);
    TextDrawTextSize(newsTitle, 400.000000, 17.000000);
    TextDrawSetOutline(newsTitle, 0);
    TextDrawSetShadow(newsTitle, 0);
    TextDrawAlignment(newsTitle, 2);
    TextDrawColor(newsTitle, 255);
    TextDrawBackgroundColor(newsTitle, 255);
    TextDrawBoxColor(newsTitle, 50);
    TextDrawUseBox(newsTitle, false);
    TextDrawSetProportional(newsTitle, true);
    TextDrawSetSelectable(newsTitle, false);

    newHeader_one = TextDrawCreate(70.000000, 207.000000, "Las carreras de verano comienzan!");
    TextDrawFont(newHeader_one, 1);
    TextDrawLetterSize(newHeader_one, 0.300000, 1.200000);
    TextDrawTextSize(newHeader_one, 187.500000, 20.000000);
    TextDrawSetOutline(newHeader_one, 0);
    TextDrawSetShadow(newHeader_one, 0);
    TextDrawAlignment(newHeader_one, 1);
    TextDrawColor(newHeader_one, 255);
    TextDrawBackgroundColor(newHeader_one, 255);
    TextDrawBoxColor(newHeader_one, -1);
    TextDrawUseBox(newHeader_one, false);
    TextDrawSetProportional(newHeader_one, true);
    TextDrawSetSelectable(newHeader_one, true);

    aestheticDesign1 = TextDrawCreate(373.000000, 76.000000, "_");
    TextDrawFont(aestheticDesign1, 2);
    TextDrawLetterSize(aestheticDesign1, 0.500000, 1.400000);
    TextDrawTextSize(aestheticDesign1, 20.000000, 19.000000);
    TextDrawSetOutline(aestheticDesign1, 0);
    TextDrawSetShadow(aestheticDesign1, 0);
    TextDrawAlignment(aestheticDesign1, 2);
    TextDrawColor(aestheticDesign1, -168430081);
    TextDrawBackgroundColor(aestheticDesign1, 255);
    TextDrawBoxColor(aestheticDesign1, -168430081);
    TextDrawUseBox(aestheticDesign1, true);
    TextDrawSetProportional(aestheticDesign1, true);
    TextDrawSetSelectable(aestheticDesign1, false);

    newBanner_one = TextDrawCreate(70.000000, 124.000000, "ld_race:race05");
    TextDrawFont(newBanner_one, 4);
    TextDrawLetterSize(newBanner_one, 0.600000, 2.000000);
    TextDrawTextSize(newBanner_one, 118.000000, 70.000000);
    TextDrawSetOutline(newBanner_one, 1);
    TextDrawSetShadow(newBanner_one, 4);
    TextDrawAlignment(newBanner_one, 3);
    TextDrawColor(newBanner_one, -1);
    TextDrawBackgroundColor(newBanner_one, 255);
    TextDrawBoxColor(newBanner_one, 50);
    TextDrawUseBox(newBanner_one, true);
    TextDrawSetProportional(newBanner_one, true);
    TextDrawSetSelectable(newBanner_one, false);

    newTime_one = TextDrawCreate(95.000000, 196.000000, "hace 1 dia");
    TextDrawFont(newTime_one, 1);
    TextDrawLetterSize(newTime_one, 0.174999, 0.699999);
    TextDrawTextSize(newTime_one, 187.500000, 118.000000);
    TextDrawSetOutline(newTime_one, 0);
    TextDrawSetShadow(newTime_one, 0);
    TextDrawAlignment(newTime_one, 1);
    TextDrawColor(newTime_one, 1296911871);
    TextDrawBackgroundColor(newTime_one, 255);
    TextDrawBoxColor(newTime_one, -1);
    TextDrawUseBox(newTime_one, false);
    TextDrawSetProportional(newTime_one, true);
    TextDrawSetSelectable(newTime_one, false);

    newCategory_one = TextDrawCreate(70.000000, 196.000000, "Evento");
    TextDrawFont(newCategory_one, 1);
    TextDrawLetterSize(newCategory_one, 0.174999, 0.699999);
    TextDrawTextSize(newCategory_one, 187.500000, 118.000000);
    TextDrawSetOutline(newCategory_one, 0);
    TextDrawSetShadow(newCategory_one, 0);
    TextDrawAlignment(newCategory_one, 1);
    TextDrawColor(newCategory_one, -1811885057);
    TextDrawBackgroundColor(newCategory_one, 255);
    TextDrawBoxColor(newCategory_one, -1);
    TextDrawUseBox(newCategory_one, false);
    TextDrawSetProportional(newCategory_one, true);
    TextDrawSetSelectable(newCategory_one, false);

    aestheticDesing2 = TextDrawCreate(373.000000, 110.000000, "_");
    TextDrawFont(aestheticDesing2, 1);
    TextDrawLetterSize(aestheticDesing2, 0.500000, 1.400000);
    TextDrawTextSize(aestheticDesing2, 20.000000, 19.000000);
    TextDrawSetOutline(aestheticDesing2, 0);
    TextDrawSetShadow(aestheticDesing2, 0);
    TextDrawAlignment(aestheticDesing2, 2);
    TextDrawColor(aestheticDesing2, -168430081);
    TextDrawBackgroundColor(aestheticDesing2, 255);
    TextDrawBoxColor(aestheticDesing2, -168430081);
    TextDrawUseBox(aestheticDesing2, true);
    TextDrawSetProportional(aestheticDesing2, true);
    TextDrawSetSelectable(aestheticDesing2, false);

    newBanner_two = TextDrawCreate(70.000000, 241.000000, "loadsc13:loadsc13");
    TextDrawFont(newBanner_two, 4);
    TextDrawLetterSize(newBanner_two, 0.600000, 2.000000);
    TextDrawTextSize(newBanner_two, 118.000000, 70.000000);
    TextDrawSetOutline(newBanner_two, 1);
    TextDrawSetShadow(newBanner_two, 0);
    TextDrawAlignment(newBanner_two, 3);
    TextDrawColor(newBanner_two, -1);
    TextDrawBackgroundColor(newBanner_two, 255);
    TextDrawBoxColor(newBanner_two, 50);
    TextDrawUseBox(newBanner_two, true);
    TextDrawSetProportional(newBanner_two, true);
    TextDrawSetSelectable(newBanner_two, false);

    newCategory_two = TextDrawCreate(70.000000, 313.000000, "Bandas");
    TextDrawFont(newCategory_two, 1);
    TextDrawLetterSize(newCategory_two, 0.174999, 0.699999);
    TextDrawTextSize(newCategory_two, 187.500000, 118.000000);
    TextDrawSetOutline(newCategory_two, 0);
    TextDrawSetShadow(newCategory_two, 0);
    TextDrawAlignment(newCategory_two, 1);
    TextDrawColor(newCategory_two, 9145343);
    TextDrawBackgroundColor(newCategory_two, 255);
    TextDrawBoxColor(newCategory_two, -1);
    TextDrawUseBox(newCategory_two, false);
    TextDrawSetProportional(newCategory_two, true);
    TextDrawSetSelectable(newCategory_two, false);

    newTime_two = TextDrawCreate(95.000000, 313.000000, "Mayo 29");
    TextDrawFont(newTime_two, 1);
    TextDrawLetterSize(newTime_two, 0.174999, 0.699999);
    TextDrawTextSize(newTime_two, 187.500000, 118.000000);
    TextDrawSetOutline(newTime_two, 0);
    TextDrawSetShadow(newTime_two, 0);
    TextDrawAlignment(newTime_two, 1);
    TextDrawColor(newTime_two, 1296911871);
    TextDrawBackgroundColor(newTime_two, 255);
    TextDrawBoxColor(newTime_two, -1);
    TextDrawUseBox(newTime_two, false);
    TextDrawSetProportional(newTime_two, true);
    TextDrawSetSelectable(newTime_two, false);

    newHeader_two = TextDrawCreate(70.000000, 324.000000, "Balances en beneficios por conquista");
    TextDrawFont(newHeader_two, 1);
    TextDrawLetterSize(newHeader_two, 0.300000, 1.200000);
    TextDrawTextSize(newHeader_two, 187.500000, 20.000000);
    TextDrawSetOutline(newHeader_two, 0);
    TextDrawSetShadow(newHeader_two, 0);
    TextDrawAlignment(newHeader_two, 1);
    TextDrawColor(newHeader_two, 255);
    TextDrawBackgroundColor(newHeader_two, 255);
    TextDrawBoxColor(newHeader_two, -1);
    TextDrawUseBox(newHeader_two, false);
    TextDrawSetProportional(newHeader_two, true);
    TextDrawSetSelectable(newHeader_two, true);
    return 1;
}

hook OnPlayerClickTextDraw(playerid, clickedid) {
    new lContentDialog[2000];
    if (clickedid == _:faqButton) {
        format(lContentDialog, sizeof(lContentDialog), "Tu usuario de Tempo ID te permite loguear con la misma contraseña en todos nuestros \
                                                        servidores.\n\nNo es lo mismo que el nombre de tu personaje. Podrás tener varios personajes\
                                                        con un mismo Tempo ID.\n\nSEGURIDAD\n\nAuto-LOGIN");
        Dialog_ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "¿Qué es Tempo ID?", lContentDialog, "Entiendo", "");
    }
    else if (clickedid == _:forgotButton) {
        format(lContentDialog, sizeof(lContentDialog), "Te notificaremos cuando esta característica esté disponible.\n\nMientras, contacta a un administrador en nuestro Discord.");
        Dialog_ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Lo sentimos, aún no disponible", lContentDialog, "Entiendo", "");
    }
    else if (clickedid == _:loginText) {
        TID_DisplayLoginPrompt(playerid);
    }
    else if (clickedid ==_:signupText) {
        TID_DisplayRegisterPrompt(playerid);
    }
   
    return 1;
}

hook TID_OnUserLogin(playerid)
{
    UI_HidePlayerTempoID(playerid);
    return 1;
}

/// <summary>* * *</summary>
/// <param name="playerid">The ID of the player</param>
/// <seealso name="UI_HidePlayerTempoID"/>
stock UI_ShowPlayerTempoID(playerid) {
    TextDrawShowForPlayer(playerid, TIDUI_sBackgroundBannerUp);
    TextDrawShowForPlayer(playerid, bgBannerDown);
    TextDrawShowForPlayer(playerid, bgMain);
    TextDrawShowForPlayer(playerid, bgButtonOne);
    TextDrawShowForPlayer(playerid, logoTempoIDA);
    TextDrawShowForPlayer(playerid, loginText);
    TextDrawShowForPlayer(playerid, logoTempoIDB);
    TextDrawShowForPlayer(playerid, descText);
    TextDrawShowForPlayer(playerid, bgButtonTwo);
    TextDrawShowForPlayer(playerid, signupText);
    TextDrawShowForPlayer(playerid, faqButton);
    TextDrawShowForPlayer(playerid, forgotButton);
    TextDrawShowForPlayer(playerid, bgNews);
    TextDrawShowForPlayer(playerid, newsTitle);
    TextDrawShowForPlayer(playerid, aestheticDesign1);
    TextDrawShowForPlayer(playerid, aestheticDesing2);
    SelectTextDraw(playerid, Y_ALICEBLUE);
}

/// <summary>* * *</summary>
/// <param name="playerid">The ID of the player</param>
/// <seealso name="UI_ShowPlayerTempoID"/>
stock UI_HidePlayerTempoID(playerid) {
    TextDrawHideForPlayer(playerid, TIDUI_sBackgroundBannerUp);
    TextDrawHideForPlayer(playerid, bgBannerDown);
    TextDrawHideForPlayer(playerid, bgMain);
    TextDrawHideForPlayer(playerid, bgButtonOne);
    TextDrawHideForPlayer(playerid, logoTempoIDA);
    TextDrawHideForPlayer(playerid, loginText);
    TextDrawHideForPlayer(playerid, logoTempoIDB);
    TextDrawHideForPlayer(playerid, descText);
    TextDrawHideForPlayer(playerid, bgButtonTwo);
    TextDrawHideForPlayer(playerid, signupText);
    TextDrawHideForPlayer(playerid, faqButton);
    TextDrawHideForPlayer(playerid, forgotButton);
    TextDrawHideForPlayer(playerid, bgNews);
    TextDrawHideForPlayer(playerid, newsTitle);
    TextDrawHideForPlayer(playerid, aestheticDesign1);
    TextDrawHideForPlayer(playerid, aestheticDesing2);
    CancelSelectTextDraw(playerid);
}

// EOF
