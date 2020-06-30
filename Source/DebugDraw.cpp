#include "DebugDraw.h"
#include "Link.h"

namespace GameDev2D
{
    DebugDraw::DebugDraw(Link* link)
    {
        //Initialize the Link pointer
        m_Link = link;

        //Initialize the debug state
        m_DebugState = DebugDraw_Nothing;

        //Create the debug textures
        PixelFormat pixelFormat = PixelFormat(PixelFormat::RGBA, PixelFormat::UnsignedByte);
        ImageData imageData(pixelFormat, GetScreenWidth(), GetScreenHeight());
        for (int i = 0; i < DebugDraw_Count; i++)
        {
            m_DebugCanvas[i] = new Texture(imageData);
        }

        //Load the Fonts
        LoadFont("OpenSans-CondBold_32");
        LoadFont("OpenSans-CondBold_22");

        //Create the index Label objects
        SpriteFont* indexFont = new SpriteFont("OpenSans-CondBold_32");
        indexFont->SetAnchor(Vector2(0.5f, 0.5f));

        //Create the coordinates Label objects
        SpriteFont* coordinatesFont = new SpriteFont("OpenSans-CondBold_22");
        coordinatesFont->SetAnchor(Vector2(0.5f, 0.5f));

        //Create the render target for the first debug canvas and beging drawing
        RenderTarget* renderTarget = new RenderTarget(m_DebugCanvas[0]);
        renderTarget->Begin();

        //Cycle through and draw the tile's bounding box to the debug canvas
        for (int i = 0; i < NUM_TILES; i++)
        {
            int column = GetColumn(i);
            int row = GetRow(i);
            float x = column * TILE_SIZE;
            float y = row * TILE_SIZE;

            Services::GetGraphics()->DrawRectangle(Vector2(x, y), Vector2(TILE_SIZE, TILE_SIZE), Rotation::Radians(0.0f), Vector2::Zero, Color::WhiteColor(), false);
        }

        //End drawing to the RenderTarget
        renderTarget->End();

        //Delete the RenderTarget
        delete renderTarget;

        //Create the render target for the second debug canvas and beging drawing
        renderTarget = new RenderTarget(m_DebugCanvas[1]);
        renderTarget->Begin();

        //Cycle through and draw the tile's index to the debug canvas
        for (int i = 0; i < NUM_TILES; i++)
        {
            int column = GetColumn(i);
            int row = GetRow(i);
            float x = column * TILE_SIZE + TILE_SIZE * 0.5f;
            float y = row * TILE_SIZE + TILE_SIZE * 0.5f;

            indexFont->SetText(to_string(i));
            indexFont->SetPosition(Vector2(x, y));
            indexFont->Draw();

            Services::GetGraphics()->DrawRectangle(Vector2(x, y), Vector2(TILE_SIZE, TILE_SIZE), Rotation::Radians(0.0f), Vector2(0.5f, 0.5f), Color::WhiteColor(), false);
        }

        //End drawing to the RenderTarget
        renderTarget->End();

        //Delete the RenderTarget
        delete renderTarget;

        //Create a new RenderTarget object for the third debug canvas and begin drawing
        renderTarget = new RenderTarget(m_DebugCanvas[2]);
        renderTarget->Begin();

        //Cycle through and draw the tile's coordinates to the debug canvas
        for (int i = 0; i < NUM_TILES; i++)
        {
            int column = GetColumn(i);
            int row = GetRow(i);
            float x = column * TILE_SIZE + TILE_SIZE * 0.5f;
            float y = row * TILE_SIZE + TILE_SIZE * 0.5f;

            std::string text = "(" + to_string(row) + "," + to_string(column) + ")";
            coordinatesFont->SetText(text);
            coordinatesFont->SetPosition(Vector2(x, y));
            coordinatesFont->Draw();

            Services::GetGraphics()->DrawRectangle(Vector2(x, y), Vector2(TILE_SIZE, TILE_SIZE), Rotation::Radians(0.0f), Vector2(0.5f, 0.5f), Color::WhiteColor(), false);
        }

        //End drawing to the RenderTarget
        renderTarget->End();

        //Delete the RenderTarget object
        SafeDelete(renderTarget);

        //Delete the Label objects
        SafeDelete(indexFont);
        SafeDelete(coordinatesFont);

        //Unload the Fonts
        UnloadFont("OpenSans-CondBold_32");
        UnloadFont("OpenSans-CondBold_22");

    }

    DebugDraw::~DebugDraw()
    {
        for (int i = 0; i < DebugDraw_Count; i++)
        {
            SafeDelete(m_DebugCanvas[i]);
        }
    }

    void DebugDraw::Draw()
    {
        if (m_DebugState != DebugDraw_Nothing)
        {
			Vector2 cameraPosition = Services::GetGraphics()->GetActiveCamera()->GetPosition();
			Vector2 halfScreenSize = Vector2(GetScreenWidth(), GetScreenHeight()) * 0.5f;
			Services::GetGraphics()->GetActiveCamera()->SetPosition(halfScreenSize);

            //Draw the correct debug canvas
            Services::GetGraphics()->DrawTexture(m_DebugCanvas[m_DebugState], Vector2::Zero, Rotation::Radians(0.0f));

			Services::GetGraphics()->GetActiveCamera()->SetPosition(cameraPosition);

            //Draw which Tile Link is in
            int column = m_Link->GetPosition().x / TILE_SIZE;
            int row = m_Link->GetPosition().y / TILE_SIZE;
            float x = column * TILE_SIZE;
            float y = row * TILE_SIZE;
            Services::GetGraphics()->DrawRectangle(Vector2(x, y), Vector2(TILE_SIZE, TILE_SIZE), Rotation::Radians(0.0f), Vector2::Zero, Color::RedColor(), false);
        }
    }

    void DebugDraw::ToggleState()
    {
        int state = m_DebugState;
        state++;
        if (state >= DebugDraw_Count)
        {
            state = DebugDraw_Nothing;
        }

        m_DebugState = (DebugDrawState)state;
    }

    int DebugDraw::GetRow(int aIndex)
    {
        int row = aIndex / NUM_COLUMNS;
        return row;
    }

    int DebugDraw::GetColumn(int aIndex)
    {
        int column = aIndex % NUM_COLUMNS;
        return column;
    }
}