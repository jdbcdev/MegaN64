#include "opengl_WrappedFunctions.h"

namespace opengl {

	std::vector<char> GlDrawArraysUnbufferedCommand::m_attribsData;
	std::vector<char> GlDrawElementsUnbufferedCommand::m_attribsData;
	std::unordered_map<int, std::shared_ptr<std::vector<u8>>> GlMapBufferRangeReadAsyncCommand::m_data;
	std::mutex GlMapBufferRangeReadAsyncCommand::m_mapMutex;
	std::unordered_map<int, GlVertexAttribPointerManager::VertexAttributeData> GlVertexAttribPointerManager::m_vertexAttributePointers;
	const void* GlVertexAttribPointerManager::smallestDataPtr = nullptr;
    std::unordered_map<int, GlVertexAttribPointerManager::VertexAttributeData> GlVertexAttribPointerManager::m_vertexAttributePointersRender;
    const void* GlVertexAttribPointerManager::smallestDataPtrRender = nullptr;
	splicer::ObjectPool<std::vector<char>> GlVertexAttribPointerManager::m_vectorPool(1024);
}
