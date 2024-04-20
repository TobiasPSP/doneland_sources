function Get-LedResistor
{
  <#
      .SYNOPSIS
      Calculates the required series resistor for a LED

      .DESCRIPTION
      You submit the LED forward voltage, current, and desired operating voltage, and the command returns the required series resistor

      .EXAMPLE
      Get-LedResistor -OperatingVoltage 12 -ForwardVoltage 3.2 -Current 10
      Returns the value of the required series resistor for one LED with a forward voltage of 3.2V and an intended current of 10mA at a desired operating voltage of 12V
      The result is 1136 Ohm. Round up to the next resistor value you have available.
      The output shows the guessed LED color based on the submitted forward voltage.

      .EXAMPLE
      Get-LedResistor -OperatingVoltage 12 -Color green
      Calculates the required series resistor for a green standard LED. The values for forward voltage and current are taken from guessed standard values. Use at own risk.

      .EXAMPLE
      3.3, 5, 9, 12, 24 | Get-LedResistor -ForwardVoltage 3.2 -Current 10 | Format-Table
      The parameter -OperatingVoltage can also be piped in. This command calculates the required resistors for 3.3V, 5V, 9V, 12V, and 24V

      .EXAMPLE
      3.3, 5, 9, 12, 24 | Get-LedResistor -Color yellow -Current 10 | Format-Table
      The parameter -OperatingVoltage can also be piped in. This command calculates the required resistors for supply voltages of 3.3V, 5V, 9V, 12V, and 24V for a yellow LED, overriding the default value for current and using an intended current of 10mA instead.

      .LINK
      https://done.land/tools/powershell
  #>


  [CmdletBinding(DefaultParameterSetName='ForwardVoltage')]
  param
  (
    # the desired voltage to operate the led
    [Parameter(Mandatory,ValueFromPipeline)]
    [double]
    $OperatingVoltage,
    
    # the specific forward voltage for the led you want to use
    [Parameter(Mandatory,ParameterSetName='precise')]
    [double]
    $ForwardVoltage,
    
    # the color of the led. This will guess a forward voltage based on typical values for led colors.
    # the results may be inaccurate. Use at own risk.
    [Parameter(Mandatory,ParameterSetName='guess')]
    [ValidateSet('yellow','orange','red','green','blue','white')]
    [string[]]
    $Color,
    
    # the current to use. When not specified, 20mA are assumed.
    [int]
    $Current = 20    
  )

  begin
  {
    $colorToVoltage = @{
      yellow = 1.8
      orange = 1.9
      red = 2.0
      green = 2.4
      blue = 3.0
      white = 3.2
    }
  }
  process
  {
    $Color | ForEach-Object {
      $curColor = $_
      if ($PSCmdlet.ParameterSetName -eq 'guess')
      {
        $ForwardVoltage = $colorToVoltage[$curColor]
      }
      else
      {
        $curColor = $colorToVoltage.GetEnumerator() | 
        Sort-Object { [Math]::Abs($_.Value - $ForwardVoltage)  } | 
        Select-Object -First 1 -ExpandProperty Key
      }
    
      $voltageDrop = $OperatingVoltage - $ForwardVoltage
      $resistance = $Current * 1000 / $voltageDrop
  
      [PSCustomObject]@{
        'Required Resistor (Ohm)' = $resistance -as [Int]
        'Operating Voltage (V)'   = $OperatingVoltage
        'Led Current (mA)'        = $Current
        'Led Voltage (V)'         = $ForwardVoltage
        'Led Color'               = $curColor
      }
    }
  }
  end
  {
    if ($PSCmdlet.ParameterSetName -eq 'guess')
    {
      Write-Warning "LED Forward Voltage was guessed from color and can be completely different. Use at own risk."
    }
  }
}