function Test-FileLock {
  param (
    [parameter(Mandatory=$true)][string]$Path
  )

  $exists = Test-Path -Path $Path -PathType Leaf
  if (!$exists) 
  {
    return $false
  }

  $file = [System.IO.FileInfo]::new($Path)


  try 
  {
    $stream = $file.Open([System.IO.FileMode]::Open, [System.IO.FileAccess]::ReadWrite, [System.IO.FileShare]::None)

    if ($stream) { $stream.Close() }
    return $false
  } 
  catch 
  {
    return $true
  }
}