#include "simulation/ElementCommon.h"
#include "simulation/Air.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_BMTL()
{
	Identifier = "DEFAULT_PT_BMTL";
	Name = "BMTL";
	Colour = PIXPACK(0x505070);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.10f * CFDS;
	AirLoss = 1.00f;
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

	HeatConduct = 251;
	Description = "Breakable metal. Common conductive building material, can melt and break under pressure.";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 1.0f;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1273.0f;
	HighTemperatureTransition = PT_LAVA;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	if (parts[i].tmp>1)
	{
		parts[i].tmp--;
		for (rx=-1; rx<2; rx++)
			for (ry=-1; ry<2; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
						continue;
					if ((TYP(r)==PT_METL || TYP(r)==PT_IRON) && RNG::Ref().chance(1, 100))
					{
						sim->part_change_type(ID(r),x+rx,y+ry,PT_BMTL);
						parts[ID(r)].tmp = (parts[i].tmp<=7) ? parts[i].tmp=1 : parts[i].tmp - RNG::Ref().between(0, 4);
					}
				}
	}
	else if (parts[i].tmp==1 && RNG::Ref().chance(1, 1000))
	{
		parts[i].tmp = 0;
		sim->part_change_type(i,x,y,PT_BRMT);
		
	}
	
	// int bmtl = 0;
	// if (nt <= 2)
	//   bmtl = 2;
	// else if (nt <= 6)
	// {
	//   for (int rx = -1; rx <= 1; rx++)
	//     for (int ry = -1; ry <= 1; ry++)
	//       if ((!rx != !ry) && BOUNDS_CHECK)
	//       {
	//         if (TYP(pmap[y+ry][x+rx]) == PT_BMTL)
	//           bmtl++;
	//       }
	// }
	// 
	// if (bmtl >= 2)
	// {
	//   sim->air->bmap_blockair[y/CELL][x/CELL] = 1;
	//   sim->air->bmap_blockairh[y/CELL][x/CELL] = 0x8;
	// }
	
	
	float p = sim->pv[y/CELL][x/CELL];
	float v = pow(sim->pv[y/CELL+1][x/CELL] - p,2) + pow(sim->pv[y/CELL-1][x/CELL] - p,2);
	float h = pow(sim->pv[y/CELL][x/CELL+1] - p,2) + pow(sim->pv[y/CELL][x/CELL-1] - p,2);
	if (h+v > 1)
	  sim->part_change_type(i,x,y,PT_BRMT);
	return 0;
}




