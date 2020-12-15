

//#define F_BOTH true
//#define RCW false

enum motors{F_LEFT, F_RIGHT, F_BOTH, B_LEFT, B_RIGHT, B_BOTH, RCW, RCCW, PIVCW, PIVCCW};
struct moveStruct
{
  enum motors mtrs;
  float amount;     // inches or angle if 0 then end of moves
};


struct accelStruct
{
  int stpcntchg;  // move type: F_BOTHar or rotational TRUE for F_BOTHar FALSE for rotational
  int compa;     // inches or angle if 0 then end of moves
};

accelStruct deltaV[20] = {

{ .stpcntchg =  0 , .compa =  239 },
{ .stpcntchg =  24  , .compa =  210 },
{ .stpcntchg =  45  , .compa =  187 },
{ .stpcntchg =  64  , .compa =  168 },
{ .stpcntchg =  80  , .compa =  153 },
{ .stpcntchg =  96  , .compa =  140 },
{ .stpcntchg =  110 , .compa =  130 },
{ .stpcntchg =  123 , .compa =  121 },
{ .stpcntchg =  135 , .compa =  113 },
{ .stpcntchg =  146 , .compa =  106 },
{ .stpcntchg =  157 , .compa =  99  },
{ .stpcntchg =  167 , .compa =  94  },
{ .stpcntchg =  176 , .compa =  89  },
{ .stpcntchg =  185 , .compa =  84  },
{ .stpcntchg =  193 , .compa =  80  },
{ .stpcntchg =  201 , .compa =  77  },
{ .stpcntchg =  209 , .compa =  73  },
{ .stpcntchg =  216 , .compa =  70  },
{ .stpcntchg =  223 , .compa =  68  },
{ .stpcntchg =  230 , .compa =  65  }
};

moveStruct moves[] = {                // 30x30 inch square CCW

  {.mtrs = F_BOTH, .amount = 20.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 20.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 20.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 20.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 0} 
};
moveStruct moves_1[] = {

  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 8.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 8.0}, 
  {.mtrs = B_BOTH, .amount = 8.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = B_BOTH, .amount = 6.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = B_BOTH, .amount = 8.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = B_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};



moveStruct moves_7[] = {                // 6x6 inch square CW

  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};

moveStruct moves_2[] = {              // move 6 inch forward
  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};

moveStruct moves_3[] = {              // rotate 360 CW
  {.mtrs = RCW, .amount = 360.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};

moveStruct moves_4[] = {              // rotate 90 CW
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};

moveStruct moves_5[] = {              // move 6 inches back
  {.mtrs = B_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};

moveStruct moves_6[] = {              // rotate 90 CCW
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};

moveStruct moves_8[] = {

  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 8.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 6.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = F_BOTH, .amount = 8.0}, 
  {.mtrs = B_BOTH, .amount = 8.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = B_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 90.0}, 
  {.mtrs = B_BOTH, .amount = 8.0}, 
  {.mtrs = RCCW, .amount = 90.0}, 
  {.mtrs = B_BOTH, .amount = 6.0}, 
  {.mtrs = RCW, .amount = 0.0} 
};

moveStruct *pm; 
