#include "simulation/ElementCommon.h"

static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);
static int update(UPDATE_FUNC_ARGS);

void Element::Element_TEST() 
{
  Identifier = "DEFAULT_PT_TEST";
  Name = "TEST";
  Colour = PIXPACK(0x808080);
  MenuVisible = 1;
  MenuSection = SC_SPECIAL;
  Enabled = 1;
  
  Advection = 0.7f;
  AirDrag = 0.02f * CFDS;
  AirLoss = 0.9f;
  Loss = 1.00f;
  Collision = 0.0f;
  Gravity = 0.2f;
  Diffusion = 0.00f;
  HotAir = 0.000f	* CFDS;
  Falldown = 2;
  
  Flammable = 0;
  Explosive = 0;
  Meltable = 0;
  Hardness = 20;
  PhotonReflectWavelengths = 0x12345678;
  
  Weight = 90;
  
  DefaultProperties.tmp = 50;
  DefaultProperties.life = 1;
  
  HeatConduct = 100;
  Description = "Experimental element.";
  
  Properties = TYPE_LIQUID | PROP_NEUTPENETRATE | PROP_HOT_GLOW;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = 1234.4321f;
  HighTemperatureTransition = NT;
  
  Graphics = &graphics;
  Create = &create;
  Update = &update;
  
  
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
  int z = (cpart->tmp - 5) / 8;
  *colr += z;
  *colg += z + cpart->life*20;
  *colb += z;
  *pixel_mode |= PMODE_BLUR;
  return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  //sim->parts[i].tmp = RNG::Ref().between(0, 6);
}

static int update(UPDATE_FUNC_ARGS)
{
  
  int rx = 0;
  int ry = 0;
  int r = 0;
  int chance = 20;
  bool h = 0;
  
  if (parts[i].temp > parts[i].tmp*parts[i].life + 273.15) {
    parts[i].life += 1;
    parts[i].temp -= 100;
  }
  else if (parts[i].temp < parts[i].tmp * (parts[i].life - 1)  +  273.15) {
    parts[i].life -= 1;
    parts[i].temp += 100;
  }
  
  
  for (rx=-1; rx<2; rx++) 
    for (ry=-1; ry<2; ry++)
      if (BOUNDS_CHECK && (rx || ry))
      {
        r = pmap[y+ry][x+rx];
        if (!r) {
          continue;
        }
        

        else if (TYP(r) == PT_GOLD && !h)
        {
          chance -= 1;
          
          parts[i].vx = 0;
          parts[i].vy = 0;
          if (RNG::Ref().chance(1,chance) and parts[ID(r)].life == 0) {
            parts[ID(r)].x = x;
            parts[ID(r)].y = y;
            parts[i].x += rx;
            parts[i].y += ry;
            //std::cout << h << "\n";
            h = 1;
            parts[ID(r)].life = 1;
          }
        }
      }
  
  
  return 0;
}
