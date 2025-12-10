#pragma once

#include "Include.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	map.Init();
	mapManager.Init();
	sound.Init();
	sql.Init();
}

void Game::Draw()
{
	map.Draw();
	mapManager.Draw();
	sql.Draw();
}

void Game::Update(double frame)
{
	Gmanager.Update();
	mapManager.Collision();
	mapManager.Update();
	map.Update(frame);
	sql.Update(frame);
}

void Game::OnMessage(MSG* msg)
{

}