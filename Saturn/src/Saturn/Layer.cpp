#include "sppch.h"
#include "Layer.h"



namespace Saturn {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName), OBJ_NAME(debugName)
	{
	}

	Layer::~Layer()
	{

	}
}

