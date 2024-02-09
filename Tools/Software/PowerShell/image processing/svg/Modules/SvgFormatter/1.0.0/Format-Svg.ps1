function Format-Svg
{
  <#
      .SYNOPSIS
      Takes path to a SVG file and adds a solid-color background

      .DESCRIPTION
      Uses a browser to take SVG and trim off whitespace plus add a solid color background
      New files are stored in the folder where the input svg file resides.
      New files overwrite existing files without prompt or warning.

      .EXAMPLE
      Format-Svg 
      Trims whitespace and adds a white background to a SVG file, and saves it as a new file with filename suffix '_w'
      This assumes the SVG file path was copied to the clipboard prior to calling this function:
      (hold SHIFT, then right-click a SVG file in Windows Explorer, then choose "Copy as path" in the context menu) 

      .EXAMPLE
      Format-Svg -Title 'XL6019' -Description 'Simple Example'
      Trims whitespace and adds a white background to a SVG file, and saves it as a new file with filename suffix '_w'
      Replaces title and description in svg with provided values
      This assumes the SVG file path was copied to the clipboard prior to calling this function:
      (hold SHIFT, then right-click a SVG file in Windows Explorer, then choose "Copy as path" in the context menu)


      .EXAMPLE
      Format-Svg -Transparent
      Trims whitespace, and saves it as a new file with filename suffix '_t'
      This assumes the SVG file path was copied to the clipboard prior to calling this function:
      (hold SHIFT, then right-click a SVG file in Windows Explorer, then choose "Copy as path" in the context menu)

      .EXAMPLE
      Format-Svg -Title 'New Title' -NoTrim
      Just sets a new title and adds a white background. New file is saved with filename suffix '_w'
      (assuming the SVG file path was copied to the clipboard prior to calling this function)

      .EXAMPLE
      Format-Svg -Title 'New Title' -NoTrim -Transparent
      Just sets a new title and leaves everything else unchanged. New file is saved with filename suffix '_t'
      (assuming the SVG file path was copied to the clipboard prior to calling this function)

      .EXAMPLE
      Format-Svg -Path c:\temp\test.svg -Suffix '' -BackgroundColor Green 
      Trims whitespace and adds a green background to a SVG file, and updates it. No new file is created. The original file is changed.
      After the change, the file is opened in the default app.

      .EXAMPLE
      Format-Svg -BackgroundColor FFAA76 -Suffix '_new'
      Trims whitespace and adds a self-defined RGB background color to a SVG file, and saves it as a new file with filename suffix '_new'
      (assuming the SVG file path was copied to the clipboard prior to calling this function)
    
      .EXAMPLE
      Format-Svg -BackgroundColor FFAA7640 -Suffix '_new'
      Trims whitespace and adds a self-defined RGB background color to a SVG file and sets its transparency to 25% (value 64, hex value '40'), and saves it as a new file with filename suffix '_new'
      (assuming the SVG file path was copied to the clipboard prior to calling this function)

      .EXAMPLE
      Format-Svg -Red 255 -Green 100 -Blue 150 -Opaque 50 -Suffix '_new'
      Trims whitespace and adds a self-defined RGB background color to a SVG file and sets its transparency to 50%, and saves it as a new file with filename suffix '_new'
      (assuming the SVG file path was copied to the clipboard prior to calling this function)
  
      .EXAMPLE
      Format-Svg -BackgroundColor FFAA76 -MarginHorizontal 5 -MarginVertical 10
      Trims whitespace, adds a self-defined RGB background color to a SVG file, adds a margin of 5 to left and right edge, adds a margin of 10 to top and bottom edge, and saves it as a new file with filename suffix '_new'
      (assuming the SVG file path was copied to the clipboard prior to calling this function)
  
      .EXAMPLE
      Format-Svg -BackgroundColor FFAA76 -MarginHorizontal 5 -MarginVertical 10 -PngExport
      Trims whitespace, adds a self-defined RGB background color to a SVG file, adds a margin of 5 to left and right edge, adds a margin of 10 to top and bottom edge.
      The svg is then converted to a PNG image with default width of 3000 pixels, and saved with default suffix "_w"
      (assuming the SVG file path was copied to the clipboard prior to calling this function)
  
      .EXAMPLE
      Format-Svg -BackgroundColor FFAA76 -MarginHorizontal 5 -MarginVertical 10 -PngExport -Width 2000
      Trims whitespace, adds a self-defined RGB background color to a SVG file, adds a margin of 5 to left and right edge, adds a margin of 10 to top and bottom edge.
      The svg is then converted to a PNG image with a width of 2000 pixels, and saved with default suffix "_w"
      (assuming the SVG file path was copied to the clipboard prior to calling this function)

      .EXAMPLE
      Format-Svg -BackgroundColor FFAA7640 -MarginHorizontal 5 -MarginVertical 10 -PngExport -Width 2000
      Trims whitespace, adds a self-defined transparent RGB background color to a SVG file, adds a margin of 5 to left and right edge, adds a margin of 10 to top and bottom edge.
      The svg is then converted to a transparent PNG image with a width of 2000 pixels, and saved with default suffix "_w"
      (assuming the SVG file path was copied to the clipboard prior to calling this function)
  
      .EXAMPLE
      Format-Svg -Transparent -PngExport -Width 1000
      Trims whitespace, convers svg to a transparent PNG image with a width of 1000 pixels, and saved with default suffix "_t"
      (assuming the SVG file path was copied to the clipboard prior to calling this function)
  
      .EXAMPLE
      Format-Svg -Width 10 -WidthUnit Centimeters
      Trims whitespace and sets the width to 10cm. Height is calculated automatically to maintain aspect ratio. 
      (assuming the SVG file path was copied to the clipboard prior to calling this function)

      .EXAMPLE
      format-svg -Width 1000 -WidthUnit Pixels -BackgroundColor AAFF9950 -Dpi 300 -PngExport -Suffix '_test'
      Trims whitespace, sets width to 1000 pixels, sets height automatically to maintain aspect ratio, sets a color background with transparency, sets DPI to 300
      and exports file as PNG with suffix "_test"
      (assuming the SVG file path was copied to the clipboard prior to calling this function)



  #>


  # add a white background to a svg
  
  [CmdletBinding(DefaultParameterSetName='DefaultColors')]
  param
  (
    # path to existing SVG file
    # if not specified, default value is taken from clipboard
    [string]$Path = $(
      $clip = Get-Clipboard
      $exists = if ($null -eq $clip) { $false } else {
        $temp = ($clip | Select-Object -First 1).Trim('" ')
        Test-Path -Path $temp -PathType Leaf
      }
      if (!$exists)
      {
        throw "You must specify the path to a SVG file or make sure a valid path was copied to the clipboard.`r`n'$temp' is no valid path or does not exist."
      }
      $temp
            
    ),
    
    [Parameter(ParameterSetName='Transparent')]
    [switch]$Transparent,
    
    # desired background color, can also be a hex RGB code
    [Parameter(ParameterSetName='StringColors', Position=1)]
    [string]$BackgroundColor = 'White',
    
    [Parameter(ParameterSetName='RGBColors', Position = 1)]
    [byte]$Red = 255,
    [Parameter(ParameterSetName='RGBColors', Position = 2)]
    [byte]$Green = 255,
    [Parameter(ParameterSetName='RGBColors', Position = 3)]
    [byte]$Blue = 255,
    [Parameter(ParameterSetName='RGBColors', Position = 3)]
    [byte]$Opaque = 255,
    
    # a horizontal margin to the left and right of the image. Default is 0 (no extra margin)
    [uint16]$MarginHorizontal = 0,
    
    # a vertical margin to the top and bottom of the image. Defaults to 0.
    [uint16]$MarginVertical = 0,
    
    # set suffix that is added to the new file
    # if the suffix is a blank string, the original file is overwritten
    [string]$Suffix = '_w',
    
    # when specified, svg whitespace is not trimmed
    [switch]$NoTrim,

    # when specified, png file is exported instead of svg file
    [switch]$PngExport,

    # width of exported png in pixels or millimeters (depending on -WidthUnit, defaults to "Pixels".
    # height is calculated automatically to maintain aspect ratio
    # when specified as millimeter, the pixel value is calculated using the DPI (default 300dpi).
    # use -Dpi to set a different DPI, i.e. for high resolution printing
    # use -PngWidthUnit to change the unit (pixels, millimeters, centimeters)
    # defaults to 3000 pixels.
    [double]$Width = 3000,
    
    # Unit for -PngWidth, can be 'Pixels','Millimeters','Centimeters'
    # defaults to 'Pixels'
    [ValidateSet('Pixels','Millimeters','Centimeters')]
    [string]$WidthUnit='Pixels',
    
    # DPI setting, defaults to 96dpi. This setting is used only when image is exported to PNG.
    # This way, the PNG "knows" the physical dimensions by dividing the pixel size by DPI
    [UInt32]$Dpi = 96,
    
    # when specified, updates svg title attribute
    [string]$Title = '',
    
    # when specified, updates svg description attribute
    [string]$Description = ''
  )


  Add-Type -AssemblyName System.Drawing
if ($Path -notlike '*.svg')
  {
    throw "You must specify a path to a *.svg file. '$Path' is no svg file."
  }
  $transparentEnabler = $titleEnabler = $descriptionEnabler = $trimenabler = ''
  $widthEnabler = '//'
  
  if ($PSBoundParameters.ContainsKey('Width')) { $widthEnabler = '' }
  
  if ($PSBoundParameters.ContainsKey('PngExport') -or $PSBoundParameters.ContainsKey('WidthWidth'))
  {
    $svgExportEnabler = '//'
    $pngExportEnabler = ''
    $isPngExport = $true
  }
  else
  {
    $svgExportEnabler = ''
    $pngExportEnabler = '//'
    $isPngExport = $false
  }
  if ($NoTrim) { $trimenabler = '//' }
 
  if ($PSCmdlet.ParameterSetName -eq 'RGBColors')
  {
    $BackgroundColor = '#{0:x2}{1:x2}{2:x2}{3:x2}' -f $Red, $Green, $Blue, $Opaque
  }
  elseif ($PSCmdlet.ParameterSetName -eq 'Transparent')
  {
    $transparentEnabler = '//'
    if ($PSBoundParameters.ContainsKey('Transparent') -and -not $PSBoundParameters.ContainsKey('Suffix'))
    {
      $Suffix = '_t'
    }
  }
  else
  {
    $isHexValue = Test-HexValue -Value $BackgroundColor
    if ($isHexValue)
    {
        $BackgroundColor = '#' + $BackgroundColor.TrimStart('#')
    }
  }
  
  if (!$PSBoundParameters.ContainsKey('title'))
  {
    $titleEnabler = '//'
  }
  
  if (!$PSBoundParameters.ContainsKey('description'))
  {
    $descriptionEnabler = '//'
  }
  
  $inch = 2.54
  $desiredWidth = if ($WidthUnit -eq 'Centimeters') 
  { 
    $Width / $inch * $Dpi
    $unit = 'cm'
  }
  elseif ($WidthUnit -eq 'Millimeters')
  {
    $Width / 10 / $inch * $Dpi
    $unit = 'mm'
  }
  else
  {
    $Width
    $unit = 'px'
  }

  $folder = Split-Path -Path $Path
  $filename = [System.Io.Path]::GetFileNameWithoutExtension($path)
  $extension = [System.Io.Path]::GetExtension($path)
  $outFileSvg = "$filename$Suffix$Extension"
  $outFilePng = "$filename$Suffix.png"

  $randomFileName = (New-Guid).Guid.toString() + '.htm'
  $tempFilePath = Join-Path -Path $env:temp -ChildPath $randomFileName

  $libsFolder = Join-Path -Path $PSScriptRoot -ChildPath libs
  $libsContent = Get-ChildItem -Path $libsFolder -Filter *.js | Get-Content -Raw

  if ($isPngExport)
  {
    if ($WidthUnit -ne 'Pixels') {
      $Width = $desiredWidth
      $unit = 'px'
    }
  }

  $template = @"
<html><head>
<script>$libsContent</script>
</head><body>
$(Get-Content -Path $Path -Raw)
<script>
window.onload = function () {
  $trimEnabler trimWhitespace();
  $transparentEnabler addSolidBackground();
  $descriptionEnabler updateDescription("$Description");
  $titleEnabler updateTitle("$Title");
  $widthEnabler updateWidth($Width);
  $svgExportEnabler saveSvg();
  $pngExportEnabler saveAsPng();  
};
function updateWidth(width) {
  try {
    var svgElement = document.getElementsByTagName("svg")[0];
    bbox = svgElement.getBBox();
    var ratio = bbox.height/bbox.width;
    svgElement.setAttribute('width', '$Width$Unit');
    var height = $Width * ratio;
    svgElement.setAttribute('height', height + '$unit'); 

  } catch (error) { 
    console.error('Error setting width and height', error); 
  }
}
function trimWhitespace() {
  try {
    var svg = document.getElementsByTagName("svg")[0];
    box = svg.getBBox();
    viewBox = [box.x, box.y, box.width, box.height].join(" ");
    svg.setAttribute("viewBox", viewBox);
  } catch {
    prompt('Error trimming whitespace', error);
  }
}
function updateTitle(newTitle) {
  try {
    var svg = document.getElementsByTagName("svg")[0];
    let titleElement = svg.querySelector("title");
    if (!titleElement) {
      titleElement = document.createElementNS("http://www.w3.org/2000/svg", "title");
      svg.insertBefore(titleElement, svg.firstChild);
  } 
  titleElement.textContent = newTitle;
  } catch {
    prompt('Error setting title: ', error);
  }
}
function updateDescription(newDescription) {
  try {
    var svg = document.getElementsByTagName("svg")[0];
    let descElement = svg.querySelector("desc");
    if (!descElement) {
      descElement = document.createElementNS("http://www.w3.org/2000/svg", "desc");
     svg.insertBefore(descElement, svg.firstChild);
    }
    descElement.textContent = newDescription;
  } catch {
    prompt('Error setting description: ', error);
  }
}
function addSolidBackground() {
  try {
    var color = "$BackgroundColor";
    var marginH = $MarginHorizontal;
    var marginV = $MarginVertical;
    var svg = document.getElementsByTagName("svg")[0];
    var bbox = svg.getBBox();
    var x = bbox.x - marginH;
    var y = bbox.y - marginV;
    var width = bbox.width + (2 * marginH);
    var height = bbox.height + (2 * marginV);
    var viewBox = [x, y, width, height].join(" ");
    svg.setAttribute("viewBox", viewBox);
    var svgns = "http://www.w3.org/2000/svg";
    var rect = document.createElementNS(svgns, 'rect');
    rect.setAttribute('x', x);
    rect.setAttribute('y', y);
    rect.setAttribute('height', height);
    rect.setAttribute('width', width);
    rect.setAttribute('fill', color);
    svg.insertBefore(rect, svg.firstChild);
  } catch {
    prompt('Error setting background:', error);
  }
}
function saveSvg() {
  try {
    var contentElement = document.getElementsByTagName("svg")[0];
    var htmlContent = contentElement.outerHTML;
    var blob = new Blob([htmlContent], { type: 'text/html' });
    var downloadLink = document.createElement('a');
    downloadLink.href = URL.createObjectURL(blob);
    downloadLink.download = '$outFileSvg';
    document.body.appendChild(downloadLink);
    downloadLink.click();
    document.body.removeChild(downloadLink);
  } catch (error) {
    prompt('Error saving svg to file:', error);
  }
}

  function saveAsPng() {
    const svgElement = document.getElementsByTagName("svg")[0];
    var canvas = document.createElement('canvas');
    var context = canvas.getContext('2d');
    canvg(canvas, new XMLSerializer().serializeToString(svgElement));
    const pngData = canvas.toDataURL('image/png');
    const downloadLink = document.createElement('a');
    downloadLink.href = pngData;
    downloadLink.download = '$outFilePng';
    document.body.appendChild(downloadLink);
    downloadLink.click();
    document.body.removeChild(downloadLink);
}
</script></body></html>
"@

    Set-Content -Path $tempFilePath -Value $template -Encoding UTF8
    Invoke-Item -Path $tempFilePath
    Start-Sleep -Seconds 2

    $download = Get-SystemFolderPathForDownload
    $filePath = if ($isPngExport)
    { 
      Join-Path -Path $download -ChildPath $outFilePng
    }
    else
    {
      Join-Path -Path $download -ChildPath $outFileSvg
    }
    
    $success = $false
    
    1..100 | ForEach-Object {
            Write-Progress -Activity 'Retrieving File' -Status "$_ %" -PercentComplete $_
            Start-Sleep -Milliseconds 100
            $exists = Test-Path -Path $filePath
            if ($exists)
            {
                $isLocked = Test-FileLock $filePath
                if (!$isLocked) 
                { 
                  $success = $true
                  Get-Item -Path $filePath 
                }
            } 
        } |
        Select-Object -First 1 |
        Move-Item -Destination $folder -Force
        
    if (!$success) { throw 'Output file could not be generated. There may be an issue with your browser. "Chrome" needs to be your default browser for htm files.' }

    if ($isPngExport -and $PSBoundParameters.ContainsKey('Dpi'))
    {
      $randomImageFileName = (New-Guid).Guid.toString() + '.png'
      $randomImageFilePath = Join-Path -Path $folder -ChildPath $randomImageFileName
      $originalImageFilePath = Join-Path -Path $folder -ChildPath $outFilePng
      Rename-Item -Path $originalImageFilePath -NewName $randomImageFileName
       
      $inputImagePath = "C:\Users\Tobias\Documents\powershell\SVG.NET\2 Inlne svg\V7png\sample2.png"
      $outputImagePath = $inputImagePath # "C:\Users\Tobias\Documents\powershell\SVG.NET\2 Inlne svg\V7png\sample2Out.png"
      $image = [System.Drawing.Image]::FromFile($randomImageFilePath)
      $image.SetResolution($Dpi, $Dpi)
      $image.Save($originalImageFilePath)
      $image.Dispose()
      Remove-Item -Path $randomImageFilePath
    }

    if ($isPngExport)
    {
      Test-ImageMetaData -Path $originalImageFilePath | 
        Select-Object -Property @{N='Name';E={$outFilePng}}, Height, Width, *Resolution, PixelDepth, IsAlphaPixelFormat, @{N='Path';E={$originalImageFilePath}}
    }
    else
    {
        $originalSvgFilePath = Join-Path -Path $folder -ChildPath $outFileSvg
        Get-Item -Path $originalSvgFilePath
    }

}
 