all:
	@echo Enter VAR name
VAR6: clean
	gcc keypad.c -o keypad_v6 -D VAR6 -lbcm2835
VAR8: clean
	gcc keypadv8.c -o keypad_v8_asp -lpigpio
VAR10: clean
	gcc keypad.c -o keypad_v10 -D VAR10 -lbcm2835
clean:
	rm -f *.o
