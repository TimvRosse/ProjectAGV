#ifndef STEPPERLIBV1_0_H_INCLUDED

#define STEPPERLIBV1_0_H_INCLUDED

#define stepperLoc DDRB
#define stepperPort PORTB
#define stepperDir1 PB2 //10, onderste
#define stepperPin1 PB1 //9

#define stepperDir2 PB4 //12
#define stepperPin2 PB3  //11

#define voorruit 0
#define achteruit 1

#define linker 1
#define rechter 0

#define heel 1
#define half 2
#define kwart 4
#define achtste 8

void initStepper(void);
void stepperGoto(int steps, int dir, int mode);
void stepperSetSpeed(float rps, int mode);
void singleStepperGoTo(int steps, int dir, int mode, int stepper);


#endif // STEPPERLIBV1_0_H_INCLUDED
