

bool handling_white = false;
unsigned long on_white__time_threshold = 1000;
unsigned long on_white__start_time = 0;
unsigned long on_white__gone_rogue_threshold = 3000; 
int on_white__speed = ( base_speed * 70 ) / 100;

void handle_white(){
  
   if( !handling_white ) {
      on_white__start_time = current_time;
      handling_white = true;
      block_flag_change = true;
   }

    lcd.setCursor(7,0);
    lcd.print("W");

   if( current_time > on_white__start_time + on_white__time_threshold || last_sensor % 2 || (last_sensor >> 5) == 1 ) {
      if( dir_flag == 1 ) {
        motorL.run(on_white__speed);
        motorR.run(-on_white__speed);
      }else {
        motorL.run(-on_white__speed);
        motorR.run(on_white__speed);
      }

      if( check_if_on_line_again() ) {
        block_flag_change = false;
        handling_white = false;
      }
      
   }

//   if( current_time > on_white__start_time + on_white__gone_rogue_threshold ) {
//      motorL.brake();
//      motorR.brake();
//   }

}
