#pragma once

#include <GameDev2D.h>
#include "Link.h"
#include "DebugDraw.h"
#include "Region.h"
#include "Cave.h"
#include "HeadsUpDisplay.h"
#include "SoundManager.h"


namespace GameDev2D
{
    class Game
    {
    public:
        Game();
        ~Game();

        void Update(double delta);
        void Draw();

        void HandleLeftMouseClick(float mouseX, float mouseY);
        void HandleRightMouseClick(float mouseX, float mouseY);
        void HandleMouseMoved(float mouseX, float mouseY, float previousX, float previousY);

        void HandleKeyPress(Keyboard::Key key);

        void Load();
        bool IsLoading();

		void CheckRegionTrees();

		bool IsWon();
		void SetIsWon(bool isWon);

		LinkSoundManager* GetSoundManager();

		Region* GetRegion(const Vector2& position);
		void ShiftCamera(Region* region);

		void SetState(GameState state);

    private:
        //Member variables should go here
        Link* m_Link;
		HeadsUpDisplay* m_HeadsUpDisplay;
		LinkSoundManager* m_SoundManager;
		Region* m_Regions[NUM_REGIONS];
		Region* m_ActiveRegion;
		Region* m_TransitionRegion;
        DebugDraw* m_DebugDraw;
		Timer m_CameraTimer;
		GameState m_GameState;
        LoadStep m_LoadStep;

		Polygon* m_EndFade;

		bool m_IsWon;

		Cave* m_Cave;
    };
}