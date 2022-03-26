#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_CRDE()
{
  Identifier = "DEFAULT_PT_CRDE";
  Name = "CRDE";
  Colour = PIXPACK(0x302010);
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
  
  Flammable = 20;
  Explosive = 0;
  Meltable = 0;
  Hardness = 5;
  
  Weight = 20;
  
  HeatConduct = 42;
  Description = "Crude oil. Flammable. Can be refined into various components by fractional distillation";
  
  Properties = TYPE_LIQUID | PROP_NEUTPASS;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = 333.0f;
  HighTemperatureTransition = NT;
  
  DefaultProperties.tmp = 20;
  
  Update = &update;
}
static int update(UPDATE_FUNC_ARGS)
{
  if (parts[i].temp > RNG::Ref().between(350,2000))
  {
    int nt = RNG::Ref().between(0,2);
    switch (nt) {
    case 0:
      sim->part_change_type(i,x,y,PT_MWAX);
      break;
    case 1:
      sim->part_change_type(i,x,y,PT_GAS);
      parts[i].temp -= 20;
      break;
    case 2:
      sim->part_change_type(i,x,y,PT_LNPV);
      parts[i].temp -= 20;
      break;
    }
  }
  return 0;
}