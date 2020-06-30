#include "HeadsUpDisplay.h"
#include "Link.h"


namespace GameDev2D
{
	HeadsUpDisplay::HeadsUpDisplay(Link* link)
	{
		m_Background = new Polygon();
		m_Background->MakeRectangle(1024.0f, 128.0f, true);
		m_Background->SetColor(Color::BlackColor());
		m_Background->SetPosition(Vector2(0.0f, 704.0f));

		m_WoodSword = new SpriteAtlas("Tileset");
		m_WoodSword->UseFrame("HUD-Sword-Wooden");
		m_WoodSword->SetAnchor(Vector2(0.5f, 0.0f));
		m_WoodSword->SetPosition(Vector2(532.0f, 740.0f));

		m_Shield = new SpriteAtlas("Tileset");
		m_Shield->UseFrame("HUD-Shield");
		m_Shield->SetAnchor(Vector2(0.5f, 0.0f));
		m_Shield->SetPosition(Vector2(592.0f, 740.0f));

		m_OldLetter = new SpriteAtlas("Tileset");
		m_OldLetter->UseFrame("Letter");
		m_OldLetter->SetAnchor(Vector2(0.5f, 0.0f));
		m_OldLetter->SetPosition(Vector2(310.0f, 716.0f));

		m_Bracelet = new SpriteAtlas("Tileset");
		m_Bracelet->UseFrame("PowerBracelet");
		m_Bracelet->SetAnchor(Vector2(0.5f, 0.0f));
		m_Bracelet->SetPosition(Vector2(250.0f, 716.0f));

		m_Candle = new SpriteAtlas("Tileset");
		m_Candle->UseFrame("Candle-Red");
		m_Candle->SetAnchor(Vector2(0.5f, 0.0f));
		m_Candle->SetPosition(Vector2(300.0f, 716.0f));

		m_Bombs = new SpriteAtlas("Tileset");
		m_Bombs->UseFrame("HUD-Bombs");
		m_Bombs->SetAnchor(Vector2(0.5f, 0.0f));
		m_Bombs->SetPosition(Vector2(376.0f, 716.0f));

		LoadFont("slkscr_32");
		m_BombsLabel = new SpriteFont("slkscr_32");
		m_BombsLabel->SetColor(Color::WhiteColor());
		m_BombsLabel->SetAnchor(Vector2(0.0f, 0.0f));
		m_BombsLabel->SetPosition(Vector2(404.0f, 716.0f));
		m_BombsLabel->SetText("x0");

		m_StartPosheart = Vector2(650.0f, 750.0f);

		m_EmptyHeart = new SpriteAtlas("Tileset");
		m_EmptyHeart->UseFrame("HUD-Heart-Empty");
		m_EmptyHeart->SetAnchor(Vector2(0.5f, 0.0f));
		m_EmptyHeart->SetPosition(m_StartPosheart);

		m_FullHeart = new SpriteAtlas("Tileset");
		m_FullHeart->UseFrame("HUD-Heart-Full");
		m_FullHeart->SetAnchor(Vector2(0.5f, 0.0f));
		m_FullHeart->SetPosition(m_StartPosheart);

		m_HalfHeart = new SpriteAtlas("Tileset");
		m_HalfHeart->UseFrame("HUD-Heart-Half");
		m_HalfHeart->SetAnchor(Vector2(0.5f, 0.0f));
		m_HalfHeart->SetPosition(m_StartPosheart);

		m_Link = link;
	}

	HeadsUpDisplay::~HeadsUpDisplay()
	{
		SafeDelete(m_Background);
		SafeDelete(m_WoodSword);
		SafeDelete(m_Shield);
		SafeDelete(m_OldLetter);
		SafeDelete(m_Bombs);
		SafeDelete(m_BombsLabel);
		UnloadFont("slkscr_32");
	}

	void HeadsUpDisplay::Draw()
	{
		Vector2 cameraPosition = Services::GetGraphics()->GetActiveCamera()->GetPosition();
		Vector2 halfScreenPosition = Vector2(GetScreenWidth(), GetScreenHeight()) * 0.5f;
		Services::GetGraphics()->GetActiveCamera()->SetPosition(halfScreenPosition);

		m_Background->Draw();
		m_Shield->Draw();

		//Does link have the sword?
		if (m_Link->HasSword() == true)
		{
			m_WoodSword->Draw();
		}

		//Does link has the old letter?
		if (m_Link->HasOldLetter() == true)
		{
			m_OldLetter->Draw();
		}

		//Does link has the candle?
		if (m_Link->HasCandle() == true)
		{
			m_Candle->Draw();
		}

		//Does link has the bracelet?
		if (m_Link->HasBracelet() == true)
		{
			m_Bracelet->Draw();
		}

		//Draw the Bombs Label
		std::string bombs = "x" + to_string(m_Link->GetBombCount());
		m_BombsLabel->SetText(bombs);
		m_BombsLabel->Draw();

		//Draw the Bombs sprite
		m_Bombs->Draw();

		//Draw Life
		for (int i= 0; i<LINK_INITIAL_HEALTH; i++)
		{
			if (i%2 == 0)
			{
				if (i != 0)
				{
					m_EmptyHeart->Translate(Vector2(1.5 * m_EmptyHeart->GetWidth(), 0.0f));
				}
				m_EmptyHeart->Draw();
			}
		}
		m_EmptyHeart->SetPosition(m_StartPosheart);
		for (int i = 0; i<m_Link->GetCurentHealth(); i++)
		{
			if (i%2 == 0)
			{
				if (i != 0)
				{
					m_HalfHeart->Translate(Vector2(1.5 * m_EmptyHeart->GetWidth(), 0.0f));
					m_FullHeart->Translate(Vector2(1.5 * m_EmptyHeart->GetWidth(), 0.0f));
				}
				m_FullHeart->Draw();
			}
			if (m_Link->GetCurentHealth() % 2 == 1 && i== m_Link->GetCurentHealth()-1)
			{
				m_HalfHeart->Draw();
			}
		}
		m_FullHeart->SetPosition(m_StartPosheart);
		m_HalfHeart->SetPosition(m_StartPosheart);

		Services::GetGraphics()->GetActiveCamera()->SetPosition(cameraPosition);
	}
}