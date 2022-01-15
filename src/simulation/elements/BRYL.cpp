#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
// static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_BRYL()
{
  Identifier = "DEFAULT_PT_BRYL";
  Name = "BRYL";
  Colour = PIXPACK(0x485040);
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
  
  Flammable = 1;
  Explosive = 0;
  Meltable = 1;
  Hardness = 1;
  
  Weight = 100;
  
  HeatConduct = 251;
  Description = "Beryllium. Brittle metal. Reflects and diffuses neutrons. Can produce neutrons when irradiated by alpha rays.";
  
  Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW|PROP_NEUTPASS|PROP_PAVGDP;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = 1560.0f;
  HighTemperatureTransition = PT_LAVA;
  
  DefaultProperties.tmp = 5;
  
  Update = &update;
  // Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
  auto press = int(sim->pv[y/CELL][x/CELL] * 64);
  auto diff = press - parts[i].tmp3;
  if (diff > 24 || diff < -24)
  {
    sim->part_change_type(i,x,y,PT_BRMT);
    parts[i].ctype = PT_BRYL;
  }
  parts[i].tmp3 = press;
  return 0;
}

// static void create(ELEMENT_CREATE_FUNC_ARGS)
// {
//   //sim->parts[i].tmp2 = RNG::Ref().between(0, 10);
//   sim->parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
// }
