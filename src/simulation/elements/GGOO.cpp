#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_GGOO()
{
  Identifier = "DEFAULT_PT_GGOO";
  Name = "GGOO";
  Colour = PIXPACK(0x808080);
  MenuVisible = 0;
  MenuSection = SC_SPECIAL;
  Enabled = 1;
  
  Advection = 0.4f;
  AirDrag = 0.04f * CFDS;
  AirLoss = 0.94f;
  Loss = 0.80f;
  Collision = 0.0f;
  Gravity = 0.0f;
  Diffusion = 0.10f;
  HotAir = 0.000f	* CFDS;
  Falldown = 2;
  
  Flammable = 0;
  Explosive = 0;
  Meltable = 0;
  Hardness = 20;
  
  Weight = 70;
  
  HeatConduct = 200;
  Description = "Grey goo. Turns everything into more of itself";
  
  Properties = TYPE_LIQUID;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = ITH;
  HighTemperatureTransition = NT;
  
  Update = &update;
  
}


static int update(UPDATE_FUNC_ARGS)
{
  
  int rx = 0;
  int ry = 0;
  int r = 0;
  
  for (rx=-1; rx<2; rx++) 
    for (ry=-1; ry<2; ry++)
      if (BOUNDS_CHECK && (rx || ry))
      {
        r = pmap[y+ry][x+rx];
        if (!r) {
          continue;
        }
        
        else if (TYP(r) == PT_POTA && RNG::Ref().chance(1,3))
        {
          //sim->kill_part(i);
          //sim->create_part(i,x,y,PT_POTA);
          sim->part_change_type(i, x, y, PT_POTA);
          parts[i].tmp = RNG::Ref().between(-3,3); // Darker than normal potatoes
        }
        
        else if (TYP(r) != PT_DMND && RNG::Ref().chance(1,10))
        {
          sim->part_change_type(ID(r), x+rx, y+ry, PT_GGOO);
        }
      }
      
      
  return 0;
}