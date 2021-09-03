#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_UNST()
{
  Identifier = "DEFAULT_PT_UNST";
  Name = "UNST";
  Colour = PIXPACK(0xFF8040);
  MenuVisible = 1;
  MenuSection = SC_NUCLEAR;
  Enabled = 1;
  
  Advection = 2.0f;
  AirDrag = 0.0f * CFDS;
  AirLoss = 0.99f;
  Loss = 0.50f;
  Collision = 0.0f;
  Gravity = 0.0f;
  Diffusion = 0.1f;
  HotAir = 0.000f	* CFDS;
  Falldown = 0;
  
  Flammable = 0;
  Explosive = 0;
  Meltable = 0;
  Hardness = 0;
  PhotonReflectWavelengths = 0xFFFFFFFF;
  
  Weight = 92;
  
  DefaultProperties.temp = R_TEMP + 2.0f + 273.15f;
  HeatConduct = 251;
  Description = "Unstable. Decays very quickly and releases a lot of heat.";
  
  Properties = TYPE_GAS | PROP_NEUTPASS | PROP_RADIOACTIVE;
  
  LowPressure = IPL;
  LowPressureTransition = NT;
  HighPressure = IPH;
  HighPressureTransition = NT;
  LowTemperature = ITL;
  LowTemperatureTransition = NT;
  HighTemperature = ITH;
  HighTemperatureTransition = NT;
  
  Update = &update;
  Create = &create;
  Graphics = &graphics;
}

static int update(UPDATE_FUNC_ARGS)
{
  parts[i].temp += 50000.0f/parts[i].life;
  sim->pv[y/CELL][x/CELL] += 30.0f/parts[i].life * CFDS;
  if (RNG::Ref().chance(1,parts[i].life))
  {
    //decay
    float otemp = parts[i].temp;
    if (parts[i].tmp > 255) {
      parts[i].tmp -= 4; //alpha decay
      
      
      if (RNG::Ref().chance(1,3)) { // spontaneous fission
        //sim->kill_part(i);
        //sim->create_part(i,x,y,PT_LAVA);
        
        int n1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_NEUT);
        int n2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_NEUT);
        int n3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_NEUT);
        parts[n1].temp = parts[i].temp+100;
        parts[n2].temp = parts[i].temp+100;
        parts[n3].temp = parts[i].temp+100;
        
        
        float ratio = (float)RNG::Ref().between(30,36) / 100.0f;
        parts[i].tmp = (int)((1.0f - ratio)*parts[i].tmp);
        parts[i].life = parts[i].life * 0.3 + RNG::Ref().between(1,20);
        
        int f2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_UNST);
        parts[f2].temp = parts[i].temp+100;
        parts[f2].tmp = (int)(parts[i].tmp * ratio);
        parts[f2].life = parts[i].life * 0.2 + RNG::Ref().between(1,20);
        
        sim->pv[y/CELL][x/CELL] += 5.0f * CFDS;
      }
      else {
        int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
        parts[a1].temp = parts[i].temp+20;
      }
    }
    
    
    else if (parts[i].tmp > 251 && RNG::Ref().chance(2,3)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_CALI);
      int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[a1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    
    else if (parts[i].tmp > 238 && RNG::Ref().chance(2,3)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_PLUT);
      int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[a1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    
    else if (parts[i].tmp > 232 && RNG::Ref().chance(2,3)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_URAN);
      int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[a1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    
    else if (parts[i].tmp > 225 && RNG::Ref().chance(9,10)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_THOR);
      int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[a1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    
    else if (parts[i].tmp > 210 && RNG::Ref().chance(8,10)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_POLO);
      int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      int a2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      int a3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      parts[a1].temp = otemp+20;
      parts[a2].temp = otemp+20;
      parts[a3].temp = otemp+20;
    }
    
    else if (parts[i].tmp > 180 && RNG::Ref().chance(9,10)) {
      //sim->kill_part(i);
      if (RNG::Ref().chance(1,3)) {sim->create_part(i,x,y,PT_MERC);}
      else if (RNG::Ref().chance(1,2)) {sim->create_part(i,x,y,PT_GOLD);}
      else {sim->create_part(i,x,y,PT_PTNM);}
      parts[i].life = 200;
      int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[a1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
  }
    
    else if (parts[i].tmp > 130 && RNG::Ref().chance(5,10)) {    // I might add something here
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_LAVA);
      
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    else if (parts[i].tmp > 111 && RNG::Ref().chance(7,10)) { 
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_TIN);
      parts[i].life = 200;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    else if (parts[i].tmp > 80 && RNG::Ref().chance(5,10)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_RBDM);
      parts[i].life = 200;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    else if (parts[i].tmp > 69 && RNG::Ref().chance(5,10)) { // NTCT = germanium?
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_NTCT);
      parts[i].life = 200;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    else if (parts[i].tmp > 52 && RNG::Ref().chance(8,10)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_IRON);
      parts[i].life = 200;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    else if (parts[i].tmp > 45 && RNG::Ref().chance(8,10)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_TTAN);
      parts[i].life = 200;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    
    // else if (parts[i].tmp > 45 && RNG::Ref().chance(58,10)) {
    //   sim->kill_part(i);
    //   sim->create_part(i,x,y,PT_TTAN);
    //   int e1 = sim->create_part(-1,x,y,PT_ELEC);
    //   int e2 = sim->create_part(-1,x,y,PT_ELEC);
    //   int e3 = sim->create_part(-1,x,y,PT_ELEC);
    //   parts[e1].temp = parts[i].temp+20;
    //   parts[e2].temp = parts[i].temp+20;
    //   parts[e3].temp = parts[i].temp+20;
    // }
    else if (parts[i].tmp > 27 && RNG::Ref().chance(9,10)) {
      //sim->kill_part(i);;
      sim->create_part(i,x,y,PT_SLCN);
      parts[i].life = 200;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    else if (parts[i].tmp > 27 && RNG::Ref().chance(8,10)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_O2);
      parts[i].life = 200;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e3 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      parts[e3].temp = otemp+20;
    }
    else if (parts[i].tmp > 11 && RNG::Ref().chance(9,10)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_BCOL);
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      int e2 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      //int e3 = sim->create_part(-1,x,y,PT_ELEC);
      parts[e1].temp = otemp+20;
      parts[e2].temp = otemp+20;
      //parts[e3].temp = parts[i].temp+20;
    }
    else if (parts[i].tmp > 5 && RNG::Ref().chance(1,2)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_BRYL);
      parts[i].life = 100;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
    }
    else if (parts[i].tmp > 5 && RNG::Ref().chance(1,2)) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_LITH);
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
    }
    
    else if (parts[i].tmp > 7) {  //alpha-decaying light nuclei
     // sim->kill_part(i);
      sim->create_part(i,x,y,PT_NBLE);
      parts[i].life = 50;
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      int a1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ALPH);
      parts[a1].temp = otemp+20;
    }
    
    else if (parts[i].tmp > 4) {  //nucleon-emitting light nuclei
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_NEUT);
      int n1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_NEUT);
      parts[n1].temp = parts[i].temp+20;
    }
    
    else if (parts[i].tmp > 2) {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_NBLE);
      int n1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_NEUT);
      parts[n1].temp = otemp+20;
    }
    
    else {
      //sim->kill_part(i);
      sim->create_part(i,x,y,PT_PROT);
      int e1 = sim->create_part(-1,x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1),PT_ELEC);
      parts[e1].temp = otemp+20;
      //int p1 = sim->create_part(-1,x,y,PT_PROT);
      //parts[p1].temp = otemp+20;
    }
    parts[i].temp = otemp;
    return 1;
  }
  return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
  sim->parts[i].tmp = 218; // tmp is weight
  sim->parts[i].life = 90; // life is avg. lifespan in frames
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
  //int z = (cpart->tmp - 5) * 5;////speckles!
  //*colr += (100-cpart->tmp2);
  //*colg += z;
  //*colb += (cpart->tmp)*2;
  
  *firea = 50;
  *firer = *colr;
  *fireg = *colg;
  *fireb = *colb;
  *pixel_mode |= FIRE_ADD;
  return 0;
}
