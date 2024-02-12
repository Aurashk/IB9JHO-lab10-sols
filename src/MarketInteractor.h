#pragma once
#include "Asset.h"

class MarketInteractor
{

public:
	// interact with an asset in some way
	virtual void interact(const Asset& asset) = 0;

};