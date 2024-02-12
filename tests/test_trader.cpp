#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Trader.h"

TEST_CASE("sell inverts a buy", "[tests]")
{
	Trader t(100.0);

	// asset with price of 50
	Asset a("MSFT", 50.0, 0.0);
	
	// we should be able to buy two at 50 each
	t.buy(a.name(), a.price(), 2.0);

	REQUIRE(t.get_asset_quantity(a) == 2.0);
	REQUIRE(t.get_cash() == 0.0);

	// sell at the same price we bought
	t.sell(a.name(), a.price(), 2.0);

	REQUIRE(t.get_asset_quantity(a) == 0.0);
	REQUIRE(t.get_cash() == 100.0);
}

TEST_CASE("can't buy when out of cash", "[tests]")
{
	Trader t(100.0);

	// asset with price of 50
	Asset a("MSFT", 50.0, 0.0);
	
	// we should be able to buy two at 50 each
	t.buy(a.name(), a.price(), 2.0);

	REQUIRE(t.get_asset_quantity(a) == 2.0);
	REQUIRE(t.get_cash() == 0.0);

	// we are out of cash so nothing should happen
	t.buy(a.name(), a.price(), 2.0);

	REQUIRE(t.get_asset_quantity(a) == 2.0);
	REQUIRE(t.get_cash() == 0.0);
}

TEST_CASE("can't sell when out of assets", "[tests]")
{
	Trader t(100.0);

	// asset with price of 50
	Asset a("MSFT", 50.0, 0.0);
	
	// we should be able to buy two at 50 each
	t.buy(a.name(), a.price(), 2.0);

	REQUIRE(t.get_asset_quantity(a) == 2.0);
	REQUIRE(t.get_cash() == 0.0);

	t.sell(a.name(), a.price(), 2.0);

	REQUIRE(t.get_asset_quantity(a) == 0.0);
	REQUIRE(t.get_cash() == 100.0);

	// doing another sell should have no effect
	t.sell(a.name(), a.price(), 2.0);

	REQUIRE(t.get_asset_quantity(a) == 0.0);
	REQUIRE(t.get_cash() == 100.0);

}