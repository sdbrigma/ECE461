# invoke SourceDir generated makefile for uartecho.pem4f
uartecho.pem4f: .libraries,uartecho.pem4f
.libraries,uartecho.pem4f: package/cfg/uartecho_pem4f.xdl
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/uartecho_MSP_EXP432P401R_TI_MSP432P401R/src/makefile.libs

clean::
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/uartecho_MSP_EXP432P401R_TI_MSP432P401R/src/makefile.libs clean

