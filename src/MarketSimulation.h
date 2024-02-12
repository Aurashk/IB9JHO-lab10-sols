#pragma once

#include <array>
#include <string>
#include <map>
#include "Asset.h"
#include "MarketInteractor.h"

class MarketSimulation
{
private:
	// total unique asset types in the simulation
	static const unsigned int TOTAL_AVALIABLE_ASSETS = 5;

	// All the different asset names in the simulation
	static const std::array<std::string, TOTAL_AVALIABLE_ASSETS> ASSET_NAMES;

	// The initial prices of each asset
	static const std::array<double, TOTAL_AVALIABLE_ASSETS> INITIAL_ASSET_PRICES;

	// The initial volatilities of each asset - this is considered constant between each tick
	static const std::array<double, TOTAL_AVALIABLE_ASSETS> INITIAL_ASSET_VOLATILITIES;

	// The assets in the simulation
	std::array<Asset, TOTAL_AVALIABLE_ASSETS> m_assets_in_market;

	// Amount of ticks that have passed since simulation start
	unsigned int m_current_tick;

	// Update the simulation after a single tick of time has passed
	void tick_update();

public:

	MarketSimulation();

	////////////////////////////////////////////////////////////////////
	// Run the simulation for a chosen number of ticks
	// The interactor will interact with assets at regular intervals
	// every time 'interaction_ticks' ticks have passed
  ////////////////////////////////////////////////////////////////////
	void run(unsigned int number_of_ticks, MarketInteractor& interactor, unsigned int interaction_ticks);

	// retrieve total of cash obtained by selling all the assets in the portfolio
	double liquidate_portfolio(const std::map<std::string, double>& portfolio) const;

};