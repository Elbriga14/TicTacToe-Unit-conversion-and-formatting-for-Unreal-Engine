TicTacToe's Unit Conversion and Formatting plugin is a Blueprint library that can convert and format any unit to be displayed to the end user.

It handles metric and Imperial conversions, and displayed to the user with fully localizable text.
Supported units are length, area, volume, temperature, pressure, speed, time, weight and more to be added.

<img width="1055" height="524" alt="image" src="https://github.com/user-attachments/assets/81064a24-d355-491d-80c4-b27b6b47f41c" />

It also supports automatic unit choice from input value, for metric and imperial units.
For example, 180300cm will be displayed as 1.8km in automatic metric, and 1.2mi in automatic imperial.

Coupled with your own player settings, you can easily display numbers in the user's preferred unit system.

The library is implemented in C++, and fully exposed to Blueprints.

Extended unit support is planned with far more esoteric units. British imperial system and nautical units are currently partly implemented.

<img width="1751" height="840" alt="image" src="https://github.com/user-attachments/assets/cd66052a-db6f-4b1f-a77a-9bdc10f36305" />

<img width="1870" height="1028" alt="image" src="https://github.com/user-attachments/assets/79105b88-b2f0-462d-9a2a-b18c56000fe7" />

Please note that this plugin is intended for unit display only, and not with gameplay systems. This is because units are first converted to an intermediary unit, such as meter, and reconverted to the unit to be displayed.
Although the plugin is using double float precision, this may still lead to some substantial loss of precision in some unit conversions.
