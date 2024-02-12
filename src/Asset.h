#pragma once
#include <string>
#include <queue>
#include <random>
#include <ctime>

class Asset
{
private:
	// name the asset
	std::string m_name;

	// starting price of the asset
	double m_initial_price;

	// current price of the asset
	double m_price;

	// current volatility of the asset
	double m_volatility;

	// Historical price data for this asset
	// Using a double-ended queue
	std::deque<double> m_history;

	// used to generate random numbers
	thread_local static std::default_random_engine RANDOM_GENERATOR;

public:

	static const unsigned int MAXIMUM_HISTORY = 250;

	Asset();

	// asset constructor
	Asset(const std::string& name, double initial_price, double initial_volatility);

	// Update the asset after a single tick of time has passed
	void tick_update();

	// copy the price history into an array, amount of data specified by 'amount'
	// if total history is less than amount, we just copy all the available history
	// returns the actual amount copied
	unsigned int get_price_history(double* const history,  unsigned int amount) const;

	// retrieve current asset price
	double price() const;

	// retrieve name of the asset
	const std::string& name() const;

};