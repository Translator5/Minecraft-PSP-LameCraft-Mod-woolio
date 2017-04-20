#include "StateMenu.h"
#include "StateOptions.h"
#include "StatePlay.h"
#include "LoadingScreen.h"
#include "InputHelper.h"
#include "TextureHelper.h"

#include <Aurora/System/NetworkManager.h>

#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>


StateMenu::StateMenu()
{

}

StateMenu::~StateMenu()
{

}

void StateMenu::Init()
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();

    logoSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Logo),0,0,256,64);
    logoSprite->Scale(1.5f,1.5f);
    logoSprite->SetPosition(240,50);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,22,200,20);
    buttonSprite->SetPosition(240,150);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,62,200,20);
    sbuttonSprite->SetPosition(240,150);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,42,200,20);
    nbuttonSprite->SetPosition(240,150);

    buttonSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,22,200,20);
    buttonSprite2->SetPosition(240,150);
    buttonSprite2->Scale(0.5f,1);

    sbuttonSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,62,200,20);
    sbuttonSprite2->SetPosition(240,150);
    sbuttonSprite2->Scale(0.5f,1);

    mbuttonSprite2 = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,82,200,20);
    mbuttonSprite2->SetPosition(240,150);
    mbuttonSprite2->Scale(0.5f,1);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt),0,0,16,16);
    backSprite->Scale(4,4);

    selectSaveSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Glass),0,0,64,64);
    selectSaveSprite->Scale(7,0.6f);

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft),0,0,300,64);
    lamecraftSprite->SetPosition(240,50);

    screen1Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen1));
    screen1Sprite->SetPosition(260,136);

    screen2Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen2));
    screen2Sprite->SetPosition(260,136);

    screen3Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen3));
    screen3Sprite->SetPosition(260,136);

    screen4Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen4));
    screen4Sprite->SetPosition(260,136);
    selectPos = 0;

    //load save info
    ScanSaveFiles("Save/");

    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    aboutPos = 0;
    newWorldName = "World";
    newWorldSeed = "";

    size_f = 0.35f;
    //for map generation

    makeTrees = true;
    makeWater = true;
    makeCaves = true;
    makePumpkins = true;
    makeClouds = true;
    makeTypes = true;
    makeIron = true;
    makeCoal = true;
    makeGold = true;
    makeRedStone = true;
    makeDiamond = true;
    makeDirt = true;
    makeCanes = true;
    generateSelectPose = 0;
    SplashNumber = rand() % 5;
    time_s = 0;

    saveSubmenu = false;
    saveSubMenuSelect = 2;
    seed_1 = 0;

    newWorldNamestr = newWorldName.c_str();
    currentVersion = 30;

    //input helper
    InputHelper::Instance()->Init();
    InputHelper::Instance()->Load();

	animationscreen = 1;
	timex = 2400;
	fontcoloroption = 0;
	fontcolor = 0;
	srand(time(0));
}

void StateMenu::Enter()
{
    mRender->SetOrtho(0,0,0,0,0,0);
    selectPos = 0;
}

void StateMenu::CleanUp()
{
delete screen1Sprite;
delete screen2Sprite;
delete screen3Sprite;
delete screen4Sprite;
}

void StateMenu::Pause()
{

}

void StateMenu::Resume()
{
    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    mRender->SetOrtho(0,0,0,0,0,0);
}

void StateMenu::HandleEvents(StateManager* sManager)
{
    //update input
    mSystemMgr->InputUpdate();

    switch(menuState)
    {
    case 0://main menu
    {
        //if triangle button pressed the exit
        if(mSystemMgr->KeyPressed(PSP_CTRL_START))
        {
            //running = false;
            sManager->Quit();
        }

        //up, down
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            selectPos--;
            if(selectPos < 0)
                selectPos = 2;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            selectPos++;
            if(selectPos > 2)
                selectPos = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            SplashNumber = rand() % 5;
            if(selectPos == 0)//play state
            {
            generateSelectPose = 0;
            menuState = 7;
            }

            if(selectPos == 1)
            {
                //w teori opcje
                StateOptions *stateOptions = new StateOptions();
                stateOptions->Init();
                sManager->PushState(stateOptions);
            }
            if(selectPos == 2)
            {
                //about
                menuState = 3;
                aboutPos = 1;
            }
        }
    }
    break;
    case 1://load
    {
        if(saveSubmenu)
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                saveSubMenuSelect--;
                if(saveSubMenuSelect < 1)
                    saveSubMenuSelect = 2;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                saveSubMenuSelect++;
                if(saveSubMenuSelect > 2)
                    saveSubMenuSelect = 1;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(saveSubMenuSelect == 1)//remove file
                {
                    //remove file
                    if(saveFilesList.size() > 0)
                    {
                        if(saveFilesList[loadSavePos].compression)
                        {
                            //remove normal file
                            remove(saveFilesList[loadSavePos].fileName.c_str());

                            //remove compressed one
                            saveFilesList[loadSavePos].fileName += "c";
                            remove(saveFilesList[loadSavePos].fileName.c_str());

                        }
                        else
                        {
                            remove(saveFilesList[loadSavePos].fileName.c_str());
                        }

                        ScanSaveFiles("Save/");

                        loadSelectPos = 0;
                        loadSavePos = 0;
                        loadSaveStart = 0;
                        loadSaveEnd = saveFilesList.size();
                        loadSaveMax = 4;
                        if(loadSaveMax > loadSaveEnd)
                            loadSaveMax = loadSaveEnd;

                        saveSubmenu = false;
                        saveSubMenuSelect = 2;
                    }
                }
                if(saveSubMenuSelect == 2)//return
                {
                    saveSubMenuSelect = 2;
                    saveSubmenu = false;
                }
            }


        }
        else
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                loadSelectPos--;
                if(loadSelectPos < 0)
                    loadSelectPos = 2;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                loadSelectPos++;
                if(loadSelectPos > 2)
                    loadSelectPos = 0;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
            {
                loadSavePos--;
                if(loadSaveEnd > 4)
                {
                    loadSaveStart--;
                    loadSaveMax--;

                    if(loadSaveMax < 4)
                    {
                        loadSaveStart = 0;
                        loadSaveMax = 4;
                    }
                }

                if(loadSavePos < 0)
                {
                    loadSavePos = saveFilesList.size() - 1;
                    loadSaveMax = loadSaveEnd;
                    loadSaveStart = loadSaveEnd - 4;
                    if(loadSaveStart < 0)
                        loadSaveStart = 0;
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
            {
                loadSavePos++;
                if(loadSavePos == loadSaveMax)
                {
                    loadSaveStart++;
                    loadSaveMax++;
                    if(loadSaveMax > loadSaveEnd)
                    {
                        loadSaveStart = loadSaveEnd - 4;
                        if(loadSaveStart < 0)
                            loadSaveStart = 0;
                        loadSaveMax = loadSaveEnd;
                    }
                }
                if(loadSavePos >= saveFilesList.size())
                {
                    loadSavePos = 0;
                    loadSaveStart = 0;
                    loadSaveMax = 4;
                    if(loadSaveMax > loadSaveEnd)
                        loadSaveMax = loadSaveEnd;
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                menuState = 7;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(loadSelectPos == 0)//play state
                {
						//load map
                    if(saveFilesList.size() > 0)
                    {
                        StatePlay *statePlay = new StatePlay();
                        LoadingScreen *loading = new LoadingScreen();
                        statePlay->LoadMap(saveFilesList[loadSavePos].fileName,saveFilesList[loadSavePos].compression);
                        statePlay->InitCamera();
                        loading->KillLoadingScreen();
                        delete loading;
                        sManager->PushState(statePlay);
                    }

                }
                if(loadSelectPos == 1)//daelete save
                {
                    if(saveFilesList.size() > 0)
                    {
                        saveSubmenu = true;
                        saveSubMenuSelect = 2;
                    }
                }
                if(loadSelectPos == 2)
                {
                    menuState = 7;

                }
            }
        }
    }
    break;
    case 3://about
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            aboutPos--;
            if(aboutPos < 0)
                aboutPos = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            aboutPos++;
            if(aboutPos > 1)
                aboutPos = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(aboutPos == 1)
            {
                menuState = 0;
            }
            if(aboutPos == 0)
            {
                //checking for new update
                NetworkManager::Instance()->Init();
                //initialize connection
                if(NetworkManager::Instance()->InitializeConnection())
                {
                    //show network dialog and connect to ap
                    if(SystemManager::Instance()->ShowNetworkDialog())
                    {
                        //download update info
                        if(NetworkManager::Instance()->GetFile("http://drakon.ixan.net/psp/version.txt","version.txt"))
                        {
                            //check what version is inside
                            int fileVersion = 0;
                            FILE * pFile;
                            pFile = fopen("version.txt","r");
                            if (pFile!=NULL)
                            {
                                char buffer[3];
                                fread(buffer,1,3,pFile);
                                fileVersion = atoi(buffer);
                                fclose (pFile);

                                if(fileVersion > currentVersion)
                                {
                                    SystemManager::Instance()->ShowMessage("There is new version available");

                                    //ask question if user want to download updater
                                    if(SystemManager::Instance()->ShowMessageYesNo("Do you want to dowload LameCraft updater?") == 1)
                                    {
                                        //make new directory
                                        mkdir("ms0:/PSP/GAME/LameUpdater",777);
                                        //download updater there
                                        NetworkManager::Instance()->GetFile("http://drakon.ixan.net/psp/updater/EBOOT.PBP","ms0:/PSP/GAME/LameUpdater/EBOOT.PBP");
                                        //
                                        SystemManager::Instance()->ShowMessage("LameUpdater was installed.");
                                    }
                                }
                                else
                                {
                                    SystemManager::Instance()->ShowMessage("You have latest version.");
                                }
                            }
                            else
                            {
                                SystemManager::Instance()->ShowMessage("Can't open version.txt .");
                            }
                        }
                        else
                        {
                            SystemManager::Instance()->ShowMessage("Can't download update information.");
                        }
                    }
                    else
                    {
                        SystemManager::Instance()->ShowMessage("You must connect to an access point.");
                    }
                }
                else
                {
                    SystemManager::Instance()->ShowMessage("Can't initialize network.");
                }

                //turn off connection
                NetworkManager::Instance()->ShutDownConnection();
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            menuState = 0;
        }
    }
    break;
    case 5://parametric terrain
    {


        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            mSoundMgr->PlayMenuSound();
            if (generateSelectPose >= 2 && generateSelectPose <= 4)
            {
                generateSelectPose = 1;
                return;
            }
            if (generateSelectPose >= 5 && generateSelectPose <= 6)
            {
                generateSelectPose = 4;
                return;
            }
            if (generateSelectPose == 0)
            {
                generateSelectPose = 7;
                return;
            }
            generateSelectPose--;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
        {
            if (generateSelectPose >= 2 && generateSelectPose <= 3)
            {
                generateSelectPose ++;
                mSoundMgr->PlayMenuSound();
                return;
            }
            if (generateSelectPose == 5)
            {
                generateSelectPose = 6;
                mSoundMgr->PlayMenuSound();
                return;
            }
            if (generateSelectPose == 0)
            {
                generateSelectPose = 1;
                mSoundMgr->PlayMenuSound();
                return;
            }

        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
        {
            if (generateSelectPose >= 3 && generateSelectPose <= 4)
            {
                generateSelectPose --;
                mSoundMgr->PlayMenuSound();
                return;
            }
            if (generateSelectPose == 6)
            {
                generateSelectPose = 5;
                mSoundMgr->PlayMenuSound();
                return;
            }
            if (generateSelectPose == 1)
            {
                generateSelectPose = 0;
                mSoundMgr->PlayMenuSound();
                return;
            }


        }



        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            mSoundMgr->PlayMenuSound();
            if (generateSelectPose >= 2 && generateSelectPose <= 4)
            {
                generateSelectPose = 5;
                return;
            }
            if (generateSelectPose >= 5 && generateSelectPose <= 6)
            {
                generateSelectPose = 7;
                return;
            }
            if (generateSelectPose >= 0 && generateSelectPose <= 1)
            {
                generateSelectPose = 2;
                return;
            }
            generateSelectPose++;
            if(generateSelectPose > 7)
                generateSelectPose = 0;

        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 7;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0)
            {

                newWorldName = "";

                unsigned short test[128];
                unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
                if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                {

                    for(int j = 0; test[j]; j++)
                    {
                        unsigned c = test[j];

                        if(32 <= c && c <= 127) // print ascii only
                            newWorldName += c;
                    }


                }
                newWorldNamestr = newWorldName.c_str();

                }

                if(generateSelectPose == 1)
                {
                {
                seed_1 = 0;
                newWorldSeed = "";

                unsigned short test[128];
                unsigned short opis[10] = {'W','o','r','l','d',' ','s','e','e','d'};
                if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                {

                    for(int j = 0; test[j]; j++)
                    {
                        unsigned c = test[j];

                        if(48 <= c && c <= 57)
                        {
                            newWorldSeed += c;
                        }
                    }

                    seed_1 = std::atoi(newWorldSeed.c_str());



                }

                }

                }




            if(generateSelectPose == 2)
            {
                terrainBuilder = 0;

                makeWater = false;
            }

            if(generateSelectPose == 3)
            {
                terrainBuilder = 1;

                makeWater = true;
            }

            if(generateSelectPose == 4)
            {
                terrainBuilder = 2;

                makeWater = true;
            }

            if(generateSelectPose == 5)
            {
                makeTrees = !makeTrees;
            }

            if(generateSelectPose == 6)
            {
                makeCaves = !makeCaves;
            }

            if(generateSelectPose == 7)
            {
                StatePlay *statePlay = new StatePlay();
                statePlay->InitParametric(makeTrees,makeWater,makeCaves,makePumpkins,makeTypes,makeIron,makeCoal,makeGold,makeRedStone,makeDiamond,makeDirt,makeCanes,seed_1,terrainBuilder);
                statePlay->InitCamera();
                statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                sManager->PushState(statePlay);
            }
    }


    }
    break;
    case 6://check new version menu
    {

    }
    break;
    case 7://load or new map
    {
         if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            generateSelectPose--;
            if(generateSelectPose < 0)
                generateSelectPose = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            generateSelectPose++;
            if(generateSelectPose > 1)
                generateSelectPose = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 0;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0) //new game
            {
                generateSelectPose = 0;
                menuState = 5;

                makeTrees = true;
                makeWater = true;
                makeCaves = true;
                makePumpkins = true;
                makeClouds = true;
                makeTypes = true;
                makeIron = true;
                makeCoal = true;
                makeGold = true;
                makeRedStone = true;
                makeDiamond = true;
                makeDirt = true;
                makeCanes = true;
                terrainBuilder = 0;

            }

            if(generateSelectPose == 1) //load game
            {
                ScanSaveFiles("Save/");

                menuState = 1;
                loadSelectPos = 0;
                loadSavePos = 0;
                loadSaveStart = 0;
                loadSaveEnd = saveFilesList.size();
                loadSaveMax = 4;
                if(loadSaveMax > loadSaveEnd)
                loadSaveMax = loadSaveEnd;
            }
        }
    }
    break;

    }

}

void StateMenu::Update(StateManager* sManager)
{




}

void StateMenu::Draw(StateManager* sManager)
{
    //start rendering
    mRender->StartFrame(1,1,1);

    switch(menuState)
    {
    case 0://main menu
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,0.4f));


        screen1Sprite->SetPosition(-480+(-920 + (timex/10)),136);
        screen1Sprite->Draw();
        screen2Sprite->SetPosition(0+(-920 + (timex/10)),136);
        screen2Sprite->Draw();
        screen3Sprite->SetPosition(480+(-920 + (timex/10)),136);
        screen3Sprite->Draw();
        screen4Sprite->SetPosition(960+(-920 + (timex/10)),136);
        screen4Sprite->Draw();

        sceGuColor(GU_COLOR(1,1,1,1.0f));


        time_s += 0.1f;
        //mRender->DebugPrint(240,50,"Time: %f", time_s);
        float fontsize = 0.8 + sinf(time_s) * 0.18f;
        //logo
        lamecraftSprite->Draw();

        //singlePlayer
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        //about
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //options
        buttonSprite->SetPosition(240,200);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(selectPos * 40) + 120);
        sbuttonSprite->Draw();


        //mRender->DebugPrint(240,50,"Time: %f", time_s);
        if(menuState == 0)
        {
            if (animationscreen == 1)
            {
                timex < 15000 ? timex+= 2 : animationscreen = 2;
            }
            else
            {
                timex > 2450 ? timex-= 2 : animationscreen = 1;
            }
        }



        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons
        DrawText(240,125,GU_COLOR(1,1,1,1) ,0.35f,"SinglePlayer");
        DrawText(240,165,GU_COLOR(1,1,1,1) ,0.35f, "Options");
        DrawText(240,205,GU_COLOR(1,1,1,1) ,0.35f,"About");

        mRender->SetFontStyle(0.35f ,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00000000|0x00004000);
        mRender->DebugPrint(3,270,"1.1.3 beta");
        mRender->SetFontStyle(0.35f ,GU_COLOR(1,1,1,1),0,0,0x00000000|0x00004000);
        mRender->DebugPrint(2,269,"1.1.3 beta");

        if (fontcoloroption == 0)
        {
            fontcolor += 0.05f;
            if (fontcolor > 0.9f)
            {
                fontcoloroption = 1;
            }
        }
        else
        {
            fontcolor -= 0.05f;
            if (fontcolor < 0.1f)
            {
                fontcoloroption = 0;
            }
        }

        char *SplashText;
        //Randomly generate the text number - because is in "while" not working yet
        //SplashNumber = rand() % 2; // 0-2

        switch (SplashNumber)
        {
        case 0:
            SplashText = "Woo, minecraft!";
            break;
        case 1:
            SplashText = "With survival!";
            break;
        case 2:
            SplashText = "Thanks for michal5575!";
            break;
        case 3:
            SplashText = "Woolio <3";
            break;
        case 4:
            SplashText = "S4inex <3";
            break;
        case 5:
            SplashText = "Beta!";
            break;
        case 6:
            SplashText = "Camxpspx123 sucks! ";
            break;
        }

        //mRender->SetFontStyle(fontsize ,0xFF00FFFF,0,0,0x00000200|0x00004000);
        //DrawText(360,80,GU_COLOR(1,fontcolor,0,1)  ,fontsize,SplashText);

		}
		break;
    case 1://load menu
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        //select sprite
        if(saveFilesList.size() > 0)
        {
            selectSaveSprite->SetPosition(240,50 + (loadSavePos * 40) - (loadSaveStart * 40));
            selectSaveSprite->Draw();
        }

        //save files
        for(int i = loadSaveStart; i <loadSaveMax; i++)
        {
            if(loadSavePos == i)
            {
                mRender->SetFontStyle(1.0f,0xFF000000,0xFFFFFFFF,0,0x00000000);
                mRender->DebugPrint(30,50 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].worldName);

                mRender->SetFontStyle(0.7f,0xFF7F7F7F,0xFF000000,0,0x00000000);
                mRender->DebugPrint(40,65 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].fileName.c_str());
            }
            else
            {
                mRender->SetFontStyle(0.8f,0xFFFFFFFF,0xFF000000,0,0x00000000);
                mRender->DebugPrint(30,50 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].worldName);

                mRender->SetFontStyle(0.5f,0xFF7F7F7F,0xFF000000,0,0x00000000);
                mRender->DebugPrint(40,60 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].fileName.c_str());
            }

        }

        //play
        buttonSprite->SetPosition(240,210);
        buttonSprite->Draw();

        //delete
        buttonSprite->SetPosition(240,235);
        buttonSprite->Draw();

        //back
        buttonSprite->SetPosition(240,260);
        buttonSprite->Draw();

        //selected button


        if(saveSubmenu)
        {
            sbuttonSprite->SetPosition(240,(saveSubMenuSelect * 25) + 210);
        }
        else
        {
            sbuttonSprite->SetPosition(240,(loadSelectPos * 25) + 210);
        }
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(saveSubmenu)
        {
            DrawText(240,215,GU_COLOR(1,1,1,1) ,0.35f,"Are you sure?");
            DrawText(240,240,GU_COLOR(1,1,1,1) ,0.35f,"Yes");
            DrawText(240,265,GU_COLOR(1,1,1,1) ,0.35f,"No");
        }
        else
        {
            DrawText(240,215,GU_COLOR(1,1,1,1),0.35f,"Play");
            DrawText(240,240,GU_COLOR(1,1,1,1) ,0.35f,"Delete");
            DrawText(240,265,GU_COLOR(1,1,1,1) ,0.35f,"Back");
        }
        DrawText(240,20,GU_COLOR(1,1,1,1) ,0.35f,"Load world");
    }
    break;
    case 3://about
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        //check for update
        buttonSprite->SetPosition(240,235);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,260);
        buttonSprite->Draw();

        //back
        sbuttonSprite->SetPosition(240,(aboutPos * 25) + 235);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        DrawText(240,100,GU_COLOR(1,1,1,1) ,0.7f,"Original Code: Drakon");
        DrawText(240,120,GU_COLOR(1,1,1,1) ,0.7f,"Mod by: Woolio");
        DrawText(240,140,GU_COLOR(1,1,1,1) ,0.7f,"Version: 1.1.3 beta");

        DrawText(240,240,GU_COLOR(1,1,1,1) ,0.35f,"Check for update");
        DrawText(240,265,GU_COLOR(1,1,1,1) ,0.35f,"Back");
        DrawText(240,25,GU_COLOR(1,1,1,1) ,0.345f,"About");

    }
    break;
    case 5://paramateric view
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        //logo

        //name
        nbuttonSprite->SetPosition(120,70);
        nbuttonSprite->Draw();
        //seed
        nbuttonSprite->SetPosition(360,70);
        nbuttonSprite->Draw();

        buttonSprite2->SetPosition(120,120);
        buttonSprite2->Draw();

        buttonSprite2->SetPosition(240,120);
        buttonSprite2->Draw();

        buttonSprite2->SetPosition(360,120);
        buttonSprite2->Draw();

        buttonSprite2->SetPosition(120,170);
        buttonSprite2->Draw();

        buttonSprite2->SetPosition(360,170);
        buttonSprite2->Draw();

        buttonSprite->SetPosition(240,230);
        buttonSprite->Draw();




        if(generateSelectPose >= 0 && generateSelectPose <= 1)
        {
            sbuttonSprite->SetPosition(120 + (generateSelectPose * 240),70);
        }
        if(generateSelectPose >= 2 && generateSelectPose <= 4)
        {
            sbuttonSprite2->SetPosition(120 + ((generateSelectPose-2) * 120),120);
        }
        if(generateSelectPose >= 5 && generateSelectPose <= 6)
        {
            sbuttonSprite2->SetPosition(120 + ((generateSelectPose-5) * 240),170);
        }
        if(generateSelectPose == 7)
        {
            sbuttonSprite->SetPosition(240,230);
        }

        mbuttonSprite2->SetPosition(120 + (terrainBuilder * 120),120);
        mbuttonSprite2->Draw();

        if (makeTrees == true)
        {
            mbuttonSprite2->SetPosition(120,170);
            mbuttonSprite2->Draw();
        }

        if (makeCaves == true)
        {
            mbuttonSprite2->SetPosition(360,170);
            mbuttonSprite2->Draw();
        }

        if(generateSelectPose >= 2 && generateSelectPose <= 6)
        {
            sbuttonSprite2->Draw();
        }
        else
        {
            sbuttonSprite->Draw();
        }

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons
        DrawText(120,50,GU_COLOR(1,1,1,1) ,0.35f,"Name");
        DrawText(360,50,GU_COLOR(1,1,1,1) ,0.35f,"Seed");

        DrawText(120,125,GU_COLOR(1,1,1,1) ,0.35f,"Flat");
        DrawText(240,125,GU_COLOR(1,1,1,1) ,0.35f,"Old");
        DrawText(360,125,GU_COLOR(1,1,1,1) ,0.35f,"New");

        DrawText(120,175,GU_COLOR(1,1,1,1) ,0.35f,"Trees");
        DrawText(360,175,GU_COLOR(1,1,1,1) ,0.35f,"Caves");
        DrawText(240,235,GU_COLOR(1,1,1,1) ,0.35f,"Generate");

        DrawText(240,25,GU_COLOR(1,1,1,1) ,0.35f,"New world");

        mRender->SetFontStyle(0.35f ,GU_COLOR(1,1,1,1),0,0,0x00000000|0x00004000);
        mRender->DebugPrint(28,75,"%s",newWorldName.c_str());
        mRender->DebugPrint(268,75,"%s",newWorldSeed.c_str());
    }
    break;
    case 7://New or load map
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        //Randomly
        buttonSprite->SetPosition(240,100);
        buttonSprite->Draw();

        //Parametric
        buttonSprite->SetPosition(240,140);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(generateSelectPose * 40) + 100);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons

        DrawText(240,105,GU_COLOR(1,1,1,1) ,0.35f,"New world");
        DrawText(240,145,GU_COLOR(1,1,1,1) ,0.35f,"Load world");
        DrawText(240,25,GU_COLOR(1,1,1,1) ,0.35f,"SinglePlayer");
    }
    break;

    }

    //draw debug text at the end
    /*mRender->DebugPrint(40,30,"cpu: %d%%",mRender->GetCpuUsage());
    mRender->DebugPrint(40,40,"gpu: %d%%",mRender->GetGpuUsage());
    mRender->DebugPrint(40,50,"saves: %d",saveFilesList.size());*/

    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000400);
    //mRender->DebugPrint(475,15,"CraftSite.pl Edition");
    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);

    //end frame
    mRender->EndFrame();
}

//additional functions
void StateMenu::ScanSaveFiles(const char* dirName)
{
    //clear list with save files
    saveFilesList.clear();

    DIR *Dir;
    struct dirent *DirEntry;
    Dir = opendir(dirName);

    while((DirEntry = readdir(Dir)) != NULL)
    {
        if ( DirEntry->d_stat.st_attr & FIO_SO_IFREG)
        {
            SaveFile newSaveFile;
            std::string plik = dirName;
            plik += DirEntry->d_name;
            //dont load lmsc files
            size_t found = plik.find(".lmsc");
            size_t found2 = plik.find(".LMSc");
            if(found==std::string::npos && found2==std::string::npos)//nie znaleziono
            {
                newSaveFile.fileName = plik;
                saveFilesList.push_back(newSaveFile);
            }
        }
    }

    closedir(Dir);

    /*//// this was causeing some problems
    int dfd;
    dfd = sceIoDopen(dirName);
    if(dfd > 0)
    {
    	SceIoDirent dir;

    	while(sceIoDread(dfd, &dir) > 0)
    	{
    		if(dir.d_stat.st_attr & FIO_SO_IFREG)//regular file
    		{
    			SaveFile newSaveFile;
    			std::string plik = dirName;
    			plik += dir.d_name;
    			//dont load lmsc files
    			size_t found = plik.find(".lmsc");
    			if(found==string::npos)//nie znaleziono
    			{
    				newSaveFile.fileName = plik;
    				saveFilesList.push_back(newSaveFile);
    			}
    		}
    	}

    	//close folder
    	sceIoClose(dfd);
    }*/

    //now update all info in save files
    for(unsigned int i = 0; i < saveFilesList.size(); i++)
    {
        FILE * pFile;
        pFile = fopen(saveFilesList[i].fileName.c_str(),"rb");

        if(pFile != NULL)
        {
            //version
            fread(&saveFilesList[i].saveVersion,sizeof(int),1,pFile);

            //name
            fread(saveFilesList[i].worldName,sizeof(char),50,pFile);

            if(saveFilesList[i].saveVersion >= 2)
                saveFilesList[i].compression = true;
            else
                saveFilesList[i].compression = false;

            fclose(pFile);
        }
    }

    //set next save name and numer
    nextSaveFileNumber = saveFilesList.size() + 1;
    {
        //ride thru all saves and check if i can use new name
        char liczba[3];
        sprintf(liczba,"%d",nextSaveFileNumber);
        nextSaveFileName = "Save/world";
        nextSaveFileName += liczba;
        nextSaveFileName += ".lms";

        for(unsigned int i = 0; i < saveFilesList.size(); i++)
        {
            if(nextSaveFileName.compare(saveFilesList[i].fileName) == 0)
            {
                nextSaveFileNumber+=1;
                char liczba[3];
                sprintf(liczba,"%d",nextSaveFileNumber);
                nextSaveFileName = "Save/world";
                nextSaveFileName += liczba;
                nextSaveFileName += ".lms";
            }
        }
    }
}


void StateMenu::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    mRender->SetFontStyle(size,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00000200|0x00000000);
    mRender->DebugPrint(x+(size/(float)0.35f),y+(size/(float)0.35f),message);
    mRender->SetFontStyle(size,color,0,0,0x00000200|0x00000000);
    mRender->DebugPrint(x,y,message);
}
