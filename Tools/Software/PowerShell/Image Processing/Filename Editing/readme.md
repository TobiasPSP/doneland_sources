# Bulk-Edit File Names

I use an online service to remove picture backgrounds and add transparency. 

The result files receive a suffix. This suffix needs to be removed from all files in a directory.

## Solution

I use the *PowerShell* function below to remove unwanted parts of file names:

```powershell
function Remove-FileNameSuffix
{
  <#
      .SYNOPSIS
      Removes specified text from all file names in a folder.

      .DESCRIPTION
      To remove unwanted file name suffixes, specify a folder path and the text you want to remove from all file names.

      .PARAMETER Suffix
      Unwanted text in a file name that should be removed

      .PARAMETER FolderPath
      Absolute path to the folder that contains the files to be processed. If not specified, the path is taken from the clipboard.

      .EXAMPLE
      Remove-FileNameSuffix -Suffix abcd -Path c:\images
      Removes the text 'abcd' from all file names found in c:\images

      .EXAMPLE
      Remove-FileNameSuffix 
      Takes the path to the folder to be processed from the clipboard (make sure you copied the path to the clipboard before),
      then removes the text '-removebg-preview' (which is the default value for -Suffix) from all file names found in that folder

      .EXAMPLE
      rf
      'rf' is a predefined alias for the function 'Remove-FileNameSuffix' and can save typing.
      Takes the path to the folder to be processed from the clipboard (make sure you copied the path to the clipboard before),
      then removes the text '-removebg-preview' (which is the default value for -Suffix) from all file names found in that folder

  #>

  [Alias('rf')]
  [CmdletBinding()]
  param
  (
    [String]
    $Suffix = '-removebg-preview',
  
    [String]
    $FolderPath = (Get-Clipboard)
  )
  
  Get-ChildItem -Path $FolderPath -File |
    Where-Object Name -like "*$Suffix*" |
    Rename-Item -NewName { $_.Name -replace $Suffix, '' }
}
```

I added this function to my *PowerShell* service module [ImageProcessingTools](https://github.com/TobiasPSP/doneland/tree/main/Tools/Software/PowerShell/Image%20Processing/Cropping%20and%20Transparency/.svg%20Files/Modules).

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/tools/software/powershell/imageprocessing/filenameediting?682051020426240854) - last edited 2024-02-27
