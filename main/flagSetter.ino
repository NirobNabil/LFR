
// dir_flag 
// 1 - right
// 2 - left


// 1 - on White
// 2 - 90 deg turn right
// 3 - 90 deg turn left

void set_flag() {
  flag = get_flag();
}

int get_flag() {
  int t_flag = 0;
  if( sensor == 0 ) t_flag = 1;
  else if( sensor == 0b000111 || sensor == 0b001111 || sensor == 0b011111 ) t_flag  = 2;
  else if( sensor == 0b111000 ||sensor == 0b111100 || sensor == 0b111110 ) t_flag  = 3;
  else t_flag  = 0;

  return t_flag;
}

void mandatory_set_flag(){
  if( sensor % 2 ) dir_flag = 1;
  else if( (sensor >> 5) == 1 ) dir_flag = 2;

}

bool check_if_on_line_again() {
  return get_flag() == 0;
}
