#include "simulation/ElementCommon.h"

void Element::Element_PDSC()
{
	Identifier = "DEFAULT_PT_PDSC";
	Name = "PDSC";
	Colour = PIXPACK(0x605040);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 201;
	Description = "Potato-doped silicon.";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 2345.0f;
	HighTemperatureTransition = PT_POTA;
}
