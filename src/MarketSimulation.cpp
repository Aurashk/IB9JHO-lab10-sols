#include "MarketSimulation.h"

// Set up all the different possible asset names in this simulation
const std::array<std::string, MarketSimulation::TOTAL_AVALIABLE_ASSETS> MarketSimulation::ASSET_NAMES = {"Disney", "Microsoft", "Tesla", "Bitcoin"};

// Set the initial prices of each asset
const std::array<double, MarketSimulation::TOTAL_AVALIABLE_ASSETS> MarketSimulation::INITIAL_ASSET_PRICES = {187.67, 244.99, 816.12, 48158.6};

// Set the initial voloatilities of each asset
const std::array<double, MarketSimulation::TOTAL_AVALIABLE_ASSETS> MarketSimulation::INITIAL_ASSET_VOLATILITIES = {0.0005, 0.0008, 0.0016, 0.001};

MarketSimulation::MarketSimulation()
	: m_current_tick(0)
{
	// set up the assets
	for (unsigned int i = 0; i < TOTAL_AVALIABLE_ASSETS; ++i)
		m_assets_in_market[i] = Asset(ASSET_NAMES[i], INITIAL_ASSET_PRICES[i], INITIAL_ASSET_VOLATILITIES[i]);
}

void MarketSimulation::tick_update()
{
	// update the assets
	for (unsigned int i = 0; i < TOTAL_AVALIABLE_ASSETS; ++i)
		m_assets_in_market[i].tick_update();
}

void MarketSimulation::run(unsigned int number_of_ticks, MarketInteractor &interactor, unsigned int interaction_ticks)
{

	for (unsigned int i = 0; i < number_of_ticks; ++i)
	{
		tick_update();
		++m_current_tick;

		// check if we interact on this tick
		if ((m_current_tick % interaction_ticks) == 0)
		{
			for (unsigned int i = 0; i < TOTAL_AVALIABLE_ASSETS; ++i)
				interactor.interact(m_assets_in_market[i]);
		}
	}
}

double MarketSimulation::liquidate_portfolio(const std::map<std::string, double> &portfolio) const
{
	double total = 0.0;

	for (unsigned int i = 0; i < TOTAL_AVALIABLE_ASSETS; ++i)
	{
		// check if the asset is not in the portfolio
		if (portfolio.count(ASSET_NAMES[i]) <= 0)
			continue;

		total += portfolio.at(ASSET_NAMES[i]) * m_assets_in_market[i].price();
	}

	return total;
}
