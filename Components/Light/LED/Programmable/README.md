<img src="/assets/images/light.png" width="80%" height="80%" />
 
# Programmable LED

> A Built-In Chip Controls Colors, Handles Currents, And Can Be Daisy-Chained To More Programmable LED. That Saves Effort And Wires.


Programmable **LED** are *much simpler* to operate than *simple RGB* **LED**:

* **Uniform Voltage:** for **RGB LED**, the different *currents* required by each of the three internal color **LED** is automatically adjusted by the internal driver chip. 
* **Digital Control:** to display a given *color* and *brightness*, you send a *digital control signal* to the **LED**. There is no need to manually calculate and provide the individual *current* to each of the three **LED** to mix the desired *color* or set the desired *brightness*.
* **Daisy Chain:** **LED** can be daisy-chained which reduces dramatically the *wiring*. Each **LED** in the string can still be controlled *individually*. 

> [!NOTE]
> Programmable **LED** do need a digital control signal. They are perfect for microcontroller projects. They cannot be used without one. If you don't want to program your own *microcontroller*, there are numerous cheap ready-to-use *RGB Contollers* available.

## Controllers
Since native **RGB LED** are difficult to operate, it was obvious that a dedicated *cheap and small* controller would simplify this tremendously. 

The initial approach was the *WS2811*, a dedicated chip capable of driving *three* different **LED** (*R*, *G*, and *B*). The revolutionary approach was the design of a new *one-wire* communications protocol that enabls **LED** to be easily daisy-chained: 

Whenever the control signal passes a **LED** in this string, the individual **LED** *controller* decrements a counter in the data package before it passes it on to the next **LED**, so each **LED** dynamically gets its own *Id*, based solely on its position in the string. This way, a *mirocontroller* can *individually* address each **LED**.

Since then, the controller chip was further reduced in size and finally *integrated* into the **LED** itself for further simplification. Today, these are the most common controller chips:

| Item | [WS2811](WS2811) | [WS2812](WS2812) | [WS2813](WS2813) | WS2815 | [SK6812](SK6812) | [SK6822](SK6822) | [APA102](APA102) |
| ---  | ---    | ---    | ---    | ---    | ---    | ---    | --- |
| LED  | any    | 5050/3535/2020 | 5050 | 5050 | 5050  |    5050    | 5050 |
| Color | Single/RGB | RGB | RGB/RGBW | RGB |  RGBW     |   RGBW     | RGB |
| Voltage (V) | 5/12/24 | 5 | 5 | 12           |  5  |    5    | 5V |
| Voltage Drop | Low | High | High | Low       |  Medium  | Medium       | High |
| Data Frequency (kHz) | 800 | 800 | 800 | 800 |  800  |   800     | 4Mhz SPI |
| Refresh Rate (Hz) | 800 | 400/2000 | 2000 | 4000     | 1200   |  1200      | 19.2kHz |
| Reset Time (us) | 250 | 50/280 | 250 | 280      | 80   |   50     | SPI |
| LED/m | 30/60/72/96/102/204 | 30/60/72/96/144 | 30/60/96/144 | 30/60/72/96/144 | 30/60/96/144 | 30/60/72/96/144	  | unspecified |
| Channels | 3 | 3 | 4 | 4 |                   |   3 |    3    |
| Connections | Power + Data | Power + Data | Power + 2xData | Power + 2xData | Power + 2xData | Power + SPI |
| Fail Safe | no | no | yes | yes |      yes      |  no  |    
| Price | low | medium | high | high |    low     | low   | high |   

These *controllers* can be embedded in various different *single color*, *RGB*, and *RGBW* **LED**. 

> [!TIP]
> The *brightness* and *quality of color* of *programmable **LED*** and **LED strips** does not depend on the *controller* but rather on the particular **LED** *type* the *controller* is embedded in, and on *how many of these **LED** are used per *length* or *area*.


### Colors

Each **LED** *brightness* can be controlled in *256* steps. 

For a *RGB* **LED**, the total number of colors that can be displayed is *256^3 = 16777216).



### Voltage Drop

This parameter affects color and brightness *deviations* in *long* strips with *many* **LED**.

When **LED strips** grow longer, the *voltage* drops. The further away a **LED** is located from the power supply, the more you see differences in brightness and color deviations. This *voltage drop* largely depends on the operating voltage: **5V** systems (like the very popular *WS2812*) are more prone to *voltage drop* than **12V** or **24V** systems.

To alleviate this, long **LED strips** need *power injection*: the supply power is *repeatedly* connected to parts of the strip. 

For **5V** systems, this may be necessary as often as once per *2.5m* (depending on the number of **LED** per meter). **12V** systems may require this only every *5m*.


### Data Frequency
This parameter affects the maximum number of **LED** that can be daisy-chained. Since virtually all **LED** *controllers* support the same very high data frequency of *800kHz*, and since this frequency is sufficient to transfer the control data of virtually any *practical* number of **LED**, it practically does not play an important role. It may still be interesting to know.

The primary benefit of the **LED** controllers discussed here is their simplicity: they need just one *data wire* to daisy-chain any number of **LED**.

This one *data wire* carries all the control information for all of the connected **LED**, and there is no separate *clock wire* that would enable external timings. Instead, each controller relies on a strict *static* timing: the impulses must come in a fixed speed, the *frequency*.

This data frequency is *fixed* and determined by the mentioned communications protocol. More modern controllers such as the *WS2815* are more tolerant towards frequency deviations than older controllers like *WS2812*.

### Update Frequency (Refresh)
This parameter controls *flicker*, especially when video recording.

Controllers use *PWM* (*pulse width modulation*) to control the *brightness* of a **LED**. This is not only important for overall brightness but also for *mixing red, green and blue* to emit all other colors.

Unless you are selecting a *pure red*, *green* or *blue* at *full brightness*, *PWM* is active.

The *update frequency* controls how often per second *PWM* refreshes the **LED**. The initial *WS2812B* for example came with an *update frequency* of *400Hz*. This relatively low frequency caused visible *flicker* when video recording a scene illuminated with these **LED**.

Recent *WS2812B* versions now use a much higher *update frequency* of *2000Hz* and eliminate this *flicker*. Other controller types used higher frequencies from begin on.



### Reset Time
This parameter affects the *smoothness* of animations and the *promptness* of *color* and *brightness* changes, but only very marginally. 

The **LED** controller uses a *reset time* after each data package that it processed before it is ready to process the next. This improves *robustness* because it clearly *distinguishes* one data package from the next. This is also why *extending* the *reset time* is a good thing, and most controller types today use significantly *longer reset times* than initially.

Even the popular *WS2812B* today uses a *reset time* of *280us* while the initial batch used *50us*.

> [!NOTE]
> Keep in mind that the *reset time* is added only at the end of each *update*. When your microcontroller updates the *color* and *brightness* of i.e. 100 **LED** in your string, it sends 100 individual configurations, each with the address of the particular **LED**, and **only then** adds the *reset time*.
> So the influence of the *reset time* on the maximum possible *frame rate* (updates per second) is neglectible.   




> [!CAUTION]
> Make sure the libraries and the code you use account for *reset times* **>280us** to be compatible with *any* **LED** controller.



### Frame Rate

What matters most to users - at least when playing *animations* or running *video screens* - is the *frame rate*: how often can the **LED** composition be updated per second?

This depends on these factors:

* **Number and kind of LED:** This is the most important factor. Each **LED** is addressable *individually*. Updating the entire string requires sending *one control information per **LED***. **RGB LED** require *three* pieces of color information, **RGBW LED** require *four*.
* **Microcontroller:** the *microcontroller* producing the *control signal* for the entire **LED** *string* must provide the control signal fast enough in the first place: it must be *fast enough* to compose the control signal for *all* **LED** in the strip at the desired *frame rate*. A *ESP32* can calculate roughly *65k-85k* **LED** per second. At 1000 **LED** this is a *70Hz* frame rate, dropping to *35Hz* at 2000 **LED**.
* **Data Rate:** the *data rate* is roughly the same for all **LED** *controllers* with *fixed data rate* (without a separate *clock* line): *800kHz*. 
* **LED Controller Reset Time:** the mandatory *reset time* at the end of each data packet adds to the overall time it takes to transmit *one* information packet.

### Calculating Frame Rate

To calculate the maximum possible *frame rate* for **RGB LED**, put the values from above into this formula:

*framerate = 1 / (( (24\*[total LED])/800.000) + [Reset Time] )*

For **RGBW LED**, replace *24* with *32*.

For a *WS2812* **LED strip** with *144 **RGB LED**/m and a length of *1m*, the values would be:

*framerate = 1 / (( (24\*144)/800.000) + 0.00028) = 217.4 frames/sec*

The maximum frame rate calculated is the limit set by the **LED** *controller*. To achieve it, you need to make sure your microcontroller can actually deliver the control data fast enough.

A relatively powerful dual-core *ESP32* can calculate roughly *65k-85k* **LED** per second. At 1000 **LED** this is a *70Hz* frame rate, dropping to *35Hz* at 2000 **LED**. Less performant microcontrollers like *ESP8266* perform considerably worse.

> [!TIP]
> Keep in mind that for animations, typically you do not need to change *all **LED*** at the same time at each frame. The real frame rates for a given change are therefore most probably much higher.
> If for example you run *2000* **LED** but need to update only 100 **LED** at different spots, even very weak microcontrollers can handle this with excellent frame rates.


### Frame Rate Calculator

Here is a **PowerShell** script that you can use to calculate frame rates for **LED strips**:

<details><summary>PowerShell Framerate Calculator</summary><br/>


Run this script in a **PowerShell** shell to define the new command `Get-LedStripDetail`:

```powershell
function Get-LedStripDetail
{
  [CmdletBinding(DefaultParameterSetName='framerate')]
  param
  (
    [Parameter(ParameterSetName='framerate', Mandatory)]
    [int]
    $Framerate,
    
    [Parameter(ParameterSetName='framerate', ValueFromPipeline)]
    [Parameter(ParameterSetName='ledpermeter', Mandatory, ValueFromPipeline)]
    [int]
    $LedPerMeter,
    
    [int]
    $ResetTimeMicroSec=280,
    
    [switch]
    $IncludeWhiteLed,
    
    [ValidateRange(1,10000)]
    [int]
    $DataRateKhz=800,
    
    [Parameter(ParameterSetName='ledpermeter', Mandatory)]
    [double]
    $StripLengthCm,
    
    [Parameter(ParameterSetName='totalled', Mandatory)]
    [int]
    $TotalLedCount
  )
  
  process
  {
    if ($PSBoundParameters.ContainsKey('ledpermeter'))
    {
      $TotalLedCount = $LedPerMeter * $StripLengthCm / 100
    }
    
    $bits = if ($IncludeWhiteLed)
    { 
      32 
      $type = 'RGBW'
    }
    else
    { 
      24
      $type = 'RGB'
    }
    
    $timeforSinglePackage = $bits / ($DataRateKhz * 1000)
    
    if ($PSCmdlet.ParameterSetName -eq 'framerate')
    {
      $resetTime = $ResetTimeMicroSec / 1000000
      $datarate = $DataRateKhz * 1000
      
      [int]$totalLed = $datarate * (1/$framerate-$resetTime)/$bits
      
      
      if ($PSBoundParameters.ContainsKey('ledpermeter'))
      {
        [PSCustomObject]@{
          LedCount = $totalLed
          Type = $type
          StripType = "${LedPerMeter}LED/m"
          StripLengthCm = [Math]::Round(($totalLed / $LedPerMeter) * 100, 1)
        }
      }
      else
      {
        [PSCustomObject]@{
          LedCount = $totalLed
          Type = $type
          StripType = 'n/a'
          StripLengthCm = 'n/a'
        }       
      }
    }
    else
    {
      # led count is given
      $timeForPackage = $timeforSinglePackage * $TotalLedCount
      $totalPackageTime = $timeForPackage + ($ResetTimeMicroSec/1000000)
    
      $frameRate = 1 / $totalPackageTime
    
      [PSCustomObject]@{
        LedCount = $TotalLedCount
        Type = $type
        Framerate = [Math]::Round($frameRate,1)
        'DataTime (us)' = $totalPackageTime
      }
    }
  }
}
```

</details>


#### Calculating Framerate Based on LED Count

When you know the number of **LED** (either absolute or as a combination out of **LED**/*meter* and *length of the strip*), you can calculate the maximum possible *framerate*:

````
PS> Get-LedStripDetail -TotalLedCount 100 

LedCount Type Framerate DataTime (us)
-------- ---- --------- -------------
     100 RGB        305       0.00328



PS> Get-LedStripDetail -LedPerMeter 144 -StripLengthCm 150

LedCount Type Framerate DataTime (us)
-------- ---- --------- -------------
     216 RGB        148       0.00676


# submitting a list of LED/m values:
PS> 60,90,120,144 | Get-LedStripDetail -StripLengthCm 150

LedCount Type Framerate DataTime (us)
-------- ---- --------- -------------
      90 RGB        336       0.00298
     135 RGB        231       0.00433
     180 RGB        176       0.00568
     216 RGB        148       0.00676
````

Likewise, when you know the *desired framerate*, you can calculate the number of **LED** you can drive at this framerate:

````
PS> Get-LedStripDetail -Framerate 305

LedCount Type StripType StripLengthCm
-------- ---- --------- -------------
     100 RGB  n/a       n/a          



PS> Get-LedStripDetail -Framerate 148 -LedPerMeter 144

LedCount Type StripType StripLengthCm
-------- ---- --------- -------------
     216 RGB  144LED/m            150

# submitting a list of desired framerates:
PS> 336,231,231,176,148 | Get-LedStripDetail -LedPerMeter 144

LedCount Type StripType StripLengthCm
-------- ---- --------- -------------
      90 RGB  144LED/m           62.5
     135 RGB  144LED/m           93.8
     135 RGB  144LED/m           93.8
     180 RGB  144LED/m            125
     216 RGB  144LED/m            150
````

### Fail Safe

The initial controllers like *WS2811* and *WS2812* came with the revolutionary *one-wire* data line.

Soon it was appreciated that *one* data line is nice from a point of *wiring*, but *bad* from a point of *reliability*: once a *single controller* fails, all remaining **LED** in that string also fail because they no longer receive the data signal.

That is why today there are also controllers like the *WS2813* and *WS2815* that come with *two* data wires. The data signal can skip *one failed* controller (but not *two* or more).


## Form Factors

Sophisticated **LED Strips** often use *WS2812* **LED** that come with full RGB color, an internal controller chip *per LED*, and *four* connectors: two for supplying power, and one each for *data in* and *data out*. *data out* then forwards the received data to the *next* **LED**.

> [!NOTE]
> A clever signal protocol makes sure that *each* **LED** in this string is *individually addressable* even though all **LED** are connected by just *one wire*.   
> Simplified, each **LED** increments a counter in the data protocoll when the signal passes. This way, each **LED** knows its position in the string. *Commands* to change *color* or *brightness* can therefore be addressed to an individual **LED** in the string based on its position.

**LED** *matrix displays* are essentially a variant of an **LED** *strip*, just in a different form factor:

<img src="images/led_matrix_overview_t.png" width="50%" height="50%" />


Primarily targeted towards *strips* and *matrix*-configurations involving *many* **LED**, *programmable* **LED** are available as *single* **LED** in a traditional form factor, too:


<img src="images/led_ws8212_single_back_t.png" width="50%" height="50%" />

These individual **LED** are a very smart idea when designing devices with many *indicator* **LED**: Instead of wiring each **LED** separately, and instead of investing *one precious GPIO pin* per **LED**, you  use the same *one-wire-protocol* used in **LED** strips to control *all your indicator **LED*** with just *one GPIO pin* - the ability to display any available color is an added extra bonus.



> [!NOTE]
> Some vendors call *programmable **LED*** based on the *WS2812B* chip *NeoPixel*.




### Single LED

**LED** *controllers* can also be embedded in normal **LED** form factors. Such **LED** have *four* "legs":

<img src="images/led_ws8212_single_front_t.png" width="50%" height="50%" />


* **Two different lengths:** some **LED** come with legs in *two* different lengths: two legs are shorter than the other two.
* **Four different lengths:** typically, each leg has a different length.

> [!NOTE]
> Single *programmable* **LED** can be daisy-chained just like *strips* or *matrix displays* and controlled by just one *GPIO* pin. This makes them ideal for controlling *muliple indicator **LED*** in *DIY microcontroller projects* as it significantly reduces *wiring* and reduces the number of required *GPIO* ports to just *one*, regardless of the number of **LED** needed.

#### Power Connection

The two *inner* legs are connected to the **5V** power supply. The *longer* leg is **GND**, the *shorter* leg is **+5V**.

#### Digital Connection

The two *outer* legs carry the *digital control signal*. The leg next to **V+** (*shorter* pin) is the digital *input* **DIN**. The leg on the other side (*longer* pin) is digital *output* **DOUT**.

Connect **DIN** to your microcontrollers' GPIO output, and connect **DOUT** to **DIN** of the next **LED** in the daisy chain.

## Considerations

Here are a few points to consider when using *programmable **LED***:

* **Microcontroller:** You need a *microcontroller* to operate *programmable **LED***. Either program your own, or use one of the readily available and *cheap* **RGB Controllers**
* **Voltage:** Always make sure you know the *specs* of the type of *programmable **LED*** you use. Their supply voltages may vary. While *WS2812* are operated with **5V**, there are other types that need **12V** or even **24V**.
* **Current:** A higher supply voltage lowers the required *current* which starts to matter when you daisy-chain more than just a couple of **LED**. **LED strips** operated at **5V** can quickly exceed currents of *10-20A*. For *long **LED** strips*, it's more efficient to use an **LED** type that takes **12V** or **24V** supply voltage.




> Tags: LED, Light, Anode, Cathode, RGB, Neopixel, WS2812, Programmable LED

:eye:&nbsp;[Visit Page on Website](https://done.land/components/light/led/programmable?668154031318243445) - last edited 2024-03-18
