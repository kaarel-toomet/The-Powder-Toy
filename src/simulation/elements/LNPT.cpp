#include "simulation/ElementCommon.h"


void Element::Element_LNPT()
{
	Identifier = "DEFAULT_PT_LNPT";
	Name = "LNPT";
	Colour = PIXPACK(0x505030);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.2f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 60;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 20;

	HeatConduct = 42;
	Description = "Light naphtha. Volatile and flammable";

	Properties = TYPE_LIQUID | PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 313.15f;
	HighTemperatureTransition = PT_LNPV;
	
	DefaultProperties.tmp = 30;
	
	Update = &update;
}
