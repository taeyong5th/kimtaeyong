/**========================================================================
 * KeyFrameAnimation
 * ���� ������ �̿��� �ִϸ��̼� ó��
 *=========================================================================*/

#include <d3d9.h>
#include <d3dx9.h>

 /**========================================================================
  * ���� ����
  *=========================================================================*/

LPDIRECT3D9				g_pD3D = NULL;
LPDIRECT3DDEVICE9		g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9	g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9	g_pIB = NULL;

D3DXMATRIXA16			g_matTMParent; //�θ��� �⺻ ���
D3DXMATRIXA16			g_matRParent; //�θ��� ȸ�� ���

D3DXMATRIXA16			g_matTMChild; //�ڽ��� �⺻ ���
D3DXMATRIXA16			g_matRChild; //�ڽ��� ȸ�� ���

float					g_fRot = 0.0f;

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

#define ROT_DELTA 0.1f;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct MYINDEX
{
	WORD _0, _1, _2;
};

D3DXVECTOR3			g_aniPos[2];
D3DXQUATERNION		g_aniRot[2];

/**========================================================================
 * Direct3D �ʱ�ȭ
 *=========================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

/**========================================================================
 * ���� ����
 * ���� ���۸� �����ϰ� �������� ä���ִ´�.
 *=========================================================================*/

HRESULT InitVB()
{
	CUSTOMVERTEX vertices[] =
	{
		{-1, 1, 1, 0xffff0000},
		{ 1, 1, 1, 0xff00ff00},
		{ 1, 1,-1, 0xff0000ff},
		{-1, 1,-1, 0xffffff00},

		{-1,-1, 1, 0xffff0000},
		{ 1,-1, 1, 0xffff0000},
		{ 1,-1,-1, 0xffff0000},
		{-1,-1,-1, 0xffff0000},
	};

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	void* pVertices;

	if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	g_pVB->Unlock();

	return S_OK;
}

/**========================================================================
 * �ε��� ����
 * �ε��� ���۸� �����ϰ� �������� ä���ִ´�.
 *=========================================================================*/

HRESULT InitIB()
{
	MYINDEX indices[] =
	{
		{0, 1, 2}, {0, 2, 3},
		{4, 6, 5}, {4, 7, 6},
		{0, 3, 7}, {0, 7, 4},
		{1, 5, 6}, {1, 6, 2},
		{3, 2, 6}, {3, 6, 7},
		{0, 4, 5}, {0, 5, 1},
	};

	if (FAILED(g_pd3dDevice->CreateIndexBuffer(12 * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	void** pIndices;

	if (FAILED(g_pIB->Lock(0, sizeof(indices), (void**)&pIndices, 0)))
	{
		return E_FAIL;
	}

	memcpy(pIndices, indices, sizeof(indices));

	g_pIB->Unlock();

	return S_OK;
}

/**========================================================================
 * �ִϸ��̼� �ʱ�ȭ
 *=========================================================================*/
void InitAnimation()
{
	g_aniPos[0] = D3DXVECTOR3(0, 0, 0); // ��ġ ��ȭ�� ��� �� ���� ��
	g_aniPos[1] = D3DXVECTOR3(5, 5, 5); // ��ġ ��ȭ�� ��� �� ���� ��

	FLOAT Yaw = D3DX_PI * 90.0f / 180.0f; // Y�� 90�� ȸ��
	FLOAT Pitch = 0;
	FLOAT Roll = 0;
	
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw, Pitch, Roll); // �����(Y�� 90��)

	Yaw = 0;
	Pitch = D3DX_PI * 90.0f / 180.0f; // X�� 90�� ȸ��
	Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw, Pitch, Roll); // �����(X�� 90��)
}

/**========================================================================
 * ���� ���� �ʱ�ȭ
 *=========================================================================*/

HRESULT InitGeometry()
{
	if (FAILED(InitVB()))
		return E_FAIL;

	if (FAILED(InitIB()))
		return E_FAIL;

	InitAnimation();

	return S_OK;
}

/**========================================================================
 * ī�޶� ��� ����
 *=========================================================================*/
void SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -20.0f);
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
 * �ִϸ��̼� ��� ����
 *=========================================================================*/
void Animate()
{
	static float t = 0;
	float x, y, z;
	D3DXQUATERNION quat;

	if (t > 1.0f)
		t = 0.0f;

	D3DXVECTOR3 v;
	//�̵����� ���� ���� 
	D3DXVec3Lerp(&v, &g_aniPos[0], &g_aniPos[1], t);
	//�̵� ��İ����� ��ȯ
	D3DXMatrixTranslation(&g_matTMParent, v.x, v.y, v.z);

	//ȸ������ ���� ���� ����
	D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], t);
	//������� ȸ�� ��İ����� ��ȯ
	D3DXMatrixRotationQuaternion(&g_matRParent, &quat);

	t += 0.005f;

	//�ڽ� �޽��� z�� ȸ�� ���
	D3DXMatrixRotationZ(&g_matRChild, GetTickCount() / 500.0f);

	//Ư�� vector�� ������ �ϴ� ���
	//D3DXMatrixRotationAxis(&g_matRChild, nomalVec, Angle);

	//�ڽ� �޽ô� �������� ���� (3, 3, 3)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMChild, 3, 3, 3);
}

/**========================================================================
 * Release - �ʱ�ȭ ��ü�� �Ұ�
 *=========================================================================*/
void Cleanup()
{
	if (g_pIB != NULL)
		g_pIB->Release();

	if (g_pVB != NULL)
		g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

/**========================================================================
 * �޽� �׸���
 *=========================================================================*/
void DrawMesh(D3DXMATRIXA16* pMat)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, pMat);
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->SetIndices(g_pIB);
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

/**========================================================================
 * ȭ�� �׸���
 *=========================================================================*/
void Render()
{
	D3DXMATRIXA16 matWorld;

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	Animate();

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//�׸��� ������ �ƴ� ��� ���� ������ �߿��ϴ�.

		//�θ��� ��ȯ�� ����� - ȸ�� * �⺻ ��ȯ
		matWorld = g_matRParent * g_matTMParent;

		//����� ��ȯ�� ������� �θ� ��ü�� �׸���.
		DrawMesh(&matWorld);

		//�ڽ��� ��ȯ�� ����� - �ڽ��� ȸ�� * �ڽ��� �⺻ ��ȯ * �θ��� ȸ�� * �θ��� �⺻��ȯ
		matWorld = g_matRChild * g_matTMChild * g_matRParent * g_matTMParent;
		//matWorld = g_matRChild * g_matTMChild * matWorld;

		//����� ��ȯ�� ������� �ڽ� ��ü�� �׸���.
		DrawMesh(&matWorld);

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/**========================================================================
 * ������ ���ν���
 *=========================================================================*/
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		
		if (wParam == VK_LEFT)
			g_fRot -= ROT_DELTA;

		if (wParam == VK_RIGHT)
			g_fRot += ROT_DELTA;

		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/**========================================================================
 * WinMain
 *=========================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,
		0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Animation", NULL };

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D Animation", L"D3D Animation", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitGeometry()))
		{
			SetupCamera();

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
				{
					Render();
				}
			}
		}
	}

	UnregisterClass(L"D3D Animation", wc.hInstance);
	return 0;
}