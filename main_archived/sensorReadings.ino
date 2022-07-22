

int ir_array[6];
char sensor_s[6];
int sensor;


void readData() {

    ir_array[0] = analogRead(A0);
    ir_array[1] = analogRead(A1);
    ir_array[2] = analogRead(A2);
    ir_array[3] = analogRead(A3);
    ir_array[4] = analogRead(A4);
    ir_array[5] = analogRead(A5);

    sensor = 0;
    for( int i=0; i<6; i++ ) {
        sensor += ( ir_array[i] > IRminValueWhenOnBlack ? 1 : 0 ) * ( 1 << (i+1) ); 
        sensor_s[i] = ( ir_array[i] > IRminValueWhenOnBlack ? '1' : '0' );
    }

}
