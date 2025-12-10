#pragma once

#include "lrpch.h"
#include "../Platform/OpenGL/Image2D.h"
#include "../Platform/OpenGL/Shader.h"
#include "../Platform/OpenGL/Buffer.h"

#include "../Project/Scene/Scene.h"
#include "../Project/Assets/AssetPool.h"

namespace Ballistic {

	// struct alignas(16) RTXUniformParameters {
	// 	glm::vec3 camPos;
	// 	float camFovTan;
	// 	glm::mat4 camRot;

	// 	int numInstances;
	// 	int numSpheres;
	// };

	// struct RTXComputeStatistics {
	// 	float gpuTime;
	// 	float raysCast;

	// 	int trianglesDrawn;
	// 	int spheresDrawn;
	// 	int primitivesDrawn;
	// };

	class Renderer {
	public:
		void Init();
		std::shared_ptr<Image2D> Render(AssetPool* assetPool);
		
		// RTXUniformParameters rtxUniformParameters;
		// RTXComputeStatistics rtxComputeStats;

		std::shared_ptr<Image2D> m_Texture;
		std::shared_ptr<Shader> m_Shader;

	};

}