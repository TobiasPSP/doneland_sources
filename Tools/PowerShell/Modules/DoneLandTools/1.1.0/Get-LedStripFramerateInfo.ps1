
function Get-LedStripFramerateInfo
{
  <#
      .SYNOPSIS
      Calculates the maximum frame rate possible for a LED strip or the maximum LED that can be used for a desired frame rate

      .DESCRIPTION
      In WS2182B and similar strings of LED, the one-wire data line has a maximum data transmission rate.
      This command can calculate two things:
      - given the number of LED (or the length and type of LED string), it calculates the maximum possible frame rate
      - given the framerate, it calculates the maximum possible number of LED that you can string together

      .EXAMPLE
      Get-LedStripFramerateInfo -TotalLedCount 100
      Calculates the maximum framerate achievable for 100 RGB LEDs in a string:

      LedCount Type Framerate DataTime (us)
      -------- ---- --------- -------------
         100 RGB        305       0.00328

      .EXAMPLE
      Get-LedStripFramerateInfo -TotalLedCount 100 -IncludeWhiteLed

      Calculates the maximum framerate achievable for 100 RGBW LEDs in a string (including separate white, 32 instead of 24 bit):

      LedCount Type Framerate DataTime (us)
      -------- ---- --------- -------------
         100 RGBW       234       0.00428

      .EXAMPLE
      60,90,120,144 | Get-LedStripFramerateInfo -StripLengthCm 150
      Calculates the maximum framerates for a strip of 150cm length and different LED/m:

      LedCount Type Framerate DataTime (us)
      -------- ---- --------- -------------
      90 RGB        336       0.00298
      135 RGB        231       0.00433
      180 RGB        176       0.00568
      216 RGB        148       0.00676

      .EXAMPLE
      Get-LedStripFramerateInfo -Framerate 60
      Determines the maximum number of LED that can be used to achieve a 60Hz frame rate:

      LedCount Type StripType StripLengthCm
      -------- ---- --------- -------------
         546 RGB  n/a       n/a        

      .EXAMPLE
      Get-LedStripFramerateInfo -Framerate 30 -LedPerMeter 144
      Determines the maximum length for a LED strip using 144 LED/m to achieve a 30Hz frame rate:

      LedCount Type StripType StripLengthCm
      -------- ---- --------- -------------
        1102 RGB  144LED/m          765.3


      .EXAMPLE
      200,100,60,30,15 | Get-LedStripFramerateInfo -LedPerMeter 144
      Calculates the maximum length of a 144LED/m LED strip for various frame rates:

      LedCount Type StripType StripLengthCm
      -------- ---- --------- -------------
         157 RGB  144LED/m            109
         324 RGB  144LED/m            225
         546 RGB  144LED/m          379.2
        1102 RGB  144LED/m          765.3
        2213 RGB  144LED/m         1536.8

      .LINK
      https://done.land/tools/powershell
  #>


  [CmdletBinding(DefaultParameterSetName='framerate')]
  param
  (
    # the desired frame rate in Hz
    [Parameter(ParameterSetName='framerate', Mandatory,ValueFromPipeline)]
    [int]
    $Framerate,
    
    # the number of led per meter in a string or strip
    [Parameter(ParameterSetName='framerate')]
    [Parameter(ParameterSetName='ledpermeter', Mandatory, ValueFromPipeline)]
    [int]
    $LedPerMeter,
    
    # the led reset time. If you don't know it, 280us are used.
    # this value is practically irrelevant as it has next to no influence on the results.
    [int]
    $ResetTimeMicroSec=280,
    
    # specify this switch for RGBW LED (with one distinct white led)
    [switch]
    $IncludeWhiteLed,
    
    # the data frequency in kHz. When not specified, 800kHz is assumed.
    # this parameter is practically irrelevant as all programmable one-wire controller
    # use 800kHz
    [ValidateRange(1,10000)]
    [int]
    $DataRateKhz=800,
    
    # the length of the string or strip in cm
    [Parameter(ParameterSetName='ledpermeter', Mandatory)]
    [double]
    $StripLengthCm,
    
    # the total number of leds in a string or strip
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