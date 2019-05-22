#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include <DirectXCollision.h>
#include "DDSTextureLoader.h"
#include "resource.h"
#include <iostream>
#include "structures.h"

/*
 movement
 a current direction vector
 speed is constant
 for now, new directions are instant (no rotation periods)
*/

using namespace DirectX;



struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
};

class DrawableGameObject
{
public:
	DrawableGameObject();
	~DrawableGameObject();

	HRESULT								initMesh(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
	void								update(float t, const vecDrawables& drawList, const unsigned int index);
	void								draw(ID3D11DeviceContext* pContext);
	ID3D11Buffer*						getVertexBuffer() { return m_pVertexBuffer; }
	ID3D11Buffer*						getIndexBuffer() { return m_pIndexBuffer; }
	ID3D11ShaderResourceView**			getTextureResourceView() { return &m_pTextureResourceView; 	}
	XMMATRIX*							getTransform() { return &m_World; }
	ID3D11SamplerState**				getTextureSamplerState() { return &m_pSamplerLinear; }
	MaterialPropertiesConstantBuffer	getMaterial() { return m_material;}

	void								setPosition(XMFLOAT3 position);
	XMFLOAT3*							getPosition() { return &m_position; }
	XMFLOAT3*							getDirection() { return &m_direction; }

	void								checkIsOnScreenAndFix(const XMMATRIX&  view, const XMMATRIX&  proj);

protected:
	void								setDirection(XMFLOAT3 direction); 

	void								nearbyDrawables(const vecDrawables& drawList, const unsigned int index);
	XMFLOAT3							calculateSeparationVector(const vecDrawables& drawList);
	XMFLOAT3							calculateAlignmentVector(const vecDrawables& drawList);
	XMFLOAT3							calculateCohesionVector(const vecDrawables& drawList);
	void								createRandomDirection();

	//	Helpful math functions
	XMFLOAT3							addFloat3(XMFLOAT3& f1, XMFLOAT3& f2);
	XMFLOAT3							subtractFloat3(XMFLOAT3& f1, XMFLOAT3& f2);
	XMFLOAT3							normaliseFloat3(XMFLOAT3& f1);
	float								magnitudeFloat3(XMFLOAT3& f1);
	XMFLOAT3							multiplyFloat3(XMFLOAT3& f1, const float scalar);
	XMFLOAT3							divideFloat3(XMFLOAT3& f1, const float scalar);

private:
	
	XMMATRIX							m_World;
	ID3D11Buffer*						m_pVertexBuffer;
	ID3D11Buffer*						m_pIndexBuffer;
	ID3D11ShaderResourceView*			m_pTextureResourceView;
	ID3D11SamplerState *				m_pSamplerLinear;
	MaterialPropertiesConstantBuffer	m_material;
	XMFLOAT3							m_position;

	XMFLOAT3							m_direction;
	unsigned int*						m_nearbyDrawables;
	
};

