

void readSensor() {

    ir_array[0] = analogRead(A0);
    ir_array[1] = analogRead(A1);
    ir_array[2] = analogRead(A2);
    ir_array[3] = analogRead(A3);
    ir_array[4] = analogRead(A4);
    ir_array[5] = analogRead(A5);

    for( int i=0; i<6; i++ ) {
      ir_array[i] = ir_array[i] < IRmaxValueWhenOnWhite ? 0 : ir_array[i];
//      Serial.print(ir_array[i]);
//      Serial.print(" ");
    }
    

    
//    Serial.print("c: ");
//    Serial.print(sensor >> 5, BIN);
//    Serial.println();
//
//    Serial.println(ir_array[0]);
    sensor = 0;
    for( int i=0; i<6; i++ ) {
        ir_array[i] = ( ir_array[i] > IRminValueWhenOnBlack ? 1 : 0 );
        sensor += ir_array[i] * ( 1 << i ); 
        sensor_s[i] = ir_array[i] ? '1' : '0';
    }


    double ir_sum = ir_array[0] + ir_array[1] + ir_array[2] + ir_array[3] + ir_array[4] + ir_array[5];
    if( ir_sum == 0 ) input = 0;
    else if( ir_array[0] || ir_array[1] ) input = ( ir_array[0] * 1 + ir_array[1] * 100 ) / ( ir_array[0] + ir_array[1] );
    else if( ir_array[4] || ir_array[5] ) input = ( ir_array[4] * 400 + ir_array[5] * 500 ) / ( ir_array[4] + ir_array[5] );
    else input = (  ir_array[0] * 1 + ir_array[1] * 100 + ir_array[2] * 200 
             + ir_array[3] * 300 + ir_array[4] * 400 + ir_array[5] * 500 ) 
        /  ir_sum;



     input -= 245;


}
