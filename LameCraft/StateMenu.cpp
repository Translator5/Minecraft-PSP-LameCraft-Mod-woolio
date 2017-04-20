#include "StateMenu.h"
#include "StateOptions.h"
#include "StatePlay.h"
#include "StatePlayCreative.h"
#include "LoadingScreen.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include <Aurora/System/NetworkManager.h>
#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

// font vars
#define default_size 0.5
#define default_big_size 0.687
#define PI 3.1415926535897f

#define ENGLISH 1
#define RUSSIAN 2

/*
q = э
w = ш
e = е
y = ч
u = y
i = и
o = o
p = п
g = г
j = ж
z = з
x = щ
c = ц
v = в
~ = й

$ = ь
& = ъ
^ = я
@ = ы
# = ю
*/

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

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

    rectFilledSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Rectangles),0,0,230,37);
    rectFilledSprite->SetPosition(240,150);
    rectFilledSprite->Scale(2,2);

    rectEmptySprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Rectangles),0,37,230,37);
    rectEmptySprite->SetPosition(240,150);
    rectEmptySprite->Scale(2,2);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,0,190,24); // stand
    buttonSprite->SetPosition(240,150);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,190,24); // stand selected
    sbuttonSprite->SetPosition(240,150);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,48,190,24); // dark
    nbuttonSprite->SetPosition(240,150);

    // small buttons
    buttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,0,190,24); // stand
    buttonSmallSprite->SetPosition(240,150);
    buttonSmallSprite->Scale(0.45f,1.0f);

    sbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,190,24); // stand selected
    sbuttonSmallSprite->SetPosition(240,150);
    sbuttonSmallSprite->Scale(0.45f,1.0f);

    nbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,48,190,24); // dark
    nbuttonSmallSprite->SetPosition(240,150);
    nbuttonSmallSprite->Scale(0.45f,1.0f);
    //

    mbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,72,190,24); // gray
    mbuttonSprite->SetPosition(240,150);

    smbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,96,190,24); // gray selected
    smbuttonSprite->SetPosition(240,150);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt),0,0,32,32);
    backSprite->Scale(2,2);

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft),0,0,320,90);
    lamecraftSprite->SetPosition(240,50);
    lamecraftSprite->Scale(1,1);

    blackBackground = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),174,120,16,16);
    blackBackground->SetPosition(240,116);
    blackBackground->Scale(30,11);

    selectPos = 0;

    //load save info
    ScanSaveFiles("Save/");
    ScanTexturePacks("Assets/Textures/");

    menuState = -1;
    loadSelectPos = 0;
    loadSavePos = 0;
    aboutPos = 0;

    newWorldName = "New World";
    newWorldNamestr = "";
    newWorldSeed = "";

    size_f = 0.347f;

    //for map generation
    makeTrees = true;
    makeWater = true;
    makeCaves = true;

    terrainBuilder = 0;
    worldType = 0; // default
    gameMode = 0;
    seed_1 = 0;

    SplashNumber = rand() % 5;
    splashSize = 0.0f;

    saveSubmenu = false;
    saveSubMenuSelect = 2;
    generateSelectPose = 0;

    newWorldNamestr = newWorldName.c_str();
    currentVersion = 140;

    //input helper
    InputHelper::Instance()->Init();
    InputHelper::Instance()->Load();

	animationscreen = 1;
	fontcoloroption = 0;
	fontcolor = 0;
	srand(time(0));

    tpCurrent = 0;
	tpMax = 0;
	tpEnd = 0;
	tpStart = 0;
	tpPos = 0;
	tpSelectPos = 0;

	for(int i = 0; i <= 31; i++)
	{
	    worldName[i] = ' ';
	}
}

void StateMenu::Enter()
{
    mRender->SetOrtho(0,0,0,0,0,0);
    selectPos = 0;
}

void StateMenu::CleanUp()
{
    delete logoSprite;
    delete buttonSprite;
    delete sbuttonSprite;
    delete nbuttonSprite;
    delete mbuttonSprite;
    delete smbuttonSprite;
    delete backSprite;
    delete lamecraftSprite;

    delete buttonSmallSprite;
    delete sbuttonSmallSprite;
    delete nbuttonSmallSprite;

    delete blackBackground;
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
    case -1:// language menu
    {
        //up, down
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            selectPos--;
            if(selectPos < 0)
                selectPos = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            selectPos++;
            if(selectPos > 1)
                selectPos = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            RenderManager::InstancePtr()->defaultFontType = selectPos+1;
            RenderManager::InstancePtr()->SetDefaultFont();
            selectPos = 0;
            menuState = 0;

            SplashNumber = rand() % 5;
        }
    }
    break;
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
                selectPos = 3;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            selectPos++;
            if(selectPos > 3)
                selectPos = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(selectPos == 0)//play state
            {
                ScanSaveFiles("Save/");

                loadSavePos = 0;
                loadSaveStart = 0;
                loadSaveEnd = saveFilesList.size();
                loadSaveMax = 4;
                if(loadSaveMax > loadSaveEnd)
                loadSaveMax = loadSaveEnd;

                menuState = 1;
                if(saveFilesList.empty() == false)
                {
                    loadSelectPos = 0;
                }
                else
                {
                    loadSelectPos = 3;
                }
            }
            if(selectPos == 1)
            {
                //options
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
            if(selectPos == 3)
            {
                //textures
                tpCurrent = 0;
                tpMax = 0;
                tpEnd = 0;
                tpStart = 0;
                tpPos = 0;
                tpSelectPos = 0;

                menuState = 11;
                tpSelectPos = 0;
                tpEnd = texturePackList.size();
                tpMax = 3;
                ScanTexturePacks("Assets/Textures/");
            }
        }
    }
    break;
    case 1: //select world
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

                        loadSavePos = 0;
                        loadSaveStart = 0;
                        loadSaveEnd = saveFilesList.size();
                        loadSaveMax = 4;
                        if(loadSaveMax > loadSaveEnd)
                            loadSaveMax = loadSaveEnd;

                        saveSubmenu = false;
                        saveSubMenuSelect = 2;

                        if(saveFilesList.empty() == false)
                        {
                            loadSelectPos = 0;
                        }
                        else
                        {
                            loadSelectPos = 2;
                        }
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
                if(loadSelectPos == 1 || loadSelectPos == 2)
                {
                    loadSelectPos = 0;
                    mSoundMgr->PlayMenuSound();
                }
                if(loadSelectPos == 4)
                {
                    loadSelectPos = 3;
                    mSoundMgr->PlayMenuSound();
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                if(loadSelectPos == 0 || loadSelectPos == 3)
                {
                    loadSelectPos++;
                    mSoundMgr->PlayMenuSound();
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
            {
                if(saveFilesList.empty() == false)
                {
                    switch(loadSelectPos)
                    {
                        case 2:
                        loadSelectPos = 1;
                        mSoundMgr->PlayMenuSound();
                        break;
                        case 3:
                        loadSelectPos = 0;
                        mSoundMgr->PlayMenuSound();
                        break;
                        case 4:
                        loadSelectPos = 2;
                        mSoundMgr->PlayMenuSound();
                        break;
                    }
                }
            }


            if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
            {
                switch(loadSelectPos)
                {
                    case 0:
                    loadSelectPos = 3;
                    mSoundMgr->PlayMenuSound();
                    break;
                    case 1:
                    loadSelectPos = 2;
                    mSoundMgr->PlayMenuSound();
                    break;
                    case 2:
                    loadSelectPos = 4;
                    mSoundMgr->PlayMenuSound();
                    break;
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
            {
                if(saveFilesList.empty() == false)
                {
                    loadSavePos--;

                    if(loadSavePos < loadSaveStart)
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
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
            {
                if(saveFilesList.empty() == false)
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
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                menuState = 0;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(loadSelectPos == 0)//play selected world
                {
                    if(saveFilesList.size() > 0)
                    {
                        if(saveFilesList[loadSavePos].locked == false)
                        {
                            if(saveFilesList[loadSavePos].worldGameMode == 0 || saveFilesList[loadSavePos].worldGameMode == 2)
                            {
                                StatePlay *statePlay = new StatePlay();
                                statePlay->LoadMap(saveFilesList[loadSavePos].fileName,saveFilesList[loadSavePos].compression);
                                statePlay->InitCamera();
                                sManager->PushState(statePlay);
                            }
                            else
                            {
                                StatePlayCreative *statePlay = new StatePlayCreative();
                                statePlay->LoadMap(saveFilesList[loadSavePos].fileName,saveFilesList[loadSavePos].compression);
                                statePlay->InitCamera();
                                sManager->PushState(statePlay);
                            }
                        }
                    }
                }
                if(loadSelectPos == 1)//rename world
                {
                    if(saveFilesList.size() > 0)
                    {
                        char worldNameTemp[50];

                        unsigned short test[128];
                        unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
                        if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                        {
                            std::string newWorldName = "";
                            for(int j = 0; test[j]; j++)
                            {
                                unsigned c = test[j];

                                if(32 <= c && c <= 127) // print ascii only
                                    newWorldName += c;
                            }

                            sprintf(worldNameTemp,"%s",newWorldName.c_str());
                        }

                        int saveVersionTemp = 3;
                        char worldGameModeTemp = saveFilesList[loadSavePos].worldGameMode;
                        bool locked = saveFilesList[loadSavePos].locked;

                        FILE * pFile;
                        pFile = fopen(saveFilesList[loadSavePos].fileName.c_str(),"wb");

                        if(pFile != NULL)
                        {
                            //version
                            fwrite(&saveVersionTemp, sizeof(int),1,pFile);

                            fwrite(&worldGameModeTemp, sizeof(char),1,pFile);

                            fwrite(&locked, sizeof(bool),1,pFile);
                            //name
                            fwrite(worldNameTemp ,sizeof(char),50,pFile);

                            fclose(pFile);
                        }

                        ScanSaveFiles("Save/");
                    }
                }
                if(loadSelectPos == 2)//delete world
                {
                    if(saveFilesList.size() > 0)
                    {
                        saveSubmenu = true;
                        saveSubMenuSelect = 2;
                    }
                }
                if(loadSelectPos == 3)//create new world
                {
                    generateSelectPose = 0;
                    menuState = 5;

                    makeTrees = true;
                    makeWater = true;
                    makeCaves = true;
                    terrainBuilder = 0;
                    worldType = 0;

                    newWorldName = "New World";
                    newWorldSeed = "";
                }
                if(loadSelectPos == 4)//cancel
                {
                    menuState = 0;
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
                        if(NetworkManager::Instance()->GetFile("http://net2ftp.ru/node0/kuznetsoffvyacheslav@gmail.com/version.txt","version.txt"))
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
                                    if(SystemManager::Instance()->ShowMessageYesNo("Do you want to download Minecraft PSP update?") == 1)
                                    {
                                        //download updater there
                                        NetworkManager::Instance()->GetFile("http://net2ftp.ru/node0/kuznetsoffvyacheslav@gmail.com/Minecraft-PSP.zip","ms0:/PSP/GAME/Minecraft-PSP.zip");
										theZip = pgeZipOpen("ms0:/PSP/GAME/Minecraft-PSP.zip");
                                        chdir("ms0:/PSP/GAME");
                                        pgeZipExtract(theZip, NULL);
                                        pgeZipClose(theZip);

                                        SystemManager::Instance()->ShowMessage("Update was installed. You can find it in your game directory");
                                        theZip = NULL;
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

            if (generateSelectPose == 0)
            {
                generateSelectPose = 4;
                return;
            }

            generateSelectPose--;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            mSoundMgr->PlayMenuSound();
            if (generateSelectPose == 4)
            {
                generateSelectPose = 0;
                return;
            }
            generateSelectPose++;

        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            ScanSaveFiles("Save/");

            menuState = 1;
            loadSavePos = 0;
            loadSaveStart = 0;
            loadSaveEnd = saveFilesList.size();
            loadSaveMax = 4;
            if(loadSaveMax > loadSaveEnd)
            loadSaveMax = loadSaveEnd;

            menuState = 1;

            loadSelectPos = 3;
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
                    for(int j = 0; j < 14; j++)
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
                seed_1 = 0;
                newWorldSeed = "";

                unsigned short test[128];
                unsigned short opis[10] = {'W','o','r','l','d',' ','s','e','e','d'};
                if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                {

                    for(int j = 0; j < 14; j++)
                    {
                        unsigned c = test[j];

                        if(c >= 32 && c <= 127)
                        {
                            newWorldSeed += c;
                        }
                    }
                    seed_1 = hash(newWorldSeed.c_str(),0);
                    //seed_1 = std::atoi(newWorldSeed.c_str());
                }
            }


            if(generateSelectPose == 2)
            {
                gameMode += 1;
                if (gameMode == 3)
                {
                    gameMode = 0;
                }
            }

            if(generateSelectPose == 3)
            {
                worldType += 1;
                if(worldType > 1)
                {
                    worldType = 0;
                }
            }

            if(generateSelectPose == 4)
            {
                //terrainBuilder = 2;
                if(gameMode == 0 || gameMode == 2)
                {
                    StatePlay *statePlay = new StatePlay();
                    statePlay->InitParametric(makeTrees,makeWater,makeCaves,seed_1,worldType,gameMode);
                    statePlay->InitCamera();
                    statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                    sManager->PushState(statePlay);
                }
                else
                {
                    StatePlayCreative *statePlay = new StatePlayCreative();
                    statePlay->InitParametric(makeTrees,makeWater,makeCaves,seed_1,worldType,gameMode);
                    statePlay->InitCamera();
                    statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                    sManager->PushState(statePlay);
                }
                seed_1 = 0;
            }
        }
    }
    break;
    case 6://check new version menu
    {

    }
    break;
    case 10:
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            saveSubMenuSelect == 0 ? saveSubMenuSelect = 1 : saveSubMenuSelect = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            saveSubMenuSelect == 1 ? saveSubMenuSelect = 0 : saveSubMenuSelect = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            char worldNameTemp[50];
            for(char i = 0; i <= 49; i++)
            {
                worldNameTemp[i] = saveFilesList[loadSavePos].worldName[i];
            }

            int saveVersionTemp = 3;
            char worldGameModeTemp = saveSubMenuSelect;
            bool locked = saveFilesList[loadSavePos].locked;

            FILE * pFile;
            pFile = fopen(saveFilesList[loadSavePos].fileName.c_str(),"wb");

            if(pFile != NULL)
            {
                //version
                fwrite(&saveVersionTemp, sizeof(int),1,pFile);

                fwrite(&worldGameModeTemp, sizeof(char),1,pFile);

                fwrite(&locked, sizeof(bool),1,pFile);
                //name
                fwrite(worldNameTemp ,sizeof(char),50,pFile);

                fclose(pFile);
            }

            ScanSaveFiles("Save/");

            if(saveFilesList[loadSavePos].locked == true)
            {
                loadSelectPos = 1;
            }

            menuState = 1;
        }
    }
    break;
    case 11://tp
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
        {
            tpSelectPos --;
            if(tpSelectPos < 0)
            {
                tpSelectPos = 1;
            }
            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
        {
            tpSelectPos ++;
            if(tpSelectPos > 1)
            {
                tpSelectPos = 0;
            }
            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
        {
            tpPos--;
            if(tpPos < tpStart)
            {
                tpStart--;
                tpMax--;

                if(tpMax < 3)
                {
                    tpStart = 0;
                    tpMax = 3;
                }
            }

            if(tpPos < 0)
            {
                tpPos = texturePackList.size() - 1;
                tpMax = tpEnd;
                tpStart = tpEnd - 3;
                if(tpStart < 0)
                    tpStart = 0;
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
        {
            tpPos++;
            if(tpPos == tpMax)
            {
                tpStart++;
                tpMax++;
                if(tpMax > tpEnd)
                {
                    tpStart = tpEnd - 3;
                    if(tpStart < 0)
                    {
                        tpStart = 0;
                    }
                    tpMax = tpEnd;
                }
            }
            if(tpPos >= texturePackList.size())
            {
                tpPos = 0;
                tpStart = 0;
                tpMax = 3;
                if(tpMax > tpEnd)
                    tpMax = tpEnd;
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            menuState = 0;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(tpSelectPos == 0)//play state
            {
                if(texturePackList.empty() == false)
                {
                    TextureHelper::Instance()->SetTexturePack(texturePackList[tpPos].name);
                    tpCurrent = tpPos;
                }
            }
            if(tpSelectPos == 1)//delete save
            {
                menuState = 0;
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
    case -1://language menu
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

        // english
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        // russian
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(selectPos * 40) + 120);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        selectPos == 0 ? DrawText(240,129,GU_COLOR(1,1,0.25,1) ,default_size,"English") : DrawText(240,129,GU_COLOR(1,1,1,1) ,default_size,"English");
        selectPos == 1 ? DrawText(240,169,GU_COLOR(1,1,0.25,1) ,default_size,"Russian") : DrawText(240,169,GU_COLOR(1,1,1,1) ,default_size,"Russian");

        DrawText(240,24,GU_COLOR(1,1,1,1) ,default_size,"Choose your language");
    }
    break;
    case 0://main menu
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
        lamecraftSprite->Draw();

        //singlePlayer
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        //options
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //about
        buttonSprite->SetPosition(240,200);
        buttonSprite->Draw();

        //texture pack
        buttonSprite->SetPosition(240,240);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(selectPos * 40) + 120);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        splashSize += 0.08f;
        if(splashSize > 2*PI)
        {
            splashSize = 0.0f;
        }

        if(RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH)
        {
            selectPos == 0 ? DrawText(240,129,GU_COLOR(1,1,0.25,1) ,default_size,"Singleplayer") : DrawText(240,129,GU_COLOR(1,1,1,1) ,default_size,"Singleplayer");
            selectPos == 1 ? DrawText(240,169,GU_COLOR(1,1,0.25,1) ,default_size,"Options") : DrawText(240,169,GU_COLOR(1,1,1,1) ,default_size,"Options");
            selectPos == 2 ? DrawText(240,209,GU_COLOR(1,1,0.25,1) ,default_size,"About") : DrawText(240,209,GU_COLOR(1,1,1,1) ,default_size,"About");
            selectPos == 3 ? DrawText(240,249,GU_COLOR(1,1,0.25,1) ,default_size,"Texture Packs") : DrawText(240,249,GU_COLOR(1,1,1,1) ,default_size,"Texture Packs");


            switch(SplashNumber)
            {
                case 0: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Beta!"); break;
                case 1: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Fan fiction!"); break;
                case 2: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Made on Lamecraft op-30!"); break;
                case 3: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"More polygons!"); break;
                case 4: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Large thanks to Drakon |"); break;
            }
        }
        if(RenderManager::InstancePtr()->GetFontLanguage() == RUSSIAN)
        {
            selectPos == 0 ? DrawText(240,129,GU_COLOR(1,1,0.25,1) ,default_size,"Odinoyna^ igra") : DrawText(240,129,GU_COLOR(1,1,1,1) ,default_size,"Odinoyna^ igra");
            selectPos == 1 ? DrawText(240,169,GU_COLOR(1,1,0.25,1) ,default_size,"Nastro~ki") : DrawText(240,169,GU_COLOR(1,1,1,1) ,default_size,"Nastro~ki");
            selectPos == 2 ? DrawText(240,209,GU_COLOR(1,1,0.25,1) ,default_size,"Ob igre") : DrawText(240,209,GU_COLOR(1,1,1,1) ,default_size,"Ob igre");
            selectPos == 3 ? DrawText(240,249,GU_COLOR(1,1,0.25,1) ,default_size,"Tekstur@") : DrawText(240,249,GU_COLOR(1,1,1,1) ,default_size,"Tekstur@");

            switch(SplashNumber)
            {
                case 0: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Beta!"); break;
                case 1: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Fanatska^ rabota!"); break;
                case 2: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Uje 2 goda s vami!"); break;
                case 3: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Bol$we poligonov!"); break;
                case 4: DrawText(328,86,GU_COLOR(1,1,0,1) ,0.6+sinf(splashSize)*0.04f,"Bol$woe spasibo Drakonu!"); break;
            }
        }
    }
    break;
    case 1://select world
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

        if(saveSubmenu) // delete world
        {
            buttonSprite->SetPosition(240,235);
            buttonSprite->Draw();

            buttonSprite->SetPosition(240,260);
            buttonSprite->Draw();
        }
        else
        {
            /// left part
            if(saveFilesList.empty() == false)
            {
                buttonSprite->SetPosition(120,222); // play selected world
                buttonSprite->Draw();

                buttonSmallSprite->SetPosition(67.75,255); // rename
                buttonSmallSprite->Draw();

                buttonSmallSprite->SetPosition(172.25,255); // delete
                buttonSmallSprite->Draw();
            }
            else
            {
                nbuttonSprite->SetPosition(120,222); // play selected world
                nbuttonSprite->Draw();

                nbuttonSmallSprite->SetPosition(67.75,255); // rename
                nbuttonSmallSprite->Draw();

                nbuttonSmallSprite->SetPosition(172.25,255); // delete
                nbuttonSmallSprite->Draw();
            }

            ///right part
            buttonSprite->SetPosition(360,222); // create new world
            buttonSprite->Draw();

            buttonSprite->SetPosition(360,255); // cancel
            buttonSprite->Draw();
        }


        bool smallButton = false;
        if(saveSubmenu)
        {
            sbuttonSprite->SetPosition(240,(saveSubMenuSelect * 25) + 210);
        }
        else
        {
            switch(loadSelectPos)
            {
                case 0:
                sbuttonSprite->SetPosition(120,222);
                break;
                case 1:
                sbuttonSmallSprite->SetPosition(67.75,255);
                smallButton = true;
                break;
                case 2:
                sbuttonSmallSprite->SetPosition(172.25,255);
                smallButton = true;
                break;
                case 3:
                sbuttonSprite->SetPosition(360,222);
                break;
                case 4:
                sbuttonSprite->SetPosition(360,255);
                break;
            }
        }
        smallButton == true ? sbuttonSmallSprite->Draw() : sbuttonSprite->Draw();

        blackBackground->Draw();

        //select sprite
        if(saveFilesList.size() > 0)
        {
            //save files
            for(int i = loadSaveStart; i <loadSaveMax; i++)
            {
                if(loadSavePos == i)
                {
                    mRender->SetFont(ENGLISH);
                    mRender->SetFontStyle(0.8f,GU_COLOR(1,1,0,1),0,0x00000000);
                    mRender->DebugPrint(30,54 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].worldName);

                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                    mRender->DebugPrint(30,66 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].fileName.c_str());

                    mRender->SetDefaultFont();

                    if(mRender->GetFontLanguage() == ENGLISH)
                    {
                        switch(saveFilesList[i].worldGameMode)
                        {
                            case 0:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Survival mode (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 1:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Creative mode (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 2:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Hardcore mode (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                        }
                    }
                    if(mRender->GetFontLanguage() == RUSSIAN)
                    {
                        switch(saveFilesList[i].worldGameMode)
                        {
                            case 0:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"V@jivanie (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 1:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Tvoryeski~ (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 2:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Hardkor (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                        }
                    }
                }
                else
                {
                    mRender->SetFont(ENGLISH);
                    mRender->SetFontStyle(0.8f,GU_COLOR(1,1,1,1),0,0x00000000);
                    mRender->DebugPrint(30,54 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].worldName);

                    mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                    mRender->DebugPrint(30,66 + (i * 41) - (loadSaveStart * 41),"%s",saveFilesList[i].fileName.c_str());

                    mRender->SetDefaultFont();

                    if(mRender->GetFontLanguage() == ENGLISH)
                    {
                        switch(saveFilesList[i].worldGameMode)
                        {
                            case 0:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Survival mode (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 1:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Creative mode (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 2:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                            mRender->DebugPrint(30,78  + (i * 41) - (loadSaveStart * 41),"Hardcore mode (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                        }
                    }

                    if(mRender->GetFontLanguage() == RUSSIAN)
                    {
                        switch(saveFilesList[i].worldGameMode)
                        {
                            case 0:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"V@jivanie (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 1:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                            mRender->DebugPrint(30,78 + (i * 41) - (loadSaveStart * 41),"Tvoryeski~ (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                            case 2:
                            mRender->SetFontStyle(0.5f,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                            mRender->DebugPrint(30,78  + (i * 41) - (loadSaveStart * 41),"Hardkor (%i KB)",saveFilesList[i].saveSize/1024);
                            break;
                        }
                    }
                }
            }
        }

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            if(saveSubmenu)
            {
                saveSubMenuSelect == 0 ? DrawText(240,219,GU_COLOR(1,1,0.25,1) ,default_size,"Are you sure?") : DrawText(240,219,GU_COLOR(1,1,1,1) ,default_size,"Are you sure?");
                saveSubMenuSelect == 1 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Yes") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Yes");
                saveSubMenuSelect == 2 ? DrawText(240,269,GU_COLOR(1,1,0.25,1) ,default_size,"No") : DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,"No");
            }
            else
            {
                float buttonTextColor = 1.0f; // for left part
                if(saveFilesList.empty() == true)
                {
                    buttonTextColor = 0.5f;
                }

                loadSelectPos == 0 ? DrawText(120,231,GU_COLOR(1,1,0.25,1),default_size,"Play Selected World") : DrawText(120,231,GU_COLOR(buttonTextColor,buttonTextColor,buttonTextColor,1),default_size,"Play Selected World");
                loadSelectPos == 1 ? DrawText(67.75f,264,GU_COLOR(1,1,0.25,1) ,default_size,"Rename") : DrawText(67.75f,264,GU_COLOR(buttonTextColor,buttonTextColor,buttonTextColor,1) ,default_size,"Rename");
                loadSelectPos == 2 ? DrawText(172.25f,264,GU_COLOR(1,1,0.25,1) ,default_size,"Delete") : DrawText(172.25f,264,GU_COLOR(buttonTextColor,buttonTextColor,buttonTextColor,1) ,default_size,"Delete");
                loadSelectPos == 3 ? DrawText(360,231,GU_COLOR(1,1,0.25,1) ,default_size,"Create New World") : DrawText(360,231,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,"Create New World");
                loadSelectPos == 4 ? DrawText(360,264,GU_COLOR(1,1,0.25,1) ,default_size,"Cancel") : DrawText(360,264,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,"Cancel");
            }
            DrawText(240,24,GU_COLOR(1,1,1,1) ,default_size,"Select World");
        }

        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            if(saveSubmenu)
            {
                saveSubMenuSelect == 0 ? DrawText(240,219,GU_COLOR(1,1,0.25,1) ,default_size,"V@ uveren@?") : DrawText(240,219,GU_COLOR(1,1,1,1) ,default_size,"V@ uveren@?");
                saveSubMenuSelect == 1 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Da") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Da");
                saveSubMenuSelect == 2 ? DrawText(240,269,GU_COLOR(1,1,0.25,1) ,default_size,"Net") : DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,"Net");
            }
            else
            {
                float buttonTextColor = 1.0f; // for left part
                if(saveFilesList.empty() == true)
                {
                    buttonTextColor = 0.5f;
                }

                loadSelectPos == 0 ? DrawText(120,231,GU_COLOR(1,1,0.25,1),default_size,"Igrat$ v v@brannom mire") : DrawText(120,231,GU_COLOR(buttonTextColor,buttonTextColor,buttonTextColor,1),default_size,"Igrat$ v v@brannom mire");
                loadSelectPos == 1 ? DrawText(67.75f,264,GU_COLOR(1,1,0.25,1) ,default_size,"Pereimenovat$") : DrawText(67.75f,264,GU_COLOR(buttonTextColor,buttonTextColor,buttonTextColor,1) ,default_size,"Pereimenovat$");
                loadSelectPos == 2 ? DrawText(172.25f,264,GU_COLOR(1,1,0.25,1) ,default_size,"Udalit$") : DrawText(172.25f,264,GU_COLOR(buttonTextColor,buttonTextColor,buttonTextColor,1) ,default_size,"Udalit$");
                loadSelectPos == 3 ? DrawText(360,231,GU_COLOR(1,1,0.25,1) ,default_size,"Sozdat$ nov@~ mir") : DrawText(360,231,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,"Sozdat$ nov@~ mir");
                loadSelectPos == 4 ? DrawText(360,264,GU_COLOR(1,1,0.25,1) ,default_size,"Otmena") : DrawText(360,264,GU_COLOR(1.0f,1.0f,1.0f,1) ,default_size,"Otmena");
            }
            DrawText(240,24,GU_COLOR(1,1,1,1) ,default_size,"V@bor mira");
        }
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

        blackBackground->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,100-40,"Original Code:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,100-40,"Marcin Ploska(Drakon)");

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,124-40,"Modder:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,124-40,"Kirill Skibin(Woolio)");

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,172-40,"Website:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,172-40,"vk.com/mine_psp");

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,196-40,"Version:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,196-40,"1.4.2");

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,220-40,"Development stage:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,220-40,"Beta");

            aboutPos == 0 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Check for update") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Check for update");
            aboutPos == 1 ? DrawText(240,269,GU_COLOR(1,1,0.25,1) ,default_size,"Cancel") : DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,"Cancel");
            DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"About");
        }
        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,100-40,"Dvijok igr@:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,100-40,"Marsin Ploska(Drakon)");

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,124-40,"Modifikaci^:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,124-40,"Kirill Skibin(Volio)");

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,172-40,"Vebsa~t:");

            mRender->SetFont(ENGLISH);
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,172-40,"vk.com/mine_psp");
            mRender->SetDefaultFont();

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,196-40,"Versi^:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,196-40,"1.4");

            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000000);
            mRender->DebugPrint(40,220-40,"Stadi^ razrabotki:");
            mRender->SetFontStyle(0.687,GU_COLOR(1,1,1,1),2,0x00000400);
            mRender->DebugPrint(440,220-40,"Beta");

            aboutPos == 0 ? DrawText(240,244,GU_COLOR(1,1,0.25,1) ,default_size,"Proverit$ obnovleni^") : DrawText(240,244,GU_COLOR(1,1,1,1) ,default_size,"Proverit$ obnovleni^");
            aboutPos == 1 ? DrawText(240,269,GU_COLOR(1,1,0.25,1) ,default_size,"Otmena") : DrawText(240,269,GU_COLOR(1,1,1,1) ,default_size,"Otmena");
            DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"Ob igre");
        }
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


        //name
        mbuttonSprite->SetPosition(240,70);
        mbuttonSprite->Draw();
        //seed
        mbuttonSprite->SetPosition(240,110);
        mbuttonSprite->Draw();

        buttonSprite->SetPosition(240,150);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,190);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,230);
        buttonSprite->Draw();

        if(generateSelectPose > 1)
        {
            sbuttonSprite->SetPosition(240,150+(generateSelectPose-2)*40);
            sbuttonSprite->Draw();
        }
        if(generateSelectPose <= 1)
        {
            smbuttonSprite->SetPosition(240,70+generateSelectPose*40);
            smbuttonSprite->Draw();
        }

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"Create New World");
            DrawText(240,58,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Name");
            DrawText(240,98,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Seed");

            //draw subtitles on buttons
            if(gameMode == 0)
            {
                generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Survival") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Survival");
            }
            if(gameMode == 1)
            {
                generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Creative") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Creative");
            }
            if(gameMode == 2)
            {
                generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Game Mode: Hardcore") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Game Mode: Hardcore");
            }

            if(worldType == 0)
            {
                generateSelectPose == 3 ? DrawText(240,199,GU_COLOR(1,1,0.25,1) ,default_size,"World Type : Default") : DrawText(240,199,GU_COLOR(1,1,1,1) ,default_size,"World Type : Default");
            }
            if(worldType == 1)
            {
                generateSelectPose == 3 ? DrawText(240,199,GU_COLOR(1,1,0.25,1) ,default_size,"World Type : Superflat") : DrawText(240,199,GU_COLOR(1,1,1,1) ,default_size,"World Type : Superflat");
            }

            generateSelectPose == 4 ? DrawText(240,239,GU_COLOR(1,1,0.25,1) ,default_size,"Create New World") : DrawText(240,239,GU_COLOR(1,1,1,1) ,default_size,"Create New World");
        }
        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            DrawText(240,29,GU_COLOR(1,1,1,1) ,default_size,"Sozdat$ nov@~ mir");
            DrawText(240,58,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Nazvanie Mira");
            DrawText(240,98,GU_COLOR(0.25,0.25,0.25,1) ,default_size,"Sid Mira");

            //draw subtitles on buttons
            if(gameMode == 0)
            {
                generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Igrovo~ rejim : V@jivanie") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Igrovo~ rejim : V@jivanie");
            }
            if(gameMode == 1)
            {
                generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Igrovo~ rejim : Tvoryeski~") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Igrovo~ rejim : Tvoryeski~");
            }
            if(gameMode == 2)
            {
                generateSelectPose == 2 ? DrawText(240,159,GU_COLOR(1,1,0.25,1) ,default_size,"Igrovo~ rejim : Hardkor") : DrawText(240,159,GU_COLOR(1,1,1,1) ,default_size,"Igrovo~ rejim : Hardkor");
            }

            if(worldType == 0)
            {
                generateSelectPose == 3 ? DrawText(240,199,GU_COLOR(1,1,0.25,1) ,default_size,"Tip mira : Standartn@~") : DrawText(240,199,GU_COLOR(1,1,1,1) ,default_size,"Tip mira : Standartn@~");
            }
            if(worldType == 1)
            {
                generateSelectPose == 3 ? DrawText(240,199,GU_COLOR(1,1,0.25,1) ,default_size,"Tip mira : Super-ploski~") : DrawText(240,199,GU_COLOR(1,1,1,1) ,default_size,"Tip mira : Super-ploski~");
            }

            generateSelectPose == 4 ? DrawText(240,239,GU_COLOR(1,1,0.25,1) ,default_size,"Sozdat$ nov@~ mir") : DrawText(240,239,GU_COLOR(1,1,1,1) ,default_size,"Sozdat$ nov@~ mir");
        }

        mRender->SetFont(ENGLISH);
        mRender->SetFontStyle(default_size ,GU_COLOR(1,1,1,1),0,0x00000000|0x00004000);
        mRender->DebugPrint(159,79,"%s",newWorldName.c_str());
        if(seed_1 == 0)
        {
            mRender->SetFontStyle(default_size ,GU_COLOR(0.65,0.65,0.65,1),999,0x00000200|0x00004000);
            if(mRender->GetFontLanguage() == ENGLISH)
            {
                mRender->DebugPrint(240,119,"random");
            }
            if(mRender->GetFontLanguage() == RUSSIAN)
            {
                mRender->DebugPrint(240,119,"sluya~n@~");
            }
        }
        else
        {
            mRender->DebugPrint(159,119,"%s",newWorldSeed.c_str());
        }
        mRender->SetDefaultFont();
    }
    break;
    case 10://New or load map
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

        buttonSprite->SetPosition(240,100);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,140);
        buttonSprite->Draw();

        sbuttonSprite->SetPosition(240,100+saveSubMenuSelect*40);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            DrawText(240,64,GU_COLOR(1,1,1,1) ,default_size,"Choose Game Mode");

            saveSubMenuSelect == 0 ? DrawText(240,109,GU_COLOR(1,1,0.25,1) ,default_size,"Survival") : DrawText(240,109,GU_COLOR(1,1,1,1) ,default_size,"Survival");
            saveSubMenuSelect == 1 ? DrawText(240,149,GU_COLOR(1,1,0.25,1) ,default_size,"Creative") : DrawText(240,149,GU_COLOR(1,1,1,1) ,default_size,"Creative");
        }
        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            DrawText(240,64,GU_COLOR(1,1,1,1) ,default_size,"V@berite Igrovo~ Rejim");

            saveSubMenuSelect == 0 ? DrawText(240,109,GU_COLOR(1,1,0.25,1) ,default_size,"V@jivanie") : DrawText(240,109,GU_COLOR(1,1,1,1) ,default_size,"V@jivanie");
            saveSubMenuSelect == 1 ? DrawText(240,149,GU_COLOR(1,1,0.25,1) ,default_size,"Tvoryeski~") : DrawText(240,149,GU_COLOR(1,1,1,1) ,default_size,"Tvoryeski~");
        }
    }
    break;
    case 11://textures
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
        if(texturePackList.size() > 0)
        {

        }

        for(int i = tpStart; i < tpMax; i++)
        {
            if(i < texturePackList.size())
            {
                sceGuEnable(GU_BLEND);

                rectFilledSprite->SetPosition(240,56 - 8 + (tpCurrent * 72) - (tpStart * 72));

                if(i == tpCurrent)
                {
                    rectFilledSprite->Draw();
                }

                rectEmptySprite->SetPosition(240,56 - 8 + (tpPos * 72) - (tpStart * 72));
                if(i == tpPos)
                {
                    sceGuBlendFunc(GU_ADD, GU_FIX,GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
                    rectEmptySprite->Draw();
                    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
                }

                Sprite* DrawSprite = texturePackList[i].packSprite;
                DrawSprite->SetPosition(46,56 - 8 + (i * 72) - (tpStart * 72));
                DrawSprite->ConstDraw();

                sceGuDisable(GU_BLEND);

                mRender->SetFont(ENGLISH);
                if(i == tpPos)
                {
                    mRender->SetFontStyle(default_big_size,GU_COLOR(0.25,0.25,0,1),0,0x00000000);
                    mRender->DebugPrint(94,52 - 8 + (i * 72) - (tpStart * 72),"%s",texturePackList[i].name.c_str());

                    mRender->SetFontStyle(default_big_size,GU_COLOR(1,1,0,1),0,0x00000000);
                    mRender->DebugPrint(92,50 - 8 + (i * 72) - (tpStart * 72),"%s",texturePackList[i].name.c_str());

                    mRender->SetFontStyle(default_size,GU_COLOR(0.5,0.5,0,1),0,0x00000000);
                    mRender->DebugPrint(92,50 - 8 + (i * 72) - (tpStart * 72) + 18,"%s",texturePackList[i].description.c_str());
                }
                else
                {
                    mRender->SetFontStyle(default_big_size,GU_COLOR(0.25,0.25,0.25,1),0,0x00000000);
                    mRender->DebugPrint(94,52 - 8 + (i * 72) - (tpStart * 72),"%s",texturePackList[i].name.c_str());

                    mRender->SetFontStyle(default_big_size,GU_COLOR(1,1,1,1),0,0x00000000);
                    mRender->DebugPrint(92,50 - 8 + (i * 72) - (tpStart * 72),"%s",texturePackList[i].name.c_str());

                    mRender->SetFontStyle(default_size,GU_COLOR(0.5,0.5,0.5,1),0,0x00000000);
                    mRender->DebugPrint(92,50 - 8 + (i * 72) - (tpStart * 72) + 18,"%s",texturePackList[i].description.c_str());
                }
                mRender->SetDefaultFont();
            }
        }



        buttonSprite->SetPosition(120,254);
        buttonSprite->Draw();

        buttonSprite->SetPosition(360,254);
        buttonSprite->Draw();


        sbuttonSprite->SetPosition(120+(tpSelectPos * 240),254);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(mRender->GetFontLanguage() == ENGLISH)
        {
            tpSelectPos == 0 ? DrawText(120,263,GU_COLOR(1,1,0.25,1),default_size,"Select") : DrawText(120,263,GU_COLOR(1,1,1,1),default_size,"Select");
            tpSelectPos == 1 ? DrawText(360,263,GU_COLOR(1,1,0.25,1) ,default_size,"Cancel") : DrawText(360,263,GU_COLOR(1,1,1,1) ,default_size,"Cancel");
        }
        if(mRender->GetFontLanguage() == RUSSIAN)
        {
            tpSelectPos == 0 ? DrawText(120,263,GU_COLOR(1,1,0.25,1),default_size,"V@brat$") : DrawText(120,263,GU_COLOR(1,1,1,1),default_size,"V@brat$");
            tpSelectPos == 1 ? DrawText(360,263,GU_COLOR(1,1,0.25,1) ,default_size,"Otmena") : DrawText(360,263,GU_COLOR(1,1,1,1) ,default_size,"Otmena");
        }
    }
    break;
    }

    //mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),0,0x00000000);
    //mRender->DebugPrint(30,50,"%f",size_f);

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
        if ( DirEntry->d_stat.st_attr & FIO_SO_IFREG) // we found file
        {
            SaveFile newSaveFile;
            std::string plik = dirName;
            plik += DirEntry->d_name;
            //dont load lmsc files
            size_t found = plik.find(".lmsc");
            size_t found2 = plik.find(".LMSc");
            if(found==std::string::npos && found2==std::string::npos)
            {
                newSaveFile.fileName = plik;
                saveFilesList.push_back(newSaveFile);
            }
        }
    }

    closedir(Dir);


    //now update all info in save files
    for(unsigned int i = 0; i < saveFilesList.size(); i++)
    {
        FILE * pFile;
        pFile = fopen(saveFilesList[i].fileName.c_str(),"rb");

        if(pFile != NULL)
        {
            //version
            fread(&saveFilesList[i].saveVersion,sizeof(int),1,pFile);

            fread(&saveFilesList[i].worldGameMode,sizeof(char),1,pFile);

            fread(&saveFilesList[i].locked,sizeof(bool),1,pFile);
            //name
            fread(saveFilesList[i].worldName,sizeof(char),50,pFile);

            if(saveFilesList[i].saveVersion >= 2)
                saveFilesList[i].compression = true;
            else
                saveFilesList[i].compression = false;

            fclose(pFile);
        }

        saveFilesList[i].saveSize = fileSize(saveFilesList[i].fileName+"c");
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

               /* if (newWorldName == "World")
                {
                    newWorldName += liczba;
                } */
            }
        }
    }
}

void StateMenu::ScanTexturePacks(const char* dirName)
{
    if(texturePackList.empty() != false)
    {
        TextureHelper::Instance()->RemoveConstTextures();
        for(int j = 0; j < texturePackList.size(); j++)
        {
            if (texturePackList[j].packSprite != NULL)
            {
                delete texturePackList[j].packSprite;
            }
        }
        texturePackList.clear();
    }
    texturePackList.clear();

    TextureManager::Instance()->LoadConstTexture("Assets/unknown_pack.png");

    int TPcheck = 0;

    DIR *dir = opendir(dirName);
    struct dirent *entry;

    while((entry = readdir(dir)) != NULL)
    {
        if (FIO_SO_ISDIR(entry->d_stat.st_attr))
        {
            std::string plik = "";
            plik += entry->d_name;

            size_t found = plik.find(".");
            size_t found2 = plik.find("..");
            size_t found3 = plik.find(".svn");

            if(found==std::string::npos && found2==std::string::npos && found3==std::string::npos)//не найдено
            {
                TP newTP;

                std::string plik2 = plik + "/";
                if(plik2 == TextureHelper::Instance()->defaultFolder)
                {
                    tpCurrent = TPcheck;
                }

                newTP.name = plik;

                texturePackList.push_back(newTP);
                TPcheck++;
            }
        }
    }

    closedir(dir);

    for(int j = 0; j < texturePackList.size(); j++)
    {
        std::string packPath = "Assets/Textures/"+texturePackList[j].name+"/pack.png";

        if(fileExists(packPath) == true) // if we have pack sprite
        {
            TextureManager::Instance()->LoadConstTexture(packPath);
            texturePackList[j].packSprite = new Sprite(TextureManager::Instance()->GetConstTextureNumber(packPath),true);
        }
        else
        {
            texturePackList[j].packSprite = new Sprite(TextureManager::Instance()->GetConstTextureNumber("Assets/unknown_pack.png"),true);
        }

        std::string packDescriptionPath = "Assets/Textures/"+texturePackList[j].name+"/pack.txt";

        if(fileExists(packDescriptionPath) == true) // if we have pack description file
        {
            std::string str;
            std::string file_contents;

            std::ifstream file(packDescriptionPath.c_str());

            if (file.is_open())
            {
                while (std::getline(file, str))
                {
                    file_contents += str;
                    file_contents.push_back('\n');
                }
            }

            file.close();
            texturePackList[j].description = file_contents;
        }
    }
}

/*
    texturePackList.clear();

	FILE *infile;
	char textLine[80];
	char textPack[80];

	infile = fopen("Assets/texturePacks.txt","rt");

	 while(fgets(textLine, 80, infile) != NULL)
	 {
		 sscanf(textLine,"%s",textPack);
		 std::string texturePack = textPack;

		 size_t found = texturePack.find(".tp");
		 size_t found2 = texturePack.find(".TP");
		 if(found != std::string::npos || found2 != std::string::npos)// found
		 {
		 	texturePackList.push_back(texturePack);
		 }
	 }
	 fclose(infile);

*/

inline bool StateMenu::fileExists (const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

unsigned int StateMenu::hash(const char* s, unsigned int seed)
{
    unsigned int hash = seed;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
    return hash;
}

int StateMenu::fileSize (const std::string& name)
{
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? (int)stat_buf.st_size : -1;
}

void StateMenu::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    mRender->SetFontStyle(size,color,0,0x00000200|0x00000000);
    mRender->DebugPrint(x,y,message);
}
