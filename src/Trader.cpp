#include "Trader.h"

thread_local std::array<double, Asset::MAXIMUM_HISTORY> Trader::history_working_array({});

Trader::Trader(double initial_cash)
	:
	m_initial_cash(initial_cash),
	m_cash(initial_cash)
{
	// Make sure we don't allow construction with a negative amount of starting cash
	if (m_cash < 0.0)
		throw std::runtime_error("Can't have a negative amount of cash");
}

void Trader::buy(const std::string& name, double price, double amount)
{
	if (amount <= 0.0)
		return;

	// this ensures we will not be able to overspend, if we don't have enough
	// cash we buy the max amount we can which is m_cash / price
	amount = std::min<double>(m_cash / price, amount);

	// add amount of asset
	m_portfolio[name] += amount;

	// remove the cash we used to buy
	m_cash -= amount * price;
}

void Trader::sell(const std::string& name, double price, double amount)
{
	if (amount <= 0.0)
		return;

	// if we don't have enough to sell we just sell all the asset we own (possibly 0)
	amount = std::min<double>(m_portfolio[name], amount);

	// remove amount of asset
	m_portfolio[name] -= amount;

	// add cash from selling
	m_cash += amount * price;
}

double Trader::determine_buy_amount(const Asset& asset)
{
	// get the last 50 prices
	const unsigned int history_to_use = 50;

	// retrieve the historical prices from the asset 
	// note the amount of history we request might not be avaiable
	// amount_copied contained the true amount of history we have
	unsigned int amount_copied = asset.get_price_history(history_working_array.data(), history_to_use);

	// not enough history to make decision
	if (amount_copied < history_to_use)
		return 0.0;

	// compute the moving average
	double average = 0.0;

	for (unsigned int i = 0; i < amount_copied; ++i)
		average += history_working_array[i];

	average /= history_to_use;

	// if current price is less than 95% of moving average, we buy as much as we can
	if (asset.price() < average * 0.95)
		return m_cash / asset.price();

	// otherwise, don't buy anything
	return 0.0;
}

double Trader::determine_sell_amount(const Asset& asset)
{
	// get the last 50 prices
	const unsigned int history_to_use = 50;

	// retrieve the historical prices from the asset 
	// note the amount of history we request might not be avaiable
	// amount_copied contained the true amount of history we have
	unsigned int amount_copied = asset.get_price_history(history_working_array.data(), history_to_use);

	// not enough history to make decision
	if (amount_copied < history_to_use)
		return 0.0;

	// compute the moving average
	double average = 0.0;

	for (unsigned int i = 0; i < amount_copied; ++i)
		average += history_working_array[i];

	average /= history_to_use;

	// if current price is more than than 105% of moving average, we sell all we own
	if (asset.price() > average * 1.05)
		return m_portfolio[asset.name()];

	// otherwise, don't sell anything
	return 0.0;
}

void Trader::interact(const Asset& asset)
{
	// note it would be optimal to compute the difference between 
	// buying and selling amount and just do one trade
	// but not too important
	buy(asset.name(), asset.price(), determine_buy_amount(asset));
	sell(asset.name(), asset.price(), determine_sell_amount(asset));
}


double Trader::liquidated_total(const MarketSimulation& ms) const
{
	return m_cash + ms.liquidate_portfolio(m_portfolio);
}

double Trader::liquidated_revenue(const MarketSimulation& ms) const
{
	return liquidated_total(ms) - m_initial_cash;
}

double Trader::get_asset_quantity(const Asset& asset) const
{
	return m_portfolio.at(asset.name());
}

double Trader::get_cash() const
{
	return m_cash;
}