#include "MarketSimulation.h"
#include "Trader.h"
#include <iostream>

int main()
{
	MarketSimulation sim;

	double initial_currency = 1000.0;
	
	// run 10 simulations
	for (unsigned int i = 0; i < 10; ++i)
	{
		// Make a trader with currency to spend
		Trader trader(initial_currency);

		// put the trader in the market simulation 
		// running for 10000 steps
		// the trader interacts (buys/sells) with market every 50 steps
		sim.run(10000, trader, 50);

		std::cout << "Starting cash " << initial_currency << std::endl;
		std::cout << "Ending liquidated total " << trader.liquidated_total(sim) << std::endl;
		std::cout << "Ending revenue " << trader.liquidated_revenue(sim) << std::endl;
		std::cout << std::endl;
	}
}

