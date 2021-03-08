#pragma once
#include "DXUT.h"
#include <thread>

using namespace DirectX;

class SnowParticleSystem
{
private:
	struct ParticleType
	{
		XMFLOAT3 initialPos;
		XMFLOAT3 initialVel;
		float age;
		float offset;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT4 color;
	};

public:
	SnowParticleSystem();
	SnowParticleSystem(const SnowParticleSystem&);
	~SnowParticleSystem();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const WCHAR*, int);
	bool Frame(float, ID3D11DeviceContext*);
	void Render(ID3D11DeviceContext*);

	//ID3D11UnorderedAccessView* GetUAV() { return m_uav; }
	ID3D11ShaderResourceView* GetTexture() { return m_TextureView; }
	int GetIndexCount() { return m_indexCount; }
	int GetVertexCount() { return m_vertexCount; }
	int GetInstaceCount() { return m_instanceCount; }
	int GetCurrentParticleCount() { return m_currentParticleCount; }
	int GetParticlesPerSecond() { return m_particlePerSecond; }
	void SetParticlesPerSecond(int value) { m_particlePerSecond = value; }
private:
	// Initialize
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const WCHAR*);
	bool InitializeParticleSystem(int);
	bool InitializeBuffers(ID3D11Device*, ID3D11DeviceContext*);
	void CalculateInstancePositions(int, int);

	// Particle methods
	void EmitParticles(float);
	void UpdateParticles(float);
	void SpawnParticle();

	// Render & Update
	bool UpdateBuffers(ID3D11DeviceContext*);
	void RenderBuffers(ID3D11DeviceContext*);
private:

	float m_cloudPosX, m_cloudPosY, m_cloudPosZ;
	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVeclocity, m_particleVelocityVariation;
	float m_particleSize, m_particlePerSecond;
	int m_maxParticles;

	int m_currentParticleCount;
	float m_accumulatedTime;

	ID3D11UnorderedAccessView* m_uav;
	ID3D11Texture2D* m_uavTex;

	ID3D11Resource* m_Texture;
	ID3D11ShaderResourceView* m_TextureView;

	ParticleType* m_particleList;

	int m_vertexCount, m_indexCount, m_instanceCount;
	InstanceType* m_instance;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer, * m_instanceBuffer;

	std::vector<std::thread> m_threads;
};