GLOBAL Stop_flag
FWD_IN(0)=0
REV_IN(0)=1
Datum_in(0)=2

FWD_IN(1)=3
REV_IN(1)=4
Datum_in(1)=5

'OP(8,ON)
'OP(9,ON)

FWD_IN(2)=6
REV_IN(2)=7
Datum_in(2)=8

FWD_IN(3)=9
REV_IN(3)=10
Datum_in(3)=11

'FWD_IN(4)=12
'REV_IN(4)=13
'Datum_in(4)=14
'
'FWD_IN(5)=15
'REV_IN(5)=16
'Datum_in(5)=17
'
'FWD_IN(6)=18
'REV_IN(6)=19
'Datum_in(6)=20

'FWD_IN(7)=21
'REV_IN(7)=22
'Datum_in(7)=23



INVERT_IN(0,OFF)  '常闭限位设置ON
INVERT_IN(1,OFF)
INVERT_IN(2,ON)                            

INVERT_IN(3,OFF)
INVERT_IN(4,OFF)
INVERT_IN(5,ON)

INVERT_IN(6,OFF)  
INVERT_IN(7,OFF)
INVERT_IN(8,ON)

INVERT_IN(9,OFF)
INVERT_IN(10,OFF)
INVERT_IN(11,ON)
''''OP(0,ON)
'OP(1,ON)
'OP(2,ON)
'OP(8,ON)
'OP(9,ON)
'OP(10,ON)
'INVERT_IN(12,ON)  '常闭限位设置ON
'INVERT_IN(13,ON)
'INVERT_IN(14,ON)                            
'
'INVERT_IN(15,ON)
'INVERT_IN(16,ON)
'INVERT_IN(17,ON)

'INVERT_IN(18,ON)  
'INVERT_IN(19,ON)
'INVERT_IN(20,ON)
'
'INVERT_IN(21,ON)
'INVERT_IN(22,ON)
'INVERT_IN(23,ON)
'BASE(0)
'ATYPE=7
'UNITS=1000
'DECEL=500
'ACCEL=500
'SPEED=10
'MERGE(2)=ON
while 1
'BASE(0)
'MOVE(200)
'WAITIDLE
'MOVE(-200)
'WAITIDLE
if in(23)=OFF  then   '急停

  cancel(2) axis(0)
  cancel(2) axis(1)
  cancel(2) axis(2)
  cancel(2) axis(3)
'  cancel(2) axis(4)
'  cancel(2) axis(5)
'  cancel(2) axis(6)
'  cancel(2) axis(7)
  Stop_flag=1
  ELSE
  Stop_flag=0

 
    endif
	
	
wend	


