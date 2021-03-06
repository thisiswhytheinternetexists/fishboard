# FishBoard
## An Oak-Based controller for 12 Volts aquarium device control

Basic useful feature list:

- [ ] Switches LED strips on and off on a schedule or triggered by a REST call (REST call works, schedule is untested)
- [X] Allows up to 3 devices to be controlled (channel 1 and 2 work, todo: channel 3 troubleshooting)
- [ ] Manual override using buttons (doesn't currently work, todo: hardware troubleshooting)
- [X] Connects to your existing 2.4GHz WiFi Network for remote control and management (handled by the Oak Config, todo: write guide)
- [ ] Supports an SSD1306 OLED display for status and standalone operation
- [X] Integration with Domoticz (todo: write guide. Is a shell script that does a [particle API call](https://docs.particle.io/reference/firmware/photon/#particle-function-))


BOM:

| Manufacturer       | P/N            | Amount |
| ------------------ | -------------- | ------ |
| Multicomp          | MJ-179PH       | 1      |
| Fairchild          | FQP30N06L      | 3      |
| Multicomp          | 1N5819         | 3      |
| WURTH Elektronik   | 61300911121    | 2      |
| DigiStump          | Oak            | 1      |
| TE Connectivity    | CFR16J10K      | 1      | 
| Molex              | 22-23-2021     | 7      |
| Molex              | 22-01-2027     | 7      |
| Molex              | 08-50-0032     | 14     |
| Multicomp          | R13-24AL-05-BB | 4      |
| DELTRON ENCLOSURES | 479-0140-0     | 1      |
| Pro Power          | PPW00030       | 2      |
 
Total BOM cost (excluding Oak and PCB) is roughly about EUR14.

Datasheet for MOSFET: http://www.mouser.com/ds/2/149/FQP30N06L-244344.pdf
Datasheet for enclosure: http://www.farnell.com/datasheets/1792140.pdf
