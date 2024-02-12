#pragma once

#include <map>
#include <stdexcept>
#include "MarketInteractor.h"
#include "MarketSimulation.h"

class Trader : public MarketInteractor
{
private:
	// asset price history is copied into this array for examination
	thread_local static std::array<double, Asset::MAXIMUM_HISTORY> history_working_array;

	// initial amount of cash the trader is constructed with
	double m_initial_cash;

	// currency held by trader which can be used to buy assets
	double m_cash;

	// The portfolio of the trader is a map of strings (asset names)
	// to doubles (amount of that asset which is held)
	std::map<std::string, double> m_portfolio;

	// use some systematic method to determine how much of the asset should be bought
	// based on the assets history
	double determine_buy_amount(const Asset& asset);

	// use some systematic method to determine how much of the asset should be sold 
	// based on the assets history
	double determine_sell_amount(const Asset& asset);

public:

	// constructs a trader with a given amount of cash
	Trader(double initial_cash);

	// retrieve the amount of cash the trader has
	double get_cash() const;

	// retrieve the amount of an asset held by a trader
	double get_asset_quantity(const Asset& asset) const;

	// buy some amount of the named asset at given price, 
	// adding it to our portfolio
	// if cash is insufficient we buy the maximum we can
	void buy(const std::string& name, double price, double amount);

	// sell some amount of the named asset at given price,
	// removing it from our portfolio
	// if we don't have enough of the asset we sell the maximum we can
	void sell(const std::string& name, double price, double amount);

	// interact with the provided asset (decide to buy or sell and then adjust portfolio)
	void interact(const Asset& asset) override;

	// retrieve current liquidated total of assets + cash
	double liquidated_total(const MarketSimulation& ms) const;

	// retrieve current liquidated revenue 
	double liquidated_revenue(const MarketSimulation& ms) const;
};