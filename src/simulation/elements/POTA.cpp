#include "simulation/ElementCommon.h"

static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);
static int update(UPDATE_FUNC_ARGS);

void Element::Element_POTA() //Kaarli jura
{
  Identifier = "DEFAULT_PT_POTA";
  Name = "POTA";
  Colour = PIXPACK(0x907040);
  MenuVisible = 1;
  MenuSection = SC_POWDERS;
  Enabled = 1;
  
  Advection = 0.7f;
  AirDrag = 0.02f * CFDS;
  AirLoss = 0.96f;
  Loss = 1.00f;
  Collision = 0.0f;
  Gravity = 0.2f;
  Diffusion = 0.00f;
  HotAir = 0.000f	* CFDS;
  Falldown = 1;
  
  Flammable = 0;
  Explosive = 0;
  Meltable = 1;
  Hardness = 40;
  PhotonReflectWavelengths = 0x3DEEDC84;
  
  Weight = 87;
  
  HeatConduct = 20;
  Description = "Potatoes.";
  
  Properties = TYPE_PART | PROP_NEUTPENETRATE;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = 266.0f;
  LowTemperatureTransition = PT_ICEI;
  HighTemperature = MAX_TEMP - 20.0f;
  HighTemperatureTransition = PT_PLSM;
  
  Graphics = &graphics;
  Create = &create;
  Update = &update;
  
 
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
  int z = (cpart->tmp - 5) * 8;
  *colr += z;
  *colg += z;
  *colb += z;
  return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  sim->parts[i].tmp = RNG::Ref().between(0, 6);
}

static int update(UPDATE_FUNC_ARGS)
{
  
  bool canburn = false;
  int oxygenaccess = 0;
  bool fire = false;
  int oxygen_x = 0;
  int oxygen_y = 0;
  int rx = 0;
  int ry = 0;
  int r = parts[i].type;
  for (rx=-2; rx<3; rx++)
    for (ry=-2; ry<3; ry++)
      if (BOUNDS_CHECK && (rx || ry))
      {
        r = pmap[y+ry][x+rx];
        if (!r) {
          if (oxygenaccess <= 1) 
            {
            oxygenaccess = 1;
            oxygen_x = x+rx;
            oxygen_y = y+ry;
            }
          continue;
          }
          
        else if (TYP(r) == PT_PTNM) {
          canburn = true;
          
        }
        else if (TYP(r) == PT_O2) {
          oxygenaccess = 2;
          oxygen_x = x+rx;
          oxygen_y = y+ry;
        }
        else if (TYP(r) == PT_FIRE) {
          fire = true;
        }
      }
  if (canburn && (oxygenaccess > 0) && (fire ||  (parts[i].temp > 800.0f) )) {
    
    if (oxygenaccess == 2) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_FIRE);
      parts[i].temp = parts[i].temp+1000;
      sim->kill_part(ID(pmap[oxygen_y][oxygen_x]));
    }
    else {
      
      int f = sim->create_part(-1,oxygen_x,oxygen_y,PT_FIRE);
      parts[f].temp = parts[i].temp+200;
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_FIRE);
      parts[i].temp = parts[i].temp+200;
    }
    return 1;
  }
  
  return 0;
}
