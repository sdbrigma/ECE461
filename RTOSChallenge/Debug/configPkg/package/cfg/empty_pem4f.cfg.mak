# invoke SourceDir generated makefile for empty.pem4f
empty.pem4f: .libraries,empty.pem4f
.libraries,empty.pem4f: package/cfg/empty_pem4f.xdl
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/RTOSChallenge/src/makefile.libs

clean::
	$(MAKE) -f /Users/marybiggs/Desktop/ECE461/RTOSChallenge/src/makefile.libs clean

