#include "simulation/ElementCommon.h"

static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);
static int update(UPDATE_FUNC_ARGS);

void Element::Element_GTIN()
{
	Identifier = "DEFAULT_PT_GTIN";
	Name = "GTIN";
	Colour = PIXPACK(0x707C7C);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.3f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 2;
	Hardness = 2;

	Weight = 90;

	HeatConduct = 211;
	Description = "Gray tin. Created from TIN at cold temperatures, especially in contact with silicon";

	Properties = TYPE_PART | PROP_LIFE_DEC; // PROP_LIFE_DEC is necessary for MERC amalgamation

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 9505.08f; // melting in update function
	HighTemperatureTransition = NT;

	Update = &update;
	Graphics = &graphics;
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 505.08f)
	{
	  sim->part_change_type(i, x, y, PT_LAVA);
	  parts[i].ctype = PT_TIN;
	  return 1;
	}
	if (parts[i].life != 0) 
	{
	  parts[i].vx=0;
	  parts[i].vy=0;
	}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
  int z = (cpart->tmp - 5) * 8;
  *colr += z;
  *colg += z;
  *colb += z;
  return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  sim->parts[i].tmp = RNG::Ref().between(0, 6);
}





