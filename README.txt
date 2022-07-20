https://sudoroom.org/mediawiki/index.php?title=Giant_robot_arm

specifically:
http://servo-repair.com/documents/yaskawa/CACR-SR.pdf

page 37 (labeled as page 32)

we are sending serial data to the YASNAC to simulate an Absolute Encoder to avoid errors relating to the fact that we have removed two extra motors from the system.  To reprogram the YASNAC ERC (to boot up without seeing the extra motors/encoders) would require a working EPROM programmer and the knowledge of what bytes to change.

on CN1 of circuitboard SVO3(1) we have jumped pins 14,15,16,17 (corresponding to robot connector pins 8, 28, 40, 38) to Ground at pin 11
CN1 pin 8 (robot 19) goes to a grey thin wire to Arduino Uno pin 11
CN2 pin 8 (robot 19) goes to a violet thin wire to Arduino Uno pin 12
CN1 pin 5 (robot 4) goes to a white wire to Arduino Uno pin 9 and a 2.2kΩ resistor to an LED to ground
CN2 pin 5 (robot 4) goes to an orange wire to Arduino Uno pin 8 and a 2.2kΩ resistor to an LED to ground
CN2 pin 1 (robot 33) goes to a white wire to Arduino Uno pin 1 (labeled RX on the white P.BADGER arduino we're using, but actually TX)
CN2 pin 2,4,9 (robot 34,36,20) go to a 2.2kΩ resistor to +5V, and to an LED to ground (so this node can't go above 2 or 3.2 volts?)
Arduino is connected to Ground at CN2 and to +5V nearby at HIC5 pin 1

circuitboard SVO3(1) has a three-jumper SW1 "PG SHORT" which was set to the following:
AXIS 1: OFF
AXIS 2: OFF
AXIS 3: ON

changing the jumper for AXIS 1 to ON makes the ERROR 234 PULSE GENERATOR FAILURE 1 stop happening.
probably changing the jumper for 2 will make it unnecessary to do and of this LOL
