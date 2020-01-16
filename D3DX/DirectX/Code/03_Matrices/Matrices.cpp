/**========================================================================
 * ��� ���
 * ����� �����ϰ� ��ȯ�ϴ� ���� �����ϰ� �ȴ�.
 *=========================================================================*/

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h> // TimeGetTime() �Լ��� ����ϱ� ���ؼ� �����ϴ� ���

/**========================================================================
 * ���� ����
 *=========================================================================*/

LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; 

struct CUSTOMVERTEX
{
	FLOAT x, y, z; 
	DWORD color;		
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

/**========================================================================
 * Direct3D �ʱ�ȭ
 *=========================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS	d3dpp;			
	ZeroMemory(&d3dpp, sizeof(d3dpp));			

	d3dpp.Windowed = TRUE;						
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// �ø� ����� ����, �ﰢ���� �ո�, �޸��� ��� �������Ѵ�.
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//������ ������ �����Ƿ� ���� ����� ����.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

/**========================================================================
 * ���� �ʱ�ȭ : ���� ���۸� �����ϰ� �������� ä�� �ִ´�.
 *=========================================================================*/
HRESULT InitVB()
{
	CUSTOMVERTEX vertices[] =
	{
		//{ -1.0f, -1.0f, 0.0f, 0xffff0000, }, // x, y, z, color
		//{ 1.0f, -1.0f, 0.0f, 0xff00ff00, },
		//{ 0.0f, 1.0f, 0.0f, 0xff00ffff, },

		{ 0.0f, 0.0f, 0.0f, 0xffff0000, }, // x, y, z, color
		{ 1.0f, 0.0f, 0.0f, 0xff00ff00, },
		{ 0.0f, 1.0f, 0.0f, 0xff00ffff, },
	};

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	void* pVertices;

	if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	memcpy(pVertices, vertices, sizeof(vertices));

	g_pVB->Unlock();

	return S_OK;
}

/**========================================================================
 * ��� ���� : ��Ŀ��� 3������ ������, ���� ����, ��, �������� ����̴�.
 *=========================================================================*/
void SetupMatrices()
{
	//���� ���
	D3DXMATRIXA16 matWorld;

	UINT iTime = timeGetTime() % 1000; // float ������ ���е��� ���ؼ� 1000���� ������ �����Ѵ�.

	//FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f; // 1000�и��ʸ��� �� ������(2 * pi) ȸ�� �ִϸ��̼� ����� �����.

	D3DXMatrixRotationY(&matWorld, GetTickCount() / 500.0f);

	//D3DXMatrixRotationY(&matWorld, fAngle); // Y���� ȸ�������� ȸ�� ����� �����Ѵ�.

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld); // ������ ȸ�� ����� ���� ��ķ� ����̽��� �����Ѵ�.

	//�� ���(ī�޶�)�� �����ϱ� ���ؼ��� 3���� ���� �ʿ��ϴ�.
	D3DXVECTOR3 vEyePt(0.0f, -10.0f, -10.0f); //���� ��ġ(0.0f, 3.0f, -5.0f)
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f); // ���� �ٶ󺸴� ��ġ(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f); // �� ������ ��Ÿ���� ��� ����(0.0f, 1.0f, 0.0f)

	//�� ���(ī�޶�)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);// 3���� Point�� �̿��� �� ����� �����Ѵ�.

	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView); // ������ �� ����� ����̽��� �����Ѵ�.

	// �������� ����� �����ϱ� ���ؼ��� �þ߰�(FOV = Field Of View)�� ��Ⱦ��(aspect ratio), Ŭ���� ����� ���� �ʿ��ϴ�.
	D3DXMATRIXA16 matProj;
	//ù ��° : ������ ���
	//�� ��° : �þ߰�
	//�� ��° : ��Ⱦ��
	//�� ��° : ���� Ŭ����
	//�ټ� ��° : ���Ÿ� Ŭ����
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 2, 1.0f, 1.0f, 100.0f);

	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj); // ������ �������� ����� ����̽��� ����.
}


/**========================================================================
 * �ʱ�ȭ ��ü�� Release
 *=========================================================================*/
void Cleanup()
{
	if (g_pVB != NULL)
		g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

/**========================================================================
 * ȭ�� �׸���
 *=========================================================================*/
void Render()
{
	if (NULL == g_pd3dDevice)
		return;

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//����, ��, �������� ����� �����Ѵ�.
	SetupMatrices();

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));

		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/**========================================================================
 * WinProc
 *=========================================================================*/
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/**========================================================================
 * Window ����
 *=========================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Matrices", NULL };

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D Matrices", L"D3D Matrices", WS_OVERLAPPEDWINDOW, 100, 100, 1024, 768,
		GetDesktopWindow(), NULL, NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitVB()))
		{
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();
			}
		}
	}

	UnregisterClass(L"D3D Matrices", wc.hInstance);
	return 0;
}



