// HEADERS
#include "src\RFIDHeader.h"
#include "src\OTAHeader.h"
#include "src\nextionHeader.h"
#include "src\servoHeader.h"
#include "src\LEDHeader.h"
#include "src\loadCellHeader.h"
#include "src\A4988Stepper.h"
#include "config.h"

/* Define states for program flow */
enum SM_states{
  WAIT_FOR_USER_SELECTION = 0,
  READY_SEQUENCER,
  START_MOTOR_SCHEDULER,
  WAIT_FOR_OPTICAL_SENSOR_ALIGNMENT,
  READ_TAG;
  IDENTIFY_CONTAINER,
  ACTIVATE_SERVO,
  TERMINATE_STATE_MACHINE
};

/* Helper function definitions */
char* get_user_color_comb(void )
{
    // get color comibbination from touch screen  
}

char* select_ingredients(char *colr)
{
    // based on color combincation identify tray with ingredinets  
}

char *find_sequence_step_angle(char *ingred)
{
  // find step angle order to be applied  
}

bool *check_filling_status(char *ingred)
{
  // check if ingredinets are present in respective trat or not  
}

stepper_motor_rotate(int angle)
{
    // apply angle in stepper motor  
}

bool get_optical_value(void);
{
  // read optical sensor and find approproate positioning for cartidge  
}

void activate_rfid(void)
{
  // activate RFIDs 1 and 2 for reading  
}

int32_t start_reading_rfid(void)
{
  // satrt reading now tags  
}

bool start_servo_motor(int time)
{
  // start sevo motor with approporiate time duration as significant  
}

int32_t get_wight_scale()
{
  // read weight of contianer and see if its above threshold as agree in SM
}

int current_state = WAIT_FOR_USER_SELECTION;

// MAIN PROGRAM
void setup() {
  Serial.begin(115200);
  Serial.println("\n\nBooting...");

  Serial.println("initPins...");
  initPins();
  Serial.println("initReader...");
  initReader();
  Serial.println("initNextion...");
  initNextion();
  Serial.println("initLED...");
  initLED();
  Serial.println("initLoadCell...");
  initLoadCell();
  Serial.println("initWiFiAP...");
  initWiFiAP();
  Serial.println("\nAll Init'd...");

}

// servoRun(100, 0);
// if readCard(mfrc522Container).length() > 5
// readWeight()   // in grams
// handleWiFiClients()

void loop() {
  handleWiFiClients();
  char *ingred;
  char *color;
  char *step_angle;
  int step_pos = 0;
  int current_step_angle;
  int32_t tag, tag2 = 0;
  int _time = 10; 
  
  switch(current_state){
  
    case WAIT_FOR_USER_SELECTION:
        color = get_user_color_comb();
        ingred = select_ingredients(color);
        current_state = READY_SEQUENCER;
        break;
      
    case READY_SEQUENCER:
        step_angle = find_sequence_step_angle(ingred);   //return step angle in order and reutrn a list
        bool status = check_filling_status(ingred);
        current_step_angle = step_angle[step_pos]
        if(status == true){
          step_pos++;
          current_state = START_MOTOR_SCHEDULER;
        } else{
          // wait for filling station to be filled
        }
        break;
      
    case START_MOTOR_SCHEDULER:
        stepper_motor_rotate(current_step_angle);
        current_state = WAIT_FOR_OPTICAL_SENSOR_ALIGNMENT;
        break;
        
    case WAIT_FOR_OPTICAL_SENSOR_ALIGNMENT:
        bool align = get_optical_value();
        if(align == true){
          activate_rfid();
          current_state = READ_TAG;
        }
      break;
      
    case READ_TAG:
        tag = start_reading_rfid();
        if(tag != 0){
          current_state = IDENTIFY_CONTAINE;
        }
     break;
     
    case IDENTIFY_CONTAINE:
        tag2 = start_reading_rfid_container();
        if(tag != 0){
          current_state = ACTIVATE_SERVO;
        }
     break;
     
    case ACTIVATE_SERVO:
        int32_t init_wieght = get_wight_scale();
        bool expired = start_servo_motor(_time);
        if(expired == true){
          int32_t new_wieght = get_scale_wight();
          if((new_wieght - init_wieght) >= threshold_point){
            current_state = READY_SEQUENCER;
          }
        }
        break;
        
    default:
     current_state = WAIT_FOR_USER_SELECTION;
  }
}


void initPins() {
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(directionPin, OUTPUT);

  digitalWrite(enablePin, HIGH);  // stepper motor off on start up
}
