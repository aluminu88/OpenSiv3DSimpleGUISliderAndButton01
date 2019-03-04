
# include <Siv3D.hpp> // OpenSiv3D v0.3.1

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(20);

	const Texture textureCat(Emoji(U"🐈"), TextureDesc::Mipped);




	//GUI用変数
	double block_w = 100.0, block_h = 100.0,block_r = 0.0, block_rp = 0.0, block_vx = 0.0, block_vy = 0.0;
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

	int rad = 0, block_x = 80, block_y = 100;


	while (System::Update())
	{
		
		//デバック用

		font(Cursor::Pos()).draw(20, 560, ColorF(0.6));

		textureCat.resized(80).draw(700, 500);

		//vx,vyの有効状態（どちらか一方しか0以外の値をとれない）
		if ((int)block_vx == 0)c_vy = true;
		else c_vy = false;
		if ((int)block_vy == 0)c_vx = true;
		else c_vx = false;


		//角度計算

		rad += (int)block_rp;

		if (rad >= 360)
		{
			rad = rad - 720;

		}
		else if (rad < -360)
		{
			rad = rad + 720;
		}

		if (block_rp != 0)
		{
			block_r = rad;
		}
		else rad = block_r;


		//移動計算
		if (block_vx != 0) block_x += block_vx;
		else if (block_vy != 0)block_y += block_vy;

		//画面外に出たら戻るだけ
		if (!RectF(block_x, block_y, block_w, block_h).rotated(ToRadians(block_r)).intersects(Rect(Window::Size()))) 
		{
			block_x = 80, block_y = 100;
		}

		//表示用ブロック
		RectF(block_x, block_y, block_w, block_h).rotated(ToRadians(block_r)).draw(Palette::White);
	

		BlockGUIheader.pos = BlockGUIBox.pos;

		if (objectoptions[objectIndex] == U"Block")
		{
			BlockGUIBox.x = 400;
		}
		else if(objectoptions[objectIndex] == U"None")
		{
			BlockGUIBox.x = 2000;
		}

		BlockGUIBox.draw(Palette::Silver);
		BlockGUIheader.draw(Palette::White);
		datafont(U"BlockGUI").drawAt(BlockGUIheader.center(), Palette::Black);


		//GUIレイアウト＆処理


		//ラジオボタン
		itemfont(U"Object:").draw(402, 60, Palette::Black);
		SimpleGUI::RadioButtons(objectIndex, objectoptions, Vec2(400, 90), 100);


		//Rectの要素を決定するスライダーとボタン

		//１つの値のためのGUI------------------------------------------------------------

		itemfont(U"width:").draw(BlockGUIBox.pos + Vec2(2, 40), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 40), 20))
		{
			block_w--;
		}
		SimpleGUI::Slider(block_w, 0, 250, BlockGUIBox.pos + Vec2(90, 40), 200);//幅
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 40), 20))
		{
			block_w++;
		}
		datafont((int)block_w).draw(BlockGUIBox.pos + Vec2(320, 40), Palette::Black);
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 40), 20))
		{
			block_w = 0;
		}
		
		//ここまで----------------------------------------------------------------------




		itemfont(U"height:").draw(BlockGUIBox.pos + Vec2(2, 80), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 80), 20))
		{
			block_h--;
		}
		SimpleGUI::Slider(block_h, 0, 250, BlockGUIBox.pos + Vec2(90, 80), 200);//高さ
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
			block_r -= 1;
		}
		SimpleGUI::Slider(block_r, -360, 360, BlockGUIBox.pos + Vec2(90, 120), 200);//角度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 120), 20))
		{
			block_r += 1;
		}
		datafont(U"{:.0f}"_fmt(block_r)).draw(BlockGUIBox.pos + Vec2(320, 120), Palette::Black);//値の見え方、小数点以下なし
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 120), 20))
		{
			block_r = 0;
		}
		//intにキャストして代入して補正
		block_r = (int)block_r;
		

		itemfont(U"radplus:").draw(BlockGUIBox.pos + Vec2(2, 160), Palette::Black);
		if (SimpleGUI::Button(U"-", BlockGUIBox.pos + Vec2(65, 160), 20))
		{
			block_rp -= 1;
		}
		SimpleGUI::Slider(block_rp, -360, 360, BlockGUIBox.pos + Vec2(90, 160), 200);//角速度
		if (SimpleGUI::Button(U"+", BlockGUIBox.pos + Vec2(295, 160), 20))
		{
			block_rp += 1;
		}
		datafont(U"{:.0f}"_fmt(block_rp)).draw(BlockGUIBox.pos + Vec2(320, 160), Palette::Black);//値の見え方、小数点以下なし
		if (SimpleGUI::Button(U"0", BlockGUIBox.pos + Vec2(365, 160), 20))
		{
			block_rp = 0;
		}
		//intにキャストして代入して補正
		block_rp = (int)block_rp;


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
		block_vx = (int)block_vx;

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
		block_vy = (int)block_vy;
		
		if (SimpleGUI::Button(U"reset", BlockGUIBox.pos + Vec2(150, 300), 100))
		{
			block_x = 80, block_y = 100, block_h = 100, block_w = 100, block_r = 0, block_rp = 0, block_vx = 0, block_vy = 0;
		}

		



	/*	if (BlockGUIheader.leftClicked()) {
				BlockGUIgrabbed = true;
			}
			else if (MouseL.up()) {
				BlockGUIgrabbed = false;
			}
			else if (BlockGUIgrabbed) {
				BlockGUIBox.pos += Cursor::DeltaF();
				BlockGUIheader.pos = BlockGUIBox.pos;
			}*/


	}
}
