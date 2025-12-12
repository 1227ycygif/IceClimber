class Sprite
{
public:

	Sprite(void);
	~Sprite(void);
 
	IDirect3DTexture9 *Texture;
	D3DXIMAGE_INFO imagesinfo;
	D3DCOLOR color;

	bool Create(const char* filename, bool bUseTransparency, D3DCOLOR TransparencyColor);

	void Draw(float x, float y); // #01
	void Render( float x , float y , float radian, float sx, float sy);
	void SetColor( int r , int g , int b , int a );
};

extern Sprite g_Load;