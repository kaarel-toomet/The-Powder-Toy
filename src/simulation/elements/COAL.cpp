#include "simulation/ElementCommon.h"

int Element_COAL_update(UPDATE_FUNC_ARGS);
int Element_COAL_graphics(GRAPHICS_FUNC_ARGS);
// static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_COAL()
{
	Identifier = "DEFAULT_PT_COAL";
	Name = "COAL";
	Colour = PIXPACK(0x222222);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.0f;
	HotAir = 0.0f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;
	PhotonReflectWavelengths = 0x00000000;

	Weight = 100;

	HeatConduct = 12;
	Description = "Coal, Burns very slowly. Gets red when hot.";

	Properties = TYPE_SOLID|PROP_PAVGDP;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	DefaultProperties.life = 100;
	DefaultProperties.tmp = 50;

	Update = &Element_COAL_update;
	Graphics = &Element_COAL_graphics;
	// Create = &create;
}

int Element_COAL_update(UPDATE_FUNC_ARGS)
{
	if (parts[i].life<=0) {
		sim->create_part(i, x, y, PT_FIRE);
		return 1;
	} else if (parts[i].temp > 500 + RNG::Ref().between(-150,1000)) {
		
		int f = sim->create_part(-1, x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1), PT_FIRE);
		//
		if (f != -1)
		{
		  parts[i].life--;
		  parts[i].temp += 20;
		  parts[f].temp = parts[i].temp;
		  if (parts[i].life < 50 && RNG::Ref().chance(1,100) && parts[i].temp > 500) {
		    sim->pv[y/CELL][x/CELL] += 0.5f * CFDS;
		    sim->part_change_type(i, x, y, PT_BCOL);
		    return 1;
		  }
		}
	}
	if (parts[i].type == PT_COAL)
	{
	  // parts[i].pavg[0] = parts[i].pavg[1];
	  // parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
	  auto press = int(sim->pv[y/CELL][x/CELL] * 64);
	  auto diff = press - parts[i].tmp3;
	  if (diff > 8 || diff < -8)
	  {
	    parts[i].tmp -= (int)diff*20;
	  }
	  parts[i].tmp3 = press;
	  // float diff = parts[i].pavg[1] - parts[i].pavg[0];
	  // if (diff > 0.20f || diff < -0.20f)
	  // {
	  //   parts[i].tmp -= (int)diff*20;
	  // }
	  
		// if ((sim->pv[y/CELL][x/CELL] > 4.3f)&&parts[i].tmp>40)
		// 	parts[i].tmp=39;
		// else if (parts[i].tmp<40&&parts[i].tmp>0)
		// 	parts[i].tmp--;
		if (parts[i].tmp<=0) {
		  sim->part_change_type(i, x, y, PT_BCOL);
		  return 1;
	  }
	}
	if(parts[i].temp > parts[i].tmp2)
		parts[i].tmp2 = int(parts[i].temp);
	return 0;
}

constexpr float FREQUENCY = 3.1415f/(2*300.0f-(300.0f-200.0f));

int Element_COAL_graphics(GRAPHICS_FUNC_ARGS)
 //Both COAL and Broken Coal
{
	*colr += int((cpart->tmp2-295.15f)/3);

	if (*colr > 170)
		*colr = 170;
	if (*colr < *colg)
		*colr = *colg;

	*colg = *colb = *colr;

	// ((cpart->temp-295.15f) > 300.0f-200.0f)
	if (cpart->temp > 395.15f)
	{
		//  q = ((cpart->temp-295.15f)>300.0f)?300.0f-(300.0f-200.0f):(cpart->temp-295.15f)-(300.0f-200.0f);
		auto q = int((cpart->temp > 595.15f) ? 200.0f : cpart->temp - 395.15f);

		*colr += int(sin(FREQUENCY*q) * 226);
		*colg += int(sin(FREQUENCY*q*4.55 + 3.14) * 34);
		*colb += int(sin(FREQUENCY*q*2.22 + 3.14) * 64);
	}
	return 0;
}

// static void create(ELEMENT_CREATE_FUNC_ARGS)
// {
  // sim->parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
// }