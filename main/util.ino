

//void print(int count, ...) {
//    va_list ap;
//    va_start(ap, count);
//    for(int i=0; i<count; i++) {
//        Serial.print(va_arg(ap, int));
//        Serial.print(" ");
//    }
//    Serial.println("");
//}

void print(char name[], int val) {
  Serial.print(name);
  Serial.println(val);
}


void printBinary(char val){
    for (int i = 0; i < 8; i++) {
      Serial.print(!!((val << i) & 0x80));
    }
    //Serial.print("\n");
}

double mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (double)( (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min );
}
