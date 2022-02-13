# WiFi_Locator
A C program that runs an open source embedded server implementation named Civetweb, that is capable of searching for Wifi devices in the vicinity. A simple Webpage has been designed to list the names and allow for connection.




## Running the code
1. First compile the code in Vscode using already present configurations or build the code using the command:

`gcc server.c wifi_search.c include/libcivetweb.a -pthread -ldl -o server`


2. Run the executable directly through Vscode (might require sudo access later) or in the build folder directly run:

`sudo ./WiServer`


3. Go to your preferred web browser and type in "localhost:8080" to view the Web UI or you can use Postman to execute individual https calls.

4. Check the terminal output/debug messages for more information and responses to button clicks on the web UI.


## Some additional libraries required
1. json-c <https://github.com/json-c/json-c>
2. pthread
3. civetweb <https://github.com/civetweb/civetweb>