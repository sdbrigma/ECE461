# invoke SourceDir generated makefile for clock.pem4f
clock.pem4f: .libraries,clock.pem4f
.libraries,clock.pem4f: package/cfg/clock_pem4f.xdl
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/clock_MSP_EXP432P401R_TI_MSP432P401R/src/makefile.libs

clean::
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/clock_MSP_EXP432P401R_TI_MSP432P401R/src/makefile.libs clean

