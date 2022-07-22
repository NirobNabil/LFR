

void pidControl() {

  block_flag_change = false;     //////// this is a hack RED FLAG change this
  
                                                                /*       base is actually the highest speed        */
  if(output<0){                                                 //if output less than 0 turn left                                           
    motorR.run(base_speed);                                           //set the right motor to highest speed and reduce left motor speed
    motorL.run(base_speed + (output));                                //had to use "base + output" because output is negative here 
  }else if(output>=0){                                           //if output greater than 0 turn right
    motorR.run(base_speed - (output));                               //set the left motor to highest speed and reduce right motor speed
    motorL.run(base_speed);                                           //used "base - output" here because output is positive
  }
//
//  if (sensor == 0b001100) 
//      {
//        if (pos != 0) {
//          (pos == 1) ? motor_set(-10 * SL, 10 * SR) : motor_set(10 * SL, -10 * SR);
//          delay(20); pos = 0;
//        }
//        motor_set(10 * SL, 10 * SR);
//      }
//      //right side
//      else if (sensor == 0b000100) motor_set(10 * SL, 9 * SR); 
//      else if (sensor == 0b000110) 
//      {
//        pos = 1; motor_set(10 * SL, 6 * SR);
//      }
//      else if (sensor == 0b000010) 
//      {
//        pos = 1; motor_set(10 * SL, 3 * SR);
//      }
//      else if (sensor == 0b000011) 
//      {
//        pos = 1; motor_set(10 * SL, 0 * SR);
//      }
//      else if (sensor == 0b000001) 
//      {
//        pos = 1;
//        motor_set(10 * SL, -3 * SR);
//      }
//      //left side
//      else if (sensor == 0b001000) motor_set(9 * SL, 10 * SR);
//      else if (sensor == 0b011000) 
//      {
//        pos = -1; motor_set(6 * SL, 10 * SR);
//      }
//      else if (sensor == 0b010000) 
//      {
//        pos = -1; motor_set(3 * SL, 10 * SR);
//      }
//      else if (sensor == 0b110000) 
//      {
//        pos = -1; motor_set(0 * SL, 10 * SL);
//      }
//      else if (sensor == 0b100000) 
//      {
//        pos = -1; motor_set(-3 * SL, 10 * SR);
//      }

}
