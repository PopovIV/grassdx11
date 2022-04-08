#pragma once

#include "../../pch.h"

namespace AvocadoSky {
	struct Vertex {
		float x, y, z;
		float u, v;
	};

	enum class DefaultMesh {
		CUBE,
		SQUARE,
		PLANE,
		SKY_PLANE
	};

	class MeshData {
	private:
		std::vector<Vertex> vertices;
		std::vector<int> indices;

		void createCube();
		void createSquare();
		void createPlane(int resX, int resY);
		void createSkyPlane(int skyPlaneResolution, float skyPlaneWidth, float skyPlaneTop, float skyPlaneBottom, int textureRepeat);
		Vertex createVert(float _x, float _y, float _z, float _u, float _v);
		void transformVertices(const XMMATRIX& meshTransform);

	public:
		MeshData(
			DefaultMesh defaultMeshType, int resolutionX, int resolutionY,
			bool shouldInvertFaces = false,
			const XMMATRIX meshTransform = XMMatrixIdentity()
		);

		void createDefault(DefaultMesh defaultMeshType, int resolutionX = 0, int resolutionY = 0);
		void invertFaces();

		std::vector<Vertex>& getVertices();
		std::vector<int>& getIndices();
	};
}