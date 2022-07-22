

bool handling_sharp_angle = false;
unsigned long handling_start_time;
const unsigned long sharp_angle__on_white_time_threshold = 50;
bool dir_to_turn; // 1 - right,  2 - left
int sharp_angle__speed = ( base_speed * 70 ) / 100;;


void handle_sharp_angle(){

    if( !handling_sharp_angle ) {
      block_flag_change = 1;                    // blocking flag change so that main loop always delivers control to this function while sharp angle handling is not completed
      handling_start_time = current_time;
      handling_sharp_angle = true;
      dir_to_turn = ( flag == 2 ? 1 : 2);       // assuming this func wont be executed if flag is not either 2 or 3

      motorL.run(-sharp_angle__speed);
      motorR.run(-sharp_angle__speed);
      delay(50);
    
    }

    lcd.setCursor(7,0);
    lcd.print("S");

    if( current_time > handling_start_time + sharp_angle__on_white_time_threshold  ) {
      if( dir_to_turn ) {
        motorL.run(sharp_angle__speed);
        motorR.run(-sharp_angle__speed);
      }else {
        motorL.run(-sharp_angle__speed);
        motorR.run(sharp_angle__speed);
      }

      if( check_if_on_line_again() ) {
         block_flag_change = false;
         handling_sharp_angle = false;
      }
    }
    
    
}
