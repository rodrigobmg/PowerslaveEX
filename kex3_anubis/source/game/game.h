//
// Copyright(C) 2014-2015 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

#ifndef __GAME_H__
#define __GAME_H__

class kexFont;
class kexTitleScreen;
class kexTranslation;
class kexWorld;
class kexPlayer;
class kexRenderView;

typedef enum
{
    IA_ATTACK   = 0,
    IA_JUMP,
    IA_FORWARD,
    IA_BACKWARD,
    IA_LEFT,
    IA_RIGHT,
    IA_STRAFELEFT,
    IA_STRAFERIGHT,
    IA_WEAPNEXT,
    IA_WEAPPREV,
    
    NUMINPUTACTIONS
} inputActions_t;

typedef enum
{
    GS_NONE     = 0,
    GS_TITLE,
    GS_LEVEL,
    NUMGAMESTATES
} gameState_t;

class kexGameLoop
{
public:
    virtual void        Init(void) {};
    virtual void        Start(void) {};
    virtual void        Stop(void) {};
    virtual void        Draw(void) {};
    virtual void        Tick(void) {};
    virtual bool        ProcessInput(inputEvent_t *ev) { return false; }
};

class kexGame
{
public:
    kexGame(void);
    ~kexGame(void);

    void                Init(void);
    void                Shutdown(void);
    void                Tick(void);
    void                Draw(void);
    bool                ProcessInput(inputEvent_t *ev);

    kexTitleScreen      *TitleScreen(void) { return titleScreen; }
    kexTranslation      *Translation(void) { return translation; }
    kexWorld            *World(void) { return world; }
    kexRenderView       *RenderView(void) { return renderView; }
    kexFont             *SmallFont(void) { return smallFont; }
    kexFont             *BigFont(void) { return bigFont; }
    const int           GetTicks(void) const { return ticks; }
    const gameState_t   GameState(void) const { return gameState; }
    void                SetGameState(const gameState_t state) { pendingGameState = state; }
    kexPlayer           *Player(void) { return player; }

    void                DrawSmallString(const char *string, float x, float y, float scale, bool center,
                                        byte r = 0xff, byte g = 0xff, byte b = 0xff);
    void                DrawBigString(const char *string, float x, float y, float scale, bool center,
                                        byte r = 0xff, byte g = 0xff, byte b = 0xff);

private:
    kexFont             *smallFont;
    kexFont             *bigFont;
    kexTitleScreen      *titleScreen;
    kexTranslation      *translation;
    kexWorld            *world;
    int                 ticks;
    gameState_t         gameState;
    gameState_t         pendingGameState;
    kexPlayer           *player;
    kexRenderView       *renderView;
    kexGameLoop         gameLoopStub;
    kexGameLoop         *gameLoop;
};

#endif