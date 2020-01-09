/**========================================================================
 * �ؽ���
 * �޽��� �ؽ��ĸ� ������ ���θ� �Ѵ�.
 *=========================================================================*/

#include <Windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>

//SHOW_HOW_TO_USE_TCT�� ����� �Ͱ� ������� ���� ���� ������ ����� �ݵ�� ������.
//#define SHOW_HOW_TO_USE_TCT

/**========================================================================
 * ���� ����
 *=========================================================================*/

LPDIRECT3D9				g_pD3D			= NULL;
LPDIRECT3DDEVICE9		g_pd3dDevice	= NULL;
LPDIRECT3DVERTEXBUFFER9	g_pVB			= NULL;
LPDIRECT3DTEXTURE9		g_pTexture		= NULL; // �ؽ�ó �������̽� ����

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;
	D3DCOLOR	color;
	FLOAT		tu, tv; // �ؽ�ó ��ǥ
};

//����� ���� ����ü�� ���� ������ ��Ÿ���� FVF ��
#ifdef SHOW_HOW_TO_USE_TCI
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#else
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#endif

/**========================================================================
 * �ʱ�ȭ
 *=========================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
								D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/**========================================================================
 * ���� ���� �ʱ�ȭ
 * ���� ���ۿ� �ؽ��� ����
 *=========================================================================*/
HRESULT InitGeometry()
{
	//D3DX �迭 �Լ��� ����Ͽ� ���Ϸκ��� �ؽ�ó ����
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"nayeon.jpg", &g_pTexture)))
	{	//���� ������ ������ ������ ���� ���� �˻�
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\nayeon.jpg", &g_pTexture)))
		{
			MessageBox(NULL, L"Could not find nayeon.jpg", L"Texture.exe", MB_OK);

			return E_FAIL;
		}
	}

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(50 * 2 * sizeof(CUSTOMVERTEX), 0, 
							D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	CUSTOMVERTEX* pVertices;

	if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}
	
	for (DWORD i = 0; i < 50; i++)
	{
		FLOAT theta = (2 * D3DX_PI * i) / (50 - 1);

		pVertices[2 * i + 0].position = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));
		pVertices[2 * i + 0].color = 0xffffffff;

#ifndef SHOW_HOW_TO_USE_TCI
		//�ڵ����� ��ǥ�� �������� �ʰ� �����ϴ� ���.
		pVertices[2 * i + 0].tu = ((FLOAT)i) / (50 - 1);
		pVertices[2 * i + 0].tv = 1.0f;

#endif

		pVertices[2 * i + 1].position = D3DXVECTOR3(sinf(theta), 1.0f, cosf(theta));
		pVertices[2 * i + 1].color = 0xff808080;

#ifndef SHOW_HOW_TO_USE_TCI
		//�ڵ����� ��ǥ�� �������� �ʰ� �����ϴ� ���.
		pVertices[2 * i + 1].tu = ((FLOAT)i) / (50 - 1);
		pVertices[2 * i + 1].tv = 0.0f;

#endif
	}

	g_pVB->Unlock();

	return S_OK;
}

/**========================================================================
 * �ʱ�ȭ ��ü�� Release
 *=========================================================================*/
void Cleanup()
{
	//���� ������ �߿� �������̽� ������ �������� ��������.
	if (g_pTexture != NULL)
		g_pTexture->Release();

	if (g_pVB != NULL)
		g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

/**========================================================================
 * ��� ���� : ��Ŀ��� 3������ ������, ���� ����, ��, �������� ����̴�.
 *=========================================================================*/
void SetupMatrices()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matWorld, timeGetTime() / 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);

	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

/**========================================================================
 * ȭ�� �׸���
 *=========================================================================*/
void Render()
{
	if (NULL == g_pd3dDevice)
		return;

	// �ĸ� ���۸� �Ķ���(0, 0, 255)���� �����.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	SetupMatrices();

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//������ �ؽ�ó�� 0�� �ؽ�ó ���������� �ø���.
		//�ؽ�ó ���������� ���� ���� �ؽ�ó�� ���� ������ ��� ����� �� ����Ѵ�.
		//���⼭�� �ؽ�ó�� ����� ������ ���� ������ modulate �������� ��� ����Ѵ�.
		g_pd3dDevice->SetTexture(0, g_pTexture); // 0�� �ؽ�ó ���������� �ؽ�ó ����
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE); // MODULATE �������� ������ ����
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE); // ù ��° ���� ���� �ؽ�ó�� ��
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); // �� ��° ���� ���� ������ ��
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE); // alpha ������ ������� ���� ����

#ifndef SHOW_HOW_TO_USE_TCI
		//D3D�� �ؽ�ó ��ǥ ���� ����� ���
		//ī�޶� ��ǥ�迡���� ���� ������ ����Ͽ� �ؽ�ó ��ǥ�� ����.
		//4*4 ũ���� �ؽ�ó ��ȯ ����� �ؽ�ó ��ǥ �ε���(TCI=Texture Coord Index)���� ���ڸ�
		//����Ͽ� x, y, z TCI ��ǥ�� u, v �ؽ�ó ��ǥ�� ��ȯ�Ѵ�.
		//����� ���� �ܼ���(-1.0 ~ +1.0) ���� (0.0 ~ 1.0)������ ������ ��ȯ�Ѵ� ����̴�.
		// ����, ��, �������� ��ȯ�� ��ģ ������ (-1.0 ~ +1.0)������ ���� ���� �ȴ�.
		D3DXMATRIXA16 mat;
		mat._11 = 0.25f; mat._12 = 0.00f; mat._13 = 0.00f; mat._14 = 0.00f;
		mat._21 = 0.25f; mat._22 = 0.00f; mat._23 = 0.00f; mat._24 = 0.00f;
		mat._31 = 0.25f; mat._32 = 0.00f; mat._33 = 0.00f; mat._34 = 0.00f;
		mat._41 = 0.25f; mat._42 = 0.00f; mat._43 = 0.00f; mat._44 = 0.00f;

		//�ؽ�ó ��ȯ���
		g_pd3dDevice->SetTransform(D3DTS_TEXTURE0, &mat);
		//2���� �ؽ�ó ���
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		//ī�޶� ��ǥ�� ��ȯ
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
#endif

		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2);

		//������ ����
		g_pd3dDevice->EndScene();
	}

	// �ĸ� ���۸� ���̴� ȭ������ ��ȯ.
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
	//������ Ŭ���� ���
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Texture", NULL };

	//winclass �������Ϳ� ���
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D Texture", L"D3D Texture", WS_OVERLAPPEDWINDOW, 100, 100, 1024, 768,
		GetDesktopWindow(), NULL, NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitGeometry()))
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

	//��ϵ� ������Ʈ winclass ������.
	UnregisterClass(L"D3D Texture", wc.hInstance);
	return 0;
}