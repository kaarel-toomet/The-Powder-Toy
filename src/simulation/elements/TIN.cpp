#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_TIN()
{
  Identifier = "DEFAULT_PT_TIN";
  Name = "TIN";
  Colour = PIXPACK(0xD0D0C0);
  MenuVisible = 1;
  MenuSection = SC_SOLIDS;
  Enabled = 1;
  
  Advection = 0.003f;
  AirDrag = 1.00f * CFDS;
  AirLoss = 0.20f;
  Loss = 0.90f;
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
  Description = "Tin. Soft metal with a low melting temperature. Can turn into gray tin at cold temperatures.";
  
  Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = 505.08f;
  HighTemperatureTransition = PT_LAVA;
  
  Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
  float temp_under = (13.0f + 273.15f) - parts[i].temp;
  int n = 1;
  int r, rx, ry, rt;
  for (rx=-1; rx<2; rx++)
    for (ry=-1; ry<2; ry++)
      if (BOUNDS_CHECK && (rx || ry))
        {
          r = pmap[y+ry][x+rx];
          if (!r)
            continue;
          rt = TYP(r);
          if (rt==PT_SLCN || rt==PT_PSCN || rt==PT_NSCN || rt==PT_NTCT) {n += 2000;}
          if (rt==PT_GTIN) {n += 10000;}
        }
  if (RNG::Ref().chance(temp_under*n*(parts[i].temp/(13.0f + 273.15f)),300000000) && temp_under > 0) {
    sim->part_change_type(i,x,y,PT_GTIN);
    sim->parts[i].tmp = RNG::Ref().between(0, 6);
    sim->parts[i].life = RNG::Ref().between(0, 2000);
    //return 1;
  }
  return 0;
}


