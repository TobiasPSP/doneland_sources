
function Get-PsoImageDetail
{
  param
  (
    [Alias('FullName')]
    [String]
    [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName)]
    $Path
  )
  
  begin
  {
    Add-Type -AssemblyName System.Drawing
    
    class ImageDetail
    {
      [int]$Height
      [int]$Width
      [System.Drawing.Imaging.ImageFormat]$Format
      [string]$Path
    }
    
    $formatTranslate = [System.Drawing.Imaging.ImageFormat].GetProperties().Name -ne 'Guid' |
    ForEach-Object -Begin { $h = @{} } -Process {
      $h[[System.Drawing.Imaging.ImageFormat]::$_.Guid.Guid] = $_
    } -end { $h }
      
  }

  process
  {
    [System.Drawing.Image]$image = [System.Drawing.Image]::FromFile($Path)
    
    [ImageDetail]@{
      Path = $Path
      Height = $image.Height
      Width = $image.Width
      Format = $formatTranslate[$image.RawFormat.Guid.Guid]
    }

    $image.Dispose()
    
  }

}

function Convert-PngToWebP
{
  <#
      .SYNOPSIS
      Converts png images to webp format to save space.

      .DESCRIPTION
      Add a more complete description of what the function does.

      .PARAMETER Path
      Describe parameter -Path.

      .EXAMPLE
      Convert-PngToWebP -Path Value
      Describe what this call does

      .NOTES
      Place additional notes here.

      .LINK
      URLs to related sites
      The first link is opened by Get-Help -Online Convert-PngToWebP

      .INPUTS
      List of input types that are accepted by this function.

      .OUTPUTS
      List of output types produced by this function.
  #>


  param
  (
    [Alias('FullName')]
    [String]
    [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName)]
    $Path
  )
  
  begin
  {
    # find the convert tool
    $toolPath = Join-Path -Path $PSScriptRoot -ChildPath 'bin\cwebp.exe'
    $exists = Test-Path -Path $toolPath
    if (!$exists)
    {
      Write-Warning "File $toolPath not found. You may have to download the free library first and extract the tool: https://storage.googleapis.com/downloads.webmproject.org/releases/webp/index.html"
      throw 'cwebp.exe not found'
    }
  }
  
  process
  {
    $newPath = [System.Io.Path]::ChangeExtension($Path, '.webp')
    & $toolPath $Path -o $newPath
  }

}

Get-ChildItem -Path C:\Users\Tobias\Documents\GitHub\WEB\WORKFLOW\doneland_sources\Components\Audio -Filter *.png -Recurse |
Get-PsoImageDetail


Get-ChildItem -Path C:\Users\Tobias\Documents\GitHub\WEB\WORKFLOW\doneland_sources\Components\Audio -Filter *.png -Recurse | copy-item -Destination  d:\samplePics\

Get-ChildItem D:\samplePics | Get-PsoImageDetail