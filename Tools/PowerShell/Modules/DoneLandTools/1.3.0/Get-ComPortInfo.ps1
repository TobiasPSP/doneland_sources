function Get-ComPortInfo
{
  Get-CimInstance -ClassName win32_pnpentity -Filter 'PNPClass="Ports" and Present=TRUE and ConfigManagerErrorCode=0 and Status="OK"' |
  ForEach-Object {
    $file = $_ | Get-CimAssociatedInstance -ResultClassName CIM_DataFile
    $driver = $_ | Get-CimAssociatedInstance -ResultClassName Win32_SystemDriver
    
    $shortName = $driver.Name.Trim()
    $longName = $driver.DisplayName.Trim()
    
    $drivername = if ($shortname -ne $longname)
    {
      "$shortname ($longname)"
    }
    else
    {
      $shortname
    }
    
    [PSCustomObject]@{
      Name = $_.Description
      ComPort = if ($_.Name -match 'COM(\d+)') { 'COM' + $Matches[1] } else { $null }
      Manufacturer = $_.Manufacturer
      DriverPath = $file.Name
      DriverVersion = $file.Version
      DriverName = $drivername
    }
  }
  

}


