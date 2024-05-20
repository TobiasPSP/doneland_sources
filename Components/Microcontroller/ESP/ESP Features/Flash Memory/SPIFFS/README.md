<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# SPIFFS (SPI Flash File Storage)

> Built-In File-Based Data Storage

*SPIFFS* (*Serial Peripheral Interface Flash File System*) takes a portion of the *Flash* memory and utilizes it similar to a *USB Stick*: data can be organized and stored as files, similar to attaching an external *SD Drive* to your microcontroller.

> [!TIP]
> *SPIFFS* is a *file-based* filesystem (no *directories* and *hierarchies*) that utilizes only around 75% of assigned partition space, tends to *fragmentation*, and when the chip experiences a power loss during a file system operation, this can result in SPIFFS corruption. A much more *robust* and *modern* alternative is *LittleFS*.





## Basic SPIFFS Actions
The basic file operations are simple and *straight-forward* to use:


### Formatting
Before you can store data with *SPIFFS*, you need to *format* its memory. This needs to be done only once, and *formatting* erases the entire *SPIFFS* memory.

````c++
#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"


boolean initSpiffs() {
  // try and use SPIFFS
  bool ok = SPIFFS.begin(false);
  
  if (ok) {
    Serial.println("SPIFFS ok.");
    return ok;
  }

  // if not ok, try formatting
  Serial.print("SPIFFS is not ok, trying to format...");
  ok = SPIFFS.begin(true);
  Serial.println("done.");

  // check to see whether SPIFFS is 
  if (!ok) {
    Serial.println("SPIFFS still not ok.");
  } else {
    Serial.println("SPIFFS ok.");
  }
  
  return ok;
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
  delay(500);  
  
  initSpiffs();
}

void loop(){
}
````

On first run, the result may look like this:

````
SPIFFS is not ok, trying to format...done.
SPIFFS ok.
````

This indicates that *SPIFFS* was not formatted yet. Formatting may take from a few seconds to a few minutes, based on *SPIFFS* partition size.

Once *SPIFFS* was formatted, on next boot or power-up the output looks like below, and there are no more delays since *formatting* needs to be done only once:

````
SPIFFS ok.
````

#### Forced Formatting
In above example, the *formatting* was done *implicitly* by `begin(true);`: if the method runs into an error, it tries and formats *SPIFFS*. 

There are good reasons why you may want to *re-format* an already formatted *SPIFFS* drive, i.e. to erase all data. For this, you can call `SPIFFS.format();`.

### Saving And Reading File Content
Writing text to a file, and reading back the text from a file is trivial. Here is a sketch demonstrating how it is done:

````c++
#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"

void setup() {
  Serial.begin(115200);
  while(!Serial);
  delay(500);  

  // init SPIFFS (format SPIFFS if not formatted yet)
  if(!SPIFFS.begin(true)) {
    Serial.println("Unable to mount SPIFFS - aborting.");
    return;
  }

  // creating a new file:
  File file = SPIFFS.open("/firstFile.txt", FILE_WRITE, true);  // true = create a NEW file
  // writing a line to it:
  file.println("I am adding this line of text.");
  // writing text to it:
  file.print("Hello ");
  // writing more text and a linefeed to it:
  file.println("World!");
  // closing file:
  file.close();

  // re-opening file to append more information
  file = SPIFFS.open("/firstFile.txt", FILE_APPEND);
  // appending one more line
  file.println("Third line...");
  // close file
  file.close();

  // reading file
  // does the file exist?
  if (!SPIFFS.exists("/firstFile.txt")) {
    Serial.println("File not found - aborting.");
    return;
  }

  file = SPIFFS.open("/firstFile.txt", FILE_READ);
  if (!file || file.isDirectory()) {
    Serial.println("File not found - aborting.");
  }

  file = SPIFFS.open("/firstFile.txt", FILE_READ);
  int line=0;
  while(file.available()) {
      line++;
      Serial.print(line);
      Serial.print(": ");
      Serial.println(file.readStringUntil('\n'));
    }

}

void loop() {}
````

The result in the *Serial Monitor* looks like this:

````
1:I am adding this line of text.
2:Hello World!
3:Third line...
````

Basically, the method `SPIFFS.open();` provides access to a file. The *mode* determines *what* you want to do with the file: `FILE_WRITE`, `FILE_APPEND`, or `FILE_READ`.



> Tags: SPIFFS, Filesystem, Flash, Memory

[Visit Page on Website](https://done.land/components/microcontroller/esp/espfeatures/flashmemory/spiffs?161442050021242211) - created 2024-05-20 - last edited 2024-05-20
