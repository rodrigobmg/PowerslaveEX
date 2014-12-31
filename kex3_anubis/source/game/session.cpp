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
// DESCRIPTION:
//      Game session
//

#include "kexlib.h"
#include "renderMain.h"

static kexSession sessionLocal;
kexSession *kex::cSession = &sessionLocal;

kexCvar cvarClientFPS("cl_maxfps", CVF_INT|CVF_CONFIG, "60", 1, 60, "Game render FPS");

//
// pausegame
//

COMMAND(pausegame)
{
    if(kex::cCommands->GetArgc() < 1)
    {
        return;
    }

    sessionLocal.TogglePause(sessionLocal.IsPaused() ^ 1);
}

//
// kexSession::kexSession
//

kexSession::kexSession(void)
{
    this->gameTimeMS    = 0;
    this->fps           = 0;
    this->time          = 0;
    this->curtime       = 0;
    this->deltaTime     = 0;
    this->ticks         = 0;
    this->bPaused       = false;
}

//
// kexSession::~kexSession
//

kexSession::~kexSession(void)
{
}

//
// kexSession::ProcessEvents
//

void kexSession::ProcessEvents(void)
{
    inputEvent_t *ev;

    kex::cInput->PollInput();

    while((ev = eventQueue.Pop()) != NULL)
    {
        if(kex::cConsole->ProcessInput(ev))
        {
            continue;
        }
    }
}

//
// kexSession::DrawFrame
//

void kexSession::DrawFrame(void)
{
    kexRender::cBackend->ClearBuffer();
    
    kex::cConsole->Draw();
    kexRender::cBackend->SwapBuffers();
}

//
// kexSession::RunGame
//

void kexSession::RunGame(void)
{
    int msec;
    int prevmsec;
    int nextmsec;

    prevmsec = kex::cTimer->GetMS();

    while(1)
    {
        do
        {
            nextmsec = kex::cTimer->GetMS();
            msec = nextmsec - prevmsec;
        }
        while(msec < 1);

        curtime += msec;

        if(curtime >= (int)kexMath::FrameSec(cvarClientFPS.GetInt()))
        {
            deltaTime = kexMath::MSec2Sec(curtime);
            kexMath::Clamp(deltaTime, 0.0f, 1.0f);

            fps = (int)kexMath::FrameSec(kexMath::Sec2MSec(deltaTime));

            time += curtime;
            curtime = 0;

            // check for new inputs
            ProcessEvents();
            
            kex::cConsole->Tick();

            // draw scene
            DrawFrame();

            // update ticks
            UpdateTicks();
        }

        prevmsec = nextmsec;
        Mem_GC();
    }
}
