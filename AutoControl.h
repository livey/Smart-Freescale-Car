#ifndef AUTO_CONTROL 
#define AUTO_CONTROL 

#define Steer_Kp          1
#define Steer_Ki          0 
#define Steer_Kd          0

#define  Kp_left           3
#define  Ki_left           1/10  // 0  
#define  Kd_left           1/20//1/15//2/5

#define  Kp_right          3
#define  Ki_right          1/10  //0
#define  Kd_right          1/20//1/15//2/5   


#define  Direction_left_max  2060               //  2000/20000 * 50 hz   220 dynamic
#define  Direction_right_max 1620               //  1700/20000 * 50 hz 
#define  Direction_mid       1840 

              
#define  Motor_speed_max     100
#define  Motor_speed_mim     10  

void AutoControl(void);

#endif 