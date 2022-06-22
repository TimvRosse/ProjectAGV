#ifndef STEPPERLIBV1_0_H_INCLUDED

#define STEPPERLIBV1_0_H_INCLUDED

#define stepperLoc DDRD
#define stepperPort PORTD
#define stepperLoc2 DDRB
#define stepperPort2 PORTB
#define stepperDir1 PD2 //8, onderste
#define stepperPin1 PD3 //9

#define stepperDir2 PD7 //10
#define stepperPin2 PB0 //11

#define voorruit 0
#define achteruit 1

#define linker 1
#define rechter 0

#define heel 1
#define half 2
#define kwart 4
#define achtste 8
#define zestiende 16

void initStepper(void);
void stepperGoto(int steps, int dir, int mode);
void stepperSetSpeed(float rps, int mode);
void singleStepperGoTo(int steps, int dir, int mode, int stepper);


#endif // STEPPERLIBV1_0_H_INCLUDED
