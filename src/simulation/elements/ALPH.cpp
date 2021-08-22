#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_ALPH()
{
  Identifier = "DEFAULT_PT_ALPH";
  Name = "ALPH";
  Colour = PIXPACK(0x303030);
  MenuVisible = 1;
  MenuSection = SC_NUCLEAR;
  Enabled = 1;
  
  Advection = 0.0f;
  AirDrag = 0.00f * CFDS;
  AirLoss = 1.00f;
  Loss = 1.00f;
  Collision = -0.99f;
  Gravity = 0.0f;
  Diffusion = 0.00f;
  HotAir = 0.000f	* CFDS;
  Falldown = 0;
  
  Flammable = 0;
  Explosive = 0;
  Meltable = 0;
  Hardness = 0;
  
  Weight = -1;
  
  HeatConduct = 61;
  Description = "Alpha particles. Common radiation from heavy nuclides, easy to block";
  
  Properties = TYPE_ENERGY;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = ITH;
  HighTemperatureTransition = NT;
  
  DefaultProperties.life = 75;
  
  Update = &update;
  Graphics = &graphics;
  Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
  //sim->pv[y/CELL][x/CELL] -= .003f;
  parts[i].vy *= 0.98;
  parts[i].vx *= 0.98;
  int under = pmap[y][x];
  int utype = TYP(under);
  int uID = ID(under);
  switch (utype)
  {
  // case PT_SPRK:
  // {
  //   //remove active sparks
  //   int sparked = parts[uID].ctype;
  //   if (!sim->part_change_type(uID, x, y, sparked))
  //   {
  //     parts[uID].life = 44 + parts[uID].life;
  //     parts[uID].ctype = 0;
  //   }
  //   else
  //     utype = 0;
  //   break;
  // }
  case PT_WATR:
  case PT_SLTW:
  case PT_DSTW:
  case PT_SOAP:
  case PT_CBNW:
  case PT_DEUT:
    parts[i].vx *= 0.9;
    parts[i].vy *= 0.9;
    break;
  case PT_BRMT:
    if (parts[uID].ctype != PT_BRYL) {break;}
  case PT_BRYL:
    if (RNG::Ref().chance(1,5)) {
      float temp = parts[i].temp;
      sim->create_part(i,x,y,PT_NEUT);
      parts[i].temp = temp;
      return 1;
    }
    break;
  default:
    //set off explosives (only when hot because it wasn't as fun when it made an entire save explode)
    if (parts[i].temp > 273.15f + 900.0f && (sim->elements[utype].Flammable || sim->elements[utype].Explosive || utype == PT_BANG))
    {
      sim->create_part(uID, x, y, PT_FIRE);
      parts[uID].temp += restrict_flt(float(sim->elements[utype].Flammable * 5), MIN_TEMP, MAX_TEMP);
      sim->pv[y / CELL][x / CELL] += 1.00f;
    }
    break;
  }
  if (parts[i].life) {
    parts[i].life = std::max(1.0,(parts[i].life-1) - 1.0/(0.001 + parts[i].vx*parts[i].vx + parts[i].vy*parts[i].vy));
  }
  if (parts[i].life == 1) {
    sim->kill_part(i);
    return 1;
  }
  return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
  *firea = 64;
  *firer = 32;
  *fireg = 32;
  *fireb = 32;
  
  *pixel_mode |= FIRE_BLEND;
  return 1;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  float r = RNG::Ref().between(128, 255) / 127.0f;
  float a = RNG::Ref().between(0, 60) * 3.14159f / 30.0f;
  sim->parts[i].life = RNG::Ref().between(480, 959);
  sim->parts[i].vx = r * cosf(a);
  sim->parts[i].vy = r * sinf(a);
}
