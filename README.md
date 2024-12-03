# RFID-based Attendance System with ThingSpeak Integration

This project implements a simple **RFID-based attendance system** using an **ESP8266** Wi-Fi module, an **RFID reader (RC522)**, an **LCD display**, and a **servo motor** to automate attendance marking and entry control. The system logs the attendance data (student name and roll number) to the **ThingSpeak** cloud platform in real-time, allowing for easy tracking of attendance.

## Features
- **RFID Scanning:** Scans RFID cards and checks their unique identifiers to match against predefined entries.
- **LCD Display:** Displays the student's name and roll number when they successfully scan their card.
- **Servo Motor:** Controls an automated door lock based on the scan, allowing entry if the student is authorized.
- **Buzzer:** Beeps when a valid RFID card is scanned.
- **Cloud Integration:** Logs attendance data (name and roll number) to **ThingSpeak** in real-time.
- **Wi-Fi Connectivity:** Connects to a Wi-Fi network to enable cloud communication and real-time data logging.

## Components Required
- **ESP8266 Wi-Fi module** (NodeMCU, Wemos D1 Mini, etc.)
- **RFID Reader (RC522 or similar)**
- **RFID Cards**
- **16x2 I2C LCD Display**
- **Servo Motor** (for door control)
- **Buzzer**
- **Jumper Wires**
- **Breadboard**
- **Power Supply for ESP8266**

## Circuit Connections
- **RFID Module (RC522):**
  - `SDA` to `D2`
  - `SCK` to `D5`
  - `MOSI` to `D7`
  - `MISO` to `D6`
  - `GND` to `GND`
  - `RST` to `D8`
  - `3.3V` to `3.3V`

- **LCD I2C:**
  - `SCL` to `D1`
  - `SDA` to `D2`
  - `VCC` to `3.3V`
  - `GND` to `GND`

- **Servo Motor:**
  - `Signal` to `D6`
  - `VCC` to `5V`
  - `GND` to `GND`

- **Buzzer:**
  - `Pin` to `D5`
  - `GND` to `GND`
 
## Software Libraries Used
- **ESP8266WiFi:** Used for handling the Wi-Fi connection.
- **ThingSpeak:** Used to communicate with the ThingSpeak IoT platform for logging attendance data.
- **SoftwareSerial:** Used to communicate with the RFID module.
- **LiquidCrystal_I2C:** Controls the LCD display for showing student information.
- **Servo:** Used to control the servo motor to unlock/lock the door.
- **WiFiClient:** Manages communication with the ThingSpeak platform.

## ThingSpeak Setup
1. Create a ThingSpeak account [here](https://thingspeak.com/).
2. Create a new channel on ThingSpeak to log the attendance data.
3. Retrieve the **Channel Number** and **Write API Key** from the ThingSpeak channel.
4. Update the following values in the code:
   - `myChannelNumber` with your ThingSpeak channel number.
   - `myWriteAPIKey` with your ThingSpeak channel's write API key.
  
## Code Overview
The following code integrates an RFID reader with an ESP8266 to log attendance to ThingSpeak and control a servo for access control.

```cpp
void setup()
{
  Serial.begin(9600);
  rfid.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  servo.attach(D6);
  delay(1000);
  servo.write(0);
  delay(1000);

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  ThingSpeak.begin(client);
  
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
}

void loop()
{
  lcd.clear();
  lcd.print(" SCAN YOUR CARD ");
  delay(100);

  ThingSpeak.setField(1, name);
  ThingSpeak.setField(2, number);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (rfid.available() > 0) {
    beep();
    data = " ";
    name = " ";
    number = " ";
    data = rfid.readString();
    Serial.print("RFID data: ");
    Serial.println(data);
  }

  // Check for specific RFID tags
  if (data == "0100660F147C") {
    name = "    Nageswari   ";
    number = "   ECE-456   ";
    lcd.clear();
    lcd.print(" ATTENDENCE  OK ");
    delay(2000);
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0, 1);
    lcd.print(number);
    servo.write(90);  // Unlock door
    delay(3000);
    servo.write(0);   // Lock door
    delay(1000);
  }
  // Add other RFID cards here with the same format as the above
}
