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

#ifndef __SESSION_H__
#define __SESSION_H__

class kexTexture;

class kexSession
{
public:
    kexSession(void);
    ~kexSession(void);

    void                        RunGame(void);

    const bool                  IsPaused(void) const { return bPaused; }
    void                        TogglePause(const bool bToggle) { bPaused = bToggle; }
    const int                   GetTime(void) const { return time; }
    const float                 GetDeltaTime(void) const { return deltaTime; }
    const int                   GetTicks(void) const { return ticks; }
    const int                   GetFPS(void) const { return fps; }
    void                        UpdateTicks(void) { ticks++; }
    kexQueue<inputEvent_t>      &EventQueue(void) { return eventQueue; }
    const bool                  CursorVisible(void) const { return bShowCursor; }
    void                        ToggleCursor(const bool b) { bShowCursor = b; }

private:
    void                        ProcessEvents(void);
    void                        DrawFrame(void);
    void                        RunFrame(void);
    void                        InitCursor(void);
    void                        DrawCursor(void);

    uint64_t                    gameTimeMS;

    int                         fps;
    int                         time;
    int                         curtime;
    float                       deltaTime;
    int                         ticks;
    bool                        bPaused;
    bool                        bShowCursor;
    kexTexture                  *cursorTexture;

    kexQueue<inputEvent_t>      eventQueue;
};

#endif
