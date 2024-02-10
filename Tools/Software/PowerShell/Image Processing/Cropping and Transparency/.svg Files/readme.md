# Cropping and Background Image

## Objective
Vector images in SVG format have a transparent background. When published on web pages, their content may beconme unreadable based on user preferences.

For example, in *github* when the user has choosen a *dark* theme, a transparent *.svg* image will render on *black* background. By default, the same image will render on *white* background.

In order for *svg* images to render predictably, a solid background needs to be added, regardless of whether the *svg* is used *directly* on a web page, or whether it first will be converted to a pixel-based image format such as *png*.

In addition, many *svg* images are surrounded by excessive *whitespace*. For example, when you *plot* a *KiCAD* schematic, the *svg* image contains the entire page and not just the schematics. A method is needed to remove the excessive whitespace.


## Solution
The *PowerShell* module **SvgFormatter** provides the function `Format-Svg` which can both *crop* a *svg* image by removing surrounding whitespace, and *add a solid background*.

This function utilizes the capabilities of modern *browsers* like *Chrome*.

> [!IMPORTANT]  
> `Format-Svg` is tested with the *Chrome* browser only. Many other modern browsers might work as well.
>
> To be safe, make sure you have *Chrome* installed, and it is your *default browser* for opening *html* files.

The command line below, executed in a **PowerShell** console, takes the path of a *svg* file from the clipboard (make sure you hold `SHIFT` and right-click the original *svg* file in *Windows Explorer* first, then copy its full path to the clipboard, before you run below command.

It updates *title* and *description*, resizes the *svg* to 10 centimeters width, crops surrounding *whitespace*, and adds a margin of 10.

The new *svg* file is then saved in the folder where the original *svg* file is stored, and the new filename gets the suffix "_new":

```powershell
Format-Svg -Title 'Some Title Text' -Description 'Some Description' -Width 10 -WidthUnit Centimeters -MarginHorizontal 10 -MarginVertical 10 -Suffix _clean
```

If you want to additionally add a solid-color background and remove transparency, add the appropriate parameters to the command.
