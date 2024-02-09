# Exporting SVG To PNG

## Objective

While *svg* vector image files are great for lossless scaling, *svg* images in websites may be rendered differently based on platform and browser, or do not render at all.

That's why I needed to convert *svg* images (i.e. plotted schematics from *KiCAD*) to *png* images. *PNG* is a well-established standard, compressed resulting in small file sizes, with support for transparency. 

*Png* being pixel images, rendering is not object to browser type. This provides much better controllable user experience.

The conversion process needs a way to control the *png* image dimensions and output high-quality hi-res *png* images. High-definition screens are used today to browse websites. To leverage this resolution and provide visitors with a "lossless" scaling experience, images for websites need to be a width of 3000px at minimum.

## Solution
Using *Inkscape* to convert a *svg* image (i.e. a "plot" export from *KiCAD*) to a *png* image.

The command below runs in a **PowerShell** console and takes the path to the *svg* image from the clipboard.

I typically first hold `SHIFT`, then right-click the *svg* file to convert, then choose *Copy as path* in the context menu.

Next, I run the command line below. The converted *png* image file will be saved to the same folder where the input *svg* image file is stored.

```powershell
inkscape --export-type="png" --export-width=3000 $(Get-Clipboard)
```
> [!IMPORTANT]  
> Add the absolute path to *inkscape.exe* to the **PATH** environment variable in *user* scope.
>
> Only then will **PowerShell** (or any console) find the command *inkscape*. Without adjusting the environment variable, you have to specify the full absolute path name to *inkscape.exe* which is impractical.
