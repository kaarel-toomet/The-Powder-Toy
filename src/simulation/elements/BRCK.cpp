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

	HeatConduct = 40;
	Description = "Brick, breakable building material.";

	Properties = TYPE_SOLID|PROP_HOT_GLOW|PROP_PAVGDP;

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
  auto press = int(sim->pv[y/CELL][x/CELL] * 64);
  auto diff = press - parts[i].tmp3;
  if (diff > 16 || diff < -16)
  {
    sim->part_change_type(i,x,y,PT_STNE);
    //parts[i].ctype = PT_BRYL;
  }
  parts[i].tmp3 = press;
  return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  sim->parts[i].tmp3 = int(sim->pv[y/CELL][x/CELL] * 64);
}