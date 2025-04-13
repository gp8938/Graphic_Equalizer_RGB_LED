# Graphic Equalizer RGB LED

This project uses an RGB LED strip to visualize audio spectrum data in real-time. The visualization is achieved by mapping audio spectrum values to different colors and brightness levels on the LED strip.

## Features
- Real-time audio spectrum visualization
- Customizable LED colors and brightness
- Noise filtering to ignore low-level signals
- Sine wave animation for idle mode

## Requirements
- Arduino-compatible microcontroller
- WS2811 or compatible RGB LED strip
- Audio spectrum analyzer IC (e.g., MSGEQ7)
- FastLED library
- FastGPIO library

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/Graphic_Equalizer_RGB_LED.git
   ```
2. Open `Graphic_Equalizer_RGB_LED.ino` in the Arduino IDE.
3. Install the required libraries via the Arduino Library Manager:
   - FastLED
   - FastGPIO
4. Connect the hardware as per the pin definitions in the code.
5. Upload the code to your microcontroller.

## Usage
- Power on the system and play audio through the connected input.
- The LED strip will visualize the audio spectrum in real-time.
- If no audio is detected, the LEDs will turn off.
- Use the sine wave animation function for a dynamic idle mode.

## Customization
- Modify the `NUM_LEDS` and `DATA_PIN` constants in the code to match your LED strip configuration.
- Adjust the `map` function parameters to fine-tune the spectrum value mapping.
- Change the colors in the `updateLEDs` function to customize the visualization.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
