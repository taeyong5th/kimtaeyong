/**========================================================================
 * ���� ����
 * ������ ����Ͽ� �� ������ �����ϴ� ���θ� �Ѵ�.
 *=========================================================================*/

#include <Windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>

/**========================================================================
 * ���� ����
 *=========================================================================*/

LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; //������ ������ ���� ����

//������ ����ϱ� ���ؼ��� ���� ������ ������ �߰� �Ǿ�� �Ѵ�.
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;	//������ 3���� ��ǥ
	D3DXVECTOR3 nomarl;			//������ ���� ����
};

// ����� ���� ����ü�� ���� ������ ��Ÿ���� FVF��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

/**========================================================================
 * Direct3D �ʱ�ȭ
 *=========================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	// ����̽��� �����ϱ� ���� D3D ��ü ����
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS	d3dpp;				
	ZeroMemory(&d3dpp, sizeof(d3dpp));			

	d3dpp.Windowed = TRUE;						
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	//z���� ����� ���� ����
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	//�ø� ����� �Ҵ�.
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//z ���� ����� �Ҵ�.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/**========================================================================
 * ���� �ʱ�ȭ : ���� ���۸� �����ϰ� �������� ä�� �ִ´�.
 *
 *=========================================================================*/
HRESULT InitVB()
{
	// �Ǹ����� �׸��� ���� �Ʒ� ���� ���� �׸��� �������۸� �غ��Ѵ�.
	// 50 * 2 ��ŭ�� ũ���..
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(50 * 2 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
											D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	CUSTOMVERTEX* pVertices;

	if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	//���� ���ۿ� �� ���� �����͸� ����� �����Ѵ�.
	for (DWORD i = 0; i < 50; i++)
	{
		FLOAT theta = (2 * D3DX_PI * i) / (50 - 1);

		pVertices[2 * i + 0].position = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));
		pVertices[2 * i + 0].nomarl = D3DXVECTOR3(sinf(theta), 0.0f, cosf(theta));
		pVertices[2 * i + 1].position = D3DXVECTOR3(sinf(theta), 1.0f, cosf(theta));
		pVertices[2 * i + 1].nomarl = D3DXVECTOR3(sinf(theta), 0.0f, cosf(theta));
	}

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

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationX(&matWorld, timeGetTime() / 500.0f); 

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld); // ������ ȸ�� ����� ���� ��ķ� ����̽��� �����Ѵ�.

	//�� ���(ī�޶�)�� �����ϱ� ���ؼ��� 3���� ���� �ʿ��ϴ�.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f); //���� ��ġ(0.0f, 3.0f, -5.0f)
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
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);

	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj); // ������ �������� ����� ����̽��� ����.
}
/**========================================================================
 * ���� ����
 *=========================================================================*/
void SetupLights()
{
	//���� ����
	//������ ����̽��� �� �ϳ��� ������ �� �ִ�.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial(&mtrl);

	//���� ����
	D3DXVECTOR3 vecDir;
	//���⼺ ����(directional light)�� ���� ���� ����
	//���� ����ü
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	//������ Ȯ�걤 ������ ��⸦ �����Ѵ�.
	//������ ������ �����Ѵ�(����Ʈ ����Ʈ, ���̷��� ����Ʈ, ����Ʈ ����Ʈ)
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	//������ ���� ����
	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.0f), 1.0f, sinf(timeGetTime() / 350.0f));

	//������ ������ ���� ���ͷ� �����.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f; // ������ �ٴٸ� �� �ִ� �ִ�Ÿ�
	g_pd3dDevice->SetLight(0, &light); // ����̽��� ���� 0���� ��ġ
	g_pd3dDevice->LightEnable(0, TRUE); // ���� 0���� Ȱ��ȭ �Ѵ�.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);// ���� ������ Ȱ��ȭ �Ѵ�.

	//ȯ�� ������ �� ����
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

/**========================================================================
 * �ʱ�ȭ ��ü�� Release
 *=========================================================================*/
void Cleanup()
{
	//���� ������ �߿� �������̽� ������ �������� ��������.
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

	// �ĸ� ���۸� �Ķ���(0, 0, 255)���� �����.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	SetupLights();

	SetupMatrices();

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// ���� ������ ��� �ִ� ���� ���۸� ��� ��Ʈ������ �Ҵ��Ѵ�.
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));

		// D3D���� ���� ���̴� ������ �����Ѵ�. ��κ��� ��쿡�� FVF�� �����Ѵ�.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// ���� ������ ����ϱ� ���� DrawPrimitive() �Լ��� ȣ���Ѵ�.
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
		L"D3D Light", NULL };

	//winclass �������Ϳ� ���
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D Light", L"D3D Light", WS_OVERLAPPEDWINDOW, 100, 100, 1024, 768,
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

	//��ϵ� ������Ʈ winclass ������.
	UnregisterClass(L"D3D Light", wc.hInstance);
	return 0;
}



