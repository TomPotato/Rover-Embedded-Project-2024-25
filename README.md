<h1 align="center">The Mars Rover</h1>

<p>With this project we aim to get a better understanding of what skills developing a Mars Rover takes.</p>
<p><i>"How does a Rover really work?","What defines a Rover?","How can we make it connect to an external Module?"</i></p>
<p>While it would be challenging to build a full Mars Rover in a limited timeframe, understanding how they work and the challenges engineers face can give us a greater appreciation for the level of innovation and precision that goes into their development.</p>

<h3 align="center">The finished Product</h3>

<p float="left" align="center">
<img src="./images_readme/Rover1.jpg" height="250">
<img src="./images_readme/Rover2.jpg" height="250">
</p>

<br>

<p float="left" align="center">
<img src="./images_readme/Rover3.jpg" height="175">
<img src="./images_readme/Rover4.jpg" height="175">
</p>

<h3 align="center">Components</h3>

<ul list-style-type: "square">
    <li>a few (a lot) 3d printable components</li>
    <li>4x mini servomotors of 3v outtage</li>
    <li>27x Jumpers Arduino</li>
    <li>1x Micro Servo motor SG90</li>
    <li>1x Arduino compatible Voltmeter</li>
    <li>1x Arduino OSOYOO UNO Board</li>
    <li>1x Arduino ESP8266 Shield for Arduino</li>
    <li>1x Buzzer compatible with Arduino</li>
    <li>1x Module Driver Motors OSOYOO Model X</li>
    <li>1x Bluetooth sensor Arduino compatible HC05</li>
    <li>1x Ultrasonic sensor Arduino compatible HC-SR04</li>
    <li>nx Various screws and knobs to model the Body of the Rover</li>
    <li>1x Texas Instruments MSP432P401R</li>
    <li>1x Texas Instruments BoosterPack MKII</li>
    <li>1x Breadboard</li>
    <li>1x Logic level converter</li>
    <li>1x LED</li>
    <li>PC/LAPTOP</li>
</ul>

<h3 align="center">Software</h3>

<ul>
    <li>Visual Studio Code</li>
    <li>Arduino IDE</li>
    <li>Energia IDE</li>
    <li>Putty Serial Communication App</li>
    <li>Windows CMD/Powershell</li>
</ul>

<h3 align="center">Programming Language</h3>

<ul>
    <li>C/C++</li>
    <li>Python</li>
</ul>

<h3 align="center">Library</h3>

<ul>
    <li>Python library:serial</li>
    <li>Arduino library: <SoftwareSerial.h> , <Servo.h> </li>
</ul>

<h3 align="center">Project Layout</h3>

<pre>
<code>
ROVER
│
├── README.md
├── LICENSE (MIT defined)
├── rover_exoscheleton               # stl used for the exoskeleton of the rover
├── images_readme                   
│   └──images                        # images used inside the readme
├── images_schematics               
│  └──images                         # schematics of the Arduino jumpers connections in the Rover
├── presentation!!                   # presentation of the project
└── Our Code
    ├── ArduinoUNO                   # Arduino side code
    │   ├── ComponentsCode           # Components template code with testing before implementation
    │   └── RoverFinalSketch         # Final sketch to be burned into the Rover
    ├── MSP43P401R                   # Texas side code
    └── SideCode                     # Side code to make the BLE module to connect to the pc 
</code>
</pre>

<h3 align="center">How to Reproduce the Project</h3>

<h3 align="center">Contributors</h3>

<p><i>Agosti Tommaso, Nodari Francesco, Wu Alessio, Wu Davide</i></p>

<ul>
    <li>RICORDA</li>
    <li>voli della sigaretta elettronica: 9</li>
    <li>RX e TX non sono posizionati correttamente, scambiali!!!</li>
    <li>hc-05 non funziona coi 5V</li>
    <li></li>
</ul>

<h3 align="center">Goals</h3>

<ul>
    <li>sending commands from msp to arduino via bluetooth to control the rover </li>
    <li>Commands:</li>
    <li>F(Forward)</li>
    <li>B(Backward)</li>
    <li>L(Left)</li>
    <li>R(Right)</li>
    <li>P(rovers' led on)</li>
    <li>W(rovers' led off)</li>
    <li>sending rovers' led status and information of distance from arduino to msp432</li>
    <li>The multicolor LED integrated into the BoosterPack operates in accordance with control commands (e.g., LED ON/OFF) transmitted by the Arduino             
    microcontroller.</li>
</ul>
<h3 align="center">Steps</h3>
<ul>
   <li></li> 
</ul>
