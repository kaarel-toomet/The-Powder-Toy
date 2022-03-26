#include "simulation/ElementCommon.h"

void Element::Element_LNPV()
{
	Identifier = "DEFAULT_PT_LNPV";
	Name = "LNPV";
	Colour = PIXPACK(0x808060);
	MenuVisible = 1;
	MenuSection = SC_GAS;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 1.0f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.75f;
	HotAir = 0.0005f	* CFDS;
	Falldown = 0;

	Flammable = 60;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 1;

	HeatConduct = 10;
	Description = "Light naphtha vapors. Very flammable. Can explode when mixed with air; watch out!";

	Properties = TYPE_GAS | PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 313.15f;
	LowTemperatureTransition = PT_LNPT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	DefaultProperties.tmp = 5;
	DefaultProperties.temp = 333.15f;
}
