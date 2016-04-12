# invoke SourceDir generated makefile for mutex.pem4f
mutex.pem4f: .libraries,mutex.pem4f
.libraries,mutex.pem4f: package/cfg/mutex_pem4f.xdl
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/mutex_MSP_EXP432P401R_TI_MSP432P401R/src/makefile.libs

clean::
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/mutex_MSP_EXP432P401R_TI_MSP432P401R/src/makefile.libs clean

