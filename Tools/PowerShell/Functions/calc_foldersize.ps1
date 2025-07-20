

function Get-FolderSize
{
  <#
      .SYNOPSIS
      Calculates the size of a folder structure, reporting the folder size per folder (without subfolders)

      .DESCRIPTION
      Tool to help identify subfolders that hog data on a drive
      If your hard drive is almost full, use Get-FolderSize to identify the subfolders where possibly 
      large and unneeded files are stored.
      
      .EXAMPLE
      Get-ChildItem -Path $env:appdata -Recurse -Force -File | Get-FolderSize -ThresholdSizeMB 10 | Sort-Object -Property Size -Descending | Out-GridView
      examines the entire user profile (including hidden files), ignores folders smaller than 10MB, and reports total folder size for all folders,
      sorted by size descendent (largest folders first)
  #>


  param
  (
    # Path to a file. This is typically piped from Get-ChildItem.
    [Alias('FullName')]
    [String]
    [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName,Position=0)]
    $Path,
    
    # binds a FileInfo object so the function knows a file was piped
    [Parameter(ValueFromPipeline, Position=0)]
    [System.IO.FileInfo]
    $File,
    
    # binds to a DirectoryInfo object so the function knows a folder was piped (which can be ignored)
    [Parameter(ValueFromPipeline, Position=0)]
    [System.IO.DirectoryInfo]
    $Folder,
    
    # Folders with a total size less than threshold are excluded:
    [ValidateRange(0,1000)]
    [int]
    $ThresholdSizeMB = 0
    
  )
  
  begin
  {
    $h = @{}
    $currentFolder = ''
    
    function outputResult($Key)
    {
      # is the key valid?
      if ($null -eq $key) { return }
      if (!$h.ContainsKey($Key)) { return }
      
      # is folder equals or larger than threshold?
      $size = $h[$key]
      $sizeMB = $size/1MB
      if ($sizeMB -lt $ThresholdSizeMB) { return }
      [PSCustomObject]@{
        Path = $key
        SizeMB = [Math]::Round($sizeMB,1)
        LargestFileSize = $h["fs_$key"]
        LargestFileName = $h["f_$key"]
      }
    }
  }
  process
  {
    if ($File)
    {
      if ($currentFolder -ne $_.DirectoryName)
      {
        # we hit a new folder
        outputResult -Key $currentFolder
        $currentFolder = $_.DirectoryName
        if ($null -eq $currentFolder)
        {
          # note: $_.Directory/$_.DirectoryName fails with path names longer than 260 characters and returns null in these cases
          $currentFolder = Split-Path -Path $_.FullName
        }
      }
      
      $currentFileSizeBytes = $_.Length
      $h[$currentFolder] += $currentFileSizeBytes
      
      
      $currentFileSize = [Math]::Round(($currentFileSizeBytes/1MB),1)
      
      # log the largest file in the folder:
      $folderLargestFileSize = $h["fs_$currentFolder"]
      if ($currentFileSize -gt $folderLargestFileSize)
      {
        $h["fs_$currentFolder"] = $currentFileSize
        $h["f_$currentFolder"] = $_.Name
        
      }
      
    }
  }
  end
  {
    outputResult -Key $currentFolder
  }
}


Get-ChildItem -Path c:\ -Recurse -Force -ErrorAction Ignore -File |
  . Get-FolderSize -ThresholdSizeMB 1000 |
  Out-GridView
    