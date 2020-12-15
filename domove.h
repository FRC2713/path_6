
//  check IR to see if stop command
    if (irrecv.decode(&results)){
      Serial.println(results.value, HEX);
      irrecv.resume();
    }
    if (results.value ==0xff22dd) break;

//  makeMove ------------------------      
       Serial.println(pm[i].amount, 10);

switch (pm[i].mtrs) {
    case F_LEFT:
      digitalWrite (L_ENPIN, LOW);
      digitalWrite (L_DIRPIN, LOW);
      moveSteps = (pm[i].amount)*stepsPerInch;
      break;
    case F_RIGHT:
      digitalWrite (R_ENPIN, LOW);
      digitalWrite (R_DIRPIN, HIGH);
      moveSteps = (pm[i].amount)*stepsPerInch;
      break;
    case F_BOTH:
      digitalWrite (L_ENPIN, LOW);
      digitalWrite (L_DIRPIN, LOW);
      digitalWrite (R_ENPIN, LOW);
      digitalWrite (R_DIRPIN, HIGH);
      moveSteps = (pm[i].amount)*stepsPerInch;
      break;
    case B_LEFT:
      digitalWrite (L_ENPIN, LOW);
      digitalWrite (L_DIRPIN, HIGH);
      moveSteps = (pm[i].amount)*stepsPerInch;
      break;
    case B_RIGHT:
      digitalWrite (R_ENPIN, LOW);
      digitalWrite (R_DIRPIN, LOW);
      moveSteps = (pm[i].amount)*stepsPerInch;
      break;
    case B_BOTH:
      digitalWrite (L_ENPIN, LOW);
      digitalWrite (L_DIRPIN, HIGH);
      digitalWrite (R_ENPIN, LOW);
      digitalWrite (R_DIRPIN, LOW);
      moveSteps = (pm[i].amount)*stepsPerInch;
      break;
    case RCCW:
      digitalWrite (L_ENPIN, LOW);
      digitalWrite (L_DIRPIN, LOW);
      digitalWrite (R_ENPIN, LOW);
      digitalWrite (R_DIRPIN, LOW);
      moveSteps = abs(pm[i].amount)*stepsPerDegree;
      break;
    case RCW:
      digitalWrite (L_ENPIN, LOW);
      digitalWrite (L_DIRPIN, HIGH);
      digitalWrite (R_ENPIN, LOW);
      digitalWrite (R_DIRPIN, HIGH);
      moveSteps = pm[i].amount*stepsPerDegree;
      break;
    case PIVCW:
      digitalWrite (L_ENPIN, LOW);
      digitalWrite (L_DIRPIN, LOW);
      digitalWrite (R_ENPIN, HIGH);
      digitalWrite (R_DIRPIN, HIGH);
      moveSteps = abs(pm[i].amount)*2*stepsPerDegree;
      break;
    case PIVCCW:
      digitalWrite (L_ENPIN, HIGH);
      digitalWrite (L_DIRPIN, HIGH);
      digitalWrite (R_ENPIN, LOW);
      digitalWrite (R_DIRPIN, LOW);
      moveSteps = pm[i].amount*2*stepsPerDegree;
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
    break;
  }

      if (moveSteps > 0) 

        stepCount = 0;
        stepSave = 0;
        Serial.print(i, 10);
        Serial.print(" steps-> ");
        Serial.println(moveSteps, 10);
        moveDone = false;
//        digitalWrite (ENPIN, LOW);              // enable drivers
//        digitalWrite (L_ENPIN, LOW);              // enable drivers

        stepSave = 0;
        stepCount = 0;
        runState = accel;

        for (j=0;j<=19;j++)
        {
          if (moveSteps < 2*deltaV[j].stpcntchg) break;
        }
        jfinal = j;
        
        j = 0;

        do {
            cli();//stop interrupts
            stepSave = stepCount; 
            sei();
            switch (runState) {
            case accel:
              if (j < jfinal) {      
                if ((stepSave >= deltaV[j].stpcntchg)) {
//                  digitalWrite (TESTPIN, !bitRead(PORTB, 5));          
                  compVal = deltaV[j++].compa;
//                  digitalWrite (TESTPIN, LOW);
                  }
              }
              else
              {
                if (jfinal > 19) jfinal = 19;
                runState = conspd;                
              }
            break;
            case conspd:
              if ((moveSteps-stepSave) < deltaV[jfinal].stpcntchg) {
                j = jfinal;
                runState = decel;
              }
            break;
            case decel:
              if (((moveSteps-stepSave) <= deltaV[j].stpcntchg)&&(j > 0)) {
//              digitalWrite (TESTPIN, !bitRead(PORTB, 5));          
              compVal = deltaV[j--].compa;            
            break;
            }
          }
      } while (stepSave < moveSteps);

//      TIMSK0 = 0;
      digitalWrite (R_ENPIN, HIGH);              // disable drivers
      digitalWrite (L_ENPIN, HIGH);              // disable drivers
      digitalWrite (TESTPIN, LOW);
      
