#include "simulation/ElementCommon.h"
#include "simulation/Air.h"

static int update(UPDATE_FUNC_ARGS);
//static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_PTST()
{
  Identifier = "DEFAULT_PT_PTST";
  Name = "PTST";
  Colour = PIXPACK(0x706050);
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
  Meltable = 1;
  Hardness = 1;
  
  Weight = 100;
  
  HeatConduct = 251;
  Description = "Potato steel. Strong but explosive.";
  
  Properties = TYPE_SOLID | PROP_CONDUCTS | PROP_LIFE_DEC | PROP_HOT_GLOW | PROP_PAVGDP;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = 2098.8f;
  HighTemperatureTransition = PT_LAVA;
  
  Update = &update;
  //Graphics = &graphics;
  Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
  // parts[i].pavg[0] = parts[i].pavg[1];
  // parts[i].pavg[1] = sim->pv[y/CELL][x/CELL];
  auto press = int(sim->pv[y/CELL][x/CELL] * 64);
  auto diff = press - parts[i].tmp3;
  if (diff > 32 || diff < -32)
  {
    //sim->kill_part(i);
    //sim->create_part(i,x,y,PT_POTA);
    sim->part_change_type(i,x,y,PT_POTA);
    parts[i].temp += 5000;
    sim->pv[y/CELL][x/CELL] += 20.0f * CFDS;
    return 1;
  }
  parts[i].tmp3 = press;
  //if (parts[i].pavg[1]-parts[i].pavg[0] > 2.0f)
  // {
  //   //sim->part_change_type(i,x,y,PT_POTA);
  //   sim->kill_part(i);
  //   sim->create_part(i,x,y,PT_POTA);
  //   parts[i].temp += 5000;
  //   sim->pv[y/CELL][x/CELL] += 20.0f * CFDS;
  //   return 1;
  // }
  return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  sim->parts[i].tmp2 = RNG::Ref().between(0, 10);
  sim->parts[i].tmp3 = int(sim->pv[y/CELL][x/CELL] * 64);
}
