# ESP8266 MQTT Client for Home Automation

This repository contains an Arduino sketch for an ESP8266 board that acts as an MQTT client. It connects to a WiFi network, publishes messages to an MQTT topic, and subscribes to the same topic to receive commands, demonstrating a basic home automation setup where the ESP8266 can control an LED based on MQTT messages.

-----

## Table of Contents

  - [Features]
  - [Prerequisites]
  - [Installation]
      - [Arduino IDE Setup]
      - [Library Installation]
      - [Code Upload]
  - [Configuration]
  - [Usage]
  - [MQTT Topics]
  - [Circuit Diagram (Conceptual)]
  - [Contributing]
  - [License]

-----

## Features

  * **WiFi Connectivity:** Connects the ESP8266 to your local WiFi network.
  * **MQTT Communication:** Utilizes the MQTT protocol for lightweight messaging.
  * **Periodic Publishing:** Publishes a "Hello from ESP\!" message with an incrementing counter every 5 seconds to `myhome/test`.
  * **Message Subscription:** Subscribes to the `myhome/test` topic to receive incoming messages.
  * **LED Control:** Toggles an LED connected to pin D4 "Built in Led" based on "on" and "off" messages received via MQTT.
  * **Automatic Reconnection:** Automatically attempts to reconnect to the MQTT broker if the connection is lost.

-----

## Prerequisites

Before you begin, ensure you have the following:

  * **ESP8266 Development Board:** (e.g., NodeMCU ESP-12E, ESP-01, etc.)
  * **Arduino IDE:** Installed on your computer.
  * **Micro-USB Cable:** To connect the ESP8266 to your computer.
  * **LED and a Resistor:** For the LED control functionality (e.g., 220 Ohm resistor).
  * **Breadboard and Jumper Wires:** For prototyping the circuit.
  * **WiFi Network:** With internet access (if using a public MQTT broker).
  * **MQTT Broker:** This code uses `broker.hivemq.com` as a public broker. You can replace this with your own local MQTT broker if preferred.

-----

## Installation

### Arduino IDE Setup

1.  **Install ESP8266 Board Manager:**
      * Open Arduino IDE.
      * Go to `File > Preferences`.
      * In "Additional Boards Manager URLs," add: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
      * Go to `Tools > Board > Boards Manager...`
      * Search for "esp8266" and install the "ESP8266 by ESP8266 Community" package.

### Library Installation

1.  **Install PubSubClient Library:**
      * In Arduino IDE, go to `Sketch > Include Library > Manage Libraries...`
      * Search for "PubSubClient" and install the library by `Nick O'Leary`.

### Code Upload

1.  **Open the Sketch:** Copy and paste the provided code into a new Arduino IDE sketch.
2.  **Select Your Board:** Go to `Tools > Board` and select your specific ESP8266 board (e.g., "NodeMCU 1.0 (ESP-12E Module)").
3.  **Select Port:** Go to `Tools > Port` and select the serial port connected to your ESP8266.
4.  **Upload:** Click the "Upload" button (right arrow icon) to compile and upload the code to your ESP8266 board.

-----

## Configuration

Before uploading the code, you need to modify the following lines in the sketch to match your network details:

```cpp
const char* ssid = "Orange_";         // WiFi SSID
const char* password = "orange1234";  // WiFi password
```

Replace `"Orange_"` with your WiFi network name and `"orange1234"` with your WiFi password.

Optionally, you can change the MQTT broker and port:

```cpp
const char* mqtt_server = "broker.hivemq.com";
const int mqttPort = 1883;
```

If your MQTT broker requires authentication, uncomment and fill in the `mqttUser` and `mqttPassword` variables:

```cpp
// const char* mqttUser = "MQTT_USERNAME";
// const char* mqttPassword = "MQTT_PASSWORD";
```

-----

## Usage

Once the code is uploaded and your ESP8266 is connected to WiFi and the MQTT broker:

1.  **Open Serial Monitor:** Open the Serial Monitor in Arduino IDE (`Tools > Serial Monitor`) at a baud rate of `115200`. You will see messages indicating WiFi connection status, MQTT connection attempts, and published messages.
2.  **Publishing Messages:** The ESP8266 will automatically publish messages like "Hello from ESP\! Count: X" to the `myhome/test` topic every 5 seconds.
3.  **Controlling the LED:**
      * To turn the LED **on**, publish the message `"on"` to the `myhome/test` topic.
      * To turn the LED **off**, publish the message `"off"` to the `myhome/test` topic.

You can use any MQTT client (e.g., MQTT Explorer, Mosquitto command line, another ESP32/ESP8266) to subscribe to `myhome/test` and observe the published messages, as well as to publish "on" or "off" commands to control the LED.

-----

## MQTT Topics

  * **`myhome/test`**:
      * **Published:** "Hello from ESP\! Count: X" (periodic status updates)
      * **Subscribed:** Receives "on" or "off" commands to control the LED.

-----

## Circuit Diagram (Conceptual)

Here's a simple conceptual wiring for the LED:

```
ESP8266 (NodeMCU)
             +--------------------+
             |                    |
       D4 ---| LED Pin            |-----> (Short Leg of LED)
             |                    |
             |                    |
             |         GND        |-----> (Resistor) ----> (Long Leg of LED)
             +--------------------+
```

  * Connect the **long leg (anode)** of the LED to one end of a **220 Ohm resistor**.
  * Connect the other end of the resistor to the **GND** pin on the ESP8266.
  * Connect the **short leg (cathode)** of the LED directly to the **D4** pin on the ESP8266.

-----

## Contributing

Feel free to fork this repository, suggest improvements, or open issues. Contributions are always welcome\!

-----

## License

This project is open-source and available under the [MIT License](https://www.google.com/search?q=LICENSE).
