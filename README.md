# Simple Battery Meter
## Description

Just a really simple battery meter that display the current battery level of ~~your PC / laptop / Windows tablet~~ any Windows device on a little window floating at the corner of your screen, nothing fancy at all.

<img width="71" alt="2024-06-05 (1)" src="https://github.com/EbonCorvin/SimpleBatteryMeter/assets/153107703/5a710a97-c2b6-4b77-a541-edfe15879226">
<img width="71" alt="2024-06-05" src="https://github.com/EbonCorvin/SimpleBatteryMeter/assets/153107703/e555b0b9-74d4-45d0-9b69-da2d0062da08">
<img width="71" alt="2024-06-05" src="https://github.com/EbonCorvin/SimpleBatteryMeter/assets/153107703/b9e304be-8e62-4790-ad52-db7f6070b9ad">

Please note that it was a project I created for myself 8 years ago, and the chance that the project may receive update is slim. Though I may still try to add some experimental features on it in the future without making it becomes too "large and useless".

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installation

You don't really have to install the program, the program only contains some simple Windows API call, as long as your Windows version is XP or later, just run the executable should be fine.

## Usage

You may look around the code and judge how bad this C++ beginner and hobbyist was. I mean, the program is really simple, it just waits for the **WM_POWERBROADCAST** message from Windows, then get the power status of your system with a function call to **GetSystemPowerStatus**. Finally, update the UI with the battery status, that's it.   

## Contributing

Wow really? You wanna contribute on this project? Just make a new project at this point LOL

## License

[LICENSE](LICENSE)

## Acknowledgements

## Contact
