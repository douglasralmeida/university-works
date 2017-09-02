#define NO_DSHOW_STRSAFE
#define COBJMACROS

#include <windows.h>
#include <dshow.h>
#include <strmif.h>
#include "funcoes.h"
#include "video.h"

int ReproduzirVideo(HWND WHandle, WCHAR* FileName)
{
	//Valor do retorno das funcoes COM
	HRESULT hr;
	// Graph Builder interface
	IGraphBuilder* MPGrafo = NULL;      
	// Media Control interface  
	IMediaControl* MPControlador = NULL;
	//	Media Event interface
	IMediaEvent* MPEvento = NULL;
	// VMR Filter interface
	IBaseFilter* MPRender = NULL;
	// Exibidor do video
	IVMRWindowlessControl* MPVideoDisplay = NULL;
		
	// Inicializa a biblioteca COM
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return MD_FALHA;
	
	// Cria o Filter Graph Manager e consulta por interfaces.
	hr = CoCreateInstance(&CLSID_FilterGraph, NULL, CLSCTX_INPROC, &IID_IGraphBuilder, (void**)&MPGrafo);
	if (FAILED(hr))
		return MD_FALHA;
	
	// Usa IGraphBuilder::QueryInterface para obter a interface IMediaControl.
	hr = IGraphBuilder_QueryInterface(MPGrafo, &IID_IMediaControl, (void**)&MPControlador);
	if (FAILED(hr))
		return MD_FALHA;
	// Usa IGraphBuilder::QueryInterface para obter a interface IMediaEvent.
	hr = IGraphBuilder_QueryInterface(MPGrafo, &IID_IMediaEvent, (void**)&MPEvento);
	if (FAILED(hr))
		return MD_FALHA;
	
	// Cria o Base Filter
	hr = CoCreateInstance(&CLSID_VideoMixingRenderer, NULL, CLSCTX_INPROC_SERVER, &IID_IBaseFilter, (void**)&MPRender);
	if FAILED(hr)
		return MD_FALHA;
		
	// Adiciona o rendereizador ao Filter Graph Manager
	hr = IGraphBuilder_AddFilter(MPGrafo, MPRender, L"VMR-7");
	if (SUCCEEDED(hr))
	{
		IVMRWindowlessControl *pWC = NULL;
		IVMRFilterConfig* pConfig = NULL;
		
		IBaseFilter_AddRef(MPRender);

		//Obtem a interface IVWRFilterConfig
		hr = IBaseFilter_QueryInterface(MPRender, &IID_IVMRFilterConfig, (void**)&pConfig);
		if (FAILED(hr))
			return MD_FALHA;
		else
		{
			//Configura o renderizador para o modo sem janela com VMR-7 Windowless
			IVMRFilterConfig_SetRenderingMode(pConfig, VMRMode_Windowless);
			//Obtem a interface IVRWindowlessControl que controla o renderizador
			IBaseFilter_QueryInterface(MPRender, &IID_IVMRWindowlessControl, (void**)&pWC);
			//Configura o renderizador para usar a janela atual como local de exibicao de video'
			IVMRWindowlessControl_SetVideoClippingWindow(pWC, WHandle);
			//Altera o Aspect Ratio do modo de exibicao do video
			IVMRWindowlessControl_SetAspectRatioMode(pWC, VMR_ARMODE_LETTER_BOX);
		}
		MPVideoDisplay = pWC;
		IVMRWindowlessControl_AddRef(MPVideoDisplay);
	
		IVMRFilterConfig_Release(pConfig);
		IVMRWindowlessControl_Release(pWC);
	}
	else
	{
		return MD_FALHA;
	}
	
	// Abre o arquivo de midia
	hr = IMediaControl_RenderFile(MPControlador, FileName);
	if (SUCCEEDED(hr))
	{
		//Reproduz a midia
		hr = IMediaControl_Run(MPControlador);
	    if(FAILED(hr))
		{
			return MD_FALHA;
		}	
	}
	else
	{
		return MD_FALHA;
		ErroSimples(L"Erro ao abrir a midia."/* Codigo: 0x%x.\n",  hr*/);
	}
	
	//Configura o renderizador para pintar o video na janela
	RECT rc;
	GetClientRect(WHandle, &rc);
	IVMRWindowlessControl_SetVideoPosition(MPVideoDisplay, NULL, &rc);
	
	PAINTSTRUCT ps;
	HDC DC = BeginPaint(WHandle, &ps);
	IVMRWindowlessControl_RepaintVideo(MPVideoDisplay, WHandle, DC);
	
	// Espera o termino da execução da mídia
	long EventCode;
	IMediaEvent_WaitForCompletion(MPEvento, INFINITE, &EventCode);
	
	//Limpa a memoria
	IGraphBuilder_RemoveFilter(MPGrafo, MPRender);
	IBaseFilter_Release(MPRender);
	IVMRWindowlessControl_Release(MPVideoDisplay);
	IMediaControl_Release(MPControlador);
	IMediaEvent_Release(MPEvento);
	IGraphBuilder_Release(MPGrafo);
	
	// Termina a biblioteca COM
	CoUninitialize();
	
	return MD_SUCESSO;
}