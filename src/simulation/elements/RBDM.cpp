#include "simulation/ElementCommon.h"

void Element::Element_RBDM()
{
	Identifier = "DEFAULT_PT_RBDM";
	Name = "RBDM";
	Colour = PIXPACK(0xCCCCCC);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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

	Flammable = 200;
	Explosive = 0;
	Meltable = 50;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 200;
	Description = "Rubidium. Explosive, especially on contact with water. Low melting point.";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 312.0f;
	HighTemperatureTransition = PT_LRBD;
	
	DefaultProperties.tmp = 10;
}
