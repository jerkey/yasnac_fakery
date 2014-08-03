https://sudoroom.org/mediawiki/index.php?title=Giant_robot_arm

specifically:
http://servo-repair.com/documents/yaskawa/CACR-SR.pdf

page 37 (labeled as page 32)

we are sending serial data to the YASNAC to simulate an Absolute Encoder to avoid errors relating to the fact that we have removed two extra motors from the system.  To reprogram the YASNAC ERC (to boot up without seeing the extra motors/encoders) would require a working EPROM programmer and the knowledge of what bytes to change.
