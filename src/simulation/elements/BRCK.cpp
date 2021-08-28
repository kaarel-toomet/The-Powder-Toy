#include "simulation/ElementCommon.h"

static int graphics(GRAPHICS_FUNC_ARGS);
static int update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_BRCK()
{
	Identifier = "DEFAULT_PT_BRCK";
	Name = "BRCK";
	Colour = PIXPACK(0x808080);
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
	Meltable = 0;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "Brick, breakable building material.";

	Properties = TYPE_SOLID|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 8.8f;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1223.0f;
	HighTemperatureTransition = PT_LAVA;

	Graphics = &graphics;
	Update = &update;
	Create = &create;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	if (cpart->tmp == 1)
	{
		*pixel_mode |= FIRE_ADD;
		*colb += 100;

		*firea = 40;
		*firer = *colr;
		*fireg = *colg;
		*fireb = *colb;
	}
	return 0;
}

int update(UPDATE_FUNC_ARGS)
{
  parts[i].pavg[0] = parts[i].pavg[1];
  parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
  float diff = parts[i].pavg[1] - parts[i].pavg[0];
  if (diff > 0.5f || diff < -0.5f)
  {
    sim->part_change_type(i,x,y,PT_STNE);
    return 1;
  }
  return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  sim->parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
}