# Changelog

## v3.0.0

- implement a respiratory trigger
  (_this helps the MakAir to respect the patient respiratory reflexes when he/she starts to wake up; disabled by default_)
- add an "end of production line" test program
  (_it is included in the production software and runs when booting while pressing a maintainance button; electronic hardware v2+ required_)
- support Faulhaber motors for valves
  (_they are better, faster, stronger; electronic hardware v2+ required_)
- support an optional mass flow meter
  (_this allows to estimate the volume of inspired air; electronic hardware v2+ required_)
- implement a control protocol to update settings through serial communication
  (_UI on Raspberry Pi can now send new settings values; few more settings are supported compared to physical buttons; electronic hardware v2+ required_)
- support electronic hardware v3
- improve pressure control
- improve blower speed regulation
- fix systick overflow in telemetry protocol
- update telemetry protocol to send more information
- include CRC in telemetry messages
- add a safety to shutdown system if battery is very low
  (_in this situation, everything might get damaged if not shutdown_)
- change some default settings
  (_now, Ppeak starts at 250 mmH2O and Pplateau at 220 mmH2O_)

## v1.5.4

- improve dynamic update of the peak pressure command according to the measured plateau pressure
- fix telemetry bugs
- fix minor bugs

## v1.5.3

- warn if pressure is not stable enough at startup
- improve pressure control
- fix a regression
  (_the PPeak+ button was not functioning anymore_)

## v1.5.2

- improve pressure control

## v1.5.1

- calibrate pressure sensor's offset on startup
- better round displayed pressure values (in cmH2O)
- minor improvement to the pressure control

## v1.5.0

- rework pressure and blower control
  (_blower will now take more time to ramp up/down but this will greatly improve the stability of injected air volume in many scenario_)
- rework alarms
  (_better pressure alarms, better battery alarms, better snooze behavior_)
- improve even more the measured and displayed pressures
  (_if no plateau pressure if found, screen will now display a `?` instead of an uncertain value_)
- tweak the pressure control to make the plateau more accurate
- fix an issue with blower not restarting in some cases
- make sysclock more accurate
- improve code quality (MISRA)
- add a step in integration test to check O2 pipe

## v1.4.0

_This release was depublished_

## v1.3.2

- fix blower control
  (_it used to unexpectedly slow down a bit from times to times_)
- improve the measured and displayed pressures for peak and plateau

## v1.3.1

- use the green LED near the start button to show whether the breathing mode is ON or not
- disable alarms related to the breathing cycle when program is stopped
- fix an issue with a battery alarm being briefly triggered at every boot
- integration test: open both valves at startup

## v1.3.0

- add a program to test integration
- support electronic hardware v1 **and** v2
  (_v1 by default, v2 through a config flag_)
- implement start/stop
  (_from now on, machine will begin stopped!_)
- handle Emerson valves
  (_through a config flag_)
- improve the way buzzer is controlled

## v1.2.3

- fix an issue with buzzer (sometimes it was stuck buzzing whereas no alarm were triggered)
- add battery-related alarms

## v1.2.2

- handle several pneumatic systems
  _(for the first 2 working typologies of prototype)_

## v1.2.1

_Unreleased_

## v1.2.0

First release version
