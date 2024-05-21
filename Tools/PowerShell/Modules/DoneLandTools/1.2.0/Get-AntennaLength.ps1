function Get-AntennaLength
{
  <#
      .SYNOPSIS
      Calculates the required length of an antenna for a given radio frequency.

      .DESCRIPTION
      You submit the frequency (in Megahertz) and get back resonant antenna lengths that you can use for senders and receivers operating on this frequency.

      .EXAMPLE
      Get-AntennaLength -Frequency 433.95 
      Returns the lengths for an antenna that resonate on 433.95MHz.

      .LINK
      https://done.land/tools/powershell
  #>


  [CmdletBinding(DefaultParameterSetName='ForwardVoltage')]
  param
  (
    # the frequency in megahertz that you want to transmit or receive
    [Parameter(Mandatory,ValueFromPipeline)]
    [double]
    $Frequency 
  )

  begin
  {
    $speedOfLight = 299792458
  }
  process
  {
    $lambda = $speedOfLight / ($Frequency * 1000000) * 100
  
    [PSCustomObject]@{
      'Frequency (MHz)' = $Frequency
      Lambda            = [Math]::Round($lambda,1)
      'Lambda 7/8 (cm)' = [Math]::Round($lambda * 7 / 8,1)
      'Lambda 5/8 (cm)' = [Math]::Round($lambda * 5 / 8,1)
      'Lambda/2 (cm)'   = [Math]::Round($lambda/2,1)
      'Lambda/4 (cm)'   = [Math]::Round($lambda/4,1)
      'Lambda/8 (cm)'   = [Math]::Round($lambda/8,1)
    }
    
  }
}