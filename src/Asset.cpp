#include "Asset.h"
#include <algorithm>

// random seed is based on the current time
thread_local std::default_random_engine Asset::RANDOM_GENERATOR{ static_cast<long unsigned int>(time(0))};

Asset::Asset()
	:
	Asset("UNITIALISED", 0.0, 0.0)
{}

Asset::Asset(const std::string& name, double initial_price, double initial_volatility)
	:
	m_name(name),
	m_initial_price(initial_price),
	m_price(initial_price),
	m_volatility(initial_volatility)
{}

void Asset::tick_update()
{
	// object to generate Z where Z ~ N(0, 1)
	std::normal_distribution<double> dist(0.0, 1.0);

	// add the incremement
	m_price = exp(log(m_price) + dist(RANDOM_GENERATOR) * m_volatility);

	// update price history after getting new price
	m_history.push_back(m_price);

	if (m_history.size() > MAXIMUM_HISTORY)
		m_history.pop_front();
}

unsigned int Asset::get_price_history(double* const history, unsigned int amount) const
{
	if (amount > m_history.size())
		amount = (unsigned int) m_history.size();

	std::copy_n(m_history.begin(), amount, history);

	return amount;
}

double Asset::price() const
{
	return m_price;
}

const std::string& Asset::name() const
{
	return m_name;
}
