// Fill out your copyright notice in the Description page of Project Settings.


#include "VirtualSceneCaptureMComponent2D.h"

#include <d3d11.h>

#include "UnrealCamMDll.h"
#include "Engine/Classes/Kismet/KismetRenderingLibrary.h"

UVirtualSceneCaptureMComponent2D::UVirtualSceneCaptureMComponent2D()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}
void UVirtualSceneCaptureMComponent2D::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	Super::EndPlay(EndPlayReason);
	if(data)
			delete data;
	UnrealCamMDLL::release();
}
void UVirtualSceneCaptureMComponent2D::BeginPlay()
{
	Super::BeginPlay();
	ptrDLL= UnrealCamMDLL::init();
	
	
};

// Called every frame
void UVirtualSceneCaptureMComponent2D::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool res = false;
	int a =0;
	if(!GetWorld()->IsPlayInEditor())
		return;
	
	UVirtualSceneCaptureMComponent2D *This = this;
	UnrealCamMDLL* ptrDLLt = ptrDLL;
	
	
	;
	if(TextureTarget //&& D3DDevice
		)
	{
		ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
		[This,ptrDLLt](FRHICommandListImmediate& RHICmdList)
		{
			This-> D3DDevice = (ID3D11Device*) RHIGetNativeDevice();
			This->ptrDLL->SetDeviceDLL(This->D3DDevice,0);
		
			/*int size = TextureTarget->SizeX * TextureTarget->SizeY;
			if(!data || (allocated_size<(size*3)))
			{
				allocated_size = size * 3;
				if(data)
					delete data;
				
				data = new UCHAR[size * 3];
			}*/
			ID3D11Texture2D* D3D11Texture;
			FRHITexture2D* Texture2D =This->TextureTarget->Resource->TextureRHI->GetTexture2D();
			D3D11Texture = (ID3D11Texture2D*)Texture2D->GetNativeResource();
			int res = This->ptrDLL->SendTexture2DLL(D3D11Texture,0,false,false);
			if(res!=DLLReturCodes::RET_SUCCESS)
			{
				This->b=0;
			}
		});
		
		FTextureRenderTarget2DResource* textureResource = (FTextureRenderTarget2DResource*)TextureTarget->Resource;
		TArray<FColor> ColorBuffer;
		/*if (textureResource->ReadPixels(ColorBuffer))
		{
		
			for (int32 i = 0; i < size; i++)
			{
				int32 dataIndex = size * 3 - 1 - i * 3;
				data[dataIndex + 2] = ColorBuffer[i].G;
				data[dataIndex + 1] = ColorBuffer[i].R;
				data[dataIndex] = ColorBuffer[i].B;
				
				
			}
			res = ptrDLL->SendTextureFromDLL(data, TextureTarget->SizeX, TextureTarget->SizeY);

			RenderRequest* This = this;

ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
[This](FRHICommandListImmediate& RHICmdList)
{
    This->ExecuteTask();
});
		}*/
		
	}

}

