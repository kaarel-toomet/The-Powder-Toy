#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
// static int graphics(GRAPHICS_FUNC_ARGS);
//static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_CALI()
{
  Identifier = "DEFAULT_PT_CALI";
  Name = "CALI";
  Colour = PIXPACK(0x2060C0);
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
  Meltable = 1;
  Hardness = 0;
  PhotonReflectWavelengths = 0x008FFF20;
  
  Weight = 90;
  
  DefaultProperties.temp = 388.15f;
  DefaultProperties.tmp = 10000;
  HeatConduct = 251;
  Description = "Californium-252, highly radioactive. Decays with alpha particles and neutrons";
  
  Properties = TYPE_PART|PROP_NEUTPASS|PROP_RADIOACTIVE|PROP_LIFE_DEC|PROP_DEADLY;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = 1173.0f;
  HighTemperatureTransition = PT_LAVA;
  
  Update = &update;
  // Graphics = &graphics;
  //Create = &create;
}


static int update(UPDATE_FUNC_ARGS)
{

  int a1, n1;
  if (RNG::Ref().chance(1,2)) {
    a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
    parts[a1].temp = parts[i].temp;
    parts[i].tmp -= 1;
    parts[i].temp += 2;
  }
  if (RNG::Ref().chance(1,5)) {
    n1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_NEUT);
    parts[n1].temp = parts[i].temp;
    parts[i].tmp -= 1;
    parts[i].temp += 10;
  }
  return 0;
}

// static int graphics(GRAPHICS_FUNC_ARGS)
// {
//     *pixel_mode |= PMODE_GLOW;
//   
//   return 0;
// }

//static void create(ELEMENT_CREATE_FUNC_ARGS) 
//{
//  parts[i].tmp = 1000
//}
