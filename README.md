# iot-based-crowd-control-system

IoT-based real-time crowd monitoring system using Arduino UNO and ESP8266 with PIR sensors, smart ventilation control via servo motor, ThingSpeak cloud integration, data visualization, and automated email alerts for overcrowding prevention.

The system ensures accurate bidirectional people counting by preventing double detection, displays live crowd status on an LCD, and supports threshold-based automation for safety management. This project is designed as a low-cost, scalable solution for applications such as classrooms, laboratories, offices, and other small public spaces, with potential extensions to smart building and smart city systems.
****
## Technologies Used
- Arduino UNO
- ESP8266 (WEMOS D1)
- PIR Sensors
- Servo Motor
- I2C LCD Display
- ThingSpeak IoT Cloud
- Embedded C
## Hardware Setup
The system uses two PIR sensors for entry and exit detection, an Arduino UNO for processing, an ESP8266 module for cloud communication, a servo motor for ventilation control, and an LCD for live status display.
## Working Principle
PIR sensors detect entry and exit movements and update the crowd count in real time. The data is sent to the ThingSpeak cloud using ESP8266, where it is visualized and analyzed. Email alerts are triggered when the crowd exceeds a predefined threshold, and ventilation is automatically adjusted based on the count.
## Project Report
The complete project documentation is available in the repository:
- `Project_Report/IOT_BASED_CROWD_CONTROL.pdf`
## Future Enhancements
- Camera-based crowd detection for higher accuracy
- Mobile application for real-time monitoring
- Support for multiple entry and exit points
