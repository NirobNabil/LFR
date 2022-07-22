

// gloals

#define IRminValueWhenOnBlack 300
#define IRmaxValueWhenOnWhite 200
#define whiteRangeLow 12
#define whiteRangeHigh 18
#define onWhiteCountdownThreshold1 300   //the amount of milliseconds it'll wait before it takes actions to get on the track
#define onWhiteCountdownThreshold2 1000 //this should be longer than the time taken to rotate 180deg
#define waitThesholdForFlagReset 1800
#define waitThresholdBeforeCheckForRightLeft 300
#define waitAfterTurn 1000
#define fullBlackCountdownThreshold 1000


bool block_flag_change;
int base_speed = 255;       // base speed needs to be defined at compile time because other variables are initialized depending on it




//change the timing values according to speed or set a function the void setup to chanege the timing values according to set speeds

int waitCountdown = -waitThresholdBeforeCheckForRightLeft;
int fullBlackCountdown = 0;
int speedValLow = 0;
int speedValHigh = 100;
int waitForWhite = 0;




// utilities

void print(int count, ...);
void printBinary(char val);


// motor

const int motorLForward = 3;
const int motorLBackward = 4;
const int motorLPWM = 2;

const int motorRForward = 8;
const int motorRBackward = 9;
const int motorRPWM = 10;


class motor{
  public:
  int FORWARD,BACKWARD, PWM, lastSPEED;
  char side;

  motor(char motorSIDE);

  void run(signed int SPEED);

  void reverseRun();

  void brake();
};




// sensor Readings

double ir_array[6];
char sensor_s[6];
byte sensor;

void readSensor();



// flag setter

int flag, dir_flag, last_flag, last_sensor;
void setFlag();
void mandatory_set_flag();
int get_flag();



/////////////////////////////////
//// checkpoint handlers  ///////
/////////////////////////////////


void handle_white();
void handle_sharp_angle();
