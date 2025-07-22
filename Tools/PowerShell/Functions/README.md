<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# New PowerShell Functions

> Previewing Latest PowerShell Functions


New PowerShell functions are extensively tested before they eventually are merged into the [free PowerShell module](https://done.land/tools/powershell/#install-donelandtools) `donelandtools`.

If you'd like to have a peek, or participate in testing, you'll find the latest function source codes [here](https://github.com/TobiasPSP/doneland_sources/tree/main/Tools/PowerShell/Functions).

## Cleaning Computer Disk Drives: `Get-FolderSize`

You can never have enough disk space on a computer, and with older notebooks, disk drives seem to always be low on space.

That's especially critical when you try and perform major upgrades. For example, if you plan to upgrade from *Windows 10* to *Windows 11*, this requires 10-20GB of free disk space.

> [!TIP]
> Unfortunately, many software vendors start to make *Windows 11* a requirement for their software. For example, `Fusion360` announced there will be no new versions running on *Windows 10*, and beginning 2026, **Windows 11 will be required**. 

It's hard to clean up disk space, though, especially since many Gigabytes of wasted data are hidden away in deeply nested subfolders, and often such folders are marked *hidden* and not visible in *Windows Explorer*.

That's when `Get-FolderSize` comes to the rescue: it examines folder trees (like your personal user profile) and even entire disks, then reports the sizes of all folders and subfolders (including hidden) **individually**. This way you can clearly identify the actual folders that hog massive data.

It also reports back the largest file found in each folder.

Here is a sample call that examines drive `C:\` for any folder larger than *1000MB*, including normally hidden folders:

````powershell
Get-ChildItem -Path c:\ -Recurse -Force -ErrorAction Ignore -File |
  Get-FolderSize -ThresholdSizeMB 1000 |
  Out-GridView
````

The result is displayed in real time in a gridview window. Once all results are in, you can sort the list by clicking column headers. That makes it simple to identify the folders occupying the most space.

Obviously, you can't just delete such folders and hope for the best. Many folders are vital, and deleting them would cause havok. But **identifying these folders** as a first step gives you a clue where it is worthwhile investigating further. When in doubt, I discussed folder paths with one of the readily available **AI Chats** (like *ChatGPT* or *perplexity.ai*), and this way it was simple to identify the purpose of unknown subfolders, and more often than not identify space hogs that could be safely deleted.

### Test Findings

To my honest surprise, the tool found quite a lot of gigabytes of unneeded data that could easily be removed:

* **VSCode:**    
  This editor is great, however it seems to hog massive amounts of temporary data in a variety of subfolders that may stem from long-ago projects, and would be automatically re-downloaded on demand if needed in the future.
* **ArduinoIDE 15.0:**   
  This IDE proved to be a space hog, keeping massive amounts of ZIP files in a subfolder called *staging*. Apparently, these ZIP files are unpacked during installation but then left behind, not needed anymore during normal operation.
* **Installation Location:**
  Most software installs on `C:\` by default, so this drive quickly fills up. Tools like `KiCAD`, `Fusion360`, and *3D slicers* turned out to occupy Gigabytes of data.
  * Uninstall all software that you don't really need.
  * Reinstall all software that you **do need**, and freshly install it to a better location. For example, my notebook has a `D:\` partition with plenty of free space. I ended up uninstalling `KiCAD`, then reinstalling it on my drive `D:`, relieving the memory pressure from the holy `C:\` drive. `Fusion360`, also a **huge memory hog**, unfortunately cannot be configured to use any drive other than `C:\`.

> [!TIP]
> Make sure to also run `cleanmgr.exe` with local Admin privileges, then initiate a system scan. There may be gigabytes of wasted space in log files or older windows installation remnants that can be easily freed with this tool.

### Happy Results

When I started this, my notebook had **2.3-4.7GB** free space on `C:\`. It was a constant struggle to clean up files to keep things going.

After a 30 minute cleanup session, and with the help of `Get-FolderSize`, my drive `C:\` now has **21.8GB** free space, and I was finally able to upgrade to *Windows 11*. The notebook feels and works much better now with a fresh OS and plenty of space.

> [!TIP]
> My notebook originally did not qualify for a *Windows 11 upgrade* despite being from *2018*. I then learned that while there are many items on the prerequisite check list that make sense, most older computers are hit by *CPU requirements* that feel weird: even an **Intel i5** with plenty of power is (officially) not supported to perform a *Windows 11* upgrade. I then used [a PowerShell script](https://github.com/Ad3t0/DirectWindowsUpgrade) to force an upgrade on my old *i5* notebook to *Windows 11*, and it runs smoothly ever since. Just make sure you download the appropriate *Windows 11 ISO Image* that in fact matches your current *Windows 10 edition*, or else your existing license will not be transitioned, and you need a new one. 

## Converting Images To WebP

Over time, this website has grown quite large. Picture files contribute to this size. I originally chose `.png` files to support transparency. However, `.png` format isn't very space efficient.

Today, better image formats are available, among them `.webp`. This format provides all the benefits of `.png` files, including transparency, while cutting down file size by roughly 50% at the same resolution and quality.

All modern browsers and tools today support `.webp` picture format, so I decided to transition from `.png` to `.webp`.

In order to convert `.png` files easily to `.webp`, I looked into using the free google tool `cwebp.exe` which is available for all major operating systems and [can be downloaded](https://storage.googleapis.com/downloads.webmproject.org/releases/webp/index.html) as part of the `libwebp`.

### Examining Picture Files
At first, I created the function `Get-PsoImageDetail` which returns picture format, size, and image dimensions:

````powershell
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
    try
    {
      [System.Drawing.Image]$image = [System.Drawing.Image]::FromFile($Path)
      $format = $formatTranslate[$image.RawFormat.Guid.Guid]

      [ImageDetail]@{
        Path = $Path
        Height = $image.Height
        Width = $image.Width
        Format = $format
      }
      
      $image.Dispose()
    }
    catch
    {
      # image file format could not be identified
      # this may occur when "new" image formats such as "webp" are encountered
      # since the tools in this module deal with processing and converting "older" formats to more modern formats,
      # if a file cannot be identified, it is assumed that it already is a modern file, and
      # consequently, the file is ignored (by not emitted the info object)
      Write-Warning "Unsupported image format: $Path"
    }
  }
}
````

Simply pipe any number of image files into the function:

````powershell
Get-ChildItem D:\samplePics | Get-PsoImageDetail
````

The result looks similar to this:

````
Height Width Format Path                                                         
------ ----- ------ ----                                                         
   478   522 Png    D:\samplePics\audio-xy-c15h_angle_t.png                      
   592   421 Png    D:\samplePics\audio-xy-c15h_back_t.png
   593   421 Png    D:\samplePics\audio-xy-c15h_top_t.png   
   (...)
````

### Converting PNG to WEBP
Next, I created the function `Convert-PngToWebP` that internally uses the free google tool `cwebp.exe`:

````powershell
function Convert-PngToWebP
{
  <#
      .SYNOPSIS
      Converts png images to webp format to save space.

      .DESCRIPTION
      uses the tool cwebp.exe from google to convert images to webp format in an effort to reduce file size
      transparency is preserved, the conversion is lossless
  #>

  [CmdletBinding(DefaultParameterSetName='Width')]
  param
  (
    # path to original image file
    [Alias('FullName')]
    [String]
    [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName,Position=0)]
    $Path,
    
    # desired width in px
    # images that are larger than this will be downscaled to MaxWidth
    # images that are smaller than MaxWidth retain their dimensions provided you specified the original
    # image width in -Width, else image files that are smaller than -MaxWidth will be upscaled.
    # if this parameter is omitted, or if its value is 0 or less, image dimensions are not altered.
    [int]
    $MaxWidth=0,
    
    # original image height in px
    [Parameter(ValueFromPipelineByPropertyName,ParameterSetName='Height')]
    [int]
    $Height=-1,
    
    # original image width in px
    [Parameter(ValueFromPipelineByPropertyName,ParameterSetName='Width')]
    [int]
    $Width=-1
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

    class ConversionInfo
    {
      [int]$Width
      [int]$Height
      [int]$NewSize
      [int]$OldSize
      [double]$CompressionRatio
      [string]$InPath
      [string]$OutPath
      [string[]]$Option
    
    }
    
    $parser = @{
      OutPath = "'(.*?)'"
      InPath = "^File:\s{1,}(.*?)$"
      Dimension = "^Dimension:\s{1,}(.*?)$"
      NewSize = "^Output:\s{1,}(.*?) bytes$"
      Option = "^  \* (.*?)$"
    }
  }
  
  process
  {
    # new path for image to be created
    # new image file will be in the same folder as original image file
    $newPath = [System.Io.Path]::ChangeExtension($Path, '.webp')
    
    $retainDimensions = ($MaxWidth -le 0) -or ( ($Width -gt 0) -and ($Width -lt $MaxWidth))
    
    # console tool is called in a separate scriptblock so its output streams can
    # be manipulated. When console tools run inside "PowerShell ISE", their regular
    # output stream is mis-directed to the error stream, appearing in red and formatted
    # like errors - even though no error occured
    # to prevent, the error stream is explicitly redirected to the output stream,
    # then post-processed:
    & {
      if ($retainDimensions)
      {
        # retain original image dimensions:
        & $toolPath $Path -lossless -o $newPath
      }
      else
      {
        # rescale image to MaxWidth
        & $toolPath -resize $MaxWidth 0 $Path -lossless -o $newPath
      }
    } 2>&1 | ForEach-Object -Begin { 
      $h = [ConversionInfo]::new() 
    } -Process {
      $message = $_.Exception.Message
        
      foreach($key in $parser.Keys)
      {
        $pattern = $parser[$key]
        if ($message -match $pattern)
        {
          if ($key -eq 'Dimension')
          {
            $dimensions = $matches[1] -split ' x '
            $h.Width = $dimensions[0] -as [int]
            $h.Height = $dimensions[1] -as [int]
              
          }
          elseif ($key -eq 'Option')
          {
            $h.$key += $matches[1]
          }
          else
          {
            $h.$key = $matches[1]
          }
          break
        }
      }
        
        
        
    } -end { 
      $h.OldSize = (Get-Item -Path $h.InPath).Length
      $h.CompressionRatio = [Math]::Round( ($h.NewSize * 100 / $h.OldSize), 1)
      $h 
    }
  }
}
````

Initially, I planned to also *resize* images to smaller sizes (which `cwebp.exe` can also do), however I quickly realized that for unknown reasons, downscaled pictures turned out to be *larger* than simply converting pictures and keeping their sizes. 

I can only speculate that the way how `cwebp.exe` re-scales images introduces pixel noise that may cause less efficient storage. So while `Convert-PngToWebP` can still resize images, I am currently not using this feature.

Instead, I am simply using the function to batch-convert `.png` images to `.webp` format:

````powershell
Get-ChildItem 'C:\pics\Signal Processing\Level Shifter\images' -Filter *.png | Convert-PngToWebP 
````

The function automatically picks up the text status messages emitted by `cwebp.exe` and converts them to structured objects. The result looks similar to this:

````
Width            : 522
Height           : 478
NewSize          : 132204
OldSize          : 235187
CompressionRatio : 56.2
InPath           : D:\samplePics\audio-xy-c15h_angle_t.png
OutPath          : D:\samplePics\audio-xy-c15h_angle_t.webp
Option           : {Lossless features used: PREDICTION CROSS-COLOR-TRANSFORM SUBTRACT-GREEN, Precision Bits: histogram=4 transform=4 cache=0}

Width            : 421
Height           : 592
NewSize          : 150160
OldSize          : 259313
CompressionRatio : 57.9
InPath           : D:\samplePics\audio-xy-c15h_back_t.png
OutPath          : D:\samplePics\audio-xy-c15h_back_t.webp
Option           : {Lossless features used: PREDICTION CROSS-COLOR-TRANSFORM SUBTRACT-GREEN, Precision Bits: histogram=4 transform=4 cache=0}

(...)
````


> Tags: PowerShell, Disk, CLeanup, Space, Get-FolderSize, Fusion360, KiCAD, Windows 11, PNG, WEBP, Image Conversion, Compression, Space

[Visit Page on Website](https://done.land/tools/powershell/functions?867238072020254800) - created 2025-07-19 - last edited 2025-07-21
