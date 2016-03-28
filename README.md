# How to conncet to IBM Bluemix from LinkIt Smart 7688 Duo using Arduino Yun Bridge

Tutorial : How to read temperature and humidity Sensor data from  LinkIt Smart 7688 Duo and send to IBM Bluemix using Arduino 
          Yun Bridge 

#Step 1: Switch the LinkIt Smart 7688 Duo in to station mode:

      Connect the LinkIt Smart 7688 Duo to the work station using a micro-USB cable and set the 7688 in 
      “Station mode” to have internet access. Two modes are supported   by the LinkIt Smart 7688, one is
      the Access Point (AP) mode and the other is station mode. 
      By default the LinkIt Smart 7688 Duo will be in AP mode. You can change the mode to “Station mode” 
      by doing the following steps:
        a.	Connect your workstation with LinkIt Smart 7688 Duo ( from the Wi-Fi AP list) and then login
        b.	From web browser type mylinkit.local , go to Network tab , select “Station mode” , choose 
            appropriate Wi-Fi network , enter Wi-Fi AP password ( if any) and 
            press “CONFIGURE & RESTART” button. The other option would be to use UCI commands 
            in the system console to change from AP to station mode.

      For more details please check the section 4.6.5 of LinkIt Smart 7688 Developer’s guide.

#Step 2: Using SSH connect to 7688 Duo and enable Yun Bridge Library 

        Connect to 7688 console from SSH to using Putty.
          Refer section 4.5.4. Connecting to the System Console of LinkIt Smart 7688 Developer’s guide.
          http://labs.mediatek.com/fileMedia/download/87c801b5-d1e6-4227-9a29-b5421f2955ac

        Enter the below commands from the SSH console to enable Arduino Yun Bridge.
        uci set yunbridge.config.enabled=’0’
        uci set commit
        reboot
        For more information please check Section 6.7 of LinkIt Smart 7688 Developer’s guide

#Step 3: Connect DHT Temperature & Humidity Sensor with the LinkIt Smart 7688 Duo board.

          Connect the DHT sensor to the PIN, say PIN number 4. Here you can see the breakout for 
          LinkIt Smart 7688 Duo has been used to connect sensor and LinkIt Smart 7688 Duo
        1.	Download DHT library from the below link 
            https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTlib
        2.	Add the library to the Arduino IDE .
            From Arduino IDE -> Sketch -> Include Library -> Add .ZIP library, select the zip you 
            downloaded from the step 1.
            
        3. You need to have the PubsubClient library as well. You can download the same from
           https://github.com/knolleary/pubsubclient and add the library to Arduino IDE.

#Step 4: Use the Arduino Sketch, modify & Upload
      Make sure you follow the below points within the Arduino IDE.

        a.	Within the Arduino IDE, selected board “LinkIt Smart 7688 Duo” ( Menu ->Tools -> 
          Board: LinkIt Smart 7688 Duo” )
        b.	Arduino IDE detects the LinkIt Smart 7688 Duo port number ( Menu ->Tools ->Port )

      The Arduino Sketch has Mac address hardcoded. You can change the MAC address by changing 
      the string char macstr[] to your LinkIt Smart 7688 Duo’s MAC address.
      char macstr[] = "12345abcded";
    •	Compile the sketch and upload. Once upload is done, start the “Serial Monitor” to 
      check the log messages.
	
#Step 5: Go to IBM Bluemix quickstart site and observe the sensor data

    •	Go to https://quickstart.internetofthings.ibmcloud.com/#/
    •	Enter the same MAC  address( same MAC mentioned in the Arduino sketch ) in the text 
      field and press “GO”
    •	Now you should be able to see the sensor data (temperature and humidity) in a graph.
