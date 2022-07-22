
void print(int arr[], int size) {
    for(int i=0; i<size; i++) {
        Serial.print(arr[i]);
        Serial.print(" ");
    }
    Serial.print("\n");
}


void printBinary(char val){
    for (int i = 0; i < 8; i++) {
      Serial.print(!!((val << i) & 0x80));
    }
    //Serial.print("\n");
}
