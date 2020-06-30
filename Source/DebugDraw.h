#pragma once

#include <GameDev2D.h>
#include "Constants.h"


namespace GameDev2D
{
    class Link;

    class DebugDraw
    {
    public:
        DebugDraw(Link* link);
        ~DebugDraw();

        void Draw();

        void ToggleState();

        int GetRow(int index);
        int GetColumn(int index);

    private:
        Link* m_Link;
        Texture* m_DebugCanvas[DebugDraw_Count];
        DebugDrawState m_DebugState;
    };
}