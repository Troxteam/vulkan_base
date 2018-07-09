#pragma once
#include <glm/gtx/hash.hpp>

#include "Vertex.h"

namespace std {
	template<> struct hash<Vertex>
	{
		size_t operator() (Vertex const& vertex) const {
			return ((hash<glm::bvec3>()(vertex.position) ^
				(hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.textureCoord) << 1) ^
				(hash<glm::vec3>()(vertex.normals) << 1);
		}
	};
}