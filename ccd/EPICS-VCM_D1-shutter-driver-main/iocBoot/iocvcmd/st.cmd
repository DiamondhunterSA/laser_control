#!../../bin/linux-x86_64/vcmd

#- You may have to change vcmd to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/vcmd.dbd"
vcmd_registerRecordDeviceDriver pdbbase

epicsEnvSet ("STREAM_PROTOCOL_PATH", "${TOP}/vcmdApp/Db")
epicsEnvSet("PREFIX", "SLAC:Vcmd1:")
epicsEnvSet("PORT", "serial1")

drvAsynSerialPortConfigure("serial1", "/dev/ttyUSB0", 0, 0, 0)
asynSetOption("serial1",0,"baud","9600")
asynSetOption("serial1",0,"bits","8")
asynSetOption("serial1",0,"stop","1")
asynSetOption("serial1",0,"parity","none")
asynSetOption("serial1",0,"clocal","N")
asynSetOption("serial1",0,"crtscts","N")

## Load record instances
#dbLoadTemplate "db/user.substitutions"
#dbLoadRecords "db/vcmdVersion.db", "user=quan"
#dbLoadRecords "db/dbSubExample.db", "user=quan"

dbLoadRecords("${TOP}/vcmdApp/Db/VCMD1.db","P=$(PREFIX),PORT=serial1")
dbLoadRecords("$(ASYN)/db/asynRecord.db","P=$(PREFIX),R=asyn1,PORT=serial1,ADDR=0,IMAX=80,OMAX=80")
dbLoadRecords("$(AUTOSAVE)/db/save_restoreStatus.db","P=$(PREFIX),PORT=serial1")

#- Set this to see messages from mySub
#var mySubDebug 1

#- Run this to trace the stages of iocInit
#traceIocInit

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncExample, "user=quan"
