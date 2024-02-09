# PowerShell One-Liners

## Export SVG To PNG

Using *Inkscape* to convert a svg image (i.e. a "plot" export from *KiCAD*) to a PNG image.

The command line takes the path to the svg image from the clipboard, so I typically first hold `SHIFT`, then right-click the svg file I want to convert, and then in the context menu choose *Copy as path*. 

Next, I run the command line below and find the converted PNG image file in the same folder.

```powershell
inkscape --export-type="png" --export-width=3000 $(Get-Clipboard)
```
> [!IMPORTANT]  
> To be able to call *inkscape* this way, you need to add the path to the folder in which incscape.exe is located in, to your **PATH* environment variable.
>
> Else, you need to specify the absolute path name to the inkscape.exe file.
