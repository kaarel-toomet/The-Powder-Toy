#include "common/tpt-minmax.h"
#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

void Element::Element_WOOD()
{
	Identifier = "DEFAULT_PT_WOOD";
	Name = "WOOD";
	Colour = PIXPACK(0xC0A040);
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

	Flammable = 20;
	Explosive = 0;
	Meltable = 0;
	Hardness = 15;

	Weight = 100;

	HeatConduct = 64;
	Description = "Wood, flammable.";

	Properties = TYPE_SOLID | PROP_NEUTPENETRATE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 873.0f;
	HighTemperatureTransition = NT; // turning into COAL and gases done in update function, temp stored here
	
	DefaultProperties.tmp = 50;

	Update = &update;
	Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 450 && parts[i].temp > parts[i].tmp2)
		parts[i].tmp2 = (int)parts[i].temp;
	
	if (parts[i].temp > sim->elements[PT_WOOD].HighTemperature + RNG::Ref().between(0,200) && RNG::Ref().chance(1,50))
	{
	  
	  int nt = RNG::Ref().between(0,2);
	  switch (nt) {
	  case 0:
	    sim->part_change_type(i,x,y,PT_COAL);
	    parts[i].life = parts[i].tmp;
	    break;
	  case 1:
	    sim->part_change_type(i,x,y,PT_CO);
	    parts[i].life = 5;
	    break;
	  case 2:
	    sim->part_change_type(i,x,y,PT_H2);
	    parts[i].life = 5;
	    break;
	  }
	  
	  //sim->part_change_type(i, x, y, PT_COAL);
	  
	}
	  

	if (parts[i].temp > 773.0f && sim->pv[y/CELL][x/CELL] <= -10.0f)
	{
		float temp = parts[i].temp;
		sim->create_part(i, x, y, PT_BCOL);
		parts[i].temp = temp;
	}

	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	float maxtemp = std::max((float)cpart->tmp2, cpart->temp);
	if (maxtemp > 400)
	{
		*colr -= (int)restrict_flt((maxtemp-400)/3,0,172);
		*colg -= (int)restrict_flt((maxtemp-400)/4,0,140);
		*colb -= (int)restrict_flt((maxtemp-400)/20,0,44);
	}
	if (maxtemp < 273)
	{
		*colr -= (int)restrict_flt((273-maxtemp)/5,0,40);
		*colg += (int)restrict_flt((273-maxtemp)/4,0,40);
		*colb += (int)restrict_flt((273-maxtemp)/1.5,0,150);
	}
	return 0;
}
