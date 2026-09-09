<img src="/assets/images/lightning.png" width="100%" height="100%" />

# ArduinoOBI PowerShell Script

> Use PowerShell to talk to your Makita Battery

Any software can use the *ArduinoOBI* dongle to talk to Makita batteries. Below you find a PowerShell script that replaces the 
original [Open Battery Information](https://github.com/mnh-jansson/open-battery-information/tree/main) python script.

## Overview

The purpose of the provided PowerShell script is **not** to replace [Open Battery Information](https://github.com/mnh-jansson/open-battery-information), but rather to show in a simple way how talking to Makita batteries really works. It may be easier to experiment and adjust.

The PowerShell script isn't designed to be a production tool. For example, it does not use multiple communication attempts. Should a call fail, try it again. Should it fail permanently, play with the delays and timeouts. It is for learning and experimenting.

The first and longest part of the script defines the class `MySerialPort`. You can collapse and ignore this part, it is a generic implementation for serial port communication.

Focus on `ArduinoOBI`: this class is derived from `MySerialPort` and contains just the Makita specifics. Here you can see the actual command bytes that are sent, and the responses that are received.

## PowerShell Script

To run this script, the easiest way is to launch the default *PowerShell ISE editor* on Windows, then paste the script into the editor pane, and run it with `F5`.

In the interactive pane, you can then play with the implemented methods, i.e. call `$arduinoOBI.Test()`. Below the script, you find additional hints and examples.


````powershell


class MySerialPort
{
  [System.IO.Ports.SerialPort]$port = [System.IO.Ports.SerialPort]::new()
  [string]$portName = $([System.IO.Ports.SerialPort]::GetPortNames() | Select-Object -First 1)
  
  [int]$baudRate = 9600 #115200
  [bool]$oldCrc = $false
  
  MySerialPort()
  {
  }
  
  MySerialPort([int]$BaudRate)
  {
    $this.baudRate = $BaudRate
  }
  
  MySerialPort([string]$PortName,[int]$BaudRate)
  {
    $this.portName = $PortName
    $this.baudRate = $BaudRate
  }
  
  
  
  [void]Open()
  {
    if (!$this.port.IsOpen)
    {
      if([string]::IsNullOrEmpty($this.PortName))
      {
        throw "No port name set."
      }
      if($this.BaudRate -le 0)
      {
        throw "No baud rate set."
      }
      $this.port.BaudRate = $this.baudRate
      $this.port.PortName = $this.portName
      $this.port.DataBits = 8
      $this.port.Parity = [System.IO.Ports.Parity]::None
      $this.port.StopBits = [System.IO.Ports.StopBits]::One
      $this.port.ReadTimeout = 1000
      $this.port.WriteTimeout = 1000
      try
      {
        $this.port.Open()
      }
      catch
      {
        throw "Error opening COM port: $_"
      }
    }
  }

  [void]Flush()
  {
    if ($this.port.IsOpen)
    {
      $this.port.DiscardInBuffer()
      $this.port.DiscardOutBuffer()
    }
  }
  
  [void]Close()
  {
    if ($this.port.IsOpen)
    {
      $this.port.Close()
    }
  }
  [void]Dispose()
  {
    
    $this.Close()
    $this.port.Dispose()
  }
  [void]Write([byte[]]$message)
  {
    $this.Open()
    try
    {      
      $this.port.Write($message, 0, $message.length)
    }
    catch
    {
      throw "Error writing data to COM port."
    }
    
    
  }
  [void]Read([byte[]]$buffer, [int]$length)
  {
    $this.Open()
    try
    {      
      $real_length = $this.port.Read($buffer, 0, $length)
      if ($real_length -ne $length)
      {
        throw "Requested $length bytes, received $real_length bytes."
      }
    }
    catch
    {
      throw "Error reading data from COM port."
    }
  }
  
  [byte[]]GetResponse([int]$length)
  {
    $buffer = [byte[]]::new($length)
    $this.Read($buffer, $buffer.Length)
    
    return $buffer
  }

  [void]Delay([int]$Delay)
  {

    [System.Threading.Thread]::Sleep($Delay)
        
  }

  [bool]VerifyChecksum([byte[]]$Message)
  {
    # subtract 2: the last two bytes are the checksum and not part of the message
    $length = $Message.Count - 2

    [uint16]$crc = 0xffff
    for ($i = 0; $i -lt $length; ++$i) {
      $crc = $crc -bxor $Message[$i]

      for ($j = 0; $j -lt 8; ++$j) {
        [uint16]$xor = 0
        if ($crc -band 1) {
          $xor = 0xa001
        }
        $crc = ($crc -shr 1) -bxor $xor
      }
    }

    # Flip upper and lower CRC bytes for Kunkin FW Date > 2020
    if (!$this.oldCrc) {
      $crc = ([uint16]($crc -band 0xFF) -shl 8) -bor ([uint16]($crc -band 0xFF00) -shr 8)
    }
    
    # compare calculared checksum with message checksum
    return ($Message[$length+1] -eq [byte]($crc -band 0xff)) -and ($Message[$length] = [byte]($crc -shr 8))
  }


  

  [void]SetBaudRate([int]$BaudRate)
  {
    $this.baudRate = $BaudRate
    $this.Close()
  }

  [void]SetPortName([string]$PortName)
  {
    if ($this.port.IsOpen)
    {
      $this.Close()
    }
    $this.portName = $PortName
    
  }

  static [object[]] GetPortNames()
  {
    return Get-CimInstance -ClassName win32_pnpentity -Filter 'PNPClass="Ports" and Present=TRUE and ConfigManagerErrorCode=0 and Status="OK"' |
    ForEach-Object {
      $s_DeviceID = $_.PnpDeviceID
      $s_RegEnum  = "HKLM:\System\CurrentControlSet\Enum\$s_DeviceID\Device Parameters"
      $portName = (Get-ItemProperty -Path $s_RegEnum).PortName
      if (![string]::IsNullOrEmpty($portName))
      {
        $_ | Select-Object -Property @{N='Port';E={$portName}}, Description, Manufacturer, Service
      }
    }
  }
}


class MakitaBatteryInfo
{
  [string]$Name
  [double]$Capacity
  [double]$DesignVoltage
  [double]$PackVoltage
  [double]$VoltageDiff
  [int]$ChargeCount
  [datetime]$ManufactureDate
  [double]$TempCell
  [double]$TempMosFet
  [bool]$Locked
  [double]$voltage1
  [double]$voltage2
  [double]$voltage3
  [double]$voltage4
  [double]$voltage5
  [byte]$Status
  [string]$Rom_Id
  [bool]$isF05134Controller
  [string]$RawMessage
  [version]$ArduinoOBIVersion  
}

enum StatusCode
{
  Success
  Failure
  ArduinoObiNotConnected
  ArduinoObiNotResponding
  BatteryNotResponding
}
class DiagnosticInfo
{
  [StatusCode]$Status
  [bool]$SerialAvailable = $false
  [bool]$ObiResponding = $false
  [bool]$BatteryResponding = $false
  [version]$OBIVersion
  [string]$SelectedSerialPort
  [string[]]$AvailablePorts
  [string]$ConnectedBattery

}

class ArduinoObi : MySerialPort
{

  [Nullable[bool]]$isF05134Controller = $null
  

  ArduinoObi()
  {
  
  }
  
  ArduinoObi([int]$BaudRate) : base($BaudRate)
  {
  }
  
  ArduinoObi([string]$PortName,[int]$BaudRate) : base($PortName, $BaudRate)
  {
  }

  [DiagnosticInfo]Test()
  {
    $info = [DiagnosticInfo]::new()
    # test whether there are com ports at all
    $info.AvailablePorts = [System.IO.Ports.SerialPort]::GetPortNames()
    if ($info.AvailablePorts.Count -eq 0)
    {
      $info.Status = [StatusCode]::ArduinoObiNotConnected
      return $info
    }
    $info.SerialAvailable = $true
    
    # test whether ArduinoOBI is connected
    try
    {
      $info.SelectedSerialPort = $this.portName
      $info.OBIVersion = $this.GetVersion()
      $info.ObiResponding = $true
    }
    catch
    {
      $info.Status = [StatusCode]::ArduinoObiNotConnected
      return $info
    }
    
    try
    {
      $info.ConnectedBattery = $this.GetName()
      $info.BatteryResponding = $true
    }
    catch
    {
      $info.Status = [StatusCode]::BatteryNotResponding
    }
    
    return $info
  }

  [byte[]]ExecuteCommand([byte[]]$Command)
  {
    return $this.ExecuteCommand($Command, 500)
  }
  
  [byte[]]ExecuteCommand([byte[]]$Command, [int]$Delay)
  {
    $response_length = $Command[2]+2
    
    try
    {
      $this.Flush()
      $this.write($Command)
      $this.delay($Delay)
      $response = $this.GetResponse($response_length)
      if ($response.Length -ne $response_length)
      {
        throw "Incomplete Response: Expected response was $response_length, but $($response.Length) bytes were received."
      }
      else
      {
        if (($response.Length -gt 2) -and (($response[2..($response.Length - 1)] | Where-Object { $_ -ne 0xFF }).Count -eq 0)) {
          throw "Cannot communicate with battery."
        }
      
      }
      return $response
    }
    finally
    {
      $this.Close()
    }
    return $null
  }
  

  [version]GetVersion()
  {
    <#
        0x01: initiator (always 0x01)
        0x00: 0 bytes of extra data
        0x03: 3 bytes of return data expected
        0x01: command
    #>
    $command = 0x01, 0x00, 0x03, 0x01
    $response = $this.ExecuteCommand($command)
    if ($response.Length -eq 5)
    {
      return [version]::new($response[2], $response[3], $response[4])
    }
    else
    {
      return $null
    }
  }
  
  [string]GetName()
  {
    <#
        0x01: initiator (always 0x01)
        0x02: 2 bytes of extra data
        0x10: 16 bytes of return data expected
        0xCC: command
        0xdc: first extra data byte
        0x0c: second extra data byte
    #>
    $this.isF05134Controller = $false
    
    $command = 0x01, 0x02, 0x10, 0xCC, 0xDC, 0x0C
    $response = try
    {
      $this.ExecuteCommand($command)
    } catch { }

    if (($response.Length - 2) -eq 0x10) 
    {
      $modelName = [System.Text.Encoding]::UTF8.GetString($response[1..8])
      if (![string]::IsNullOrWhiteSpace($modelName))
      {
        return $modelName
      }
    }
    $this.isF05134Controller = $true  

    $command = 0x01, 0x00, 0x02, 0x31
    $response = $this.ExecuteCommand($command)
    
    $modelName = "BL{0:X}{1:X}" -f $response[2], $response[3]
    return $modelName
  }

  [MakitaBatteryInfo]GetBatteryInfo()
  {
    <#
        0x01: initiator (always 0x01)
        0x02: 2 bytes of extra data
        0x28: 40 bytes of return data expected
        0x33: command
        0xAA: first extra data byte
        0x00: second extra data byte
    #>
    
    $command = 0x01, 0x02, 0x28, 0x33, 0xAA, 0x00
    $response = $this.ExecuteCommand($command)
    
    $info = [MakitaBatteryInfo]::new()
    
    $info.Rom_Id = ($response[2..9] | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
    $info.RawMessage = ($response[10..41] | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
    
    $b36 = [ArduinoObi]::SwapNibble($response[36])
    $b37 = [ArduinoObi]::SwapNibble($response[37])
    
    $info.ChargeCount = (($b36 -shl 8) -bor $b37) -band 0x0FFF
    
    $info.Locked = $response[30] -band 0x0F
    $info.Status = $response[29]
    $capacity = [ArduinoObi]::SwapNibble($response[26])
    $info.Capacity = $capacity/10
    $voltage = [ArduinoObi]::SwapNibble($response[21])
    $info.DesignVoltage = $voltage
    
    try
    {
      $info.ManufactureDate = Get-Date -Year $response[2] -Month $response[4] -Day $response[3] -Hour 0 -Minute 0 -Second 0
    } catch {}
    
    $info.Name = $this.GetName()
    $info.isF05134Controller = $this.isF05134Controller
    
    if ($this.isF05134Controller)
    {
      $command = 0x01, 0x02, 0x00, 0xCC, 0xF0, 0x00
      $response = $this.ExecuteCommand($command, 100)
      $response = $this.ExecuteCommand($command, 100)
      
      $command = 0x01, 0x01, 0x02, 0xCC, 0x31
      $cell = $this.ExecuteCommand($command)
      $info.Voltage1 = (([uint16]$cell[2] -bor ([uint16]$cell[3] -shl 8))) / 1000

      $command = 0x01, 0x01, 0x02, 0xCC, 0x32
      $cell = $this.ExecuteCommand($command)
      $info.Voltage2 = (([uint16]$cell[2] -bor ([uint16]$cell[3] -shl 8))) / 1000

      $command = 0x01, 0x01, 0x02, 0xCC, 0x33
      $cell = $this.ExecuteCommand($command)
      $info.Voltage3 = (([uint16]$cell[2] -bor ([uint16]$cell[3] -shl 8))) / 1000

      $command = 0x01, 0x01, 0x02, 0xCC, 0x34
      $cell = $this.ExecuteCommand($command)
      $info.Voltage4 = (([uint16]$cell[2] -bor ([uint16]$cell[3] -shl 8))) / 1000

      $command = 0x01, 0x01, 0x02, 0xCC, 0x35
      $cell = $this.ExecuteCommand($command)
      $info.Voltage5 = (([uint16]$cell[2] -bor ([uint16]$cell[3] -shl 8))) / 1000

      $info.PackVoltage = $info.Voltage1 + $info.Voltage2 + $info.Voltage3 + $info.Voltage4 + $info.Voltage5
      
      $command = 0x01, 0x01, 0x02, 0xCC, 0x52
      $temperature = $this.ExecuteCommand($command)
      $lo = [uint16]$temperature[2]
      $hi = [uint16]$temperature[3]
      $info.TempCell = (($hi -shl 8) -bor $lo) / 100
      $info.TempMosFet = -1
      $voltages = $info.Voltage1, $info.Voltage2,  $info.Voltage3,  $info.Voltage4,  $info.Voltage5 | Sort-Object 
      $info.VoltageDiff = $voltages[-1] - $voltages[0]
    }
    else
    {
      $command = 0x01, 0x04, 0x1D, 0xCC, 0xD7, 0x00, 0x00, 0xFF
      $response = $this.ExecuteCommand($command)
      
      $lo = [uint16]$response[4]
      $hi = [uint16]$response[5]
      $info.Voltage1 = (($hi -shl 8) -bor $lo) / 1000
      
      $lo = [uint16]$response[6]
      $hi = [uint16]$response[7]
      $info.Voltage2 = (($hi -shl 8) -bor $lo) / 1000
      
      $lo = [uint16]$response[8]
      $hi = [uint16]$response[9]
      $info.Voltage3 = (($hi -shl 8) -bor $lo) / 1000
      
      $lo = [uint16]$response[10]
      $hi = [uint16]$response[11]
      $info.Voltage4 = (($hi -shl 8) -bor $lo) / 1000
      
      $lo = [uint16]$response[12]
      $hi = [uint16]$response[13]
      $info.Voltage5 = (($hi -shl 8) -bor $lo) / 1000
      
      $lo = [uint16]$response[14]
      $hi = [uint16]$response[15]
      $info.VoltageDiff = (($hi -shl 8) -bor $lo) / 1000000
      
      $lo = [uint16]$response[16]
      $hi = [uint16]$response[17]
      $info.TempCell = (($hi -shl 8) -bor $lo) / 100
      
      
      $lo = [uint16]$response[18]
      $hi = [uint16]$response[19]
      $info.TempMosFet = (($hi -shl 8) -bor $lo) / 100
      
      $lo = [uint16]$response[2]
      $hi = [uint16]$response[3]
      $info.PackVoltage = (($hi -shl 8) -bor $lo) / 1000
    }

    $info.ArduinoOBIVersion = $this.GetVersion()       
    
    return $info   
  }
  
  

  [void]EnableTestMode()
  {
    # we need to know battery type
    if ($null -eq $this.isF05134Controller)
    {
      $null = $this.GetName()
    }
  
    $command = if ($this.isF05134Controller)
    {
      0x01, 0x01, 0x00, 0xCC, 0x99
    }
    else
    {
      0x01, 0x03, 0x09, 0x33, 0xD9, 0x96, 0xA5
    }
    try { $this.ExecuteCommand($command, 200) } catch {}
  }
  
  [void]LedOn()
  {
    $this.EnableTestMode()
    $command = 0x01, 0x02, 0x09, 0x33, 0xDA, 0x31
    $this.ExecuteCommand($command)
  }
  
  [void]LedOff()
  {
    $this.EnableTestMode()
    $command = 0x01, 0x02, 0x09, 0x33, 0xDA, 0x34
    $this.ExecuteCommand($command)
  }
  
  [void]ClearError()
  {
    $this.EnableTestMode()
    $command = 0x01, 0x02, 0x09, 0x33, 0xDA, 0x04
    $this.ExecuteCommand($command)
  }
  
  
  static [byte]SwapNibble([byte]$byte)
  {
    return [byte]((($byte -band 0x0F) -shl 4) -bor (($byte -band 0xF0) -shr 4))
  }
}

# instantiate class:
$arduinoOBI = [ArduinoObi]::new()

# call methods on class:
$arduinoObi.GetBatteryInfo()
<#
    # other methods to play with:

    # Diagnose your setup:
    $arduinoOBI.Test()

    # turn battery LEDs all on and off:
    $arduinoObi.LEDOn()
    $arduinoObi.LEDOff()
#>
````

</details>

When you run this code in PowerShell, it instantiates the *ArduinoOBI* object in `$arduinoObi`. The first thing you should then do is run `Test()`. This tells you if your setup is working right, and if things are amiss, what you need to look into:

````powershell
PS C:\> $arduinoOBI.Test()


Status             : Success
SerialAvailable    : True
ObiResponding      : True
BatteryResponding  : True
OBIVersion         : 0.2.1
SelectedSerialPort : COM3
AvailablePorts     : {COM3}
ConnectedBattery   : BL1860B
````

Next, you can query the battery data:

````powershell
PS C:\> $arduinoObi.GetBatteryInfo()


Name               : BL1860B
Capacity           : 6
DesignVoltage      : 18
PackVoltage        : 19.407
VoltageDiff        : 0.006208
ChargeCount        : 33
ManufactureDate    : 10/6/0022 12:00:00 AM
TempCell           : 29.62
TempMosFet         : 29.69
Locked             : False
voltage1           : 3.886
voltage2           : 3.884
voltage3           : 3.887
voltage4           : 3.888
voltage5           : 3.886
Status             : 103
Rom_Id             : 16 06 0A 64 14 08 07 CA
isF05134Controller : False
RawMessage         : F1 26 BD 13 14 58 00 00 84 84 40 21 D0 80 02 4E C3 D0 8E 67 60 F8 00 43 E1 02 0E 12 00 F1 00 27
ArduinoOBIVersion  : 0.2.1
````

You get back essentially all the information that otherwise would be displayed in the *openbatteryinformation* window when you use the python script.

Likewise, all other functionality is exposed through methods, and you can switch all the battery LEDs on and off, or unlock a dead battery:

````powershell
PS C:\> $arduinoOBI.LedOn()

PS C:\> $arduinoOBI.LedOff()

PS C:\> $arduinoOBI.ClearError()
````

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/toolbatteries/makita/makitalxtdigitalinterface/3.software/arduinoobipowershellscript?756441051009261136) - created 2026-05-08 - last edited 2026-05-08
