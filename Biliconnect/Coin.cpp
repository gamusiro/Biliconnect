#include "Stage.h"
#include "Block.h"
#include "Coin.h"
#include "SEManager.h"

using namespace math;

Coin::Coin(BLOCKTYPE type, math::Float2 pos, int number)
	: Block(type, pos, math::Float2(140,140)), trigger(false), m_Number(number)
{
	int stagenum = StageNum::Get() % 10;

	if(number != 1 && number != 2)
	isCoin = true;

	// ‰Šú‰»
	if (m_Type == BLOCKTYPE::ITEM && number == 1)
		m_Tex.Create("File/file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 0)
		m_Tex.Create("File/book_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 1)
		m_Tex.Create("File/cloud_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 2)
		m_Tex.Create("File/document_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 3)
		m_Tex.Create("File/download_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 4)
		m_Tex.Create("File/game_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 5)
		m_Tex.Create("File/movie_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 6)
		m_Tex.Create("File/music_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 7)
		m_Tex.Create("File/picture_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 8)
		m_Tex.Create("File/screen_file_icon.png", 1, 1);
	else if (m_Type == BLOCKTYPE::ITEM && number == 2 && stagenum == 9)
		m_Tex.Create("File/zip_file_icon.png", 1, 1);
	m_Color = { 1,1,1,1 };

	m_Type = BLOCKTYPE::ITEM;
}

void Coin::Update()
{
	//m_Tex.Update();

	if (trigger)
	{
		m_Color.x -= 0.01f;
		m_Color.y -= 0.01f;
		m_Color.z -= 0.01f;
	}
	else
	{
		m_Color.x += 0.01f;
		m_Color.y += 0.01f;
		m_Color.z += 0.01f;
	}

	if (m_Color.x > 1)
		trigger = true;
	if (m_Color.x <= 0.7f)
		trigger = false;
}

void Coin::CollisionAction()
{

	m_Color = { 0,0,0,0 };

	if (m_Number != 1 && m_Number != 2)
		SEManager::Play(SOUND::LIFE);
	else
		SEManager::Play(SOUND::ITEM);

	if(m_Number == 1)
		coinnum += 1;
	else if (m_Number == 2)
		coinnum += 2;

}
