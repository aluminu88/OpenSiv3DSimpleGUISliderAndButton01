
# include <Siv3D.hpp> // OpenSiv3D v0.3.1

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(20);

	const Texture textureCat(Emoji(U"🐈"), TextureDesc::Mipped);




	//GUI用変数
	double block_w = 0.0, block_h = 0.0, block_r = 0.0, block_rp = 0.0, block_vx = 0.0, block_vy = 0.0;
	bool c_vx = true, c_vy = true;

	//フォント
	Font datafont{ 20 }, itemfont{ 15 };

	//GUI用ウィンドウ
	RectF BlockGUIBox = RectF(2000, 250, 400, 450);//{800,250}が定位置
	RectF BlockGUIheader = RectF(2000, 250, 400, 30);

	bool BlockGUIgrabbed = false;

	//登場させるウィンドウの種類
	const Array<String> objectoptions =
	{
		U"None",U"Block"
	};

	size_t objectIndex = 0;

	while (System::Update())
	{
		
		//デバック用

		font(Cursor::Pos()).draw(20, 560, ColorF(0.6));

		textureCat.resized(80).draw(700, 500);

		if ((int)block_vx == 0)c_vy = true;
		else c_vy = false;
		if ((int)block_vy == 0)c_vx = true;
		else c_vx = false;

		BlockGUIheader.pos = BlockGUIBox.pos;

		if (objectoptions[objectIndex] == U"Block")
		{
			BlockGUIBox.x = 400;
		}
		else if(U"None")
		{
			BlockGUIBox.x = 2000;
		}

		BlockGUIBox.draw(Palette::Silver);
		BlockGUIheader.draw(Palette::White);
		datafont(U"BlockGUI").drawAt(BlockGUIheader.center(), Palette::Black);


		//GUIレイアウト

		itemfont(U"Object:").draw(402, 60, Palette::Black);
		SimpleGUI::RadioButtons(objectIndex, objectoptions, Vec2(400, 90), 100);


		itemfont(U"width:").draw(BlockGUIBox.pos + Vec2(2, 40), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 40), 20))
		{
			block_w--;
		}
		SimpleGUI::Slider(block_w, 0, 500, BlockGUIBox.pos + Vec2(90, 40), 200);//幅
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 40), 20))
		{
			block_w++;
		}
		datafont((int)block_w).draw(BlockGUIBox.pos + Vec2(320, 40), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 40), 20))
		{
			block_w = 0;
		}


		itemfont(U"height:").draw(BlockGUIBox.pos + Vec2(2, 80), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 80), 20))
		{
			block_h--;
		}
		SimpleGUI::Slider(block_h, 0, 500, BlockGUIBox.pos + Vec2(90, 80), 200);//高さ
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 80), 20))
		{
			block_h++;
		}
		datafont((int)block_h).draw(BlockGUIBox.pos + Vec2(320, 80), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 80), 20))
		{
			block_h = 0;
		}


		itemfont(U"rad:").draw(BlockGUIBox.pos + Vec2(2, 120), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 120), 20))
		{
			block_r -= 0.01;
		}
		SimpleGUI::Slider(block_r, -3.14, 3.14, BlockGUIBox.pos + Vec2(90, 120), 200);//角度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 120), 20))
		{
			block_r += 0.01;
		}
		datafont((int)(block_r * 180 / Math::Pi)).draw(BlockGUIBox.pos + Vec2(320, 120), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 120), 20))
		{
			block_r = 0.00;
		}


		itemfont(U"radplus:").draw(BlockGUIBox.pos + Vec2(2, 160), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 160), 20))
		{
			block_rp -= 0.01;
		}
		SimpleGUI::Slider(block_rp, -3.14, 3.14, BlockGUIBox.pos + Vec2(90, 160), 200);//角速度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 160), 20))
		{
			block_rp += 0.01;
		}
		datafont((int)(block_rp * 180 / Math::Pi)).draw(BlockGUIBox.pos + Vec2(320, 160), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 160), 20))
		{
			block_rp = 0.0;
		}


		itemfont(U"vx:").draw(BlockGUIBox.pos + Vec2(2, 200), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 200), 20, c_vx))
		{
			block_vx--;
		}
		SimpleGUI::Slider(block_vx, -10, 10, BlockGUIBox.pos + Vec2(90, 200), 200, c_vx);//x速度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 200), 20))
		{
			block_vx++;
		}
		datafont((int)block_vx).draw(BlockGUIBox.pos + Vec2(320, 200), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 200), 20, c_vx))
		{
			block_vx = 0;
		}

		itemfont(U"vy:").draw(BlockGUIBox.pos + Vec2(2, 240), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 240), 20, c_vy))
		{
			block_vy--;
		}
		SimpleGUI::Slider(block_vy, -10, 10, BlockGUIBox.pos + Vec2(90, 240), 200, c_vy);//x速度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 240), 20, c_vy))
		{
			block_vy++;
		}
		datafont((int)block_vy).draw(BlockGUIBox.pos + Vec2(320, 240), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 240), 20, c_vy))
		{
			block_vy = 0;
		}
		

		RectF(100, 100, block_w, block_h).rotated(block_r).draw(Palette::White);

	}
}
