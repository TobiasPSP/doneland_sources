

function Invoke-ForeachParallel {
  param 
  (   
    [ScriptBlock]
    $Process,


    [Int]
    $ThrottleLimit = 32,

    [Int]
    $CheckIntervalMilliseconds = 200,

    [Int]
    $TimeoutSec = -1,
    
    [Switch]
    $UseLocalVariables
  )
  
  Begin {
    function CheckForCompleted
    {
      Foreach($thread in $ThreadList) {
        If ($thread.Runspace.isCompleted) {
          if($thread.powershell.Streams.Error.Count -gt 0) 
          {
            foreach($ErrorRecord in $thread.powershell.Streams.Error) {
              Write-Error -ErrorRecord $ErrorRecord
            }
          }
          if ($thread.TimedOut -ne $true)
          {
            $thread.powershell.EndInvoke($thread.Runspace)
          }
          $thread.Done = $true
        }
        elseif ($TimeoutSec -gt 0 -and $thread.TimedOut -ne $true)
        {
          $runtimeSeconds = ((Get-Date) - $thread.StartTime).TotalSeconds
          if ($runtimeSeconds -gt $TimeoutSec)
          {
            Write-Error -Message "Thread $($thread.ThreadID) timed out."
            $thread.TimedOut = $true
            $null = $thread.PowerShell.BeginStop({}, $null)
          }
        }
      }

      $ThreadCompletedList = $ThreadList | Where-Object { $_.Done -eq $true }
      if ($ThreadCompletedList.Count -gt 0)
      {
        foreach($threadCompleted in $ThreadCompletedList)
        {
          $threadCompleted.powershell.Stop()
          $threadCompleted.powershell.dispose()
          $threadCompleted.Runspace = $null
          $threadCompleted.powershell = $null
          $ThreadList.remove($threadCompleted)
        }
          
        Start-Sleep -milliseconds $CheckIntervalMilliseconds
      }
    }
  
    $SessionState = [initialsessionstate]::CreateDefault()
    
    if ($UseLocalVariables)
    {
      $ps = [Powershell]::Create()
      $null = $ps.AddCommand('Get-Variable')
      $oldVars = $ps.Invoke().Name
      $ps.Runspace.Close()
      $ps.Dispose()

      Get-Variable | 
      Where-Object { $_.Name -notin $oldVars } |
      Foreach-Object {
        $SessionState.Variables.Add((New-Object System.Management.Automation.Runspaces.SessionStateVariableEntry($_.Name, $_.Value, $null)))
      }
    }

    $RunspacePool = [Runspacefactory]::CreateRunspacePool(1, $ThrottleLimit, $SessionState, $host)
    $RunspacePool.Open() 

    $ThreadList = New-Object System.Collections.ArrayList
  }


  Process
  {
    $Code = '$args | Foreach-Object { ' + $Process.toString() + '}'
    
    $powershell = [powershell]::Create()
    $null = $PowerShell.AddScript($Code).AddArgument($_)
    $powershell.RunspacePool = $RunspacePool

    $threadID++
    $threadInfo = @{
      PowerShell = $powershell
      StartTime = Get-Date
      ThreadID = $threadID
      Runspace = $powershell.BeginInvoke()
    }

    $null = $ThreadList.Add($threadInfo)
    Write-Output (CheckForCompleted)
  }


  End 
  {
    try
    {
      Do {
        Write-Output (CheckForCompleted) 
      } while ($ThreadList.Count -gt 0)
      
    }
    finally
    {
      
      foreach($thread in $ThreadList)
      {
        $thread.powershell.dispose() 
        $thread.Runspace = $null
        $thread.powershell = $null
      }
      $RunspacePool.close()
      $RunspacePool.Dispose()
      [GC]::Collect() 
    }
  }
}


function Test-PingRange
{
  [CmdletBinding()]
  param
  (
    [Switch]
    $SuccessOnly
  )
  Get-MyIpAddress |
  Get-IpRange |
  Invoke-ForeachParallel {
    Test-Ping -ComputerName $_ -TimeoutMillisec 3000 
  } -ThrottleLimit 64 |
  Where-Object { $_.Response -or (!$SuccessOnly) }
}
function Test-PortRange
{
  param
  (
    [Parameter(Mandatory)]
    [string]
    $HostName,
    
    [Parameter(Mandatory)]
    [uint32[]]
    $Port,
    
    [Switch]
    $SuccessOnly
  )
  
  $Port |
  Invoke-ForeachParallel {
    Test-Port -ComputerName $HostName -Port $_ -TimeoutMillisec 3000 
  } -ThrottleLimit 64 -UseLocalVariables |
  Where-Object { $_.Response -or (!$SuccessOnly) }
}

function Test-Port
{
  <#
      .SYNOPSIS
      Tests Port of a network computer
      .EXAMPLE
      Test-Port -ComputerName 192.168.2.144 -Port 80
      checks to see if computer at 192.168.2.144 listens to port 80 (and thus is a webserver)
  #>
  param
  (
    [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName)]
    [string]
    $ComputerName,
        
    [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName)]
    [int]
    $Port,
        
    [int]
    $TimeoutMilliSec = 1000
  )
    
  process
  {
    try
    {
      $client = [System.Net.Sockets.TcpClient]::new()
      $task = $client.ConnectAsync($ComputerName, $Port)
        
      if ($task.Wait($TimeoutMilliSec))
      {
        $success = $client.Connected
      }
      else
      {
        $success = $false
      }
    }
    catch
    {
      $success = $false
    }
    finally
    {
      $ip = $client.Client.RemoteEndPoint.Address.IPAddressToString
      $client.Close()
      $client.Dispose()
    }
    
    [PSCustomObject]@{
      HostName = $ComputerName
      IP = $ip
      Port = $Port
      Response = $success
    }
  }
}


function Test-Ping
{
  <#
      .SYNOPSIS
      Sends ICMP request and waits for a maximum of -TimeoutMillisec milliseconds for an answer
      .EXAMPLE
      Test-Ping -ComputerName microsoft.com
      pings microsoft.com
      .EXAMPLE
      '127.0.0.1','google.de','99.99.99.99' | Test-Ping -TimeoutMillisec 2000
      pings three uris and waits a maximum of 3 seconds for an answer
  #>
  param
  (
    [Parameter(Mandatory,ValueFromPipeline)]
    [string]
    $ComputerName,
        
    [int]
    $TimeoutMillisec = 1000
  )
    
    
    
  begin
  {
    $obj = [System.Net.NetworkInformation.Ping]::new()
  }
    
  process
  {
    try
    {
      $obj.Send($ComputerName, $TimeoutMillisec) |
      Select-Object -Property @{N='HostName';E={$ComputerName}},@{N='IP';E={$_.Address}}, @{N='Port';E={'ICMP'}}, @{N='Response';E={$_.Status -eq 'Success'}}
    }
       
    catch [System.Net.NetworkInformation.PingException]
    {
      Write-Warning "$Computername ist kein gültiger Computername"
    }
  }

  end
  {    
    $obj.Dispose()
  }
}


function Get-MyIpAddress
{
  <#
      .SYNOPSIS
      Gets the IPv4 addresses of all active network adapters 
      .EXAMPLE
      Get-MyIpAddress
      gets the ip addresses of all network adapters that are up
      .EXAMPLE
      Get-MyIpAddress | Get-IpRange
      get all ip addresses in the current segment
  #>
  Get-NetAdapter | Where-Object Status -eq 'Up'  |
  Get-NetIPAddress -AddressFamily IPv4 -PrefixOrigin Dhcp,Manual

}





function Get-IpRange
{
  <#
      .SYNOPSIS
      Gets list of ip addresses 
      .EXAMPLE
      Get-IpRange -From 192.168.2.1 -To 192.168.4.22
      gets all ip addresses in the specified range
      .EXAMPLE
      Get-MyIpAddress | Get-IpRange
      get all ip addresses in the current segment
  #>
  [CmdletBinding(DefaultParameterSetName='Manual')]
  param
  (
    [Parameter(Mandatory,ParameterSetName='Manual',Position=0)]
    [ipaddress]
    $From,
    
    [Parameter(Mandatory,ParameterSetName='Manual',Position=1)]
    [ipaddress]
    $To,
    
    [Parameter(Mandatory,ParameterSetName='Auto',Position=0,ValueFromPipeline)]
    [PSTypeName('Microsoft.Management.Infrastructure.CimInstance#root/standardcimv2/MSFT_NetIPAddress')]
    [CimInstance]
    $NetIpAddress,
    
    [Hashtable]
    $Log = @{}
  )
  
  begin
  {
    function ConvertTo-UInt32 {
      param ([string]$ipAddress)
      $bytes = [ipaddress]::Parse($ipAddress).GetAddressBytes()
      [Array]::Reverse($bytes)
      return [BitConverter]::ToUInt32($bytes, 0)
    }

    function ConvertTo-IPAddress {
      param ([UInt32]$ipInt)
      $bytes = [BitConverter]::GetBytes($ipInt)
      [Array]::Reverse($bytes)
      return [ipaddress]::new($bytes)
    }

    $rangeId = 0
  }
  process
  {
    $rangeId++
    
    if ($PSCmdlet.ParameterSetName -eq 'Auto')
    {
      $ipAddress = $NetIpAddress.IPAddress
      $prefixLength = $NetIpAddress.PrefixLength

      $ipInt = ConvertTo-UInt32 -ipAddress $ipAddress
      $subnetInt = [uint32]([math]::Pow(2, 32) - [math]::Pow(2, 32 - $prefixLength))
      
      $networkInt = $ipInt -band $subnetInt
      $broadcastInt = $networkInt -bor -bnot $subnetInt

      # Calculate start and end IP addresses
      $startIpInt = $networkInt + 2
      $endIpInt = $broadcastInt - 1
      
      
      $from = ConvertTo-IPAddress -ipInt $startIpInt
      $to = ConvertTo-IPAddress -ipInt $endIpInt
    }    
  
    $key = "Range$rangeid"
    $value = '{0}-{1}' -f $from.IPAddressToString, $to.IPAddressToString
    $log[$key] = $value
  
  
    $ipFromBytes =$From.GetAddressBytes()
    $ipToBytes = $to.GetAddressBytes()
  
    # change endianness (reverse bytes)
    [array]::Reverse($ipFromBytes)
    [array]::Reverse($ipToBytes)
  
    # convert reversed bytes to uint32
    $start=[BitConverter]::ToUInt32($ipFromBytes, 0)
    $end=[BitConverter]::ToUInt32($ipToBytes, 0)
  
    # enumerate from start to end uint32
    for($x = $start; $x -le $end; $x++)
    {
      # split uit32 back into bytes
      $ip=[bitconverter]::getbytes($x)
      # reverse bytes back to normal
      [Array]::Reverse($ip)
      # output ipv4 address as string
      $ip -join '.'
    }
  }
}


function Find-NetworkDevice
{
  <#
      .SYNOPSIS
      Finds the IPv4 ip address of a device in your network
      .DESCRIPTION
      Interactive tool to find IPv4 address of devices in your network.
      When you run this command, you are instructed to first turn off the device you want to find.
      Once you turned it off and press ENTER, the tool scans your network(s) for any responding device.
      Next, you are instructed to turn on the device, then press ENTER.
      Now, the tool again scans the network(s). Once done, it compares both results and lists the differences.
      You will be presented with the IPv4 addresses that weren't responding on first scan but show up once the device was turned on.
      Note that results may not always be accurate due to network issues. If in doubt, run the tool again.
      .EXAMPLE
      Find-NetworkDevice
      identifies new devices that respond to ICMP ping requests
      .EXAMPLE
      Find-NetworkDevice -WebInterface
      identifies new devices that expose a http: webinterface on port 80
      .EXAMPLE
      Find-NetworkDevice -OpenInBrowser
      identifies new devices that expose a http: webinterface on port 80, and opens the found web interfaces in your browser
      Do not be surprised when a number of web interfaces are opened. You might be surprised to discover how many home automation devices and entertainment systems in your home expose a secret web interface.
      .EXAMPLE
      Find-NetworkDevice -FindAllWebInterfaces
      identifies all devices currently active in your network that expose a http: webinterface on port 80, and opens the found web interfaces in your browser
      This command will perform just one scan and finds all active devices.
      Do not be surprised when a number of web interfaces are opened. You might be surprised to discover how many home automation devices and entertainment systems in your home expose a secret web interface.
      .EXAMPLE
      Find-NetworkDevice -FindAllWebInterfaces -ThrottleLimit 64 -Timeout 2000 -Verbose
      identifies all devices currently active in your network that expose a http: webinterface on port 80, and opens the found web interfaces in your browser
      This command experiments with the optimization parameters and outputs scan metrics to see whether (and how much) the scan speed was improved, and whether there was an impact on the number of found devices.

  #>
  [CmdletBinding()]
  param
  (
    # scans for new devices that respond to port 80
    [Parameter(ParameterSetName='WebInterface')]
    [Switch]
    $WebInterface,
    
    # scans for new devices that respond to port 80 and opens the found web interfaces in your browser
    [Parameter(ParameterSetName='Browser')]
    [Switch]
    $OpenInBrowser,

    # scans for all currently active devices that respond to port 80 and opens the found web interfaces in your browser
    [Parameter(ParameterSetName='All')]  
    [Switch]
    $FindAllWebInterfaces,
    
    # throttlelimit defines the number of parallel processes
    # the higher this value, the faster will the scan be (as more ip addresses are examined in parallel)
    # when you increase this value too much, your network adapter will run out of resources, and your results are not complete
    $ThrottleLimit = 64,
    
    # timeout to wait for device response in milliseconds
    # the higher this value, the longer will a scan take
    # when you decrease this value too much, slow devices or devices that need to initialize port responses may not be discovered
    # ESPEasy devices i.e. require a long timeout of >=4000ms
    $Timeout = 4000,
    
    # port number to use for identifying internal web servers
    # typically, devices use port 80 for default http web interfaces
    # if you reconfigured your devices to use a different port, adjust the port:
    [Parameter(ParameterSetName='WebInterface')]
    [Parameter(ParameterSetName='Browser')]
    [Parameter(ParameterSetName='All')]
    $Port = 80
    
  )
  
  
  
  
  
  $doPortScan = $WebInterface -or $OpenInBrowser -or $FindAllWebInterfaces
  
  Write-Progress -Activity "Initialization" -Status "Calculating IP Addresses In Current Network Range."
    
  $me = Get-MyIpAddress 
  $log = @{}
  $range = $me | Get-IpRange -Log $log
  [string[]]$scan1 = $null
  
  [System.Diagnostics.Stopwatch]$stopwatch = [System.Diagnostics.Stopwatch]::new()
  
  if (!$FindAllWebInterfaces)
  {
    Write-Host "[1] Make sure the device is currently NOT TURNED ON. TURN IT OFF if necessary." -ForegroundColor Yellow
    Write-Host "Press ENTER when you are ready." -ForegroundColor Green
    $null = Read-Host 
  
    Write-Progress -Activity "Baseline Scanning Network (Your IP is $($me.IPAddress))" -Status "Scanning $($log.Values -join ',')"
    $stopwatch.Start()
    
    $scan1 = if ($doPortScan) 
    {
      $range | Invoke-ForeachParallel {
        Test-Port -ComputerName $_ -TimeoutMillisec $Timeout -Port $Port
      } -ThrottleLimit $ThrottleLimit -UseLocalVariables | 
      Where-Object Response |
      Select-Object -ExpandProperty HostName
    }   
    else
    {
      $range | Invoke-ForeachParallel {
        Test-Ping -ComputerName $_ -TimeoutMillisec $Timeout 
      } -ThrottleLimit $ThrottleLimit -UseLocalVariables | 
      Where-Object Response |
      Select-Object -ExpandProperty Ip
    }
    
    # output metrics when user specified -Verbose
    $stopwatch.Stop()
    $message = 'Initial baseline scan took {0:n1} seconds.' -f $stopwatch.Elapsed.TotalSeconds
    Write-Verbose $message 
  
    Write-Host "[2] NOW TURN ON the device." -ForegroundColor Yellow
    Write-Host "Press ENTER when you are ready." -ForegroundColor Green
    $null = Read-Host
  
  }
  
  
  [string[]]$scan2 = if ($doPortScan) 
  {
    if (!$FindAllWebInterfaces)
    {
      # wait 10 seconds to make sure the device is responsive
      Write-Progress -Activity 'Waiting' -Status "Waiting 10sec for webinterface to become responsive..."
      Start-Sleep -Seconds 10
    }
    
    Write-Progress -Activity "Discovery..." -Status 'Searching for devices...'
    
    $stopwatch.Start()
    
    $range | 
    Where-Object { $FindAllWebInterfaces -or ($_ -notin $scan1) } |
    Invoke-ForeachParallel {
      Test-Port -ComputerName $_ -TimeoutMillisec $Timeout -Port $Port
    } -ThrottleLimit $ThrottleLimit -UseLocalVariables | 
    Where-Object Response |
    Select-Object -ExpandProperty HostName
  }   
  else
  {
    # wait 3 seconds to make sure the device is responsive
    Write-Progress -Activity 'Waiting' -Status "Waiting 3sec for device to become responsive..."
    Start-Sleep -Seconds 3
    Write-Progress -Activity "Discovery..." -Status 'Searching for new devices...'
    
    $stopwatch.Start()
    
    $range | 
    Where-Object { $_ -notin $scan1 } |
    Invoke-ForeachParallel {
      Test-Ping -ComputerName $_ -TimeoutMillisec $Timeout 
    } -ThrottleLimit $ThrottleLimit -UseLocalVariables | 
    Where-Object Response |
    Select-Object -ExpandProperty Ip
  }
  
  $result = $scan2 | Where-Object { $FindAllWebInterfaces -or ($_ -notin $scan1) }
  
  # output metrics when user specified -Verbose
  $stopwatch.Stop()
  $message = 'Total scan time was {0:n1} seconds. {1} devices found.' -f $stopwatch.Elapsed.TotalSeconds, $result.Count
  
  Write-Verbose $message | Out-Default
  
  
  if ($OpenInBrowser -or $FindAllWebInterfaces)
  {
    $result | ForEach-Object { 
      $url = if ($port -eq 80)
      {
        "http://$_"
      }
      elseif ($port -eq 443 -or $port -eq 8443)
      {
        "https://$_"
      }
      else
      {
        "http://${_}:$port"    
      }
      
      Start-Process -FilePath $url 
    }
  }
  
  $result
}



