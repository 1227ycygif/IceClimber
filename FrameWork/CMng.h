class CMng
{
public:
	CMng();
	~CMng();

	Chap *chap[TOTALCHAP];
	int n_Chap;

	HWND hWnd;
	HINSTANCE hInstance;
};

extern CMng g_Mng;