#pragma once

#include "Mesh.h"

namespace AvocadoSky {
	class MeshInstancer : public Mesh
	{
	private:
	public:
		MeshInstancer(Renderer& renderer, MeshData& meshData);
		~MeshInstancer();

		void draw(unsigned int numInstances);
	};
}