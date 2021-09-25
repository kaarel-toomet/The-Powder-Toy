#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
// static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_THOR()
{
  Identifier = "DEFAULT_PT_THOR";
  Name = "THOR";
  Colour = PIXPACK(0x306050);
  MenuVisible = 1;
  MenuSection = SC_NUCLEAR;
  Enabled = 1;
  
  Advection = 0.4f;
  AirDrag = 0.01f * CFDS;
  AirLoss = 0.99f;
  Loss = 0.95f;
  Collision = 0.0f;
  Gravity = 0.4f;
  Diffusion = 0.00f;
  HotAir = 0.000f	* CFDS;
  Falldown = 1;
  
  Flammable = 0;
  Explosive = 0;
  Meltable = 0;
  Hardness = 0;
  PhotonReflectWavelengths = 0x001FCE00;
  
  Weight = 90;
  
  DefaultProperties.temp = R_TEMP + 2.0f + 273.15f;
  DefaultProperties.tmp2 = 100;
  HeatConduct = 251;
  Description = "Thorium. Heavy particles with a high melting temperature. Becomes fissile when irradiated by neutrons";
  
  Properties = TYPE_PART | PROP_NEUTPASS | PROP_RADIOACTIVE;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = 2023.0f;
  HighTemperatureTransition = PT_LAVA;
  
  Update = &update;
  // Create = &create;
  Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS)
{
 if (RNG::Ref().chance(parts[i].tmp, 100000))
 {
   parts[i].tmp -= 1;
   parts[i].temp += 50;
   int n1 = sim->create_part(-1,x,y,PT_NEUT);
   int n2 = sim->create_part(-1,x,y,PT_NEUT);
   int n3 = sim->create_part(-1,x,y,PT_NEUT);
   parts[n1].temp = parts[i].temp+50;
   parts[n2].temp = parts[i].temp+50;
   parts[n3].temp = parts[i].temp+50;
   sim->pv[y/CELL][x/CELL] += 0.1f * CFDS;
 }
 if (RNG::Ref().chance(parts[i].tmp2 + parts[i].tmp*10, 10000)) {
   int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
   parts[a1].temp = parts[i].temp;
   parts[i].temp += 1;
 }
 return 0;
}

// static void create(ELEMENT_CREATE_FUNC_ARGS)
// {
//   sim->parts[i].tmp2 = 100;
// }

static int graphics(GRAPHICS_FUNC_ARGS)
{
  

  
  *colr += (100-cpart->tmp2);
  //*colg += z;
  *colb += (cpart->tmp)*2;
  
  // *firea = 20;
  // *firer = 48;
  // *fireg = 96;
  // *fireb = 80;
  
//   double tempOver = (cpart->temp - 800);
//   
//   //if(tempOver > 0)
// //  {
//     //if(tempOver > (2000))
//      // tempOver = (2000);
//     
//     *firer = (int)(tempOver * 6);
//     *fireg = (int)(tempOver * 4);
//     *fireb = (int)(tempOver * 2);
//     *firea = (int)(tempOver * 0.5);
//  // }
  
  *pixel_mode |= PMODE_GLOW;
  return 0;
}
