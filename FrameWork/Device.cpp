#pragma once
#include "Include.h"

bool Device::Create(IDirect3DDevice9* Device)
{
    Device9 = Device;

    D3DXCreateSprite(Device9, &Sprite);

    ZeroMemory(&fdesc, sizeof(fdesc));
    fdesc.Height = 25;
    fdesc.Width = 12;
    fdesc.Weight = 500;
    fdesc.Italic = FALSE;
    fdesc.CharSet = DEFAULT_CHARSET;

    // 글꼴 설정 ("돋움")
    _tcscpy_s(fdesc.FaceName, _T("돋움"));

    D3DXCreateFontIndirect(Device9, &fdesc, &Fonts);

    return true;
}

bool Device::DrawString(const TCHAR* msg, int x, int y, D3DCOLOR color)
{
    RECT rect = { x, y, x + (int)_tcslen(msg) * fdesc.Width, y + fdesc.Height };

    Sprite->Begin(D3DXSPRITE_ALPHABLEND);
    Fonts->DrawText(Sprite, msg, -1, &rect, DT_NOCLIP, color);
    Sprite->End();

    return true;
}