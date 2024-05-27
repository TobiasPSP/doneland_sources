function Show-Fat32Converter
{
  <#
    .SYNOPSIS
    Provides a GUI to format removable disks using a command line utility. The command line utility requires the Windows operating system.

    .DESCRIPTION
    The actual formatting is performed by an open-source command line utility (requiring Windows).
    This function provides a simple GUI interface that lets you select a removable drive, and set its label.
    Your input is then automatically submitted to the command line utility.

    .EXAMPLE
    Show-Fat32Converter
    Opens the GUI

    .LINK
    https://done.land/tools/powershell
  #>

  Add-Type -AssemblyName PresentationFramework
  $xaml = @'
<Window
xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
Width ="400"
SizeToContent="Height"
ResizeMode="NoResize"
WindowStartupLocation = "CenterScreen"
Title="FAT32 Disk Formatting - done.land"
Topmost="True">
<Grid Margin="10,40,10,10">
<Grid.ColumnDefinitions>
<ColumnDefinition Width="Auto"/>
<ColumnDefinition Width="*"/>
</Grid.ColumnDefinitions>
<Grid.RowDefinitions>
<RowDefinition Height="Auto"/>
<RowDefinition Height="Auto"/>
<RowDefinition Height="Auto"/>
<RowDefinition Height="*"/>
</Grid.RowDefinitions>
<TextBlock Name="txtHeader" Grid.Column="0" Grid.Row="0" Grid.ColumnSpan="2" Margin="5">Please select the disk drive to format:</TextBlock>

<TextBlock Grid.Column="0" Grid.Row="1" Margin="5">Drive</TextBlock>
<TextBlock Grid.Column="0" Grid.Row="2" Margin="5">Volume Label</TextBlock>
<ComboBox Name="comboDrive" Grid.Column="1" Grid.Row="1" Margin="5"/>
<TextBox Name="txtLabel" Grid.Column="1" Grid.Row="2" Margin="5" CharacterCasing="Upper" MaxLength="11"/>

<StackPanel Orientation="Horizontal" HorizontalAlignment="Right" VerticalAlignment="Bottom" Margin="0,10,0,0" Grid.Row="3" Grid.ColumnSpan="2">
<Button Name="ButOk" MinWidth="80" Height="22" Margin="5">Format</Button>
<Button Name="ButCancel" MinWidth="80" Height="22" Margin="5">Cancel</Button>
</StackPanel>
</Grid>
</Window>
'@
  #endregion
  
  #region find formatting tool
  $exepath = Join-Path -Path $PSScriptRoot -ChildPath "binaries/fat32format.exe"
  $exists = Test-Path -Path $exepath -PathType Leaf
  if (!$exists)
  {
    [System.Windows.MessageBox]::Show("fat32format.exe not found. This file must be located in binaries/$PSScriptRoot", "FAT32 Disk Formatting - done.land", 'Ok', 'warning')
    return
  }
  
  try { Unblock-File -Path $exepath } catch {}
  #endregion find formatting tool
  
  #region get removable disks
  [Array]$list = Get-CimInstance -ClassName Win32_Volume -Filter 'DriveType=2' | 
  Select-Object -Property DriveLetter, FileSystem, Label, @{N='FriendlyName';E={
      $label = if ([string]::IsNullOrEmpty($_.Label)) { '(no drive label set)' } else { $_.Label }
    '{0} [{1:n1} GB {3}] - {2}' -f $_.DriveLetter, ($_.Capacity/1GB),$label, $_.FileSystem}
  } | 
  Sort-Object -Property DriveLetter
    
  if ($list.Count -eq 0)
  {
    [System.Windows.MessageBox]::Show("No removable disks found. Insert disk and try again.", "FAT32 Disk Formatting - done.land", 'Ok', 'warning')
    return
  }
    
    
  $firstNonFat32 = 0
  foreach($_ in $list)
  {
    if ($_.FileSystem -ne 'FAT32') { break }
    $firstNonFat32++
  }
    
  $count = ($list | Where-Object FileSystem -ne 'FAT32').Count
  if ($count -eq 0)
  {
    if ([System.Windows.MessageBox]::Show("All removable disks are already FAT32.`r`n`r`nContinue anyway?", "FAT32 Disk Formatting - done.land", 'yesNo', 'warning', 'no') -eq 'no')
    {
      return
    }
    $firstNonFat32 = 0
  }
    
  #endregion get removable disks
  
  #region Code Behind
  function Convert-XAMLtoWindow
  {
    param
    (
      [Parameter(Mandatory=$true)]
      [string]
      $XAML
    )
      
    Add-Type -AssemblyName PresentationFramework
      
    $reader = [XML.XMLReader]::Create([IO.StringReader]$XAML)
    $result = [Windows.Markup.XAMLReader]::Load($reader)
    $reader.Close()
    $reader = [XML.XMLReader]::Create([IO.StringReader]$XAML)
    while ($reader.Read())
    {
      $name=$reader.GetAttribute('Name')
      if (!$name) { $name=$reader.GetAttribute('x:Name') }
      if($name)
      {$result | Add-Member NoteProperty -Name $name -Value $result.FindName($name) -Force}
    }
    $reader.Close()
    $result
  }
    
  function Show-WPFWindow
  {
    param
    (
      [Parameter(Mandatory=$true)]
      [Windows.Window]
      $Window
    )
      
    $result = $null
    $null = $window.Dispatcher.InvokeAsync{
      $result = $window.ShowDialog()
      Set-Variable -Name result -Value $result -Scope 1
    }.Wait()
    $result
  }
  #endregion Code Behind
  
  #region Convert XAML to Window
  $window = Convert-XAMLtoWindow -XAML $xaml 
  #endregion
  
  #region Define Event Handlers
  $window.ButCancel.add_Click(
    {
      $window.DialogResult = $false
    }
  )
    
  $window.ButOk.add_Click(
    {
      $window.ButCancel.IsEnabled = $false
      $window.ButOk.IsEnabled = $false
      $window.txtLabel.isEnabled = $false
      $window.comboDrive.IsEnabled = $false
      $drive = $window.comboDrive.SelectedItem.DriveLetter
      $label = $window.txtLabel.Text.Trim()
      $containsData = (Get-ChildItem -Path "$drive\").Count -gt 0
      $message = 
      if ($containsData)
      {
        "The drive contains data that will be lost.`r`n`r`nAll data on drive $drive will be erased. Are you sure?"
      }
      else
      {
        "All data on drive $drive will be erased. Are you sure?"
      }
      if ([System.Windows.MessageBox]::Show($window, $message, "FAT32 Disk Formatting - done.land", 'yesNo', 'warning', 'no') -eq 'yes')
      {
        try
        {
          $window.txtHeader.Text = 'Formatting...'
          $window.Dispatcher.Invoke([System.Action]{}, 'Background')
          
          $arguments = "-l""$label""", '-y', $drive
          Start-Process -FilePath $exepath -ArgumentList $arguments -Wait -WindowStyle Hidden
          
          $window.txtHeader.Text = 'Formatting completed.'
          $window.Dispatcher.Invoke([System.Action]{}, 'Background')
          
          [System.Windows.MessageBox]::Show($window, "Formatting completed.", "FAT32 Disk Formatting - done.land", 'Ok', 'information')
        }
        catch
        {
          [System.Windows.MessageBox]::Show($window, "Unable to format: $($_.Exception.Message)`r`n`r`nThis tool requires the Windows operating system.", "FAT32 Disk Formatting - done.land", 'Ok', 'information')
        }
        $window.DialogResult = $true
        try
        {
          explorer.exe shell:MyComputerFolder
        }
        catch {}
      }
      else
      {
        $window.DialogResult = $false
      }
    }
  )
  $window.comboDrive.add_SelectionChanged{
    $window.txtLabel.Text = $_.source.SelectedItem.Label
  }
    
  #endregion Event Handlers
  
  #region Manipulate Window Content
  
    
  $window.comboDrive.ItemsSource = $list
  $window.comboDrive.SelectedIndex = $firstNonFat32
  $window.comboDrive.DisplayMemberPath = 'FriendlyName'
    
  $window.txtLabel.SelectionLength = $window.txtLabel.Text.Length
  $null = $window.txtLabel.Focus()
  #endregion
  
  # Show Window
  $result = Show-WPFWindow -Window $window
}